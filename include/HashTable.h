#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "LinkedList.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════════
//  Class HashTable – Bảng băm 26 bucket (A-Z)
//  Mỗi bucket là một LinkedList chứa thí sinh có tên bắt đầu cùng chữ cái
//
//  Hash Function: index = toUpper(firstLetter_of_lastName) - 'A'  (0..25)
//  Collision resolution: Separate chaining (LinkedList)
// ═══════════════════════════════════════════════════════════════════════════════
class HashTable {
public:
    static const int TABLE_SIZE = 26;  // 26 chữ cái A-Z

private:
    LinkedList             buckets[TABLE_SIZE]; // 26 danh sách liên kết (A-Z)
    int                    totalCount;          // Tổng số thí sinh
    unordered_set<string>  idSet;              // Tra cứu ID nhanh O(1)

    // Tính hash index từ họ tên đầy đủ
    int computeIndex(const string& fullName) const;

public:
    HashTable();

    // ── Thêm thí sinh; trả về false nếu examID đã tồn tại ───────────────────
    bool add(const Candidate& c);

    // ── Xoá thí sinh theo examID; trả về false nếu không tìm thấy ─────────
    bool remove(const string& examID);

    // ── Tìm theo examID (duyệt tất cả bucket) ───────────────────────────────
    Candidate* findByID(const string& examID) const;

    // ── Tìm theo tên (gần đúng, tất cả bucket) ───────────────────────────────
    vector<Candidate> findByName(const string& keyword) const;

    // ── Lấy toàn bộ thí sinh (theo thứ tự bucket A→Z) ───────────────────────
    vector<Candidate> getAllCandidates() const;

    // ── Lấy bucket tại vị trí i (0-25) ──────────────────────────────────────
    const LinkedList& getBucket(int i) const;
    LinkedList&       getBucket(int i);

    // ── Tổng số thí sinh ──────────────────────────────────────────────────────
    int getTotalCount() const { return totalCount; }

    // ── Hiển thị thống kê phân bố ────────────────────────────────────────────
    void printStats() const;
};

#endif
