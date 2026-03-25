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
