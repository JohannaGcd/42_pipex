# README

## Task

This program implements a simple version of a command pipeline using fork and pipe system calls. The program creates two child processes to execute two different commands and redirects their input and output through a pipe. The main function:

## How to build and run the program
### Build it using:
```
git clone git@github.com:JohannaGcd/42_pipex.git && cd 42_pipex && make
```
### Run it with:
```
 ./pipex infile "ls -l" "wc -l" outfile
```
Should behave as:
```
< infile ls -l | wc -l > outfile
```

## What I Learned

1. **Process Management**:
   - **Forking Processes**: Using `fork()` to create child processes and managing process IDs.
   - **Waiting for Processes**: Using `waitpid()` to wait for child processes to finish and get their exit statuses.

2. **Inter-Process Communication (IPC)**:
   - **Pipes**: Using `pipe()` to create a pipe for communication between processes and `dup2()` to redirect standard input and output.

3. **File Descriptors and Redirection**:
   - **File Operations**: Using `open()` to open files and handle file descriptors.
   - **Redirection**: Redirecting input and output streams using `dup2()`.

4. **Error Handling**:
   - **Error Reporting**: Using `perror()` to report errors and handle them gracefully.

5. **Command Execution**:
   - **Executing Commands**: Using `execve()` to execute commands within child processes.
   - **Retrieving Command Paths**: Determining executable paths using environment variables (`PATH`) and handling command execution errors.

6. **Memory Management**:
   - **Dynamic Memory**: Allocating and freeing memory for command arguments and paths using functions like `ft_split()` and `free()`.

### Functions

- `main()`: Initializes pipes and processes, forks two child processes, and waits for their completion.
- `execute_child()`: Prepares and executes commands in child processes, handling input/output redirection and command execution.
- `open_file()`: Opens input or output files based on the child process.
- `redirect_fds()`: Redirects file descriptors for input and output.
- `close_pipes()`: Closes unused pipe file descriptors.
- `set_in_and_out()`: Sets up input and output redirection for child processes.
- `retrieve_cmds()`: Retrieves the full path of commands to be executed.
- `retrieve_env_path()`: Retrieves the PATH environment variable.
- `get_cmd()`: Splits a command string into arguments.
- `get_env_path()`: Retrieves the value of the PATH environment variable.
- `get_cmd_path()`: Constructs the full path for an executable command.

This README provides a brief overview of the functionality and key concepts utilized in the program, focusing on process management, inter-process communication, and command execution in a Unix-like environment.
