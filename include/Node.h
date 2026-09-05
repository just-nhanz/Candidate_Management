#ifndef NODE_H
#define NODE_H

#include "Candidate.h"

// ═══════════════════════════════════════════════════════════════════════════════
//  Struct Node – nút trong danh sách liên kết đơn
// ═══════════════════════════════════════════════════════════════════════════════
struct Node {
    Candidate data;  // Dữ liệu thí sinh
    Node*     next;  // Con trỏ đến nút tiếp theo

    explicit Node(const Candidate& c) : data(c), next(nullptr) {}
};

#endif
