#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv)
{
        FILE *f;
        const char *read_flag = "r";
        char c;
        int n = 0;

        f = popen(argv[1], read_flag);

        if (f == NULL) {
                perror("popen()");
                if (errno) 
                        exit(errno);
                else
                        exit(1);
        }
        while (c != EOF) {
                c = (char)fgetc(f);
                if (c == 'o')
                        n++;
        }       
        printf("%d\n", n);
        pclose(f);
        return 0;

}
