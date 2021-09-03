# mimibash

School 21 project <br>
Working in a team

## Status

IN PROGRESS

## Description

The objective of this project is to create a simple shell.

<table>
  <tr>
    <td> <b>Builtins</b> </td> <td>
												<b>cd</b> with only a relative or absolute path <br>
                                                <b>pwd</b> with no options <br>
                                                <b>export</b> with no options <br>
                                                <b>unset</b> with no options <br>
												<b>env</b> with no options or arguments <br>
												<b>exit</b> with no options </td>
  </tr>
  <tr>
    <td> <b>Redirections</b> </td> <td>
                                               <b><</b> does redirect input <br>
                                               <b>></b> does redirect output <br>
                                               <b><<</b> reads input from the current source until a line containing only the delimiter <br>
                                               <b>>></b> does redirect output with append mode </td>
  </tr>
  <tr>
    <td> <b>Signals</b> </td> <td>
                                               <b>ctrl-C</b> prints a new prompt on a newline <br>
                                               <b>ctrl-D</b> exits the shell <br>
                                               <b>ctrl-\</b> does nothing </td>
  </tr>
</table>

The output of each command in the pipeline is connected via a pipe to the
input of the next command. <br>
$? expands to the exit status of the most recently executed foreground
pipeline. <br>
Environment variables ($ followed by characters) expand to their values. <br>
The wildcard * works for the current working directory.

<table>
  <tr>
    <td> <b>External functions</b> </td> <td> readline, rl_clear_history, rl_on_new_line,
											rl_replace_line, rl_redisplay, add_history, printf,
											malloc, free, write, open, read, close, fork,
											waitpid, signal, kill, exit, getcwd, chdir, stat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, </td>
  </tr>
</table>

Mimibash does not interpret unclosed quotes or unspecified special characters like \ or ; and generally in those cases the behavior is undefined. Sometimes the program may treat it as syntax errors.
