/* 方針
 * ファイルの行数をカウント
 * 出力する行数を決める
 * ファイルを頭からなめていき、必要な番号まできたら出力
 *
 * または、、
 * ファイルを上下反転
 * headの容量で出力
 * 出力を反転
 * */

#include <stdio.h>
#include <stdlib.h>

static void do_tail(FILE *f, long nlines);
static long wc_cnt(FILE *f);

int
main(int argc, char *argv[])
{
    /* とりあえず固定*/
    long nlines;
    long file_nlines;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        exit(1);
    }
    nlines = atol(argv[1]);
    
    int i;
    for (i = 2; i < argc; i++){
        FILE *f;
        f = fopen(argv[i], "r");
        if (!f) {
            perror(argv[i]);
            exit(1);
        }
        file_nlines = wc_cnt(f);
        f = fopen(argv[i], "r");
        do_tail(f, file_nlines - nlines);
        fclose(f);
    }
    exit(0);
}

static void
do_tail(FILE *f, long nlines)
{
    int c;
    while ((c = getc(f)) != EOF) {
        if (nlines <= 0) {
            if (putchar(c) < 0) exit(1);
        }
        if (c == '\n') {
            nlines--;
        }
    }
}


static long 
wc_cnt(FILE *f)
{
    int c;
    long cnt = 0;
    while ((c = getc(f)) != EOF) {
        if (c == '\n') {
            cnt++;
        }
    }
    return cnt;
}
