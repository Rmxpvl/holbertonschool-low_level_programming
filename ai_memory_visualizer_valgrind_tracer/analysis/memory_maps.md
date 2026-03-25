## Memory Maps and Lifetime Reasoning

This document explains memory behavior from the code itself (not only from tools).

---

## stack_example.c

### Memory model
- `walk_stack` and `dump_frame` use stack-allocated objects only (`local_int`, `local_buf`, `marker`).
- No user heap allocation is performed.

### Lifetime reasoning
- Each recursive call creates a new stack frame with new instances of locals.
- At depth 0, 1, 2, 3, variables have the same names but different addresses.
- On return, the current frame is destroyed immediately; pointers to its locals become invalid.

### Pointer and aliasing reasoning
- Inside `dump_frame`, `p_local` aliases `local_int` in that same call only.
- `p_local` is not shared across recursion depths.

### What a reviewer should verify quickly
- Stack addresses move between depths, showing independent frames.
- The same depth shows stable addresses between `enter` and `exit` prints of that depth.

---

## heap_example.c

### Memory model
- `person_new` allocates two heap objects per person:
1. `Person` struct
2. `name` string buffer

### Ownership model
- Owner of `alice` allocations: `alice` in `main`.
- Owner of `bob` allocations: `bob` in `main`.
- Correct free order per person is:
1. `free(person->name)`
2. `free(person)`

### Actual misuse and lifetime consequence
- `bob` is freed correctly (`bob->name`, then `bob`).
- `alice` is freed partially via `person_free_partial(alice)` which frees only the struct.
- `alice->name` remains allocated but unreachable after freeing `alice`.
- Result: one definite leak (the string `"Alice"`, 6 bytes).

### What a reviewer should verify quickly
- Struct free does not recursively free pointed-to memory.
- Leak source is ownership break: last pointer to `alice->name` is lost.

---

## aliasing_example.c

### Memory model
- `make_numbers` allocates one heap array and returns its address.
- In `main`, `a` and `b` are two pointers to the same heap block.

### Aliasing reasoning
- Before `free(a)`: `a == b`, both valid aliases.
- After `free(a)`: heap block lifetime ends.
- `b` still stores the old address, but that address is now invalid.
- Therefore `b` becomes a dangling pointer.

### Invalid accesses
- Reading `b[2]` after `free(a)` is use-after-free (invalid read).
- Writing `b[3] = 1234` after `free(a)` is use-after-free (invalid write).

### Important distinction
- No leak is required for use-after-free to exist.
- Here, memory is freed, yet access is still invalid because lifetime already ended.

---

## crash_example.c

### Memory model
- `n` is initialized to 0.
- `allocate_numbers` returns `NULL` when `n <= 0`.
- `main` does not check `nums` before `nums[0] = 42`.

### Causal crash chain (deterministic)
1. `n = 0`
2. `allocate_numbers(0)` returns `NULL`
3. `nums[0] = 42` dereferences `NULL`
4. Invalid write to address `0x0`
5. OS raises `SIGSEGV`

### Clarification about heap at exit
- Valgrind may report `still reachable` memory at crash time (for example runtime/libc buffers).
- That is not the root cause of the crash.
- Root cause is the invalid write through a `NULL` pointer.

---

## AI Critical Review Note

- AI outputs were used as hypotheses, then checked against source code and runtime behavior.
- Rejected AI claims:
1. `p_local` points to one shared location across recursion levels.
2. Freeing a struct frees all memory referenced by its fields.
3. The crash is caused by a memory leak.
4. `malloc(0)` always returns `NULL`.
- Why rejected: each claim contradicts C lifetime/ownership rules or the observed code path.