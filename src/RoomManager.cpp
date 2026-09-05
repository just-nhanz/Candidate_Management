#include "../include/RoomManager.h"
#include <iostream>
#include <iomanip>
#include <set>
using namespace std;

// ─── Phân phòng theo thuật toán Round-Robin ─────────────────────────────────
//
//  Ý tưởng: Duyệt từng bucket A→Z, trong mỗi bucket duyệt từng thí sinh.
//  Gán thí sinh vào phòng[currentRoom % n], sau đó tăng currentRoom.
//  → Các thí sinh cùng chữ cái đầu được rải đều vào các phòng khác nhau.
//  → Xác suất 2 thí sinh cùng chữ cái đầu ngồi cùng phòng = min(1, k/n)
//     với k = số thí sinh có cùng chữ cái đầu.
//
vector<Room> RoomManager::assignRooms(const HashTable& ht, int n) {
    // Khởi tạo n phòng (đánh số từ 1)
    vector<Room> rooms;
    rooms.reserve(n);
    for (int i = 1; i <= n; i++) rooms.emplace_back(i);

    int currentRoom = 0;  // Chỉ số phòng hiện tại (vòng tròn 0..n-1)

    // Duyệt 26 bucket A→Z
    for (int i = 0; i < HashTable::TABLE_SIZE; i++) {
        const LinkedList& bucket = ht.getBucket(i);
        if (bucket.isEmpty()) continue;

        // Duyệt từng node trong bucket
        Node* cur = bucket.getHead();
        while (cur) {
            rooms[currentRoom % n].addCandidate(cur->data);
            currentRoom++;
            cur = cur->next;
        }
    }
    return rooms;
}

// ─── Hiển thị danh sách tất cả phòng ────────────────────────────────────────
void RoomManager::displayRooms(const vector<Room>& rooms) {
    cout << "\n╔══════════════════════════════════════════════════════════════╗\n";
    cout <<   "║                   KET QUA PHAN PHONG THI                    ║\n";
    cout <<   "╚══════════════════════════════════════════════════════════════╝\n";

    for (const Room& room : rooms) {
        room.display();
    }
    printSummary(rooms);
}

// ─── Thống kê ─────────────────────────────────────────────────────────────────
void RoomManager::printSummary(const vector<Room>& rooms) {
    cout << "\n┌─── Tong ket phan phong ──────────────────────────┐\n";
    for (const Room& r : rooms) {
        // Đếm số chữ cái đầu khác nhau trong phòng
        set<char> letters;
        for (const Candidate& c : r.candidates) {
            string fn = Utils::getFirstName(c.fullName);
            letters.insert(Utils::getBaseChar(fn));
        }
        cout << "│  Phong " << setw(3) << r.roomNumber
             << ": " << setw(4) << r.getCount() << " thi sinh"
             << "  |  " << letters.size() << " chu cai dau khac nhau";

        // Liệt kê các chữ cái đầu có trong phòng
        cout << " (";
        bool first = true;
        for (char c : letters) { if (!first) cout << ","; cout << c; first = false; }
        cout << ")\n";
    }
    cout << "└──────────────────────────────────────────────────┘\n";
}

// ─── Room::display() ─────────────────────────────────────────────────────────
void Room::display() const {
    cout << "\n┌─── PHONG " << roomNumber
         << " ─── (" << getCount() << " thi sinh) ────────────────────────\n";
    if (candidates.empty()) { cout << "│  (Khong co thi sinh)\n"; return; }
    Candidate::printHeader();
    for (const Candidate& c : candidates) c.display();
    Candidate::printSeparator();
}
