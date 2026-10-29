#include <iostream>
#include <locale>
#include <string>
#include <limits>
#include "modAlphaCipher.h"
using namespace std;

int main() {
    locale::global(locale("ru_RU.UTF-8"));
    wcout.imbue(locale("ru_RU.UTF-8"));
    wcin.imbue(locale("ru_RU.UTF-8"));

    wstring key;
    wstring text;
    unsigned op;

    wcout << L"Шифр Гронсфельда. Введите ключ (макс. 100 символов):";
    getline(wcin, key);

    modAlphaCipher* cipher = nullptr;
    try {
        cipher = new modAlphaCipher(key);
        wcout << L"Ключ принят\n";
    } catch (const cipher_error& e) {
        wcerr << L"Ошибка ключа: " << e.what() << L"\n";
        return 1;
    }

    do {
        wcout << L"\nВыберите действие (0-выход, 1-зашифровать, 2-расшифровать):";
        wcin >> op;
        if (op > 2) {
            wcout << L"Ошибка: недопустимая операция\n";
        } else if (op > 0) {
            wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
            wcout << L"Введите текст:";
            getline(wcin, text);

            try {
                if (op == 1) {
                    wcout << L"Зашифрованный текст: " << cipher->encrypt(text) << endl;
                } else {
                    wcout << L"Расшифрованный текст: " << cipher->decrypt(text) << endl;
                }
            } catch (const cipher_error& e) {
                wcerr << L"Ошибка: " << e.what() << L"\n";
            }
        }
    } while (op != 0);

    delete cipher;
    return 0;
}
