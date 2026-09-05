#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include "Room.h"
#include "HashTable.h"
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════════
//  Class RoomManager – Phân bổ thí sinh vào n phòng thi
//
//  Thuật toán: Round-Robin Distribution
//  ─ Duyệt từng bucket A→Z trong Hash Table
//  ─ Với mỗi thí sinh trong bucket, gán vào phòng hiện tại rồi xoay vòng
//  ─ Kết quả: thí sinh cùng chữ cái đầu được rải đều sang các phòng khác nhau
//  ─ Xác suất trùng chữ cái đầu trong 1 phòng là nhỏ nhất
//
//  Độ phức tạp: O(n) với n là tổng số thí sinh
// ═══════════════════════════════════════════════════════════════════════════════
class RoomManager {
public:
    // Tạo n phòng và phân bổ thí sinh theo Round-Robin
    static vector<Room> assignRooms(const HashTable& ht, int n);

    // Hiển thị danh sách tất cả phòng
    static void displayRooms(const vector<Room>& rooms);

    // Thống kê số thí sinh mỗi phòng
    static void printSummary(const vector<Room>& rooms);
};

#endif
