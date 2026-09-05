#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "HashTable.h"
#include <string>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════════
//  Class FileManager – Đọc và ghi file candidates.txt
//
//  Định dạng file: mỗi dòng là 1 thí sinh
//  examID|fullName|gender|birthDate|hometown
//  Ví dụ: 240101|Nguyễn Văn An|Nam|15/05/2005|Hà Nội
// ═══════════════════════════════════════════════════════════════════════════════
class FileManager {
private:
    string filePath;  // Đường dẫn file

public:
    explicit FileManager(const string& path = "data/candidates.txt");

    // ── Ghi toàn bộ Hash Table ra file ───────────────────────────────────────
    //   Trả về số thí sinh đã ghi, -1 nếu lỗi
    int saveToFile(const HashTable& ht) const;

    // ── Đọc file và nạp vào Hash Table ───────────────────────────────────────
    //   Trả về số thí sinh đã đọc, -1 nếu lỗi file
    int loadFromFile(HashTable& ht) const;

    // ── Getter/Setter đường dẫn ───────────────────────────────────────────────
    string getFilePath() const { return filePath; }
    void   setFilePath(const string& path) { filePath = path; }
};

#endif
