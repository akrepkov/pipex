Pipex is a program designed to execute shell commands in a pipeline manner, similar to the behavior of certain shell commands. It takes four arguments:

 - file1: Input file name.
 - cmd1: First shell command with its parameters.
 - cmd2: Second shell command with its parameters.
 - file2: Output file name.

When executed, Pipex will behave exactly like the following shell command:

<pre>
< file1 cmd1 | cmd2 > file2
</pre>
