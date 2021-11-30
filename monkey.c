/*
 * Zachary S. Porter
 * ASSIGNMENT 6
 * CSCI 4100
 * A simple recreation of the UNIX monkey cp program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#define MAXCHAR 4096

int main(int argc, char *argv[]) {
	
	if (argc != 3) {
		fputs("Usage: monkey source dstination\n", stderr);
		exit(1);
	}

	
	char buffer[MAXCHAR];	
	char *filename = argv[1];
	char *copyfile = argv[2];
	char chars_read;
	char chars_written;
	int fd;
	int fd_in;

	/* Set up file descriptor and check if valid */
	fd = creat(copyfile, 0644);
	if (fd == -1) {
		perror(copyfile);
		exit(1);
	}

	/* Open file to be copied and check for error */
	fd_in = open(filename, O_RDONLY);
	if (fd_in == -1) {
		perror(filename);
		close(fd_in);
		exit(1);
	}

	/* Read from filename and write to copyfile */
	chars_read = read(fd_in, buffer, MAXCHAR);
	chars_written = write(fd, buffer, chars_read);

	/* Check if file was read*/
	if (chars_read == -1) {
		printf("ERROR: no bytes read.");
		close(fd_in);
		exit(1);
	}

	if (chars_written == -1) {
		printf("ERROR: writing bytes");
		close(fd_in);
		exit(1);
	}

	close(fd_in);
	return 0;
}
