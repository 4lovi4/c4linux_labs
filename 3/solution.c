#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

long int *get_all_pid_from_proc(long int *all_pid, int *size)
{
        int i, nan, n = 0;
        DIR *pd;
        struct dirent *proc_dirs;
        char name[256];
        
        all_pid = (long int *)malloc(sizeof(*all_pid));
        pd = opendir("/proc");
        errno = 0;
        do {
                errno = 0;
                if ((proc_dirs = readdir(pd)) != NULL) {
                        memset(name, 0, sizeof(name));
                        strncpy(name, proc_dirs->d_name, sizeof(name));
                        i = 0;
                        nan = 0;
                        if (errno != 0) 
                                perror("readdir()");
                        while(name[i] != '\0') { 
                                if (! isdigit(name[i]))
                                        nan = 1;
                                i++;
                        }
                        if (nan == 0) {
                        all_pid = (long int *)realloc(all_pid, (n + 1) * sizeof(long int));
                        *(all_pid + n) = strtol(name, NULL, 10);
                                n++;
                        }
                        else
                                continue;
                }
        } while (proc_dirs != NULL);
        *size = n;
        closedir(pd);
        return all_pid;
}

int get_fd_from_stat(long int pid)
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
        long int *pid_a,
             parents[100], childs[100];
        int par_size = 0, chi_size = 0;
        int i, j, 
            c = 0,
            proc_n,
            nae = 1;

        pid_a = get_all_pid_from_proc(pid_a, &proc_n);
        parents[0] = strtol(argv[1], NULL, 10);
        par_size = 1;       
        while (nae == 1) {
                for (j = 0; j < par_size; j++) {
                        for (i = 0; i < proc_n; i++) {
                                if (parents[j] != pid_a[i]) {       
                                        if (get_ppid_from_stat(get_fd_from_stat(pid_a[i])) == parents[j]) {
                                                c++;
                                                childs[chi_size] = pid_a[i];
                                                chi_size++;
                                        }
                                }
                        }
                }
                if (chi_size == 0)
                        nae = 0;
                memset(parents, 0, sizeof(parents));
                for (j = 0; j < chi_size; j++) {
                       parents[j] = childs[j]; 
                }
                par_size = chi_size;
                memset(childs, 0, sizeof(childs));
                chi_size = 0;
        }
        printf("%d\n", c + 1);
        free(pid_a);
        return 0;
}

