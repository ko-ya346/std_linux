#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++) {
        FILE *f;
        int c;

        f = fopen(argv[i], "r");
        /* !f 否定*/
        if (!f) {
            perror(argv[i]);
            exit(1);
        }
        /*fgetc: 引数のstreamから1 byte読み込んで返す。streamが終了したらEOF(-1)を返す*/
        /*fputc: 引数のstreamにバイトcを書き込む*/
        while ((c = fgetc(f)) != EOF) {
                if (putchar(c) < 0) exit(1);
        }
        fclose(f);
    }
    exit(0);
}

