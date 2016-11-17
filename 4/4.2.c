#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
int read_num(long int *num, int fd) 
{
        char buf[512];
        memset(buf, 0, sizeof(buf));
        if (read(fd, buf, sizeof(buf)) < 0) {
                perror("read()");
                exit(errno);
        }
        *num = strtol(buf, NULL, 10);
        return 0;
}
int main (int argc, char **argv)
{
        int fd1, fd2, nfds;
        long int num1, num2, sum;
        fd_set fds;

        fd1 = open("./in1", O_RDONLY|O_NONBLOCK);
        fd2 = open("./in2", O_RDONLY|O_NONBLOCK);
        if (fd1 < 0 || fd2 < 0) {
                perror("open()");
                exit(errno);
        }
        for(;;) {
                FD_ZERO(&fds);
                FD_SET(fd1, &fds);
                FD_SET(fd2, &fds);

                nfds = (fd1 > fd2 ? fd1 : fd2) + 1;

                select (nfds, &fds, NULL, NULL, NULL);
        } 
        close(fd1);
        close(fd2);
        return 0;
}
