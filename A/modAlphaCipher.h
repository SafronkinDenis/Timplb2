#pragma once
#include<string>
#include<vector>
#include<map>
#include<stdexcept>

/// @brief Класс-исключение для ошибок шифрования
class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::wstring& what_arg)
        : std::invalid_argument(std::string(what_arg.begin(), what_arg.end())) {}
    explicit cipher_error(const char* what_arg)
        : std::invalid_argument(what_arg) {}
};

/// @brief Шифрование методом Гронсфельда для русского языка
class modAlphaCipher {
private:
    std::wstring numAlpha = L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    std::map<wchar_t, int> alphaNum;
    std::vector<int> key;
    
    static const unsigned MAX_KEY_LEN = 100; // Ограничение длины ключа (защита от огромных ключей)

    std::vector<int> convert(const std::wstring& s);
    std::wstring convert(const std::vector<int>& v);

    std::wstring getValidKey(const std::wstring& s);
    std::wstring getValidOpenText(const std::wstring& s);
    std::wstring getValidCipherText(const std::wstring& s);

public:
    modAlphaCipher() = delete;
    modAlphaCipher(const std::wstring& skey);
    std::wstring encrypt(const std::wstring& open_text);
    std::wstring decrypt(const std::wstring& cipher_text);
};
