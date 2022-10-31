#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*他のファイルからの参照を禁止する
 https://monozukuri-c.com/langc-funclist-static*/
static void wc_cnt(const char *path);
static void die(const char *s);

int
main(int argc, char *argv[])
{
    int i;
    if (argc == 1) {
        wc_cnt("/dev/stdin");
    }

    for (i = 1; i < argc; i++) {
        wc_cnt(argv[i]);
    }
    exit(0);
}

/*プリプロセッサ(コンパイル前に前処理を行うプログラム)への指示のひとつ
 define 文字列1 文字列2 
 と書くと、コンパイル時に文字列1が文字列2に置き換わる*/
#define BUFFER_SIZE 2048

static void
wc_cnt(const char *path)
{
    int fd;
    unsigned char buf[BUFFER_SIZE];
    int n;
    /* 4 byteの符号なし整数*/
    unsigned long cnt = 0;
    unsigned long i;

    fd = open(path, O_RDONLY);
    if (fd < 0) die(path);
    for (;;) {
        n = read(fd, buf, sizeof buf);
        if (n < 0) die(path);
        if (n == 0) break;
        /* 改行文字が出るたびにcntを増やす*/
        for (i = 0; i < BUFFER_SIZE; i++) {
            if (buf[i] == '\n') cnt++;
        }
    }
    if (close(fd) < 0) die(path);
    printf("%lu\n", cnt);
}

static void
die(const char *s)
{
    perror(s);
    exit(1);
}
