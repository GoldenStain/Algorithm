import sys

def main():
    n = int(input().strip())
    cur = 0
    num = 0
    while True:
        s = str(num)
        if cur + len(s) >= n:
            print(s[n - cur - 1])
            break
        else:
            cur += len(s)
            num += 2

if __name__ == "__main__":
    main()