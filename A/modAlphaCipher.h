#pragma once
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <codecvt>
#include <locale>

// Вспомогательная функция: превращает русский wstring в UTF-8 string для ошибок
inline std::string w_to_utf8(const std::wstring& s) {
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(s);
}

class modAlphaCipher {
private:
    std::wstring numAlpha = L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    std::map<wchar_t, int> alphaNum;
    std::vector<int> key;
    static constexpr unsigned MAX_KEY_LEN = 100;

    std::vector<int> convert(const std::wstring& s);
    std::wstring convert(const std::vector<int>& v);
    std::wstring getValidKey(const std::wstring& s);
    std::wstring getValidOpenText(const std::wstring& s);
    std::wstring getValidCipherText(const std::wstring& s);

public:
    modAlphaCipher() = delete;
    explicit modAlphaCipher(const std::wstring& skey);
    std::wstring encrypt(const std::wstring& open_text);
    std::wstring decrypt(const std::wstring& cipher_text);
};
