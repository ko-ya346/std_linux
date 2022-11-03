#include<stdio.h>
#include<stdlib.h>

int
main(int argc, char *argv[])
/*argc: コマンドライン引数の数、argv: コマンドライン引数の実体*/
{
    int i;
    printf("argc=%d\n", argc);
    for (i = 0; i < argc; i++) {
        printf("argv[%d]=%s\n", i, argv[i]);
    }
    exit(0);
}
