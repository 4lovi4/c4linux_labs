#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
        char namestr[128];
        struct hostent *res;       
        int i;
        struct in_addr *sa;
//        printf("%ld\n", sizeof(namestr));
        memset(namestr, 0, sizeof(namestr));
        if (argc < 2) 
                strcpy(namestr, "yandex.ru");
                
        else
                strcpy(namestr, argv[1]);

        res = gethostbyname(namestr);

        if (res == NULL) {
                fprintf(stderr, "gethostbyname() error\n");
                exit(1);
        }
        i = 0;
        while (res->h_addr_list[i] != NULL) {
                sa = (struct in_addr *)res->h_addr_list[i];
                printf("%s\n", inet_ntoa(*sa));
                i++;
        }
                return 0;
}
