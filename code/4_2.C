#include <conio.h>
#include <bios.h>
#include <dos.h>

#define ESCAPE 27
#define UP 72
#define DOWN 80

#define X1 10
#define X2 70
#define Y1 5
#define Y2 15

int presskey() {
    union REGS r;
    r.h.ah = 0x0B;
    int86(0x21, &r, &r);
    return r.h.al;
}

int getKey() {
    union REGS r;
    r.h.ah = 0x07;
    int86(0x21, &r, &r);
    return r.h.al;
}

void putchar(char ch, int x, int y) {
    gotoxy(x, y);
    putch(ch);
}

int main() {
    int x, y, ch = 0;
    int direction = 0;

    x = (X2 - X1 + 1) / 2 + X1;
    y = (Y2 - Y1 + 1) / 2 + Y1;

    window(X1, Y1, X2, Y2);
    textbackground(7);
    textcolor(6);
    _setcursortype(_NOCURSOR);
    clrscr();

    putchar('*', x, y);

    do {
        if (presskey()) {
            ch = getKey();
            if (ch == 0 || ch == 224) {
                ch = getKey();
                switch (ch) {
                    case DOWN:
                        direction = 1;
                        break;
                    case UP:
                        direction = -1;
                        break;
                }
            }
        }

        if (direction != 0) {
            clrscr();
            y += direction;

            if (y > (Y2 - Y1 + 1)) {
                y = 1;
            } else if (y < 1) {
                y = (Y2 - Y1 + 1);
            }

            putchar('*', x, y);
            delay(100);
        }
    } while (ch != ESCAPE);

    return 0;
}
