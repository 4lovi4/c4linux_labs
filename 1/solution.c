#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stringStat(const char *string, size_t multiplier, int *count)
{
        int res = 0;
        res = (int)(strlen(string) * multiplier);
        (*count)++;
        return res;
}

//int main(int argc, char **argv)
//{
//        const char *str_con = "string!";
//        int c = 10;
//        //count = malloc(sizeof(int)); 
//        //*count = 101;
//        printf("before count = %d\n", c);
//        printf("result = %d\n",stringStat(str_con, 2, &c));
//        printf("after count = %d\n", c);
//        //free(count);
//        return 0;
//}
