
# MiniShell (sash)

MiniShell is a simple Unix shell implementation, providing basic shell functionality similar to Bash. It allows users to execute commands, manage processes, and navigate the file system.

## Features

- Command execution: Execute commands with or without arguments.
- Built-in commands: Support for basic built-in commands such as `cd`, `echo`, `pwd`, `exit` and more.
- Redirection: Support for input and output redirection using `<` , `>` , `>>` and `<<` operators.
- Pipelines: Execute commands in a pipeline using the `|` operator.
- Environment variables: Manage environment variables using syntax like `$VAR_NAME`.
- Signal handling: Handle common Unix signals such as Ctrl+C or Ctrl+\ and EOF like Ctrl+D.

## Getting Started

To get started with MiniShell, follow these steps:

1. Clone the repository:

   ```shell
   git clone https://github.com/ysahih/Minishell.git
   cd minishell
   ```

2. Install the dependencies:
   - readline (should install readline lib)

3. Build the project:

   ```shell
   make
   ```

4. Run MiniShell:

   ```shell
   ./sash
   ```

5. You can now start executing commands in MiniShell.

## Usage

MiniShell supports the following command syntax:

```shell
command [arguments ...] [< input_file] [> output_file] [| command]
```

- `command`: The command to execute.
- `arguments`: Optional arguments for the command.
- `< input_file`: Redirects the input from the specified file.
- `> output_file`: Redirects the output to the specified file.
- `| command`: Pipes the output of the previous command as the input to the next command.
- `heredoc <<`: Allows input redirection from a heredoc block.
- `>> output_file`: Appends the output of a command to the specified file instead of overwriting it.

### Built-in Commands

MiniShell supports the following built-in commands:

- `cd [directory]`: Change the current working directory. If no directory is provided, it changes to the user's home directory.
- `echo [text]`: Display the given text.
- `pwd`: Print the current working directory.
- `exit`: Exit MiniShell.
- `export [variable] [value]`: Set or modify the value of an environment variable. If no arguments are provided, it lists all environment variables.
- `unset [variable]`: Remove an environment variable.
- `env` : Display the current environment variables.

### Environment Variables

You can access and modify environment variables using the syntax `$VAR_NAME`. For example:

```shell
$ echo $HOME
/Users/username

$ export MY_VAR=hello
$ echo $MY_VAR
hello
```

## Contributing

Contributions to MiniShell are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## Contact

For any inquiries or questions, please contact:
Youssef Sahih - ucefsahih@gmail.com

Feel free to reach out if you have any questions or need assistance with MiniShell.
