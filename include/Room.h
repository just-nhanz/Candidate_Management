#ifndef ROOM_H
#define ROOM_H

#include "Candidate.h"
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════════
//  Struct Room – Phòng thi chứa danh sách thí sinh được phân công
// ═══════════════════════════════════════════════════════════════════════════════
struct Room {
    int              roomNumber;    // Số phòng (bắt đầu từ 1)
    vector<Candidate> candidates;  // Danh sách thí sinh trong phòng

    explicit Room(int num) : roomNumber(num) {}

    // Thêm thí sinh vào phòng
    void addCandidate(const Candidate& c) { candidates.push_back(c); }

    // Số thí sinh trong phòng
    int getCount() const { return (int)candidates.size(); }

    // Hiển thị danh sách thí sinh trong phòng
    void display() const;
};

#endif
