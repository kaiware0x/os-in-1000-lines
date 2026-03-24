#include "common.h"

void *memcpy(void *dst, const void *src, size_t n)
{
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;
    while (n--)
    {
        *d++ = *s++;
    }
    return dst;
}

void *memset(void *buf, char c, size_t n)
{
    uint8_t *p = (uint8_t *)buf;
    while (n--)
    {
        *p++ = c;
    }
    return buf;
}

char *strcpy(char *dst, const char *src)
{
    char *d = dst;
    while (*src)
    {
        *d++ = *src++;
    }
    *d = '\0';
    return dst;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
        {
            break;
        }
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void putchar(char ch);

void printf(const char *fmt, ...)
{
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++; // 次の文字へ進む
            switch (*fmt)
            {
            case '\0':        // % が文字列の末尾だったとき
                putchar('%'); // % をPutして終了
                break;
            case '%':         // %% と続いたとき
                putchar('%'); // % をPutして終了
                break;
            case 's': // %s の場合
            {
                // 文字列として抽出
                const char *s = va_arg(vargs, const char *);
                while (*s)
                {
                    putchar(*s);
                    s++;
                }
                break;
            }
            case 'd': // %d の場合
            {
                // 10進数 int として抽出
                int value = va_arg(vargs, int);
                unsigned magnitude = value;
                if (value < 0)
                {
                    putchar('-');
                    magnitude = -magnitude;
                }

                // 桁数を取得
                unsigned divisor = 1;
                while (magnitude / divisor > 9)
                {
                    divisor *= 10;
                }

                while (divisor > 0)
                {
                    putchar('0' + magnitude / divisor);
                    magnitude %= divisor;
                    divisor /= 10;
                }

                break;
            }
            case 'x': // %x の場合
            {
                // 16進数 int として抽出
                unsigned value = va_arg(vargs, unsigned);

                // value の先頭 nibble (1/2byte) からPrintしていく
                for (int i = 7; i >= 0; --i)
                {
                    unsigned nibble = (value >> (i * 4)) & 0xf;
                    putchar("0123456789abcdef"[nibble]);
                }
            }
            }
        }
        else
        {
            putchar(*fmt);
        }

        fmt++;
    }

end:
    va_end(vargs);
}
