#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char **argv)
{
        FILE *f;
        const char *read_flag = "r";
        char c;
        long unsigned int n = 0;
        char pstring[80];
       
        if (argc < 3) {
                fprintf(stderr, "Two few arguments, should be two of them!\n\
\t%s <command> <parameter>\n", argv[0]);
                exit(1); 
        }
        memset(pstring, 0, sizeof(pstring));
        sprintf(pstring, "%s %s", argv[1], argv[2]);
       
        f = popen(pstring, read_flag);

        if (f == NULL) {
                perror("popen()");
                if (errno) 
                        exit(errno);
                else
                        exit(1);
        }
        while (c != EOF) {
                c = (char)fgetc(f);
                if (c == '0')
                        n++;
        }       
        printf("%ld\n", n);
        pclose(f);
        return 0;

}
