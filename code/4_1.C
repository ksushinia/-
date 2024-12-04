#include <stdio.h>
#include <conio.h>
#include <dos.h>

#define ESCAPE 27
#define UP 72
#define DOWN 80

#define X1 10
#define X2 70
#define Y1 5
#define Y2 15

int get_key_press() {
    union REGS regs;
    regs.h.ah = 0x08;
    int86(0x21, &regs, &regs);
    return regs.h.al;
}

int main() {
    int x = (X2 - X1 + 1) / 2 + X1;
    int y = (Y2 - Y1 + 1) / 2 + Y1;
    int direction = 0;
    int ch;

    window(X1, Y1, X2, Y2);
    textbackground(2);
    textcolor(6);
    _setcursortype(_NOCURSOR);
    clrscr();

    gotoxy(x, y);
    printf("*");

    do {
        if (kbhit()) {
            ch = get_key_press();
            if (ch == 0 || ch == 224) {
                ch = get_key_press();
                if (ch == DOWN) {
                    direction = 1;
                } else if (ch == UP) {
                    direction = -1;
                }
            }
        }

        if (direction != 0) {
            delay(100);
            clrscr();
            y += direction;

            if (y > (Y2 - Y1 + 1)) {
                y = 1;
            } else if (y < 1) {
                y = (Y2 - Y1 + 1);
            }

            gotoxy(x, y);
            printf("*");
        }
    } while (ch != ESCAPE);

    return 0;
}

