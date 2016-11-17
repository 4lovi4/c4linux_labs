#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int get_ppid_from_stat(int fd)
{
        int pid, ppid;
        char buf_stat[256];
        
        if ((read(fd, buf_stat, sizeof(buf_stat))) < 0) {
                perror("read() stat");
                return(errno);
        }

        sscanf(buf_stat, "%d %*s %*s %d",&pid, &ppid);

        return(ppid);

}

int main(int argc, char **argv)
{
        int fd, ppid;
        char buf_name[80];

        printf("%s\n", argv[1]);

        sprintf(buf_name, "/proc/%s/stat",argv[1]);
        fd = open(buf_name, O_RDONLY);
        if (fd < 0) {
                perror("open()");
                exit(errno);
        }
        while (ppid != 1) {
                ppid = get_ppid_from_stat(fd);
                printf ("%d\n", ppid);
        }
        close(fd);
        return 0;
}
