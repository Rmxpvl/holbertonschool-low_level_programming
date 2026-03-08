#include <stdio.h>

int main(int argc, char *argv[])
{
    (void)argc;  // avoid "unused variable" warning
    printf("%s\n", argv[0]);
    return 0;
}
