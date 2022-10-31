#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*他のファイルからの参照を禁止する
 https://monozukuri-c.com/langc-funclist-static*/
static void do_cat(const char *path);
static void die(const char *s);

int
main(int argc, char *argv[])
{
    int i;
    if (argc == 1) {
        fprintf(stderr, "%s: file name not given\n", argv[0]);
        exit(1);
        /* do_cat("/dev/stdin"); */
    }

    for (i = 1; i < argc; i++) {
        do_cat(argv[i]);
    }
    exit(0);
}

/*プリプロセッサ(コンパイル前に前処理を行うプログラム)への指示のひとつ
 define 文字列1 文字列2 
 と書くと、コンパイル時に文字列1が文字列2に置き換わる*/
#define BUFFER_SIZE 2048

static void
do_cat(const char *path)
{
    int fd;
    unsigned char buf[BUFFER_SIZE];
    int n;

    /* open: pathで表されるファイルにつながるストリームを作成し
     * そのストリームを指すファイルディスクリプタを返す*/
    fd = open(path, O_RDONLY);
    if (fd < 0) die(path);
    for (;;) {
        /* read: ファイルディスクリプタfd番のストリームから
         * バイト列を読み込む */
        n = read(fd, buf, sizeof buf);
        if (n < 0) die(path);
        if (n == 0) break;
        /* write: bufsize バイト分をbufからファイルディスクリプタfd番の
         * ストリームに書き込む */
        if (write(STDOUT_FILENO, buf, n) < 0) die(path);
    }
    /* close: ファイルディスクリプタfdに関連付けられている
     * ストリームを始末する */
    if (close(fd) < 0) die(path);
}

static void
die(const char *s)
{
    perror(s);
    exit(1);
}
