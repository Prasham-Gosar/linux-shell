# MyShell — Custom Linux Shell in C

## About

MyShell is a simple Linux shell built in C as part of my effort to learn systems programming and operating system concepts. Through this project, I implemented core shell features such as command execution, piping, redirection, command history, and background process handling using Linux system calls.

## Features

* Custom shell prompt
* Command execution using `fork()` and `execvp()`
* Built-in commands: `cd`, `pwd`, `exit`, and `history`
* Input and output redirection (`>`, `>>`, `<`)
* Command piping (`ls | grep txt`)
* Background process execution (`sleep 10 &`)
* Command history support
* Graceful error handling for invalid commands and syntax errors

## System Calls Used

* `fork()` – Creates a new child process.
* `execvp()` – Replaces the child process with the requested command.
* `wait()` / `waitpid()` – Waits for child processes to finish execution.
* `pipe()` – Creates a communication channel between two processes.
* `dup2()` – Redirects standard input and output streams.
* `open()` – Opens files for input/output redirection.
* `close()` – Closes file descriptors after use.
* `chdir()` – Changes the current working directory.
* `getcwd()` – Retrieves the current working directory.
* `signal()` – Handles terminated background processes and prevents zombie processes.

## How to Build and Run

Compile the project using Make:

```bash
make
```

Run the shell:

```bash
./shell
```

Clean generated files:

```bash
make clean
```

## Project Structure

* `shell.c` – Contains the main shell loop and command processing logic.
* `shell.h` – Header file containing function declarations, constants, and shared includes.
* `parser.c` – Handles parsing user input into command arguments.
* `builtins.c` – Implements built-in commands and command history.
* `executor.c` – Handles command execution, redirection, pipes, and background processes.
* `Makefile` – Automates compilation and project building.

## What I Learned

Building this project helped me understand how Linux processes are created and managed. I gained hands-on experience with important system calls such as `fork()`, `execvp()`, `pipe()`, and `dup2()`, and learned how shells implement features like piping, redirection, and background execution. It also improved my understanding of process synchronization, file descriptors, and modular C programming.
