#include "modAlphaCipher.h"
#include <cwctype>

modAlphaCipher::modAlphaCipher(const std::wstring& skey) {
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(skey));
}

std::wstring modAlphaCipher::getValidKey(const std::wstring& s) {
    if (s.empty())
        throw std::invalid_argument(w_to_utf8(L"Пустой ключ"));
    
    if (s.length() > MAX_KEY_LEN)
        throw std::invalid_argument(w_to_utf8(L"Слишком длинный ключ (максимум " + std::to_wstring(MAX_KEY_LEN) + L")"));

    std::wstring tmp(s);
    for (auto& c : tmp) {
        if (!iswprint(c))
            throw std::invalid_argument(w_to_utf8(L"Непечатный символ в ключе"));
            
        if (c >= L'а' && c <= L'я') {
            c = c - L'а' + L'А';
        } else if (c < L'А' || c > L'Я') {
            throw std::invalid_argument(w_to_utf8(L"Недопустимый символ в ключе"));
        }
    }
    return tmp;
}

std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s) {
    std::wstring tmp;
    for (auto c : s) {
        if (!iswprint(c))
            throw std::invalid_argument(w_to_utf8(L"Непечатный символ в открытом тексте"));
            
        if (c >= L'А' && c <= L'Я') {
            tmp.push_back(c);
        } else if (c >= L'а' && c <= L'я') {
            tmp.push_back(c - L'а' + L'А');
        }
    }
    if (tmp.empty())
        throw std::invalid_argument(w_to_utf8(L"Пустой открытый текст после очистки"));
    return tmp;
}

std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s) {
    if (s.empty())
        throw std::invalid_argument(w_to_utf8(L"Пустой шифротекст"));
        
    for (auto c : s) {
        if (!iswprint(c))
            throw std::invalid_argument(w_to_utf8(L"Непечатный символ в шифротексте"));
            
        if (c < L'А' || c > L'Я')
            throw std::invalid_argument(w_to_utf8(L"Недопустимый символ в шифротексте"));
    }
    return s;
}

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text) {
    std::vector<int> work = convert(getValidOpenText(open_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text) {
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s) {
    std::vector<int> result;
    for (auto c : s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v) {
    std::wstring result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}
