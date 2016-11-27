#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

static int usr_count1 = 0, 
           usr_count2 = 0;
static sig_atomic_t sig_status = 0;

void usr1_handler(void)
{
        usr_count1++;
}

void usr2_handler(void)
{
        usr_count2++;
}

void term_handler(void)
{
        sig_status = 1;
}

int main (int argc, char **argv)
{
        struct sigaction usr_act1, usr_act2, term_act;
        
        sigemptyset(&usr_act1.sa_mask);
        sigemptyset(&usr_act2.sa_mask);
        sigemptyset(&term_act.sa_mask);
        usr_act1.sa_flags = 0;
        usr_act2.sa_flags = 0;
        term_act.sa_flags = 0;
        usr_act1.sa_handler = (void *)&usr1_handler;
        usr_act2.sa_handler = (void *)&usr2_handler;
        term_act.sa_handler = (void *)&term_handler;

        for(;;) {
                if (sigaction(SIGUSR1, &usr_act1, NULL) < 0) {
                        perror("sigaction(SIGUSR1)");
                        return 1;
                }

                if (sigaction(SIGUSR2, &usr_act2, NULL) < 0) {
                        perror("sigaction(SIGUSR2)");
                        return 1;
                }

                if (sigaction(SIGTERM, &term_act, NULL) < 0) {
                        perror("sigaction(SIGUSR1)");
                        return 1;
                }
                if (sig_status == 1)
                        break;
        }

        printf("%d %d\n", usr_count1, usr_count2);

        return 0;
}
