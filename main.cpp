// ═══════════════════════════════════════════════════════════════════════════════
//  main.cpp – Điểm vào chương trình Quản lý Danh sách Thí sinh
//  Cấu trúc dữ liệu: Hash Table + Linked List
//  Ngôn ngữ: C++17
// ═══════════════════════════════════════════════════════════════════════════════
#include "include/CandidateManager.h"
#include <iostream>
#include <locale>
using namespace std;

int main() {
    // Cấu hình locale để hỗ trợ tiếng Việt UTF-8 trên Linux/macOS
    setlocale(LC_ALL, "");

    cout << "╔═══════════════════════════════════════════════════════╗\n";
    cout << "║   CHUONG TRINH QUAN LY DANH SACH THI SINH            ║\n";
    cout << "║   Hash Table (26 bucket A-Z) + Linked List           ║\n";
    cout << "║   Ngon ngu: C++17                                     ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n\n";

    CandidateManager manager;
    manager.run();

    return 0;
}
