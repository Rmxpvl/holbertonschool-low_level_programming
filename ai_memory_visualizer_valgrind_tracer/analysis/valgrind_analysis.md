## Valgrind Analysis (Interpreted, Not Just Quoted)

This file links Valgrind findings to concrete memory misuse in code.

---

## Program: stack_example.c

### Valgrind summary
- No invalid read/write reported.
- No user heap leak reported.

### Interpretation
- Behavior is expected: the program uses stack locals only.
- Recursive frames are created and destroyed normally.
- No pointer escapes the lifetime of its stack frame.

---

## Program: heap_example.c

### Valgrind summary
- `definitely lost: 6 bytes in 1 block`
- `total heap usage: 5 allocs, 4 frees`

### Issue type
- Definite leak (lost ownership).

### Why it happens
- `person_new` allocates `Person` and `name`.
- `person_free_partial` frees only `Person`.
- In `main`, `alice` is passed to `person_free_partial`, so `alice->name` is never freed.
- Once `alice` struct is freed, no pointer remains to `alice->name`.

### Code-level cause
- Missing `free(alice->name)` before `free(alice)`.

---

## Program: aliasing_example.c

### Valgrind summary
- Invalid read after free.
- Invalid write after free.
- No leak required for these errors.

### Issue type
- Use-after-free via dangling alias.

### Why it happens
- `b = a` creates aliasing to the same heap block.
- `free(a)` ends the lifetime of that block.
- Accessing through `b` afterwards is invalid because `b` is dangling.

### Code-level cause
- Post-free operations on `b` (`b[2]`, `b[3]`).

---

## Program: crash_example.c

### Valgrind summary
- `Invalid write of size 4`
- Access at address `0x0`
- Process ends with `SIGSEGV`

### Issue type
- NULL pointer dereference (invalid write).

### Why it happens
- `n` is 0.
- `allocate_numbers(0)` returns `NULL` by function logic.
- `nums[0] = 42` dereferences `NULL`.
- The fault is deterministic and occurs at the first write through `nums`.

### About "still reachable" blocks
- Valgrind can show `still reachable` bytes after abrupt termination.
- This is not evidence that a leak caused the crash.
- Root cause remains the invalid NULL write.

---

## AI Usage and Critical Review

### How AI was used
- AI helped draft first-pass explanations and identify candidate issues.
- All conclusions were then validated against source code paths and Valgrind traces.

### Detected AI limitations
1. Confusing leak symptoms with crash root cause.
2. Overgeneralizing `malloc(0)` behavior.
3. Overstating pointer persistence across recursive calls.

### Why this matters for peer review
- The report stays causal: misuse in code first, tool message second.
- If Valgrind text were removed, the reasoning would still explain each bug.