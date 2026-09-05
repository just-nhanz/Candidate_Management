#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════════
//  Struct Candidate – thông tin một thí sinh
// ═══════════════════════════════════════════════════════════════════════════════
struct Candidate {
    string examID;    // Mã dự thi (khóa định danh duy nhất)
    string fullName;  // Họ và tên
    string gender;    // Giới tính: "Nam" / "Nữ"
    string birthDate; // Ngày sinh DD/MM/YYYY
    string hometown;  // Quê quán

    // Constructors
    Candidate() = default;
    Candidate(const string& id, const string& name, const string& gen,
              const string& birth, const string& home)
        : examID(id), fullName(name), gender(gen),
          birthDate(birth), hometown(home) {}

    // Hiển thị thông tin 1 dòng bảng
    void display() const;

    // Chuyển thành chuỗi lưu file: "ID|HọTên|GioiTinh|NgaySinh|QueQuan"
    string toFileString() const;

    // In tiêu đề bảng
    static void printHeader();

    // In đường kẻ bảng
    static void printSeparator();
};

#endif
