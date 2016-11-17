#include <stdio.h>
#include <dlfcn.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

int (*dl_function)(int);
void *hdl;

bool init_lib(const char* libname, const char* f_name)
{
        hdl = dlopen(libname, RTLD_LAZY);
        if (!hdl)       {
                fprintf(stderr, "%s\n", dlerror());
                return false;
        }
        dl_function = dlsym(hdl, f_name);
}

int main(int argc, char **argv)
{
        int value = atoi(argv[3]);
        if (init_lib(argv[1], argv[2])) {
                printf("%d\n", dl_function(value));
        }
        else {
                fprintf(stderr, "Couldn't execute function %s from library %s\n",
                                argv[2], argv[1]);
        dlclose(hdl);
        }
        return 0;
}
