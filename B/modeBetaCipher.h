#pragma once
#include<string>
#include<stdexcept>

/// @brief Класс-исключение для ошибок шифра маршрутной перестановки
class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::wstring& what_arg)
        : std::invalid_argument(std::string(what_arg.begin(), what_arg.end())) {}
    explicit cipher_error(const char* what_arg)
        : std::invalid_argument(what_arg) {}
};

/// @brief Шифр табличной маршрутной перестановки
class modeBetaCipher {
private:
    unsigned cols;
    static const unsigned MAX_KEY = 100; // Максимальный размер ключа

    std::wstring getValidOpenText(const std::wstring& s);
    std::wstring getValidCipherText(const std::wstring& s);

public:
    modeBetaCipher(unsigned key);
    std::wstring encrypt(const std::wstring& text);
    std::wstring decrypt(const std::wstring& text);
};
