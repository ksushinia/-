#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>

void interrupt (*oldKeyboardISR)(void);

volatile int key_pressed = 0;

// Новый обработчик прерывания клавиатуры
void interrupt newKeyboardISR() {
    key_pressed = 1;
    outportb(0x20, 0x20);
}

// Функция для задержки на заданное количество миллисекунд
void delay_ms(unsigned int milliseconds) {
    delay(milliseconds);
}

// Функция для вычисления позиции вывода текста по центру
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

    // Устанавливаем пользовательский обработчик клавиатуры
    oldKeyboardISR = getvect(0x09); // Сохраняем старый обработчик
    setvect(0x09, newKeyboardISR);  // Устанавливаем новый обработчик

    // Временно отключаем обработчик для ввода временного интервала
    setvect(0x09, oldKeyboardISR);
    do {
        printf("Input a constant interval of time (from 300 to 3000 milliseconds): ");
        scanf("%d", &delayTime);

        if (delayTime < 300 || delayTime > 3000) {
            printf("Warning: the interval of time should be from 300 to 3000 milliseconds.\n");
        }
    } while (delayTime < 300 || delayTime > 3000);

    // Очищаем буфер ввода перед вводом фразы
    while (getchar() != '\n');

    // Временно отключаем обработчик для ввода фразы
    setvect(0x09, oldKeyboardISR);
    printf("Input phrase: ");
    fgets(phrase, sizeof(phrase), stdin);  // Чтение фразы от пользователя

    // Включаем обратно новый обработчик клавиатуры
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

        // Выводим символ с помощью прерывания BIOS
        r.h.ah = 0x0E;      // Функция для вывода символа
        r.h.al = phrase[i]; // Символ для вывода
        r.h.bh = 0;         // Номер страницы (обычно 0)
        r.h.bl = 7;         // Атрибут (белый текст на черном фоне)
        int86(0x10, &r, &r); // Вызов прерывания BIOS для вывода символа
        delay_ms(delayTime); // Задержка между выводом символов
    }

    // Восстанавливаем старый обработчик прерывания клавиатуры перед завершением программы
    setvect(0x09, oldKeyboardISR);

    // Ожидание нажатия клавиши перед выходом
    printf("\n\n\n\n\n\n\nPress any key to enter...");
    getch();  // Ожидание нажатия клавиши

    return 0;
}
