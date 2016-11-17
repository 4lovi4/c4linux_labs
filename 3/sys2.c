#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
        pid_t p, pp;
        int fd = -1, i = 0;
        char buf[80], pname[80], 
             c = 0, *pb;
        memset(buf, 0, sizeof(buf));
        memset(pname, 0, sizeof(pname));
        p = getpid();
        //printf("getpid(): %d\n", p);
        //printf("getppid(): %d\n", getppid());
        sprintf(pname, "/proc/%d/stat", p);

        fd = open(pname, O_RDONLY);
        if (fd < 0) {
                perror("open()");
                return errno;
        }
        pb = buf;
        while (c != EOF) {
                read(fd, &c, 1);
                if (c == ' ') {
                        i++;
                        continue;
                }
                if (i == 3) {
                        *pb = c;
                        pb++;
                }
                else if (i == 4) {
                        *pb = '\0';
                        break;
                }
        } 

        pp = atoi(buf);
        printf("%d\n", pp);

        close(fd);
        return 0;
}
