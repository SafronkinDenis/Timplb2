#include "modeBetaCipher.h"
#include <vector>
#include <cwctype>
using namespace std;

modeBetaCipher::modeBetaCipher(unsigned key) {
    if (key < 2) {
        throw cipher_error(L"Ключ должен быть >= 2");
    }
    if (key > MAX_KEY) {
        throw cipher_error(L"Слишком большой ключ (максимум " + to_wstring(MAX_KEY) + L")");
    }
    cols = key;
}

std::wstring modeBetaCipher::getValidOpenText(const std::wstring& s) {
    std::wstring tmp;
    for (auto c : s) {
        if (!iswprint(c)) {
            throw cipher_error(L"Непечатный символ в тексте");
        }
        if (c >= L'А' && c <= L'Я') {
            tmp.push_back(c);
        } else if (c >= L'а' && c <= L'я') {
            tmp.push_back(c - L'а' + L'А');
        }
    }
    if (tmp.empty())
        throw cipher_error(L"Пустой открытый текст после очистки");
    return tmp;
}

std::wstring modeBetaCipher::getValidCipherText(const std::wstring& s) {
    if (s.empty())
        throw cipher_error(L"Пустой шифротекст");
    for (auto c : s) {
        if (!iswprint(c)) {
            throw cipher_error(L"Непечатный символ в шифротексте");
        }
        if (c < L'А' || c > L'Я')
            throw cipher_error(L"Недопустимый символ в шифротексте");
    }
    return s;
}

wstring modeBetaCipher::encrypt(const wstring& text) {
    wstring validText = getValidOpenText(text);
    unsigned n = validText.size();
    unsigned rows = (n + cols - 1) / cols;
    vector<vector<wchar_t>> table(rows, vector<wchar_t>(cols, L'_'));

    unsigned k = 0;
    for (unsigned r = 0; r < rows; r++) {
        for (unsigned c = 0; c < cols; c++) {
            if (k < n)
                table[r][c] = validText[k++];
        }
    }

    wstring result;
    for (int c = cols - 1; c >= 0; c--) {
        for (unsigned r = 0; r < rows; r++) {
            if (table[r][c] != L'_')
                result.push_back(table[r][c]);
        }
    }
    return result;
}

wstring modeBetaCipher::decrypt(const wstring& text) {
    wstring validText = getValidCipherText(text);
    unsigned n = validText.size();
    unsigned rows = (n + cols - 1) / cols;
    unsigned fullCols = n % cols;

    vector<unsigned> colHeights(cols, rows);
    if (fullCols != 0) {
        for (unsigned c = 0; c < cols - fullCols; c++) {
            colHeights[cols - 1 - c]--;
        }
    }

    vector<vector<wchar_t>> table(rows, vector<wchar_t>(cols, L'_'));

    unsigned k = 0;
    for (int c = cols - 1; c >= 0; c--) {
        for (unsigned r = 0; r < colHeights[c]; r++) {
            table[r][c] = validText[k++];
        }
    }

    wstring result;
    for (unsigned r = 0; r < rows; r++) {
        for (unsigned c = 0; c < cols; c++) {
            if (table[r][c] != L'_')
                result.push_back(table[r][c]);
        }
    }
    return result;
}
