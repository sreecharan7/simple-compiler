# Simple Compiler 🛠️

This is a simple compiler/interpreter for a custom scripting language that handles only **integers**.

## Features

- Supports integer variable declarations and assignments.
- Handles arithmetic operations: `+`, `-`, `*`, `/`.
- Supports `while` loops with nested blocks.
- Uses **space** as a delimiter between tokens.
- Implements a **parse table** for syntax parsing.
- Uses a **stack-based approach** for managing nested loops.
- Checks loop conditions before each iteration.

## How to Use

1. **Compile the program:**

    ```bash
    gcc simple-compiler.c -o compiler
    ```

2. **Run the compiler:**

    ```bash
    ./compiler
    ```

3. **Paste your source code** 


## Example Syntax

```bash
    x = 3 ;
    while x > 0 do
        x = x - 1 ;
    endwhile ;
```

## Notes

- Only integer operations are supported.
- All tokens must be space-separated.
