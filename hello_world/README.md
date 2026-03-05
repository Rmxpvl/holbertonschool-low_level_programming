# Hello, World – C Programming Basics

This project introduces the fundamentals of compiling and running C programs, covering the different steps of the compilation pipeline and basic output functions.

## Files

| File | Description |
|------|-------------|
| `0-preprocessor` | Script that runs a C file through the preprocessor and saves the result into another file |
| `1-compiler` | Script that compiles a C file without linking and creates a `.o` object file |
| `2-assembler` | Script that generates the assembly code of a C file and creates a `.s` file |
| `3-name` | Script that compiles a C file and creates an executable named `cisfun` |
| `4-puts.c` | Program that prints a string using `puts` |
| `5-printf.c` | Program that prints a string using `printf` |
| `6-size.c` | Program that prints the size in bytes of the basic C data types |

## Concepts Covered

- The C compilation pipeline: preprocessing → compiling → assembling → linking
- Using `gcc` flags: `-E` (preprocess), `-c` (compile), `-S` (assemble)
- Printing output with `puts` and `printf`
- `sizeof` operator for basic types (`char`, `int`, `long int`, `long long int`, `float`)

## Requirements

- All scripts are written in Bash
- All C files are compiled with `gcc -Wall -Werror -Wextra -pedantic`
- Programs are compiled on Ubuntu 20.04 LTS

## Author

Holberton School – Low Level Programming
