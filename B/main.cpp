#include <iostream>
#include <locale>
#include <limits>
#include <string>
#include <cwctype>
#include "modeBetaCipher.h"
using namespace std;

int main() {
    locale::global(locale("ru_RU.UTF-8"));
    wcout.imbue(locale("ru_RU.UTF-8"));
    wcin.imbue(locale("ru_RU.UTF-8"));

    unsigned key;
    wstring text;
    unsigned op;

    wcout << L"Шифр маршрутной перестановки\n";
    wcout << L"Введите ключ (количество столбцов, 2-100):";
    wcin >> key;

    modeBetaCipher* cipher = nullptr;
    try {
        cipher = new modeBetaCipher(key);
        wcout << L"Ключ принят\n";
    } catch (const cipher_error& e) {
        wcerr << L"Ошибка ключа: " << e.what() << L"\n";
        return 1;
    }

    do {
        wcout << L"\nВыберите действие (0-выход, 1-шифрование, 2-дешифрование):";
        wcin >> op;
        if (op > 2) {
            wcout << L"Ошибка: недопустимая операция\n";
        } else if (op > 0) {
            wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
            wcout << L"Введите текст (русскими буквами):";
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
