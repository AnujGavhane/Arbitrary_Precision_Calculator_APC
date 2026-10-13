# Arbitrary Precision Calculator (APC)

A command-line calculator written in C that performs arithmetic on large decimal integers. Instead of storing a whole number in a built-in integer type, APC stores each decimal digit in a doubly linked list.

This project is intended for learners exploring linked lists, abstract data types, dynamic memory allocation, and arithmetic algorithms.

## Features

APC supports six operators:

| Operator | Operation | Example |
| --- | --- | --- |
| `+` | Addition | `125 + 75` → `200` |
| `-` | Subtraction | `125 - 200` → `-75` |
| `*` | Multiplication | `125 * 75` → `9375` |
| `/` | Integer division; returns the quotient | `125 / 7` → `17` |
| `%` | Modulus; returns the remainder | `125 % 7` → `6` |
| `^` | Power | `12 ^ 3` → `1728` |

Negative operands are supported. The exponent for `^` must be a non-negative integer from `0` through `10000`. Division or modulus by zero is rejected.

## How numbers are stored

Each linked-list node stores one decimal digit and links to the previous and next nodes. The head is the most significant digit, and the tail is the least significant digit. For example, `5072` is stored like this:

```text
head                    tail
 |                       |
 v                       v
[5] <-> [0] <-> [7] <-> [2]
```

The arithmetic functions operate on non-negative digit lists. `main.c` reads the expression, manages signs, selects the operation, and prints the answer.

## Requirements

- Linux or WSL
- GCC with C99 support

## Build and run

Open a terminal in the project directory and compile the source files:

```sh
gcc -std=c99 -Wall -Wextra -pedantic \
  main.c list.c addition.c subtraction.c multiplication.c \
  division.c modulus.c power.c -o apc
```

Run the calculator:

```sh
./apc
```

Enter each expression in the format `number operator number`, with spaces between the number and operator. For example:

```text
Enter expression (example: -123 * 45): 12345678901234567890 * 99
Result: 1222222211222222221110
Continue? [y/N]: n
```

Enter `y` at the continue prompt to calculate again. Any other answer exits.

## Project files

| File | Purpose |
| --- | --- |
| `main.c` | Reads expressions, handles signs, dispatches operations, and displays results. |
| `apc.h` | Defines the digit-list node and declares functions used across the project. |
| `list.c` | Implements shared list helpers, including append, copy, compare, print, subtract, and free. |
| `addition.c` | Adds digit lists using carry. |
| `subtraction.c` | Subtracts one magnitude from a greater than or equal magnitude using borrow. |
| `multiplication.c` | Multiplies magnitudes using the grade-school algorithm. |
| `division.c` | Performs long division and returns the integer quotient. |
| `modulus.c` | Finds the remainder using digit-by-digit division. |
| `power.c` | Calculates a power through repeated multiplication. |

## Algorithm notes

- Addition and subtraction take O(n) time for n-digit numbers.
- Grade-school multiplication takes O(n × m) digit operations for n- and m-digit numbers.
- Division and modulus use long division with repeated subtraction to find each quotient digit.
- Power uses repeated multiplication for clarity, so it is not optimized for large exponents.
