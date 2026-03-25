## stack_example.c — Memory Map Analysis

### Overview
This program demonstrates recursion and stack frame behavior. Each recursive call creates a new stack frame with its own local variables. No significant heap usage is involved.

---

### Step 1 — Enter depth = 0

STACK:
- Frame depth 0:
  - local_int = 100 at address 0x1ffefff2d4
  - p_local → 0x1ffefff2d4 (points to local_int)
  - local_buf at 0x1ffefff2e0 ('A' stored at index 0)
  - marker = 0 at 0x1ffefff324

HEAP:
- No relevant heap allocations

NOTES:
- First stack frame is created
- p_local is an alias of local_int (same address)

---

### Step 2 — Enter depth = 1

STACK:
- Frame depth 1:
  - local_int = 101 at 0x1ffefff2a4
  - p_local → 0x1ffefff2a4
  - local_buf at 0x1ffefff2b0 ('B')
  - marker = 10 at 0x1ffefff2f4

- Frame depth 0 still exists below

HEAP:
- Unchanged

NOTES:
- New stack frame created
- Variables have same names but different memory addresses
- Stack grows downward (addresses decrease)

---

### Step 3 — Enter depth = 2

STACK:
- Frame depth 2:
  - local_int = 102 at 0x1ffefff274
  - p_local → 0x1ffefff274

- Previous frames still exist

HEAP:
- Unchanged

NOTES:
- Another independent stack frame is created
- Each recursion level has its own memory

---

### Step 4 — Enter depth = 3

STACK:
- Frame depth 3:
  - local_int = 103 at 0x1ffefff244
  - p_local → 0x1ffefff244
  - local_buf at 0x1ffefff250 ('D')
  - marker = 30 at 0x1ffefff294

- Frames 0,1,2 still exist below

HEAP:
- Unchanged

NOTES:
- Maximum recursion depth reached
- All frames are active simultaneously

---

### Step 5 — Exit depth = 3

STACK:
- Frame depth 3 is about to be destroyed

NOTES:
- When the function returns, this stack frame is removed
- All its local variables become invalid after return

---

### Step 6 — Exit depth = 2 → 0

STACK:
- Frames are destroyed one by one:
  - depth 2 → destroyed
  - depth 1 → destroyed
  - depth 0 → destroyed

HEAP:
- No remaining allocations

NOTES:
- Stack unwinds in reverse order (LIFO)
- Each frame is destroyed when returning
- Memory is reused after each return

---

### Memory Behavior Summary

- Each recursive call creates a new stack frame
- Local variables exist only within their function call
- Identical variable names refer to different memory locations
- The stack grows downward in memory (addresses decrease)
- No memory leaks or invalid accesses occur in this program

---

### AI mistake detected

The AI claimed that the pointer `p_local` points to the same memory location across all recursive calls.

This is incorrect.

Each recursive call creates a new stack frame with a new instance of `local_int`, and `p_local` points to that specific instance.

Therefore, `p_local` refers to a different memory address at each recursion depth, not a shared one.
## heap_example.c — Memory Map Analysis

### Overview
This program demonstrates dynamic memory allocation on the heap and includes a deliberate memory leak. Two structures (`alice` and `bob`) are allocated, each containing a pointer to a dynamically allocated string.

---

### Step 1 — Allocation of alice

STACK:
- pointer alice → 0x4a7c480

HEAP:
- 0x4a7c480:
  - struct Person
    - name → 0x4a7c4d0
    - age = 30

- 0x4a7c4d0:
  - string "Alice" (6 bytes including '\0')

NOTES:
- Memory is allocated twice:
  1. struct Person
  2. string for name
- alice owns both allocations

---

### Step 2 — Allocation of bob

STACK:
- pointer alice → 0x4a7c480
- pointer bob → 0x4a7c520

HEAP:
- 0x4a7c520:
  - struct Person
    - name → 0x4a7c570
    - age = 41

- 0x4a7c570:
  - string "Bob" (4 bytes including '\0')

- alice allocations still present

NOTES:
- bob also owns two heap allocations
- total heap allocations so far: 4 blocks

---

### Step 3 — Freeing memory (partial)

STACK:
- alice and bob still exist as pointers

HEAP:
- alice struct → freed
- bob struct → freed

BUT:
- alice->name and bob->name are NOT both freed

NOTES:
- One of the name strings is not freed
- This leads to a memory leak

---

### Step 4 — Program exit

HEAP SUMMARY (Valgrind):
- 6 bytes still allocated
- 1 block definitely lost

INTERPRETATION:
- The leaked block corresponds to a string (likely "Alice")
- No pointer references this memory anymore

