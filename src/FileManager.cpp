#include "../include/FileManager.h"
#include "../include/Utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

FileManager::FileManager(const string& path) : filePath(path) {}

// ─── Ghi toàn bộ Hash Table ra file ─────────────────────────────────────────
int FileManager::saveToFile(const HashTable& ht) const {
    ofstream file(filePath);
    if (!file.is_open()) {
        cerr << "  [LOI] Khong mo duoc file de ghi: " << filePath << endl;
        return -1;
    }

    int count = 0;
    // Ghi theo thứ tự bucket A→Z để file có tổ chức
    for (int i = 0; i < HashTable::TABLE_SIZE; i++) {
        const LinkedList& bucket = ht.getBucket(i);
        Node* cur = bucket.getHead();
        while (cur) {
            file << cur->data.toFileString() << "\n";
            count++;
            cur = cur->next;
        }
    }
    file.close();
    return count;
}

// ─── Đọc file và nạp vào Hash Table ─────────────────────────────────────────
int FileManager::loadFromFile(HashTable& ht) const {
    ifstream file(filePath);
    if (!file.is_open()) {
        // File chưa tồn tại – không phải lỗi
        return 0;
    }

    int count = 0, skipped = 0;
    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        lineNum++;
        line = Utils::trim(line);
        if (line.empty() || line[0] == '#') continue;  // Bỏ qua dòng trống/comment

        vector<string> parts = Utils::split(line, '|');
        if (parts.size() != 5) {
            cerr << "  [CANH BAO] Dong " << lineNum << " sai dinh dang, bo qua.\n";
            skipped++;
            continue;
        }

        Candidate c(
            Utils::trim(parts[0]),  // examID
            Utils::normalizeName(parts[1]),  // fullName (chuẩn hoá)
            Utils::trim(parts[2]),  // gender
            Utils::trim(parts[3]),  // birthDate
            Utils::trim(parts[4])   // hometown
        );

        if (c.examID.empty()) { skipped++; continue; }

        if (!ht.add(c)) {
            cerr << "  [CANH BAO] Dong " << lineNum
                 << ": Ma '" << c.examID << "' bi trung, bo qua.\n";
            skipped++;
        } else {
            count++;
        }
    }
    file.close();

    if (skipped > 0)
        cout << "  Da bo qua " << skipped << " dong loi.\n";
    return count;
}
