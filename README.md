# Minishell

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)

## Introduction
Minishell is a simple shell program designed as a project for School 42. The goal is to implement a basic shell that can interpret and execute commands, similar to the real shell but with limited functionality. This project is an excellent way to understand the inner workings of a shell and how it interacts with the operating system.

## Features
- Display a prompt and wait for the user to type a command.
- Implement a series of built-in commands.
- Handle command execution using `execve`.
- Manage errors effectively and provide relevant messages.
- Handle signals like `Ctrl+C` and `Ctrl+D`.
- Implement basic redirections (`<`, `>`, `>>`).
- Implement pipes (`|`).

## Requirements
- GCC compiler
- GNU Make

## Installation
To install and set up `minishell`, follow these steps:

1. Clone the repository:
    ```sh
    git clone git@github.com:Bussiereg/Minishell.git
    cd Minishell
    ```

2. Build the project:
    ```sh
    make
    ```

## Usage
To start `minishell`, run the following command after building the project:
```sh
./minishell
```

## Built-in Commands
Minishell supports the following built-in commands:

- echo [args]: Displays the given arguments.
- cd [dir]: Changes the current directory to dir.
- pwd: Prints the current working directory.
 -export [name[=value]]: Sets an environment variable.
- unset [name]: Unsets an environment variable.
- env: Displays the environment variables.
- exit [status]: Exits the shell with the given status.
