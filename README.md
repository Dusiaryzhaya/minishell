42 Minishell Project - Short Description

Minishell is a Unix shell recreation project in the 42 School curriculum, where students build their own command-line interpreter using C.
Concept:

The goal is to develop a simple shell that can execute commands, handle pipes, redirections, and manage processes, giving a deeper understanding of system calls, file descriptors, and process management in Unix-like operating systems.

Key Features:

 - Command execution: Runs built-in and external commands using execve().
 - Pipes (|): Implements inter-process communication for command chaining.
 - Redirections (>, <, >>): Handles file input/output redirections.
 - Built-in commands: Implements commands like echo, cd, pwd, export, unset, env, and exit.
 - Signal handling: Manages CTRL+C, CTRL+D, and CTRL+\ properly.
 - Environment variables: Supports $PATH, $HOME, and custom variables.
 - Error handling & memory management: Prevents leaks and ensures stability.

## Project Contributors

- [Anna Ilchenko](https://github.com/Dusiaryzhaya)
- [Stefan Penev](https://github.com/StefanPenev)
