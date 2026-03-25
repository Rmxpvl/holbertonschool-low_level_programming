## Valgrind Analysis

---

## Program: heap_example.c

### Valgrind Output Summary
- definitely lost: 6 bytes in 1 block
- total heap usage: 5 allocs, 4 frees

---

### Error Type
Memory leak (definitely lost)

---

### Memory Object Involved
A dynamically allocated string (likely "Alice")

---

### Explanation

The program allocates memory for a struct and a string:

- struct Person (heap)
- name (heap)

However, only the struct is freed, not the internal string.

This causes a loss of ownership of the memory block storing the string.

Since no pointer references this memory anymore, it becomes "definitely lost".

---

### Root Cause

The program fails to free nested allocations.

Correct memory management requires:

1. free(name)
2. free(struct)

---

## Program: crash_example.c

### Valgrind Output Summary
- Invalid write of size 4
- Address 0x0 is not stack'd, malloc'd or free'd
- Segmentation fault (SIGSEGV)

---

### Error Type
Invalid memory write (NULL pointer dereference)

---

### Memory Object Involved
NULL pointer (address 0x0)

---

### Explanation

The program attempts to write to a pointer that is NULL.

Dereferencing a NULL pointer leads to an invalid memory access at address 0x0.

This memory region is not mapped by the operating system, causing a segmentation fault.

---

### Root Cause

The program does not check if the pointer is NULL before using it.

This leads to undefined behavior and a crash.

---

### Additional Observation

Valgrind reports:
- 1024 bytes still reachable

This is not the cause of the crash.

It indicates that some heap memory was not freed before the program terminated.

---

## Program: stack_example.c

### Valgrind Output Summary
- No errors reported
- All heap blocks freed

---

### Error Type
No memory errors

---

### Explanation

This program uses only stack memory for its operations.

Each recursive call creates a new stack frame, and all memory is automatically released when the function returns.

No heap misuse occurs.

---

## AI mistake detected

An AI explanation claimed that the crash in crash_example.c was caused by a memory leak.

This is incorrect.

The crash is caused by a NULL pointer dereference (invalid write at address 0x0).

The memory leak observed is only a side effect of the crash, since the program terminates before freeing allocated memory.