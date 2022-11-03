# 引数で受け取ったファイルの中身を連結してstdoutに出力
# python3 do_cat.py a b c

import sys


def do_cat(argv):
    try:
        with open(argv, "r") as f:
            sys.stdout.write(f.read())
    except:
        sys.stdout.write(argv)

def main():
    args = sys.argv
    if len(args) <= 1:
        print(f"{args[0]}: file name not given.")
        exit()

    for argv in args[1:]:
        do_cat(argv)

if __name__ == "__main__":
    main()
