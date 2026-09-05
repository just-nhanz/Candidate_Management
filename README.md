# 📋 Quản Lý Danh Sách Thí Sinh

![Build](https://github.com/<username>/CandidateManagement/actions/workflows/build.yml/badge.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows%20WSL-lightgrey.svg)

> **Môn học:** Cấu trúc Dữ liệu & Giải thuật  
> **Cấu trúc dữ liệu:** Hash Table (26 bucket A–Z) + Singly Linked List  
> **Thuật toán:** Merge Sort · Round-Robin Distribution

---

## 📑 Mục lục

- [Giới thiệu](#-giới-thiệu)
- [Tính năng](#-tính-năng)
- [Cấu trúc dữ liệu & Giải thuật](#-cấu-trúc-dữ-liệu--giải-thuật)
- [Cấu trúc thư mục](#-cấu-trúc-thư-mục)
- [Cài đặt & Biên dịch](#-cài-đặt--biên-dịch)
- [Hướng dẫn sử dụng](#-hướng-dẫn-sử-dụng)
- [Định dạng file dữ liệu](#-định-dạng-file-dữ-liệu)
- [Đánh giá hiệu năng](#-đánh-giá-hiệu-năng)
- [Thành viên nhóm](#-thành-viên-nhóm)

---

## 🎯 Giới thiệu

Chương trình quản lý danh sách thí sinh sử dụng **Hash Table dạng bảng tra** kết hợp **Danh sách liên kết đơn** để lưu trữ và xử lý thông tin theo chữ cái đầu của tên.

Mỗi thí sinh có 5 trường thông tin:

| Trường | Kiểu | Mô tả | Ví dụ |
|--------|------|--------|-------|
| `examID` | string | Mã dự thi — **khóa duy nhất** | `240101` |
| `fullName` | string | Họ và tên đầy đủ | `Nguyen Van An` |
| `gender` | string | Giới tính | `Nam` / `Nu` |
| `birthDate` | string | Ngày sinh `DD/MM/YYYY` | `15/05/2005` |
| `hometown` | string | Quê quán | `Ha Noi` |

---

## ✨ Tính năng

| # | Chức năng | Mô tả |
|:-:|-----------|-------|
| 1 | **Thêm thí sinh** | Validate trùng mã, tự động chuẩn hoá tên (viết hoa đầu từ, xoá space thừa) |
| 2 | **Xoá thí sinh** | Xoá theo `examID`, có bước xác nhận trước khi xoá |
| 3 | **Tra cứu theo mã** | Tìm chính xác — O(1) nhờ `unordered_set` |
| 4 | **Tra cứu theo tên** | Tìm gần đúng (substring match) trên toàn bộ họ tên |
| 5 | **Hiển thị sắp xếp** | Toàn bộ danh sách theo **tên A→Z** (Merge Sort O(n log n)) |
| 6 | **Hiển thị theo nhóm** | Nhóm thí sinh theo 26 chữ cái A–Z từ Hash Table |
| 7 | **Phân phòng thi** | Phân `n` phòng — **Round-Robin** đảm bảo tối thiểu trùng chữ cái đầu |
| 8 | **Lưu file** | Ghi toàn bộ ra `data/candidates.txt` |
| 9 | **Tải file** | Đọc & nạp dữ liệu, tự động khi khởi động |
| 10 | **Thống kê Hash Table** | Biểu đồ phân bố thí sinh theo từng bucket |

---

## 🏗️ Cấu trúc dữ liệu & Giải thuật

### Hash Table + Linked List

```
Hash Table (26 bucket — chữ cái A đến Z)
│
├── [A] ──▶ Node{An} ──▶ Node{Anh} ──▶ NULL
├── [B] ──▶ Node{Bao} ──▶ Node{Binh} ──▶ NULL
├── [C] ──▶ Node{Chi} ──▶ Node{Cuong} ──▶ NULL
│    ...
├── [M] ──▶ Node{Minh} ──▶ Node{Manh} ──▶ NULL
│    ...
└── [Z] ──▶ NULL
```

**Hàm băm:**
```
Hash("Nguyen Van An")
  → tên = "An"  → chữ cái đầu = 'A'  → index = 'A' - 'A' = 0
Hash("Hoang Van Duc")
  → tên = "Duc" → chữ cái đầu = 'D'  → index = 'D' - 'A' = 3
```

> Hỗ trợ UTF-8 tiếng Việt: `Đức` → D, `Ánh` → A, `Ọanh` → O, ...

### Tối ưu hiệu năng

| Vấn đề ban đầu | Giải pháp | Kết quả |
|----------------|-----------|---------|
| `add()` gọi `findByID()` O(n) → tổng O(n²) | Thêm `unordered_set<string>` tra cứu ID | O(1) check trùng |
| `insertBack()` duyệt đến cuối O(n/26) | Thêm con trỏ `tail` trong LinkedList | O(1) insert |
| **100k thí sinh: 187,000 ms** | Sau 2 tối ưu trên | **80 ms ↓ 2300×** |

### Sắp xếp — Merge Sort O(n log n)

```
Tiêu chí so sánh:
  1. Tên (từ cuối fullName): "An" < "Anh" < "Bao" < ...
  2. Nếu tên bằng nhau → so sánh tiếp fullName
```

### Phân phòng thi — Round-Robin O(n)

```
Duyệt bucket A→Z, mỗi thí sinh gán vào phòng[currentRoom % n], currentRoom++

Ví dụ 30 thí sinh, 3 phòng:
  Phong 1 (10 TS): A, B, D, H, K, M, N, O, Q, T  → 10 chữ khác nhau ✓
  Phong 2 (10 TS): A, C, D, H, L, M, N, P, S, U  → 10 chữ khác nhau ✓
  Phong 3 (10 TS): B, C, E, H, L, N, O, P, T, X  → 10 chữ khác nhau ✓
```

---

## 📁 Cấu trúc thư mục

```
CandidateManagement/
│
├── 📂 include/                    # Header files
│   ├── Utils.h                    # Tiện ích: trim, UTF-8 Vietnamese, hash index
│   ├── Candidate.h                # Struct thí sinh + display/toFileString
│   ├── Node.h                     # Node của Linked List
│   ├── LinkedList.h               # LinkedList với tail pointer O(1)
│   ├── HashTable.h                # 26 bucket + unordered_set ID check O(1)
│   ├── CandidateSorter.h          # Merge Sort theo tên
│   ├── GroupManager.h             # Hiển thị nhóm A–Z
│   ├── Room.h                     # Struct phòng thi
│   ├── RoomManager.h              # Phân phòng Round-Robin
│   ├── FileManager.h              # Đọc/ghi file candidates.txt
│   └── CandidateManager.h        # Facade: menu 10 chức năng
│
├── 📂 src/                        # Source files
│   ├── Node.cpp
│   ├── Candidate.cpp
│   ├── LinkedList.cpp
│   ├── HashTable.cpp
│   ├── CandidateSorter.cpp
│   ├── GroupManager.cpp
│   ├── RoomManager.cpp
│   ├── FileManager.cpp
│   └── CandidateManager.cpp
│
├── 📂 data/
│   └── candidates.txt             # Dữ liệu demo 30 thí sinh
│
├── 📂 tests/
│   ├── test_cases.txt             # 18 kịch bản kiểm thử chi tiết
│   └── benchmark.cpp              # Đo hiệu năng n = 100 / 1K / 10K / 100K
│
├── 📂 .github/workflows/
│   └── build.yml                  # GitHub Actions CI (Ubuntu + macOS)
│
├── main.cpp                       # Entry point
├── Makefile                       # make / make run / make benchmark / make clean
├── CMakeLists.txt                 # Build thay thế bằng CMake
├── .gitignore
├── LICENSE
├── CONTRIBUTING.md
└── README.md
```

---

## 🛠️ Cài đặt & Biên dịch

### Yêu cầu

- **Compiler:** g++ 7+ hoặc Clang 5+ hỗ trợ C++17
- **OS:** Linux / macOS / Windows WSL2

### Cách 1 — Makefile (khuyến nghị)

```bash
# Clone
git clone https://github.com/<username>/CandidateManagement.git
cd CandidateManagement

# Build
make

# Chạy
make run

# Build + chạy benchmark hiệu năng
make benchmark
./tests/benchmark
```

```
Các lệnh make:
  make            Build chương trình chính
  make run        Build và chạy ngay
  make benchmark  Build tool đo hiệu năng
  make clean      Xoá tất cả file build
  make help       Hiển thị hướng dẫn
```

### Cách 2 — CMake

```bash
mkdir build && cd build
cmake ..
cmake --build .
cd ..
./candidate_manager
```

### Cách 3 — Biên dịch thủ công

```bash
g++ -std=c++17 -Wall -O2 -I include \
    main.cpp src/*.cpp -o candidate_manager

./candidate_manager
```

---

## 📖 Hướng dẫn sử dụng

Khi khởi động, chương trình **tự động tải** `data/candidates.txt` rồi hiện menu:

```
╔═══════════════════════════════════════════════════════╗
║        QUAN LY DANH SACH THI SINH                    ║
║        Hash Table + Linked List – C++                ║
╠═══════════════════════════════════════════════════════╣
║  1. Them thi sinh moi                                ║
║  2. Xoa thi sinh                                     ║
║  3. Tra cuu theo Ma du thi                           ║
║  4. Tra cuu theo Ten                                 ║
║  5. Hien thi danh sach (sap xep ten A->Z)           ║
║  6. Hien thi nhom theo chu cai dau                   ║
║  7. Phan phong thi (Round-Robin)                     ║
║  8. Luu du lieu ra file                              ║
║  9. Tai du lieu tu file                              ║
║ 10. Thong ke Bang Bam (Hash Table Stats)            ║
║  0. Thoat                                            ║
╚═══════════════════════════════════════════════════════╝
  Tong: 30 thi sinh | Chon:
```

### Demo chức năng thêm (menu 1)

```
  Ma du thi          : 240131
  Ho va ten          : nguyen thi mai      ← nhập thường
  Gioi tinh (Nam/Nu) : Nu
  Ngay sinh          : 20/03/2006
  Que quan           : Da Nang

  [OK] Da them thi sinh thanh cong!
  Ten duoc chuan hoa : "Nguyen Thi Mai"   ← tự động viết hoa
  Nhom hash          : [M]                ← gán vào bucket M
```

### Demo phân phòng (menu 7)

```
  Tong so thi sinh: 30
  Nhap so phong thi n (1-100): 3

┌─── PHONG 1 ─── (10 thi sinh) ──────────
| Ma du thi | Ho va ten        | Gioi | Ngay sinh  | Que quan  |
| 240101    | Nguyen Van An    | Nam  | 15/05/2005 | Ha Noi    |
| 240122    | Tran Van Bao     | Nam  | 25/10/2005 | Ha Noi    |
  ...

  Phong 1: 10 thi sinh | 10 chu cai dau khac nhau (A,B,D,H,K,M,N,O,Q,T)
  Phong 2: 10 thi sinh | 10 chu cai dau khac nhau (A,C,D,H,L,M,N,P,S,U)
  Phong 3: 10 thi sinh | 10 chu cai dau khac nhau (B,C,E,H,L,N,O,P,T,X)
```

### Demo thống kê Hash Table (menu 10)

```
╔══════════════════════════════════════════════════════╗
║          THONG KE BANG BAM (HASH TABLE STATS)       ║
╠════════╦════════════╦═════════════════════════════════╣
║ Bucket ║ So thi sinh║ Bieu do                         ║
╠════════╬════════════╬═════════════════════════════════╣
║   [A]  ║          2 ║ ##                             ║
║   [B]  ║          2 ║ ##                             ║
║   [H]  ║          3 ║ ###                            ║
║   [N]  ║          3 ║ ###                            ║
   ...
╠════════╩════════════╩═════════════════════════════════╣
║  Tong: 30 thi sinh trong 18 nhom                   ║
╚══════════════════════════════════════════════════════╝
```

---

## 📄 Định dạng file dữ liệu

`data/candidates.txt` — mỗi dòng 1 thí sinh, phân cách bằng `|`:

```
240101|Nguyen Van An|Nam|15/05/2005|Ha Noi
240102|Tran Thi Binh|Nu|20/08/2004|Da Nang
240103|Le Hoang Cuong|Nam|01/01/2005|Hai Phong
```

**Quy tắc:**
- Đúng 5 trường, phân cách bằng `|`
- Dòng trống hoặc bắt đầu bằng `#` bị bỏ qua (dùng làm comment)
- Dòng sai định dạng → cảnh báo, bỏ qua, tiếp tục đọc
- **Tự động tải** khi khởi động · **Tự động lưu** khi thoát nếu có thay đổi

---

## 📊 Đánh giá hiệu năng

Kết quả benchmark thực tế (đo trên máy thông thường):

| n (thí sinh) | Thêm tất cả | Tìm theo ID | Merge Sort | Phân phòng | Lưu file |
|:------------:|:-----------:|:-----------:|:----------:|:----------:|:--------:|
| 100 | 0.09 ms | 0.0002 ms | 0.11 ms | 0.001 ms | 0.24 ms |
| 1,000 | 0.64 ms | 0.003 ms | 1.61 ms | 0.003 ms | 0.43 ms |
| 10,000 | 6.74 ms | 0.014 ms | 21.9 ms | 0.022 ms | 1.88 ms |
| **100,000** | **80.8 ms** | **2.08 ms** | **290 ms** | **0.28 ms** | **26.9 ms** |

### Độ phức tạp lý thuyết

| Thao tác | Trung bình | Xấu nhất | Ghi chú |
|----------|:----------:|:--------:|---------|
| Thêm thí sinh | **O(1)** | O(1) | `unordered_set` + `tail` pointer |
| Xoá thí sinh | O(n/26) | O(n) | Duyệt bucket |
| Tìm theo mã | **O(1)** | O(n/26) | Check `unordered_set` trước |
| Tìm theo tên | O(n) | O(n) | Duyệt toàn bộ |
| Sắp xếp A→Z | **O(n log n)** | O(n log n) | Merge Sort ổn định |
| Phân phòng | **O(n)** | O(n) | Round-Robin |
| Lưu / Đọc file | O(n) | O(n) | I/O tuần tự |
| Bộ nhớ | O(n) | O(n) | |

### Các tối ưu đã áp dụng

```
Vấn đề 1: add() gọi findByID() → O(n) mỗi lần → tổng O(n²)
Giải pháp: unordered_set<string> idSet song song với bucket
Kết quả : kiểm tra trùng O(n) → O(1)

Vấn đề 2: insertBack() duyệt đến node cuối → O(n/26) mỗi lần
Giải pháp: con trỏ tail trong LinkedList
Kết quả : O(n/26) → O(1)

Tổng hợp: thêm 100,000 thí sinh: 187,000 ms → 80 ms  (↓ 2,300×)
```

---

## 👥 Thành viên nhóm

| STT | Họ và tên | MSSV | Đóng góp |
|:---:|-----------|------|----------|
| 1 | | | |
| 2 | | | |
| 3 | | | |

---

## 📚 Tài liệu tham khảo

- Cormen, T. H. et al. — *Introduction to Algorithms*, 4th ed.
- Sedgewick, R. — *Algorithms in C++*, 3rd ed.
- [cppreference.com — std::unordered_set](https://en.cppreference.com/w/cpp/container/unordered_set)
- [Unicode Consortium — Latin Extended Additional U+1E00–U+1EFF](https://unicode.org/charts/PDF/U1E00.pdf)

---

## 📝 License

Dự án được cấp phép theo [MIT License](LICENSE).

---

<div align="center">
  <sub>Đồ án môn Cấu trúc Dữ liệu & Giải thuật · C++17</sub>
</div>
