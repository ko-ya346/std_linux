#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE *f, long nlines);

int
main(int argc, char *argv[])
{
    /* 引数は行数のみ */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        exit(1);
    }
    /* atol: 文字列を数値に変換 */
    do_head(stdin, atol(argv[1]));
    exit(0);
}

static void
do_head(FILE *f, long nlines)
{
    int c;

    if (nlines <= 0) return;
    /* getc: 引数のstreamから1 byte読み込んで返す
     * fgetcのマクロ */
    while ((c = getc(f)) != EOF) {
        /* putchar: stdoutに引数のバイトcを書き込む 
         * fputcのマクロ、putcの出力先固定ver.*/
        if (putchar(c) < 0) exit(1);
        if (c == '\n') {
            nlines--;
            if (nlines == 0) return;
        }
    }
}

