# Filecopy in C

## To build the project:
    On your terminal, navigate to the project directory. Then execute:
      $ gcc filecopy.c -o fc
    
## To run the project:
    After building, run the program by doing:
      $ ./fc
    To see strace list:
      $ strace -c ./fc
      
#### Code
   Following the pseudocode, I first implemented writing prompts to the screen, acquiring and accepting the user's input and output files, opening files with error checking, reading and writing with error checking, closing both files and writing the completion message all in main(). Ultimately, I decided to make opening the input and output files into their own functions, which are called from a read and write function. open() uses different flags for the input and output files. The input file could be opened with just a read only flag (O_RDONLY) while the output file can be opened with O_RDWR | O_EXCL | O_CREAT. Using the O_WRONLY flag creates a file of type text/x, while O_RDWR creates a plain text file. When both O_EXCL and O_CREAT are set, then open() will fail if the file exists (meaning there is another file already named the output file). 0644 is the permission bits that will create a read and write file for the user, and read file for everyone else. After opening the files, we can read and write using a loop. The do-while reads from the source file, then writes to the destination file (copying all conent) until the number of read bytes is 0. We then close both files, print the completion message and exit the function, then program. When the program finishes, a file named after the user's chosen output file name will appear in the same directory.
      
#### strace output:
I saw that my program made a total of 42 calls to copy 11 bytes. Initially, I was also able to see 2 errors out of 4 close syscalls. The warnings in my program showed that close expects arguments of type int, and not char. During then, close() was called in main(), where it was passed char input and output files. I then realized that I was not actually closing the source and destination files that were of type int. This was fixed by calling close() in the read and write method, where they can be passed the int arrays after they have been successfully copied.\
![alt text](https://preview.ibb.co/iL6fC8/stracefc2.png)
![alt text](https://preview.ibb.co/mXDSs8/stracefc3.png)\
\
After updating the README, copying 2371 bytes increased the number of calls to 436. The number of times it took to read and write increased dramatically while the number of all other calls, including opening and closing, stayed the same.\
![alt text](https://preview.ibb.co/bDHZ5T/stracefc.png)
