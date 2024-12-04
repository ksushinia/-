#include <iostream>
#include <cmath>  // Для floor()

using namespace std;

// вывод двоичного представления unsigned char
void printBinary(unsigned char value) {
    for (int i = sizeof(unsigned char) * 8 - 1; i >= 0; --i) {
        cout << ((value >> i) & 1); //сдвиг вправо (от старшего к младшему)
    }
    cout << endl;
}

// вывод двоичного представления целого числа
void printBinary(int value) {
    for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
        cout << ((value >> i) & 1);
    }
    cout << endl;
}

// для вывода двоичного представления float с пробелом между частями
void printBinaryFloat(float value) {
    union {
        float input;
        uint32_t bits; // для доступа к float как к целому числу
    } data;
    data.input = value;

    cout << "Двоичное представление float: ";
    for (int i = 31; i >= 0; --i) {
        cout << ((data.bits >> i) & 1);
        if (i == 31 - 8) {
            cout << ' ';  // пробел перед экспонентой
        }
        if (i == 31 - 8 - 23) {
            cout << ' ';  // пробел перед мантиссой
        }
    }
    cout << endl;
}

// установка битов в unsigned char
unsigned char setBits(unsigned char value, int startBit, int numBits, bool bitValue) {
    for (int i = startBit; i > startBit - numBits; --i) {
        if (bitValue) {
            value |= (1 << i);   // устанавливаем бит в 1
        }
        else {
            value &= ~(1 << i);  // устанавливаем бит в 0
        }
    }
    return value;
}

// установка битов в float
float setBits(float value, int startBit, int numBits, bool bitValue) {
    union {
        float input;
        uint32_t bits;
    } data;
    data.input = value;

    for (int i = startBit; i > startBit - numBits; --i) {
        if (bitValue) {
            data.bits |= (1 << i);   // устанавливаем бит в 1
        }
        else {
            data.bits &= ~(1 << i);  // устанавливаем бит в 0
        }
    }
    return data.input;
}

