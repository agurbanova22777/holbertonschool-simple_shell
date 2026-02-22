# Simple Shell (`hsh`)

A minimal UNIX command interpreter written in C.

## Synopsis

Interactive mode:
```sh
./hsh
```

Non-interactive mode:
```sh
echo "/bin/ls" | ./hsh
cat commands.txt | ./hsh
```

## Description

`hsh` reads commands from standard input, parses them into tokens separated by whitespace, and executes them using `fork()` and `execve()`.

In interactive mode, the prompt `($) ` is displayed before each command.

## Features (current)

- Interactive and non-interactive modes
- Executes programs by absolute/relative path (contains `/`)
- Searches programs in `PATH` when command has no `/`
- Builtin:
  - `exit` (exits the shell)

## Error Output

Errors match `/bin/sh` style. The only difference is the program name is your `argv[0]`.

Example:
```sh
echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
```

## Requirements

- Allowed functions include: `getline`, `fork`, `execve`, `waitpid`, `access`, `strtok`, etc.
- Compilation:
```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Files

- `main.c` - program entry point
- `shell.c` - main loop (prompt, getline, dispatch)
- `tokenize.c` - tokenization helpers
- `path.c` - `PATH` search helpers
- `exec.c` - fork/exec and error printing
- `man_1_simple_shell` - manual page
- `AUTHORS` - contributors list

## Author(s)

See `AUTHORS`.
