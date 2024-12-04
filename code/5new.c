#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>

void interrupt (*oldKeyboardISR)(void);

volatile int key_pressed = 0;

// ����� ���������� ���������� ����������
void interrupt newKeyboardISR() {
    key_pressed = 1;
    outportb(0x20, 0x20);
}

// ������� ��� �������� �� �������� ���������� �����������
void delay_ms(unsigned int milliseconds) {
    delay(milliseconds);
}

// ������� ��� ���������� ������� ������ ������ �� ������
void center_position(int phraseLength, int *x, int *y) {
    int screenWidth = 80;
    int screenHeight = 25;

    *x = (screenWidth - phraseLength) / 2;
    *y = screenHeight / 2;
}

int main() {
    int delayTime;
    char phrase[100];
    int phraseLength;
    int i;
    int startX, startY;
    union REGS r;

    // ������������� ���������������� ���������� ����������
    oldKeyboardISR = getvect(0x09); // ��������� ������ ����������
    setvect(0x09, newKeyboardISR);  // ������������� ����� ����������

    // �������� ��������� ���������� ��� ����� ���������� ���������
    setvect(0x09, oldKeyboardISR);
    do {
        printf("Input a constant interval of time (from 300 to 3000 milliseconds): ");
        scanf("%d", &delayTime);

        if (delayTime < 300 || delayTime > 3000) {
            printf("Warning: the interval of time should be from 300 to 3000 milliseconds.\n");
        }
    } while (delayTime < 300 || delayTime > 3000);

    // ������� ����� ����� ����� ������ �����
    while (getchar() != '\n');

    // �������� ��������� ���������� ��� ����� �����
    setvect(0x09, oldKeyboardISR);
    printf("Input phrase: ");
    fgets(phrase, sizeof(phrase), stdin);  // ������ ����� �� ������������

    // �������� ������� ����� ���������� ����������
    setvect(0x09, newKeyboardISR);


    phrase[strcspn(phrase, "\n")] = 0;


    phraseLength = strlen(phrase);


    clrscr();


    center_position(phraseLength, &startX, &startY);


    gotoxy(startX, startY);


    for (i = 0; i < phraseLength; i++) {
        key_pressed = 0;


        if (key_pressed) {
            break;
        }

        // ������� ������ � ������� ���������� BIOS
        r.h.ah = 0x0E;      // ������� ��� ������ �������
        r.h.al = phrase[i]; // ������ ��� ������
        r.h.bh = 0;         // ����� �������� (������ 0)
        r.h.bl = 7;         // ������� (����� ����� �� ������ ����)
        int86(0x10, &r, &r); // ����� ���������� BIOS ��� ������ �������
        delay_ms(delayTime); // �������� ����� ������� ��������
    }

    // ��������������� ������ ���������� ���������� ���������� ����� ����������� ���������
    setvect(0x09, oldKeyboardISR);

    // �������� ������� ������� ����� �������
    printf("\n\n\n\n\n\n\nPress any key to enter...");
    getch();  // �������� ������� �������

    return 0;
}
