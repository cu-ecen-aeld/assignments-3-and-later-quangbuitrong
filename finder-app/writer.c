
/*
 * - Accepts the following arguments: the first argument is a full path to a file
 *   (including * filename) on the filesystem, referred to below as writefile; the second
 *   argument is a * * text string which will be written within this file, referred to
 *   below as writestr
 *
 * - Exits with value 1 error and print statements if any of the arguments above were not
 *   specified
 *
 * - Creates a new file with name and path writefile with content writestr, overwriting
 *   any existing file and creating the path if it doesn’t exist. Exits with value 1 and
 *   error print statement if the file could not be created.
 *
 * - One difference from the write.sh instructions in Assignment 1:  You do not need to
 *   make your "writer" utility create directories which do not exist.  You can assume
 *   the directory is created by the caller.
 *
 * - Setup syslog logging for your utility using the LOG_USER facility.
 *
 * - Use the syslog capability to write a message “Writing <string> to <file>” where
 *   <string> is the text string written to file (second argument) and <file> is the file
 *   created by the script.  This should be written with LOG_DEBUG level.
 *
 * - Use the syslog capability to log any unexpected errors with LOG_ERR level.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <errno.h>

int main(int argc, char *argv[]) {

    /* syslog setup */
    openlog(NULL, LOG_CONS, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Error: requires writefile and writestr arguments");
        exit(1);
    }

    char *writefile = argv[1];
    char *writestr = argv[2];
    int fd; // file descriptor
    ssize_t nr;

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    fd = creat(writefile, 0644);
    if (fd == -1) {
        syslog(LOG_ERR, "Error: could not create %s: %s", writefile, strerror(errno));
        exit(1);
    }

    nr = write(fd, writestr, strlen(writestr));
    if (nr == -1) {
        syslog(LOG_ERR, "Error: could not write to %s: %s", writefile, strerror(errno));
        exit(1);
    }

    if (close(fd) == -1) {
        syslog(LOG_ERR, "Error: could not close %s: %s", writefile, strerror(errno));
        exit(1);
    }

    syslog(LOG_DEBUG, "Success");
    closelog();
    return 0;
}
