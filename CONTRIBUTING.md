# Hướng dẫn đóng góp (Contributing Guide)

Cảm ơn bạn đã muốn đóng góp vào dự án! Dưới đây là các quy tắc để giữ code sạch và nhất quán.

---

## 🔧 Thiết lập môi trường

```bash
git clone https://github.com/<username>/CandidateManagement.git
cd CandidateManagement
make
./candidate_manager
```

**Yêu cầu:** g++ 7+ hoặc Clang 5+ với C++17.

---

## 🌿 Quy trình làm việc với Git

```bash
# 1. Tạo branch mới từ main
git checkout -b feature/ten-tinh-nang

# 2. Commit với message rõ ràng
git commit -m "feat: them chuc nang xuat PDF danh sach"
git commit -m "fix: sua loi sap xep khi ten co dau tieng Viet"
git commit -m "docs: cap nhat README phan benchmark"

# 3. Push và mở Pull Request
git push origin feature/ten-tinh-nang
```

### Quy ước đặt tên commit

| Prefix | Ý nghĩa |
|--------|---------|
| `feat:` | Tính năng mới |
| `fix:` | Sửa lỗi |
| `docs:` | Cập nhật tài liệu |
| `refactor:` | Tái cấu trúc code |
| `perf:` | Cải thiện hiệu năng |
| `test:` | Thêm/sửa test |

---

## 📐 Quy tắc viết code C++

### Đặt tên
```cpp
// Class: PascalCase
class CandidateManager { };

// Hàm & biến: camelCase
void insertBack(const Candidate& c);
int totalCount;

// Hằng số: UPPER_SNAKE_CASE
static const int TABLE_SIZE = 26;

// File header:  PascalCase.h
// File source:  PascalCase.cpp
```

### Cấu trúc file `.h`
```cpp
#ifndef MYCLASS_H        // include guard
#define MYCLASS_H

#include <string>
using namespace std;

class MyClass {
private:
    // members...
public:
    // methods...
};

#endif
```

### Comment
- **Tiếng Việt** cho logic nghiệp vụ
- **Tiếng Anh** cho comment kỹ thuật thuần tuý
- Mỗi hàm public cần có comment mô tả **input / output / độ phức tạp**

```cpp
// Thêm thí sinh vào hệ thống
// Input : Candidate đã validate
// Return: true nếu thêm thành công, false nếu examID trùng
// O(1) trung bình nhờ unordered_set
bool add(const Candidate& c);
```

---

## 🗂️ Thêm module mới

Khi thêm tính năng mới (ví dụ `ExportManager`):

1. Tạo `include/ExportManager.h`
2. Tạo `src/ExportManager.cpp`
3. Thêm vào `MAIN_SRC` trong `Makefile`
4. Thêm vào `COMMON_SOURCES` trong `CMakeLists.txt`
5. Gọi từ `CandidateManager.cpp`
6. Thêm test case vào `tests/test_cases.txt`

---

## 🐛 Báo lỗi (Bug Report)

Mở Issue trên GitHub với template:

```
**Mô tả lỗi:** ...
**Bước tái hiện:**
  1. Chạy chương trình
  2. Chọn chức năng X
  3. Nhập Y
  4. Lỗi xảy ra

**Kết quả mong đợi:** ...
**Kết quả thực tế:** ...
**Môi trường:** OS / g++ version
```
