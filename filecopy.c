#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//You may also add more include directives as well.

//THIS VALUE CANNOT BE CHANGED.
//You should use this value when creating your buffer.
// And also to limit the amount each read CAN do.
#define BUFF_MAX 13

int openInputFile (char inputFile[])
{
    int sourceFile;
    //Open the input file
    sourceFile = open(inputFile, O_RDONLY); //Open for reading only
    //Check if the input file exists
    if (sourceFile == -1)
    {
        printf("Error: Your input file, %s, cannot be opened.\n", inputFile);
        exit(0);
    }
    return sourceFile;
}

int createOutputFile (char outputFile[])
{
    int destinationFile;
    //Create output file
    destinationFile = open(outputFile, O_RDWR|O_EXCL|O_CREAT, 0644); //Open for reading and writing,
    //Check if the output file exists
    if (destinationFile == -1)
    {
        printf("Error: Your output file, %s, already exists and cannot be created.\n", outputFile);
        exit(0);
    }
    return destinationFile;
}

int readAndWrite (char inputFile[], char outputFile[])
{
    int source, destination;
    char buffer[BUFF_MAX] = {0};
    ssize_t readByte = 0, writeByte = 0, totalReadByte = 0;

    source = openInputFile(inputFile);
    destination = createOutputFile(outputFile);
    //Read and write loop
    do
    {
        //Read from input file
        readByte = read(source, &buffer, BUFF_MAX - 1);
        //Error checking for read byte size
        if (readByte < 0)
        {
            printf("Unable to read from file.\n");
            return 0;
        }

        //Write to output file
        writeByte = write(destination, &buffer, (ssize_t) readByte);
        //Error checking for write byte size
        if (writeByte < 0)
        {
            printf("Unable to write to file.\n");
            return 0;
        }
        totalReadByte += writeByte;
    } while (readByte != 0);

    //Close files
    close(source);
    close(destination);

    //Completion message
    printf("File Copy Successful, %lu bytes copied.\n", totalReadByte);

    return (0);
}

int
main(int argc, char const *argv[])
{
    char readFile[100], writeFile[100];

    //Write prompt to screen
    printf("Welcome to the File Copy Program by Justin!\nEnter the name of the file to copy from:\n");
    //Acquire and accept input filename
    scanf("%s", readFile);

    printf("Enter the name of the file to copy to:\n");
    //Acquire and accept output filename
    scanf("%s", writeFile);

    //Reading and Writing Loop
    readAndWrite(readFile, writeFile);

    //Terminate program
    return 0;

}