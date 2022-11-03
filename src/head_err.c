#include <stdio.h>
#include <stdlib.h>
/* getopt_long() のプロトタイプ宣言を取り込むために定数を定義して
 * getopt.hをインクルード*/
#define _GNU_SOURCE
#include <getopt.h>


/* 引数が1つ: 標準入力から読み込み
 * 引数が2つ以上: 2つめ以降をファイル名とみなして処理 
 *
 * 以下オプション追加
 * 行数指定 -n
 * ↑のロングオプション版 --lines
 * helpメッセージ --help
 * */

static void do_head(FILE *f, long nlines);
#define DEFAULT_N_LINES 10

static struct option longopts[] = {
    {"lines", required_argument, NULL, 'n'},
    {"help", no_argument, NULL, 'h'},
    /* 配列末尾をgetopt_long()に教えるために全メンバ0にした要素を置く */
    {0, 0, 0, 0}
};

int
main(int argc, char *argv[])
{
    int opt;
    long nlines = DEFAULT_N_LINES;

    /* オプションを解析するloop
     * 解析したいショートオプションだけ第三引数に渡す*/
    /* ここにエラーを仕込む */
    while ((opt = getopt_long(argc, argv, "n", longopts, NULL)) != -1) {
        switch (opt) {
            case 'n':
                /* optarg: 現在処理中のオプションのパラメータ（global 変数）*/
                nlines = atoi(optarg);
                break;
            case 'h':
                fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]); 
                exit(0);
            /* 知らないオプションのときは標準エラーにhelpを返す*/
            case '?':
                fprintf(stderr, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]); 
                exit(1);
        }
    }
    /* 現在処理中のオプションのargvでのインデックス */
    if (optind == argc) {
        do_head(stdin, nlines);
    } else {
        int i;

        for (i = optind; i < argc; i++) {
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

