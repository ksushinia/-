#include <iostream>
#include <cmath>  // ��� floor()

using namespace std;

// ����� ��������� ������������� unsigned char
void printBinary(unsigned char value) {
    for (int i = sizeof(unsigned char) * 8 - 1; i >= 0; --i) {
        cout << ((value >> i) & 1); //����� ������ (�� �������� � ��������)
    }
    cout << endl;
}

// ����� ��������� ������������� ������ �����
void printBinary(int value) {
    for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
        cout << ((value >> i) & 1);
    }
    cout << endl;
}

// ��� ������ ��������� ������������� float � �������� ����� �������
void printBinaryFloat(float value) {
    union {
        float input;
        uint32_t bits; // ��� ������� � float ��� � ������ �����
    } data;
    data.input = value;

    cout << "�������� ������������� float: ";
    for (int i = 31; i >= 0; --i) {
        cout << ((data.bits >> i) & 1);
        if (i == 31 - 8) {
            cout << ' ';  // ������ ����� �����������
        }
        if (i == 31 - 8 - 23) {
            cout << ' ';  // ������ ����� ���������
        }
    }
    cout << endl;
}

// ��������� ����� � unsigned char
unsigned char setBits(unsigned char value, int startBit, int numBits, bool bitValue) {
    for (int i = startBit; i > startBit - numBits; --i) {
        if (bitValue) {
            value |= (1 << i);   // ������������� ��� � 1
        }
        else {
            value &= ~(1 << i);  // ������������� ��� � 0
        }
    }
    return value;
}

// ��������� ����� � float
float setBits(float value, int startBit, int numBits, bool bitValue) {
    union {
        float input;
        uint32_t bits;
    } data;
    data.input = value;

    for (int i = startBit; i > startBit - numBits; --i) {
        if (bitValue) {
            data.bits |= (1 << i);   // ������������� ��� � 1
        }
        else {
            data.bits &= ~(1 << i);  // ������������� ��� � 0
        }
    }
    return data.input;
}

