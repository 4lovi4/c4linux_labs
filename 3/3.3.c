#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int get_fd_from_proc(long int pid)
{
        int fd;
        char name[80];

        memset(name, 0, sizeof(name));
        sprintf(name, "/proc/%ld/stat",pid);
        fd = open(name, O_RDONLY);
        if (fd < 0) {
                perror("open() stat");
                exit(errno);
        }

        return fd;
}

int get_ppid_from_stat(int fd)
{
        int pid, ppid;
        char stat_buf[512];

        memset(stat_buf, 0, sizeof(stat_buf));
        if((read(fd, stat_buf, sizeof(stat_buf))) < 0) {
                perror("read() stat");
                exit(errno);
        }
        sscanf(stat_buf, "%d %*s %*s %d",&pid, &ppid);
        close(fd);
        return ppid;
}


int main(int argc, char **argv)
{
        long int pid = 0;
        int ppid = 0;

        errno = 0;
        pid = strtol(argv[1], NULL, 10);
        if((errno == EINVAL) || (errno == ERANGE) ||
                        (pid == 0 && errno != 0)) {
                perror("strtol()");
                exit(errno);
        }
        
        printf("%ld\n", pid);
        
        while (ppid != 1) {
                ppid = get_ppid_from_stat(get_fd_from_proc(pid));
                printf("%d\n", ppid);
                pid = (long int)ppid;
        }

        return 0;
}