NOTES:
- This is a "definitely lost" leak:
  → memory is allocated
  → no pointer can access it anymore
  → cannot be freed

---

### Memory Behavior Summary

- Heap memory must be freed manually
- Each struct owns its internal pointer (`name`)
- Freeing only the struct is not sufficient
- All nested allocations must be freed explicitly

Correct deallocation should follow this order:
1. free(name)
2. free(struct)

---

### AI mistake detected

The AI claimed that freeing the struct automatically frees the memory pointed to by its internal pointers.

This is incorrect.

In C, `free()` only releases the memory block passed to it. It does NOT recursively free any memory referenced by pointers inside the structure.

Therefore, failing to call `free()` on `name` results in a memory leak, even if the struct itself is freed.

## crash_example.c — Memory Map Analysis

### Overview
This program demonstrates a deterministic segmentation fault caused by a NULL pointer dereference. The crash occurs when the program attempts to write to address 0x0.

---

### Step 1 — Program start

STACK:
- main():
  - int n = 0
  - pointer (likely result of allocation function)

HEAP:
- 1 block allocated (1024 bytes)

NOTES:
- Program requests allocation with n = 0
- The allocation function likely returns NULL

---

### Step 2 — Allocation result

STACK:
- pointer p = NULL

HEAP:
- No usable memory returned to the program

NOTES:
- When malloc fails or is called with size 0, it may return NULL
- The program does not check if the pointer is NULL

---

### Step 3 — Invalid memory access

Operation:
- program attempts to write to *p

Valgrind output:
Invalid write of size 4
Address 0x0 is not stack'd, malloc'd or free'd

STACK:
- p = NULL

HEAP:
- unchanged

NOTES:
- Writing to address 0x0 means dereferencing a NULL pointer
- This is undefined behavior and always invalid

---

### Step 4 — Crash (Segmentation Fault)

ERROR:
- SIGSEGV (segmentation fault)

CAUSE:
- Attempt to access memory at address 0x0

NOTES:
- The operating system blocks access to NULL address
- Program is terminated immediately

---

### Step 5 — Heap state at exit

Valgrind:
- 1024 bytes still reachable

INTERPRETATION:
- Memory was allocated but not freed
- Program crashed before free() could be called

---

### Memory Behavior Summary

- NULL pointer dereference leads to immediate crash
- Always validate pointers before dereferencing
- Heap memory is not automatically freed on crash
- Program termination prevents proper cleanup

---

### AI mistake detected

The AI claimed that malloc(0) always returns NULL, which directly caused the crash.

This is incorrect.

According to the C standard, malloc(0) may return either NULL or a unique pointer that must not be dereferenced.

The actual issue is not the return value itself, but the fact that the program does not check the pointer before using it.

The crash occurs because the program dereferences a NULL pointer, not simply because malloc(0) was called

## crash_example.c — Memory Map Analysis

### Overview
This program demonstrates a segmentation fault caused by a NULL pointer dereference. The crash is deterministic and occurs when the program attempts to write to an invalid memory address (0x0).

---

### Step 1 — Program start

STACK:
- main():
  - int n = 0
  - pointer p (uninitialized yet)

HEAP:
- empty

NOTES:
- The program requests an allocation with n = 0

---

### Step 2 — Memory allocation

STACK:
- p = NULL

HEAP:
- 1 block allocated internally (1024 bytes), but not linked to p

NOTES:
- The pointer p receives NULL
- The program does not check if p is NULL before using it

---

### Step 3 — Invalid write

Operation:
- *p = some value

Valgrind output:
Invalid write of size 4  
Address 0x0 is not stack'd, malloc'd or free'd  

STACK:
- p = NULL

HEAP:
- unchanged

NOTES:
- Dereferencing NULL means accessing address 0x0
- This memory region is forbidden by the OS
- This is undefined behavior

---

### Step 4 — Crash

ERROR:
- Segmentation fault (SIGSEGV)

CAUSE:
- Attempt to write to address 0x0

NOTES:
- The OS terminates the program immediately
- The crash is deterministic (always happens)

---

### Step 5 — Heap state at exit

Valgrind:
- 1024 bytes still reachable

INTERPRETATION:
- Memory was allocated but never freed
- The crash prevented proper cleanup

---

### Memory Behavior Summary

- A NULL pointer cannot be dereferenced
- The program must always check pointers after allocation
- Heap memory requires explicit free()
- Crashes prevent normal memory cleanup

---

### AI mistake detected

The AI claimed that the segmentation fault is caused by a memory leak.

This is incorrect.

The crash occurs due to a NULL pointer dereference, not because of the memory still allocated on the heap.

The memory leak is only a consequence of the crash, since the program terminates before calling free()..
