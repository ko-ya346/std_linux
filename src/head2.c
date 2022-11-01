#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE *f, long nlines);
/* 引数が1つ: 標準入力から読み込み
 * 引数が2つ以上: 2つめ以降をファイル名とみなして処理 */

int
main(int argc, char *argv[])
{
    long nlines;

    /* 引数は行数のみ */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        exit(1);
    }
    nlines = atol(argv[1]);
    if (argc == 2) {
        do_head(stdin, nlines);
    } else {
        int i;

        for (i = 2; i < argc; i++){
            FILE *f;

            f = fopen(argv[i], "r");
            if (!f) {
                perror(argv[i]);
                exit(1);
            }
            do_head(f, nlines);
            fclose(f);
        }
    }

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