int main() {
    setlocale(LC_ALL, "ru");

    // unsigned char
    unsigned char ucharValue;
    cout << "Введите символ или число для типа unsigned char: ";
    char tempChar;
    cin >> tempChar;

    if (isdigit(tempChar)) {
        ucharValue = static_cast<unsigned char>(tempChar - '0');  // Если введена цифра
    }
    else {
        ucharValue = static_cast<unsigned char>(tempChar);  // Если введён символ
    }

    cout << "Двоичное представление unsigned char: ";
    printBinary(ucharValue);

    int startBit, numBits;
    bool bitValue;
    cout << "Введите номер старшего бита для установки (0-7): ";
    cin >> startBit;
    cout << "Введите количество бит для установки: ";
    cin >> numBits;
    cout << "Установить в 1 (1) или в 0 (0)?: ";
    cin >> bitValue;

    ucharValue = setBits(ucharValue, startBit, numBits, bitValue);
    cout << "Изменённое значение unsigned char (как символ): '" << ucharValue << "'" << endl;
    cout << "Двоичное представление после изменения: ";
    printBinary(ucharValue);

    // float
    float floatValue;
    cout << "\nВведите значение типа float: ";
    cin >> floatValue;

    printBinaryFloat(floatValue);

    cout << "Введите номер старшего бита для установки (0-31): ";
    cin >> startBit;
    cout << "Введите количество бит для установки: ";
    cin >> numBits;
    cout << "Установить в 1 (1) или в 0 (0)?: ";
    cin >> bitValue;

    floatValue = setBits(floatValue, startBit, numBits, bitValue);
    cout << "Изменённое значение float: " << floatValue << endl;
    printBinaryFloat(floatValue);

    return 0;
}
//#include <iostream>
//#include <cmath>  // Для floor()
//
//using namespace std;
//
//// вывод двоичного представления unsigned char
//void printBinary(unsigned char value) {
//    for (int i = sizeof(unsigned char) * 8 - 1; i >= 0; --i) {
//        cout << ((value >> i) & 1); //сдвиг вправо (от старшего к младшему)
//    }
//    cout << endl;
//}
//
//// вывод двоичного представления целого числа
//void printBinary(int value) {
//    for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
//        cout << ((value >> i) & 1);
//    }
//    cout << endl;
//}
//
//// для вывода двоичного представления float с пробелом между частями
//void printBinaryFloat(float value) {
//    union {
//        float input;
//        uint32_t bits; // для доступа к float как к целому числу
//    } data;
//    data.input = value;
//
//    cout << "Двоичное представление float: ";
//    for (int i = 31; i >= 0; --i) {
//        cout << ((data.bits >> i) & 1);
//        if (i == 31 - 8) {
//            cout << ' ';  // пробел перед экспонентой
//        }
//        if (i == 31 - 8 - 23) {
//            cout << ' ';  // пробел перед мантиссой
//        }
//    }
//    cout << endl;
//}
//
//// установка битов в unsigned char
//unsigned char setBits(unsigned char value, int startBit, int numBits, bool bitValue) {
//    for (int i = startBit; i > startBit - numBits; --i) {
//        if (bitValue) {
//            value |= (1 << i);   // устанавливаем бит в 1
//        }
//        else {
//            value &= ~(1 << i);  // устанавливаем бит в 0
//        }
//    }
//    return value;
//}
//
//// установка битов в float
//float setBits(float value, int startBit, int numBits, bool bitValue) {
//    union {
//        float input;
//        uint32_t bits;
//    } data;
//    data.input = value;
//
//    for (int i = startBit; i > startBit - numBits; --i) {
//        if (bitValue) {
//            data.bits |= (1 << i);   // устанавливаем бит в 1
//        }
//        else {
//            data.bits &= ~(1 << i);  // устанавливаем бит в 0
//        }
//    }
//    return data.input;
//}
//
//int main() {
//    setlocale(LC_ALL, "ru");
//
//    // unsigned char
//    unsigned char ucharValue;
//    cout << "Введите символ или число для типа unsigned char: ";
//    char tempChar;
//    cin >> tempChar;
//
//    if (isdigit(tempChar)) {
//        ucharValue = static_cast<unsigned char>(tempChar - '0');  // Если введена цифра
//    }
//    else {
//        ucharValue = static_cast<unsigned char>(tempChar);  // Если введён символ
//    }
//
//    cout << "Двоичное представление unsigned char: ";
//    printBinary(ucharValue);
//
//    int startBit, numBits;
//    bool bitValue;
//    cout << "Введите номер старшего бита для установки (0-7): ";
//    cin >> startBit;
//    cout << "Введите количество бит для установки: ";
//    cin >> numBits;
//    cout << "Установить в 1 (1) или в 0 (0)?: ";
//    cin >> bitValue;
//
//    ucharValue = setBits(ucharValue, startBit, numBits, bitValue);
//    cout << "Изменённое значение unsigned char: " << static_cast<int>(ucharValue) << endl;
//    cout << "Двоичное представление после изменения: ";
//    printBinary(ucharValue);
//
//    // float
//    float floatValue;
//    cout << "\nВведите значение типа float: ";
//    cin >> floatValue;
//
//    printBinaryFloat(floatValue);
//
//    cout << "Введите номер старшего бита для установки (0-31): ";
//    cin >> startBit;
//    cout << "Введите количество бит для установки: ";
//    cin >> numBits;
//    cout << "Установить в 1 (1) или в 0 (0)?: ";
//    cin >> bitValue;
//
//    floatValue = setBits(floatValue, startBit, numBits, bitValue);
//    cout << "Изменённое значение float: " << floatValue << endl;
//    printBinaryFloat(floatValue);
//
//    return 0;
//}//#include <iostream>
//#include <cmath>  // Для floor()
//
//using namespace std;
//
//// вывод двоичного представления unsigned char
//void printBinary(unsigned char value) {
//    for (int i = sizeof(unsigned char) * 8 - 1; i >= 0; --i) { 
//        cout << ((value >> i) & 1); //сдвиг вправо (от старшего к младшему)
//    }
//    cout << endl;
//}
//
//// вывод двоичного представления целого числа
//void printBinary(int value) {
//    for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
//        cout << ((value >> i) & 1);
//    }
//    cout << endl;
//}
//
//// для вывода двоичного представления float с пробелом между частями
//void printBinaryFloat(float value) {
//    union {
//        float input;
//        uint32_t bits; // для доступа к float как к целому числу
//    } data;
//    data.input = value;
//
//    cout << "Двоичное представление float: ";
//    for (int i = 31; i >= 0; --i) {
//        cout << ((data.bits >> i) & 1);
//        if (i == 31 - 8) {
//            cout << ' ';  // пробел перед экспонентой
//        }
//        if (i == 31 - 8 - 23) {
//            cout << ' ';  // пробел перед мантиссой
//        }
//    }
//    cout << endl;
//}
//
//// установка битов в unsigned char
//unsigned char setBits(unsigned char value, int startBit, int numBits, bool bitValue) {
//    for (int i = startBit; i > startBit - numBits; --i) {
//        if (bitValue) {
//            value |= (1 << i);   // устанавливаем бит в 1
//        }
//        else {
//            value &= ~(1 << i);  // устанавливаем бит в 0
//        }
//    }
//    return value;
//}
//
//// установка битов в float
//float setBits(float value, int startBit, int numBits, bool bitValue) {
//    union {
//        float input;
//        uint32_t bits;
//    } data;
//    data.input = value;
//
//    for (int i = startBit; i > startBit - numBits; --i) {
//        if (bitValue) {
//            data.bits |= (1 << i);   // устанавливаем бит в 1
//        }
//        else {
//            data.bits &= ~(1 << i);  // устанавливаем бит в 0
//        }
//    }
//    return data.input;
//}
//
//int main() {
//    setlocale(LC_ALL, "ru");
//
//    // unsigned char
//    unsigned char ucharValue;
//    cout << "Введите значение типа unsigned char (0-255): ";
//    int tempUchar;
//    cin >> tempUchar;
//    ucharValue = static_cast<unsigned char>(tempUchar);
//
//    cout << "Двоичное представление unsigned char: ";
//    printBinary(ucharValue);
//
//    int startBit, numBits;
//    bool bitValue;
//    cout << "Введите номер старшего бита для установки (0-7): ";
//    cin >> startBit;
//    cout << "Введите количество бит для установки: ";
//    cin >> numBits;
//    cout << "Установить в 1 (1) или в 0 (0)?: ";
//    cin >> bitValue;
//
//    ucharValue = setBits(ucharValue, startBit, numBits, bitValue);
//    cout << "Изменённое значение unsigned char: " << static_cast<int>(ucharValue) << endl;
//    cout << "Двоичное представление после изменения: ";
//    printBinary(ucharValue);
//
//    // float
//    float floatValue;
//    cout << "\nВведите значение типа float: ";
//    cin >> floatValue;
//
//    //cout << "Двоичное представление после изменения: ";
//    printBinaryFloat(floatValue);
//
//    cout << "Введите номер старшего бита для установки (0-31): ";
//    cin >> startBit;
//    cout << "Введите количество бит для установки: ";
//    cin >> numBits;
//    cout << "Установить в 1 (1) или в 0 (0)?: ";
//    cin >> bitValue;
//
//    floatValue = setBits(floatValue, startBit, numBits, bitValue);
//    cout << "Изменённое значение float: " << floatValue << endl;
//    //cout << "Двоичное представление после изменения: ";
//    printBinaryFloat(floatValue);
//
//    return 0;
//}
