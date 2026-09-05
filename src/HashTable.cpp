#include "../include/HashTable.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ─── Constructor ──────────────────────────────────────────────────────────────
HashTable::HashTable() : totalCount(0) {}

// ─── Tính hash index từ fullName ─────────────────────────────────────────────
int HashTable::computeIndex(const string& fullName) const {
    string firstName = Utils::getFirstName(fullName);   // Lấy tên (từ cuối)
    char   base      = Utils::getBaseChar(firstName);   // Chữ cái cơ bản A-Z
    return Utils::hashIndex(base);                      // Chuyển sang 0-25
}

// ─── Thêm thí sinh – O(1) trung bình ─────────────────────────────────────
bool HashTable::add(const Candidate& c) {
    // Kiểm tra trùng bằng unordered_set → O(1)
    if (idSet.count(c.examID)) return false;

    int idx = computeIndex(c.fullName);
    buckets[idx].insertBack(c);
    idSet.insert(c.examID);
    totalCount++;
    return true;
}

// ─── Xoá thí sinh – O(n/26) trong bucket ──────────────────────────────────
bool HashTable::remove(const string& examID) {
    if (!idSet.count(examID)) return false;   // O(1) check nhanh

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (buckets[i].remove(examID)) {
            idSet.erase(examID);
            totalCount--;
            return true;
        }
    }
    return false;
}

// ─── Tìm theo examID – O(n/26) trong bucket ───────────────────────────────
Candidate* HashTable::findByID(const string& examID) const {
    if (!idSet.count(examID)) return nullptr;  // O(1) check trước
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* found = buckets[i].findByID(examID);
        if (found) return &(found->data);
    }
    return nullptr;
}

// ─── Tìm theo tên (duyệt tất cả bucket) ────────────────────────────────────
vector<Candidate> HashTable::findByName(const string& keyword) const {
    vector<Candidate> results;
    for (int i = 0; i < TABLE_SIZE; i++)
        buckets[i].findByName(keyword, results);
    return results;
}

// ─── Lấy tất cả thí sinh ────────────────────────────────────────────────────
vector<Candidate> HashTable::getAllCandidates() const {
    vector<Candidate> all;
    all.reserve(totalCount);
    for (int i = 0; i < TABLE_SIZE; i++)
        buckets[i].getAllCandidates(all);
    return all;
}

// ─── Accessors bucket ────────────────────────────────────────────────────────
const LinkedList& HashTable::getBucket(int i) const { return buckets[i]; }
LinkedList&       HashTable::getBucket(int i)       { return buckets[i]; }

// ─── In thống kê phân bố ─────────────────────────────────────────────────────
void HashTable::printStats() const {
    cout << "\n╔══════════════════════════════════════════════════════╗\n";
    cout <<   "║          THONG KE BANG BAM (HASH TABLE STATS)       ║\n";
    cout <<   "╠════════╦════════════╦═════════════════════════════════╣\n";
    cout <<   "║ Bucket ║ So thi sinh║ Bieu do                         ║\n";
    cout <<   "╠════════╬════════════╬═════════════════════════════════╣\n";

    int groupCount = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        int cnt = buckets[i].getCount();
        if (cnt == 0) continue;
        groupCount++;
        char letter = (char)('A' + i);
        string bar(min(cnt, 30), '#');
        cout << right
             << "║   [" << letter << "]  ║ " << setw(10) << cnt
             << " ║ " << left << setw(31) << bar << right << "║\n";
    }
    cout << "╠════════╩════════════╩═════════════════════════════════╣\n";
    // Dòng tổng kết với độ rộng chuẩn
    string summary = "  Tong: " + to_string(totalCount)
                   + " thi sinh trong " + to_string(groupCount) + " nhom";
    // Pad to width 52
    summary.resize(52, ' ');
    cout << "║" << summary << "║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n";
}
