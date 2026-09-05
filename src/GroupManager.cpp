#include "../include/GroupManager.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ─── Hiển thị tất cả nhóm có thí sinh ───────────────────────────────────────
void GroupManager::displayAllGroups(const HashTable& ht) {
    cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
    cout <<   "║            DANH SACH THI SINH THEO NHOM CHU CAI DAU         ║\n";
    cout <<   "╚══════════════════════════════════════════════════════════════╝\n";

    bool anyGroup = false;
    for (int i = 0; i < HashTable::TABLE_SIZE; i++) {
        const LinkedList& bucket = ht.getBucket(i);
        if (bucket.isEmpty()) continue;
        anyGroup = true;

        char letter = (char)('A' + i);
        cout << "\n┌─── Nhom [" << letter << "] ─── (" << bucket.getCount() << " thi sinh) ───\n";
        Candidate::printHeader();
        bucket.display();
        Candidate::printSeparator();
    }

    if (!anyGroup) cout << "  (Chua co thi sinh nao trong he thong)\n";
    cout << "\nTong cong: " << ht.getTotalCount() << " thi sinh.\n";
}

// ─── Hiển thị nhóm cụ thể theo chữ cái ──────────────────────────────────────
void GroupManager::displayGroup(const HashTable& ht, char letter) {
    letter = toupper((unsigned char)letter);
    if (letter < 'A' || letter > 'Z') {
        cout << "  Chu cai khong hop le!\n"; return;
    }
    int idx = letter - 'A';
    const LinkedList& bucket = ht.getBucket(idx);

    cout << "\n--- Nhom [" << letter << "] --- (" << bucket.getCount() << " thi sinh) ---\n";
    if (bucket.isEmpty()) { cout << "  (Khong co thi sinh nao trong nhom nay)\n"; return; }
    Candidate::printHeader();
    bucket.display();
    Candidate::printSeparator();
}