int main() {
    setlocale(LC_ALL, "ru");

    // unsigned char
    unsigned char ucharValue;
    cout << "������� ������ ��� ����� ��� ���� unsigned char: ";
    char tempChar;
    cin >> tempChar;

    if (isdigit(tempChar)) {
        ucharValue = static_cast<unsigned char>(tempChar - '0');  // ���� ������� �����
    }
    else {
        ucharValue = static_cast<unsigned char>(tempChar);  // ���� ����� ������
    }

    cout << "�������� ������������� unsigned char: ";
    printBinary(ucharValue);

    int startBit, numBits;
    bool bitValue;
    cout << "������� ����� �������� ���� ��� ��������� (0-7): ";
    cin >> startBit;
    cout << "������� ���������� ��� ��� ���������: ";
    cin >> numBits;
    cout << "���������� � 1 (1) ��� � 0 (0)?: ";
    cin >> bitValue;

    ucharValue = setBits(ucharValue, startBit, numBits, bitValue);
    cout << "��������� �������� unsigned char (��� ������): '" << ucharValue << "'" << endl;
    cout << "�������� ������������� ����� ���������: ";
    printBinary(ucharValue);

    // float
    float floatValue;
    cout << "\n������� �������� ���� float: ";
    cin >> floatValue;

    printBinaryFloat(floatValue);

    cout << "������� ����� �������� ���� ��� ��������� (0-31): ";
    cin >> startBit;
    cout << "������� ���������� ��� ��� ���������: ";
    cin >> numBits;
    cout << "���������� � 1 (1) ��� � 0 (0)?: ";
    cin >> bitValue;

    floatValue = setBits(floatValue, startBit, numBits, bitValue);
    cout << "��������� �������� float: " << floatValue << endl;
    printBinaryFloat(floatValue);

    return 0;
}
//#include <iostream>
//#include <cmath>  // ��� floor()
//
//using namespace std;
//
//// ����� ��������� ������������� unsigned char
//void printBinary(unsigned char value) {
//    for (int i = sizeof(unsigned char) * 8 - 1; i >= 0; --i) {
//        cout << ((value >> i) & 1); //����� ������ (�� �������� � ��������)
//    }
//    cout << endl;
//}
//
//// ����� ��������� ������������� ������ �����
//void printBinary(int value) {
//    for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
//        cout << ((value >> i) & 1);
//    }
//    cout << endl;
//}
//
//// ��� ������ ��������� ������������� float � �������� ����� �������
//void printBinaryFloat(float value) {
//    union {
//        float input;
//        uint32_t bits; // ��� ������� � float ��� � ������ �����
//    } data;
//    data.input = value;
//
//    cout << "�������� ������������� float: ";
//    for (int i = 31; i >= 0; --i) {
//        cout << ((data.bits >> i) & 1);
//        if (i == 31 - 8) {
//            cout << ' ';  // ������ ����� �����������
//        }
//        if (i == 31 - 8 - 23) {
//            cout << ' ';  // ������ ����� ���������
//        }
//    }
//    cout << endl;
//}
//
//// ��������� ����� � unsigned char
//unsigned char setBits(unsigned char value, int startBit, int numBits, bool bitValue) {
//    for (int i = startBit; i > startBit - numBits; --i) {
//        if (bitValue) {
//            value |= (1 << i);   // ������������� ��� � 1
//        }
//        else {
//            value &= ~(1 << i);  // ������������� ��� � 0
//        }
//    }
//    return value;
//}
//
//// ��������� ����� � float
//float setBits(float value, int startBit, int numBits, bool bitValue) {
//    union {
//        float input;
//        uint32_t bits;
//    } data;
//    data.input = value;
//
//    for (int i = startBit; i > startBit - numBits; --i) {
//        if (bitValue) {
//            data.bits |= (1 << i);   // ������������� ��� � 1
//        }
//        else {
//            data.bits &= ~(1 << i);  // ������������� ��� � 0
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
//    cout << "������� ������ ��� ����� ��� ���� unsigned char: ";
//    char tempChar;
//    cin >> tempChar;
//
//    if (isdigit(tempChar)) {
//        ucharValue = static_cast<unsigned char>(tempChar - '0');  // ���� ������� �����
//    }
//    else {
//        ucharValue = static_cast<unsigned char>(tempChar);  // ���� ����� ������
//    }
//
//    cout << "�������� ������������� unsigned char: ";
//    printBinary(ucharValue);
//
//    int startBit, numBits;
//    bool bitValue;
//    cout << "������� ����� �������� ���� ��� ��������� (0-7): ";
//    cin >> startBit;
//    cout << "������� ���������� ��� ��� ���������: ";
//    cin >> numBits;
//    cout << "���������� � 1 (1) ��� � 0 (0)?: ";
//    cin >> bitValue;
//
//    ucharValue = setBits(ucharValue, startBit, numBits, bitValue);
//    cout << "��������� �������� unsigned char: " << static_cast<int>(ucharValue) << endl;
//    cout << "�������� ������������� ����� ���������: ";
//    printBinary(ucharValue);
//
//    // float
//    float floatValue;
//    cout << "\n������� �������� ���� float: ";
//    cin >> floatValue;
//
//    printBinaryFloat(floatValue);
//
//    cout << "������� ����� �������� ���� ��� ��������� (0-31): ";
//    cin >> startBit;
//    cout << "������� ���������� ��� ��� ���������: ";
//    cin >> numBits;
//    cout << "���������� � 1 (1) ��� � 0 (0)?: ";
//    cin >> bitValue;
//
//    floatValue = setBits(floatValue, startBit, numBits, bitValue);
//    cout << "��������� �������� float: " << floatValue << endl;
//    printBinaryFloat(floatValue);
//
//    return 0;
//}//#include <iostream>
//#include <cmath>  // ��� floor()
//
//using namespace std;
//
//// ����� ��������� ������������� unsigned char
//void printBinary(unsigned char value) {
//    for (int i = sizeof(unsigned char) * 8 - 1; i >= 0; --i) { 
//        cout << ((value >> i) & 1); //����� ������ (�� �������� � ��������)
//    }
//    cout << endl;
//}
//
//// ����� ��������� ������������� ������ �����
//void printBinary(int value) {
//    for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
//        cout << ((value >> i) & 1);
//    }
//    cout << endl;
//}
//
//// ��� ������ ��������� ������������� float � �������� ����� �������
//void printBinaryFloat(float value) {
//    union {
//        float input;
//        uint32_t bits; // ��� ������� � float ��� � ������ �����
//    } data;
//    data.input = value;
//
//    cout << "�������� ������������� float: ";
//    for (int i = 31; i >= 0; --i) {
//        cout << ((data.bits >> i) & 1);
//        if (i == 31 - 8) {
//            cout << ' ';  // ������ ����� �����������
//        }
//        if (i == 31 - 8 - 23) {
//            cout << ' ';  // ������ ����� ���������
//        }
//    }
//    cout << endl;
//}
//
//// ��������� ����� � unsigned char
//unsigned char setBits(unsigned char value, int startBit, int numBits, bool bitValue) {
//    for (int i = startBit; i > startBit - numBits; --i) {
//        if (bitValue) {
//            value |= (1 << i);   // ������������� ��� � 1
//        }
//        else {
//            value &= ~(1 << i);  // ������������� ��� � 0
//        }
//    }
//    return value;
//}
//
//// ��������� ����� � float
//float setBits(float value, int startBit, int numBits, bool bitValue) {
//    union {
//        float input;
//        uint32_t bits;
//    } data;
//    data.input = value;
//
//    for (int i = startBit; i > startBit - numBits; --i) {
//        if (bitValue) {
//            data.bits |= (1 << i);   // ������������� ��� � 1
//        }
//        else {
//            data.bits &= ~(1 << i);  // ������������� ��� � 0
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
//    cout << "������� �������� ���� unsigned char (0-255): ";
//    int tempUchar;
//    cin >> tempUchar;
//    ucharValue = static_cast<unsigned char>(tempUchar);
//
//    cout << "�������� ������������� unsigned char: ";
//    printBinary(ucharValue);
//
//    int startBit, numBits;
//    bool bitValue;
//    cout << "������� ����� �������� ���� ��� ��������� (0-7): ";
//    cin >> startBit;
//    cout << "������� ���������� ��� ��� ���������: ";
//    cin >> numBits;
//    cout << "���������� � 1 (1) ��� � 0 (0)?: ";
//    cin >> bitValue;
//
//    ucharValue = setBits(ucharValue, startBit, numBits, bitValue);
//    cout << "��������� �������� unsigned char: " << static_cast<int>(ucharValue) << endl;
//    cout << "�������� ������������� ����� ���������: ";
//    printBinary(ucharValue);
//
//    // float
//    float floatValue;
//    cout << "\n������� �������� ���� float: ";
//    cin >> floatValue;
//
//    //cout << "�������� ������������� ����� ���������: ";
//    printBinaryFloat(floatValue);
//
//    cout << "������� ����� �������� ���� ��� ��������� (0-31): ";
//    cin >> startBit;
//    cout << "������� ���������� ��� ��� ���������: ";
//    cin >> numBits;
//    cout << "���������� � 1 (1) ��� � 0 (0)?: ";
//    cin >> bitValue;
//
//    floatValue = setBits(floatValue, startBit, numBits, bitValue);
//    cout << "��������� �������� float: " << floatValue << endl;
//    //cout << "�������� ������������� ����� ���������: ";
//    printBinaryFloat(floatValue);
//
//    return 0;
//}
