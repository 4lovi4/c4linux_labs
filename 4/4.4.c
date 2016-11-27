#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
 
static sig_atomic_t sig_status = 0;

void usr1_hand()
{
        sig_status = 1;
}

int main(int argc, char **argv)
{
        pid_t p, s;
        int i;
        struct sigaction usr1_act;
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
                printf("%ld\n", (long int)s);
//setsid() = %ld;\n", (long int)getpid(), (long int)s);
                for (i = 0; i < 3; i++) 
                        close(i);
                sigemptyset(&usr1_act.sa_mask);
                usr1_act.sa_flags = 0;
                usr1_act.sa_handler = (void *)&usr1_hand;

                for(;;) {
                        if (sigaction(SIGURG, &usr1_act, NULL) < 0) {
                                perror("sigaction(SIGUSR1)");
                                return 1;
                        }
                if (sig_status == 1)
                        break;
                }
                _exit(0);
        }
        return 0;
}
