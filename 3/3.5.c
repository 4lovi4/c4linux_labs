#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv)
{
        pid_t p, s;
        int i;
        p = fork();
        if (p == -1) {
               perror("fork()");
               exit(errno);
        } 
        if (p != 0) {
        //        printf("%ld\n", (long int)p);
                _exit(0);
        }
        else {
                s = setsid();
                if (s < 0) {
                        perror("setsid()");
                        exit(errno);
                }
                printf("getpid() = %ld;\n\
setsid() = %ld;\n", (long int)getpid(), (long int)s);
                for (i = 0; i < 3; i++) 
                        close(i);
                sleep(60);
        }
                return 0;
}
