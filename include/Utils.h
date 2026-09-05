#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <cstdint>
using namespace std;

namespace Utils {

// ─── Trim khoảng trắng đầu/cuối ──────────────────────────────────────────────
inline string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// ─── Xoá khoảng trắng thừa giữa các từ ──────────────────────────────────────
inline string removeExtraSpaces(const string& s) {
    string result;
    bool prevSpace = false;
    for (char c : s) {
        if (c == ' ') {
            if (!prevSpace && !result.empty()) { result += c; prevSpace = true; }
        } else { result += c; prevSpace = false; }
    }
    return result;
}

// ─── Chuyển ký tự đầu tiên của tên → chữ cái cơ bản A-Z (hỗ trợ UTF-8) ─────
inline char getBaseChar(const string& firstName) {
    if (firstName.empty()) return 'A';
    unsigned char b0 = (unsigned char)firstName[0];

    // ASCII
    if (b0 < 0x80) {
        if (b0 >= 'a' && b0 <= 'z') return (char)(b0 - 32);
        if (b0 >= 'A' && b0 <= 'Z') return (char)b0;
        return 'A';
    }

    // 2-byte UTF-8
    if ((b0 & 0xE0) == 0xC0 && firstName.size() >= 2) {
        unsigned char b1 = (unsigned char)firstName[1];
        uint32_t cp = ((b0 & 0x1F) << 6) | (b1 & 0x3F);
        if (cp>=0xC0&&cp<=0xC5)  return 'A'; // À Á Â Ã Ä Å
        if (cp>=0xE0&&cp<=0xE5)  return 'A'; // à á â ã ä å
        if (cp==0x100||cp==0x101) return 'A'; // Ā ā
        if (cp==0x102||cp==0x103) return 'A'; // Ă ă
        if (cp==0x110||cp==0x111) return 'D'; // Đ đ  ← quan trọng với tên Việt
        if (cp>=0xC8&&cp<=0xCB)  return 'E'; // È É Ê Ë
        if (cp>=0xE8&&cp<=0xEB)  return 'E'; // è é ê ë
        if (cp>=0xCC&&cp<=0xCF)  return 'I'; // Ì Í Î Ï
        if (cp>=0xEC&&cp<=0xEF)  return 'I'; // ì í î ï
        if (cp>=0xD2&&cp<=0xD6)  return 'O'; // Ò Ó Ô Õ Ö
        if (cp>=0xF2&&cp<=0xF6)  return 'O'; // ò ó ô õ ö
        if (cp==0x1A0||cp==0x1A1) return 'O'; // Ơ ơ
        if (cp>=0xD9&&cp<=0xDC)  return 'U'; // Ù Ú Û Ü
        if (cp>=0xF9&&cp<=0xFC)  return 'U'; // ù ú û ü
        if (cp==0x1AF||cp==0x1B0) return 'U'; // Ư ư
        if (cp==0xDD||cp==0xFD)  return 'Y'; // Ý ý
    }

    // 3-byte UTF-8: Latin Extended Additional (tổ hợp dấu tiếng Việt)
    if ((b0 & 0xF0) == 0xE0 && firstName.size() >= 3) {
        unsigned char b1 = (unsigned char)firstName[1];
        unsigned char b2 = (unsigned char)firstName[2];
        uint32_t cp = ((b0 & 0x0F) << 12) | ((b1 & 0x3F) << 6) | (b2 & 0x3F);
        if (cp >= 0x1EA0 && cp <= 0x1EB7) return 'A'; // Ạ ạ Ả ả Ấ ấ ... Ặ ặ
        if (cp >= 0x1EB8 && cp <= 0x1EC7) return 'E'; // Ẹ ẹ Ẻ ẻ ... Ệ ệ
        if (cp >= 0x1EC8 && cp <= 0x1ECB) return 'I'; // Ỉ ỉ Ị ị
        if (cp >= 0x1ECC && cp <= 0x1EE3) return 'O'; // Ọ ọ Ỏ ỏ ... Ợ ợ
        if (cp >= 0x1EE4 && cp <= 0x1EF1) return 'U'; // Ụ ụ Ủ ủ ... Ự ự
        if (cp >= 0x1EF2 && cp <= 0x1EF9) return 'Y'; // Ỳ ỳ Ỵ ỵ Ỷ ỷ Ỹ ỹ
    }
    return 'A';
}

// ─── Hash index 0-25 từ char A-Z ─────────────────────────────────────────────
inline int hashIndex(char c) {
    if (c < 'A' || c > 'Z') return 0;
    return c - 'A';
}

// ─── Lấy tên (từ cuối cùng) từ họ tên đầy đủ ────────────────────────────────
inline string getFirstName(const string& fullName) {
    string s = trim(fullName);
    if (s.empty()) return s;
    size_t pos = string::npos;
    for (int i = (int)s.size() - 1; i >= 0; i--)
        if (s[i] == ' ') { pos = (size_t)i; break; }
    if (pos == string::npos) return s;
    return s.substr(pos + 1);
}

// ─── Viết hoa ký tự đầu của 1 từ (hỗ trợ UTF-8) ────────────────────────────
inline string capitalizeWord(const string& word) {
    if (word.empty()) return word;
    unsigned char b0 = (unsigned char)word[0];
    string result = word;
    if (b0 >= 'a' && b0 <= 'z') { result[0] = (char)(b0 - 32); return result; }
    if (b0 == 0xC4 && word.size() >= 2 && (unsigned char)word[1] == 0x91)
        { result[1] = 0x90; return result; } // đ→Đ
    if ((b0 & 0xE0) == 0xC0 && word.size() >= 2) {
        unsigned char b1 = (unsigned char)word[1];
        uint32_t cp = ((b0 & 0x1F) << 6) | (b1 & 0x3F);
        if (cp % 2 == 1) {
            uint32_t uc = cp - 1;
            result[0] = (char)(0xC0 | (uc >> 6));
            result[1] = (char)(0x80 | (uc & 0x3F));
        }
    }
    if ((b0 & 0xF0) == 0xE0 && word.size() >= 3) {
        unsigned char b1 = (unsigned char)word[1];
        unsigned char b2 = (unsigned char)word[2];
        uint32_t cp = ((b0 & 0x0F) << 12) | ((b1 & 0x3F) << 6) | (b2 & 0x3F);
        if (cp >= 0x1E00 && cp <= 0x1EFF && cp % 2 == 1) {
            uint32_t uc = cp - 1;
            result[0] = (char)(0xE0 | (uc >> 12));
            result[1] = (char)(0x80 | ((uc >> 6) & 0x3F));
            result[2] = (char)(0x80 | (uc & 0x3F));
        }
    }
    return result;
}

// ─── Viết hoa chữ cái đầu mỗi từ (xử lý UTF-8 multi-byte) ──────────────────
inline string capitalizeWords(const string& s) {
    string result;
    bool newWord = true;
    size_t i = 0;
    while (i < s.size()) {
        char c = s[i];
        if (c == ' ') { result += c; newWord = true; i++; continue; }
        // Xác định độ dài ký tự UTF-8
        unsigned char b = (unsigned char)c;
        size_t charLen = 1;
        if ((b & 0xF0) == 0xE0) charLen = 3;
        else if ((b & 0xE0) == 0xC0) charLen = 2;
        string ch = s.substr(i, charLen);
        if (newWord) { result += capitalizeWord(ch); newWord = false; }
        else         { result += ch; }
        i += charLen;
    }
    return result;
}

// ─── Chuẩn hoá họ tên đầy đủ ────────────────────────────────────────────────
inline string normalizeName(const string& name) {
    return capitalizeWords(removeExtraSpaces(trim(name)));
}

// ─── Tìm kiếm gần đúng (so sánh byte, không phân biệt hoa/thường ASCII) ─────
inline bool containsIgnoreCase(const string& text, const string& keyword) {
    if (keyword.empty()) return true;
    string t = text, k = keyword;
    for (char& ch : t) if (ch >= 'A' && ch <= 'Z') ch += 32;
    for (char& ch : k) if (ch >= 'A' && ch <= 'Z') ch += 32;
    return t.find(k) != string::npos;
}

// ─── Split chuỗi theo delimiter ──────────────────────────────────────────────
inline vector<string> split(const string& s, char delim) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delim)) tokens.push_back(token);
    return tokens;
}

} // namespace Utils
#endif
