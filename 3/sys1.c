#include <stdio.h>

int main(int argc, char **argv)
{
        char name[100];

        printf("What's your name? __");

        gets(name);

        return printf("Input: %s;\n",name);
}
