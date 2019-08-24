## CSE shell assignment
**PTSH**

This is a basic shell written using C.

**Running the code:**

1.`cd` to the directory the shell is present in.

2.Type the command `make`.

3.Enter `./a.out` to run the shell. 

**Code:**

1. `main.c` is the file which runs `runShell()` and is the source file. `runShell()` handles the inputs of the prompt and calls the necessary functions based on the command input.

2. `prompt.c` is solely responsible for displaying the prompt. It calls `printPrompt()`.

3. `cd.c` behaves as the cd function. It implements the `chdir()` function.

4. `utils.c` contains the `echo` and `pwd` functions. `echo` simply prints the input given. `pwd` calls `getcwd` to output the absolute path of the curent directory.

5. `ls.c` behaves as the ls function. It also handles the `-l -a -al/la` flags. It calls the `scandir()` function to enlist the files in the directory. To handle the `-l` flag, `stat()` command is used to obtain the required data of the file.

6. `pinfo.c` prints the current process information. It reads the data at the `/proc/pid/status` and `/proc/pid/exe` to get the necessary information.

7. `exec.c` uses the `wait()` and `fork()` processes to run background and foreground processes. It also calls `waitpid()` and `signal()` for detecting when a process and ended and uses flags to check if it has ended normally.

8. `nwatch.c` read the data at the `/proc/meminfo` and `/proc/interrupts` to get the data. It checks whether the user has entered a character by using the `getchar()` command.

9. `history.c` writes the commands entered in a file and reads them when the `history()` function is called.

8. `Makefile` defines the compilation rules so that multiple `gcc`s don't have to be called each time.