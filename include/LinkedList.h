#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <vector>
#include <string>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════════
//  Class LinkedList – Danh sách liên kết đơn chứa Candidate
//  Được dùng làm từng bucket trong Hash Table
// ═══════════════════════════════════════════════════════════════════════════════
class LinkedList {
private:
    Node* head;   // Con trỏ đầu danh sách
    Node* tail;   // Con trỏ cuối → insertBack O(1)
    int   count;  // Số phần tử

public:
    LinkedList();
    ~LinkedList();

    // ── Không cho phép copy (tránh double-free) ──────────────────────────────
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    // ── Thêm thí sinh vào cuối danh sách ─────────────────────────────────────
    void insertBack(const Candidate& c);

    // ── Xoá thí sinh theo examID; trả về true nếu xoá thành công ─────────────
    bool remove(const string& examID);

    // ── Tìm theo examID; trả về con trỏ Node hoặc nullptr ───────────────────
    Node* findByID(const string& examID) const;

    // ── Tìm theo tên (gần đúng); kết quả thêm vào vector results ─────────────
    void findByName(const string& keyword, vector<Candidate>& results) const;

    // ── Lấy toàn bộ thí sinh vào vector ──────────────────────────────────────
    void getAllCandidates(vector<Candidate>& out) const;

    // ── Hiển thị danh sách (dùng bảng định dạng) ─────────────────────────────
    void display() const;

    // ── Accessors ─────────────────────────────────────────────────────────────
    Node* getHead()  const { return head; }
    int   getCount() const { return count; }
    bool  isEmpty()  const { return head == nullptr; }
};

#endif
