// tests/benchmark.cpp – Đánh giá hiệu năng với tập dữ liệu lớn
// Compile: g++ -std=c++17 -O2 -I ../include benchmark.cpp
//          ../src/Candidate.cpp ../src/Node.cpp ../src/LinkedList.cpp
//          ../src/HashTable.cpp ../src/CandidateSorter.cpp
//          ../src/FileManager.cpp -o benchmark
#include "../include/HashTable.h"
#include "../include/CandidateSorter.h"
#include "../include/FileManager.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;
using namespace chrono;

// ─── Tạo dữ liệu ngẫu nhiên ─────────────────────────────────────────────────
static const vector<string> FIRST_NAMES = {
    "An","Anh","Bao","Binh","Chi","Cuong","Duc","Dung",
    "Em","Hang","Hoa","Hung","Khoa","Lan","Linh","Manh",
    "Minh","Nam","Ngoc","Nhi","Oanh","Phong","Phuc","Quynh",
    "Son","Tam","Thang","Uyen","Vinh","Xuan","Tuan","Long",
    "Khanh","Hieu","Dat","Lam","Trang","Huong","Nhung","Mai"
};
static const vector<string> LAST_NAMES = {
    "Nguyen","Tran","Le","Pham","Hoang","Vu","Dang",
    "Bui","Ngo","Do","Ho","Dinh","Trinh","Cao","Mai"
};
static const vector<string> MID_NAMES = {
    "Van","Thi","Hoang","Ngoc","Duc","Thi","Minh","Bao"
};
static const vector<string> PROVINCES = {
    "Ha Noi","TP.HCM","Da Nang","Hai Phong","Can Tho",
    "Nghe An","Hue","Quang Ninh","Binh Duong","Dong Nai"
};

Candidate makeCandidate(int id) {
    string examID = "BM" + to_string(100000 + id);
    string lastName  = LAST_NAMES[rand() % LAST_NAMES.size()];
    string midName   = MID_NAMES[rand()  % MID_NAMES.size()];
    string firstName = FIRST_NAMES[rand() % FIRST_NAMES.size()];
    string fullName  = lastName + " " + midName + " " + firstName;
    string gender    = (rand() % 2 == 0) ? "Nam" : "Nu";
    int day   = 1  + rand() % 28;
    int month = 1  + rand() % 12;
    int year  = 2000 + rand() % 6;
    char buf[16];
    snprintf(buf, sizeof(buf), "%02d/%02d/%04d", day, month, year);
    string birthDate = buf;
    string hometown  = PROVINCES[rand() % PROVINCES.size()];
    return Candidate(examID, fullName, gender, birthDate, hometown);
}

// ─── Chạy benchmark cho n thí sinh ──────────────────────────────────────────
void runBenchmark(int n) {
    cout << "\n┌─── BENCHMARK: n = " << n << " thi sinh ────────────────────\n";
    HashTable ht;

    // 1. Thêm
    auto t0 = high_resolution_clock::now();
    for (int i = 0; i < n; i++) ht.add(makeCandidate(i));
    auto t1 = high_resolution_clock::now();
    double addMs = duration<double,milli>(t1-t0).count();
    cout << "│  Them " << n << " TS         : " << fixed << setprecision(3)
         << addMs << " ms  (" << (addMs/n*1000) << " µs/TS)\n";

    // 2. Tìm theo ID (tìm phần tử giữa)
    string midID = "BM" + to_string(100000 + n/2);
    t0 = high_resolution_clock::now();
    for (int r = 0; r < 1000; r++) ht.findByID(midID);
    t1 = high_resolution_clock::now();
    double findMs = duration<double,milli>(t1-t0).count() / 1000.0;
    cout << "│  Tim theo ID (avg 1000x): " << fixed << setprecision(4)
         << findMs << " ms\n";

    // 3. Sắp xếp
    vector<Candidate> all = ht.getAllCandidates();
    t0 = high_resolution_clock::now();
    auto sorted = CandidateSorter::sortByName(all);
    t1 = high_resolution_clock::now();
    double sortMs = duration<double,milli>(t1-t0).count();
    cout << "│  Sap xep Merge Sort     : " << fixed << setprecision(3)
         << sortMs << " ms\n";

    // 4. Phân phòng (n/10 phòng)
    int rooms = max(1, n/10);
    t0 = high_resolution_clock::now();
    // Simulate round-robin counting
    vector<int> roomCounts(rooms, 0);
    int cur = 0;
    for (int i = 0; i < HashTable::TABLE_SIZE; i++) {
        int cnt = ht.getBucket(i).getCount();
        for (int j = 0; j < cnt; j++) { roomCounts[cur % rooms]++; cur++; }
    }
    t1 = high_resolution_clock::now();
    double roomMs = duration<double,milli>(t1-t0).count();
    cout << "│  Phan " << rooms << " phong (Round-Robin): "
         << fixed << setprecision(4) << roomMs << " ms\n";

    // 5. Lưu file
    FileManager fm("data/benchmark_" + to_string(n) + ".txt");
    t0 = high_resolution_clock::now();
    int saved = fm.saveToFile(ht);
    t1 = high_resolution_clock::now();
    double saveMs = duration<double,milli>(t1-t0).count();
    cout << "│  Luu file (" << saved << " dong)    : " << fixed << setprecision(3)
         << saveMs << " ms\n";
    // Xoá file benchmark
    remove(("data/benchmark_" + to_string(n) + ".txt").c_str());

    cout << "└─────────────────────────────────────────────────────\n";
}

int main() {
    srand(42);  // Seed cố định để kết quả tái lập
    cout << "╔═══════════════════════════════════════════════════════╗\n";
    cout << "║      DANH GIA HIEU NANG CHUONG TRINH                 ║\n";
    cout << "║      Hash Table + Linked List + Merge Sort           ║\n";
    cout << "╚═══════════════════════════════════════════════════════╝\n";

    runBenchmark(100);
    runBenchmark(1000);
    runBenchmark(10000);
    runBenchmark(100000);

    cout << "\n┌─── KET LUAN DO PHUC TAP ────────────────────────────┐\n";
    cout << "│  Them thi sinh    : O(1) trung binh                 │\n";
    cout << "│  Tim theo ID      : O(n/26) ~ O(n) worst case      │\n";
    cout << "│  Tim theo Ten     : O(n) duyet tat ca               │\n";
    cout << "│  Sap xep ten A->Z : O(n log n) - Merge Sort        │\n";
    cout << "│  Phan phong       : O(n) - Round-Robin              │\n";
    cout << "│  Luu/Doc file     : O(n)                            │\n";
    cout << "│  Bo nho           : O(n)                            │\n";
    cout << "└─────────────────────────────────────────────────────┘\n";
    return 0;
}
