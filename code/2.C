#include <stdio.h>
#include <conio.h>
#include <dos.h>

void scroll(int direction, char leftrow, char leftcol, char rightrow, char rightcol, char attributes)
{
    union REGS r;
    if (direction) {
	r.h.al = 1;
	r.h.ah = direction;
    }
    else {
	r.h.al = 0;
	r.h.ah = 6;
    }
    r.h.ch = leftrow;
    r.h.cl = leftcol;
    r.h.dh = rightrow;
    r.h.dl = rightcol;
    r.h.bh = attributes;
    int86(0x10, &r, &r);
}

int main() {
    int i, j = 0;
    textbackground(0);
    clrscr() ;
    window(10, 5, 70, 15);
    textbackground(0);
    clrscr();
    _setcursortype(_NOCURSOR);
    for (i = 0; i < 8; i++) {
	textbackground(i);
	clrscr();
	for(j = 0; j <= 15; j++) {
	    textcolor(j);
	    gotoxy(1,10);
	    cprintf("back: ");
	    switch(i)
	    {
		case 0: cprintf("0");
	    break;
		case 1: cprintf("1");
	    break;
		case 2: cprintf("2");
	    break;
		case 3: cprintf("3");
	    break;
		case 4: cprintf("4");
	    break;
		case 5: cprintf("5");
	    break;
		case 6: cprintf("6");
	    break;
		case 7: cprintf("7");
	    break;
	    }
	    switch(j)
	    {
		case 0: cprintf(" Text = BLACK");
	    break;
		case 1: cprintf(" Text = BLUE");
	    break;
		case 2: cprintf(" Text = GREEN");
	    break;
		case 3: cprintf(" Text = CYAN");
	    break;
		case 4: cprintf(" Text = RED");
	    break;
		case 5: cprintf(" Text = PINK");
	    break;
		case 6: cprintf(" Text = BROWN");
	    break;
		case 7: cprintf(" Text = LIGHTGRAY");
	    break;
		case 8: cprintf(" Text = DARKGRAY");
	    break;
		case 9: cprintf(" Text = LIGHTBLUE");
	    break;
		case 10: cprintf(" Text = LIGHTGREEN");
	    break;
		case 11: cprintf(" Text = LIGHTCYAN");
	    break;
		case 12: cprintf(" Text = LIGHTRED");
	    break;
		case 13: cprintf(" Text = LIGHTPINK");
	    break;
		case 14: cprintf(" Text = YELLOW");
	    break;
		case 15: cprintf(" Text = WHITE");
	    break;
	    }
	delay(300);
	gotoxy(wherex(), wherey()-1);
	scroll(6, 4, 9, 14, 69, i * 16 + j);
	scroll(6, 4, 9, 14, 69, i * 16 + j);
	}
    }
    return 0;
}