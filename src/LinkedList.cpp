#include "../include/LinkedList.h"
#include <iostream>
using namespace std;

// ─── Constructor / Destructor ─────────────────────────────────────────────────
LinkedList::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

LinkedList::~LinkedList() {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
}

// ─── Thêm vào cuối danh sách – O(1) nhờ tail pointer ────────────────────────
void LinkedList::insertBack(const Candidate& c) {
    Node* newNode = new Node(c);
    if (!head) { head = tail = newNode; }
    else        { tail->next = newNode; tail = newNode; }
    count++;
}

// ─── Xoá theo examID – O(n) với cập nhật tail ────────────────────────────────
bool LinkedList::remove(const string& examID) {
    if (!head) return false;

    // Trường hợp xoá node đầu
    if (head->data.examID == examID) {
        Node* del = head;
        head = head->next;
        if (!head) tail = nullptr;   // Danh sách rỗng → reset tail
        delete del;
        count--;
        return true;
    }

    // Tìm node trước node cần xoá
    Node* prev = head;
    Node* cur  = head->next;
    while (cur) {
        if (cur->data.examID == examID) {
            prev->next = cur->next;
            if (cur == tail) tail = prev;  // Xoá node cuối → cập nhật tail
            delete cur;
            count--;
            return true;
        }
        prev = cur;
        cur  = cur->next;
    }
    return false;
}

// ─── Tìm theo examID – O(n) ──────────────────────────────────────────────────
Node* LinkedList::findByID(const string& examID) const {
    Node* cur = head;
    while (cur) {
        if (cur->data.examID == examID) return cur;
        cur = cur->next;
    }
    return nullptr;
}

// ─── Tìm theo tên (gần đúng) – O(n) ─────────────────────────────────────────
void LinkedList::findByName(const string& keyword, vector<Candidate>& results) const {
    Node* cur = head;
    while (cur) {
        // Tìm trong fullName (không phân biệt hoa/thường ASCII)
        string fn = cur->data.fullName;
        string kw = keyword;
        for (char& ch : fn) if (ch>='A'&&ch<='Z') ch+=32;
        for (char& ch : kw) if (ch>='A'&&ch<='Z') ch+=32;
        if (fn.find(kw) != string::npos)
            results.push_back(cur->data);
        cur = cur->next;
    }
}

// ─── Lấy tất cả vào vector ───────────────────────────────────────────────────
void LinkedList::getAllCandidates(vector<Candidate>& out) const {
    Node* cur = head;
    while (cur) { out.push_back(cur->data); cur = cur->next; }
}

// ─── Hiển thị danh sách ──────────────────────────────────────────────────────
void LinkedList::display() const {
    if (!head) { cout << "  (Trong)\n"; return; }
    Node* cur = head;
    while (cur) { cur->data.display(); cur = cur->next; }
}
