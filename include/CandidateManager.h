#ifndef CANDIDATEMANAGER_H
#define CANDIDATEMANAGER_H

#include "HashTable.h"
#include "FileManager.h"
#include "CandidateSorter.h"
#include "GroupManager.h"
#include "RoomManager.h"

// ═══════════════════════════════════════════════════════════════════════════════
//  Class CandidateManager – Facade / Controller chính của hệ thống
//  Điều phối tất cả module và xử lý tương tác người dùng qua menu
// ═══════════════════════════════════════════════════════════════════════════════
class CandidateManager {
private:
    HashTable    hashTable;    // Cấu trúc dữ liệu chính
    FileManager  fileManager;  // Quản lý file
    bool         modified;     // Đánh dấu dữ liệu đã thay đổi chưa

    // ── Hiển thị banner + menu chính ─────────────────────────────────────────
    void displayMenu() const;

    // ── Handlers cho từng chức năng ──────────────────────────────────────────
    void handleAdd();               // 1. Thêm thí sinh
    void handleDelete();            // 2. Xoá thí sinh
    void handleSearchByID();        // 3. Tra cứu theo mã
    void handleSearchByName();      // 4. Tra cứu theo tên
    void handleDisplaySorted();     // 5. Hiển thị danh sách sắp xếp
    void handleDisplayGroups();     // 6. Hiển thị nhóm theo chữ cái
    void handleAssignRooms();       // 7. Phân phòng thi
    void handleSave();              // 8. Lưu file
    void handleLoad();              // 9. Tải file
    void handleStats();             // 10. Thống kê bảng băm

    // ── Input helpers ─────────────────────────────────────────────────────────
    string inputLine(const string& prompt) const;
    int    inputInt(const string& prompt, int minVal, int maxVal) const;
    bool   confirm(const string& question) const;

public:
    CandidateManager();
    ~CandidateManager();  // Tự động lưu file khi thoát

    // ── Chạy chương trình (vòng lặp menu) ────────────────────────────────────
    void run();
};

#endif
