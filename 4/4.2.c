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
        int rb;
        memset(buf, 0, sizeof(buf));
        rb = read(fd, buf, sizeof(buf));
        if(rb < 0) {
                perror("read()");
                return(rb);
        }
        else if (rb > 0)
                *num = strtol(buf, NULL, 10);
        return rb;
}
int main (int argc, char **argv)
{
        int fd1, fd2, nfds,
            r1, r2;
        long int num, sum = 0;
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

                if (FD_ISSET(fd1, &fds)) {
                        r1 = read_num(&num, fd1);
                }
                if (FD_ISSET(fd2, &fds)) {
                        r2 = read_num(&num, fd2);
                }

                if ((r1 || r2) == 0)
                        break;

                fprintf(stderr,"num = %ld;\n",num);
                sum += num;
        } 
        printf("%ld\n", sum);
        close(fd1);
        close(fd2);
        return 0;
}
