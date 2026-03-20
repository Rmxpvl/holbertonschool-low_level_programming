# Function Pointers

This directory contains introductory C exercises about function pointers.

## Learning Objectives

- Understand what a function pointer is.
- Pass a function as an argument to another function.
- Call a function through a pointer safely.
- Validate pointers before using them.

## Files

| File | Description |
|---|---|
| `0-print_name.c` | Prints a name using a callback function pointer. |
| `function_pointers.h` | Header file with function prototypes for this project. |

## Example Concept

A function pointer lets you choose behavior at runtime:

- one function prints in uppercase,
- another prints in lowercase,
- `print_name` receives either one and calls it.

## Compilation Example

```bash
gcc -Wall -Werror -Wextra -pedantic *.c -o main
```
