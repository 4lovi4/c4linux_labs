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
        int fd1, fd2;
        long int num1, num2, sum;

        fd1 = open("./in1", O_RDONLY);
        fd2 = open("./in2", O_RDONLY);
        if (fd1 < 0 || fd2 < 0) {
                perror("open()");
                exit(errno);
        }
        
        close(fd1);
        close(fd2);
        return 0;
}
