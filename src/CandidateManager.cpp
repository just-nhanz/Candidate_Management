#include "../include/CandidateManager.h"
#include "../include/Utils.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>
using namespace std;
using namespace chrono;

// ═══════════════════════════════════════════════════════════════════════════════
//  Constructor / Destructor
// ═══════════════════════════════════════════════════════════════════════════════
CandidateManager::CandidateManager()
    : fileManager("data/candidates.txt"), modified(false) {
    // Tự động tải file khi khởi động
    cout << "  Dang tai du lieu tu file...\n";
    int loaded = fileManager.loadFromFile(hashTable);
    if (loaded > 0)
        cout << "  Da tai " << loaded << " thi sinh tu file.\n\n";
    else
        cout << "  Khong co du lieu cu hoac file chua ton tai.\n\n";
}

CandidateManager::~CandidateManager() {
    // Tự động lưu nếu có thay đổi
    if (modified) {
        cout << "\n  Dang tu dong luu du lieu...\n";
        int saved = fileManager.saveToFile(hashTable);
        if (saved >= 0)
            cout << "  Da luu " << saved << " thi sinh ra file.\n";
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  Input helpers
// ═══════════════════════════════════════════════════════════════════════════════
string CandidateManager::inputLine(const string& prompt) const {
    cout << prompt;
    string s;
    getline(cin, s);
    return Utils::trim(s);
}

int CandidateManager::inputInt(const string& prompt, int minVal, int maxVal) const {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= minVal && val <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Vui long nhap so tu " << minVal << " den " << maxVal << ".\n";
    }
}

bool CandidateManager::confirm(const string& question) const {
    cout << question << " (y/n): ";
    string s; getline(cin, s);
    return !s.empty() && (s[0]=='y'||s[0]=='Y');
}

// ═══════════════════════════════════════════════════════════════════════════════
//  Hiển thị menu
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::displayMenu() const {
    cout << "\n╔═══════════════════════════════════════════════════════╗\n";
    cout <<   "║        QUAN LY DANH SACH THI SINH                    ║\n";
    cout <<   "║        Hash Table + Linked List – C++                ║\n";
    cout <<   "╠═══════════════════════════════════════════════════════╣\n";
    cout <<   "║  1. Them thi sinh moi                                ║\n";
    cout <<   "║  2. Xoa thi sinh                                     ║\n";
    cout <<   "║  3. Tra cuu theo Ma du thi                           ║\n";
    cout <<   "║  4. Tra cuu theo Ten                                 ║\n";
    cout <<   "║  5. Hien thi danh sach (sap xep ten A->Z)           ║\n";
    cout <<   "║  6. Hien thi nhom theo chu cai dau                   ║\n";
    cout <<   "║  7. Phan phong thi (Round-Robin)                     ║\n";
    cout <<   "║  8. Luu du lieu ra file                              ║\n";
    cout <<   "║  9. Tai du lieu tu file                              ║\n";
    cout <<   "║ 10. Thong ke Bang Bam (Hash Table Stats)            ║\n";
    cout <<   "║  0. Thoat                                            ║\n";
    cout <<   "╚═══════════════════════════════════════════════════════╝\n";
    cout << "  Tong: " << hashTable.getTotalCount() << " thi sinh | ";
    cout << "Chon: ";
}

// ═══════════════════════════════════════════════════════════════════════════════
//  1. THÊM THÍ SINH
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::handleAdd() {
    cout << "\n--- THEM THI SINH MOI ---\n";

    // ── Nhập mã dự thi ────────────────────────────────────────────────────────
    string examID;
    while (true) {
        examID = inputLine("  Ma du thi   : ");
        if (examID.empty()) { cout << "  Ma du thi khong duoc de trong!\n"; continue; }
        if (hashTable.findByID(examID)) {
            cout << "  Ma '" << examID << "' da ton tai! Vui long nhap ma khac.\n";
            continue;
        }
        break;
    }

    // ── Nhập họ tên ──────────────────────────────────────────────────────────
    string fullName;
    while (true) {
        fullName = inputLine("  Ho va ten   : ");
        if (fullName.empty()) { cout << "  Ho ten khong duoc de trong!\n"; continue; }
        break;
    }
    fullName = Utils::normalizeName(fullName);  // Chuẩn hoá

    // ── Nhập giới tính ────────────────────────────────────────────────────────
    string gender;
    while (true) {
        gender = inputLine("  Gioi tinh (Nam/Nu): ");
        if (gender == "Nam" || gender == "Nu" ||
            gender == "nam" || gender == "nu") {
            if (gender == "nam") gender = "Nam";
            if (gender == "nu")  gender = "Nu";
            break;
        }
        cout << "  Vui long nhap 'Nam' hoac 'Nu'.\n";
    }

    // ── Nhập ngày sinh ────────────────────────────────────────────────────────
    string birthDate;
    while (true) {
        birthDate = inputLine("  Ngay sinh (DD/MM/YYYY): ");
        if (birthDate.size() == 10 && birthDate[2]=='/' && birthDate[5]=='/') break;
        cout << "  Dinh dang sai. Vui long nhap DD/MM/YYYY (vi du: 15/05/2005).\n";
    }

    // ── Nhập quê quán ─────────────────────────────────────────────────────────
    string hometown;
    while (true) {
        hometown = inputLine("  Que quan    : ");
        if (!hometown.empty()) break;
        cout << "  Que quan khong duoc de trong!\n";
    }

    // ── Thêm vào Hash Table ───────────────────────────────────────────────────
    Candidate c(examID, fullName, gender, birthDate, hometown);
    hashTable.add(c);
    modified = true;

    cout << "\n  [OK] Da them thi sinh thanh cong!\n";
    cout << "  Ten duoc chuan hoa: \"" << fullName << "\"\n";
    cout << "  Nhom hash: [" << Utils::getBaseChar(Utils::getFirstName(fullName)) << "]\n";
}

// ═══════════════════════════════════════════════════════════════════════════════
//  2. XOÁ THÍ SINH
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::handleDelete() {
    cout << "\n--- XOA THI SINH ---\n";
    string examID = inputLine("  Nhap Ma du thi can xoa: ");
    if (examID.empty()) return;

    Candidate* found = hashTable.findByID(examID);
    if (!found) {
        cout << "  [KHONG TIM THAY] Ma '" << examID << "' khong ton tai.\n";
        return;
    }

    cout << "\n  Tim thay thi sinh:\n";
    Candidate::printHeader();
    found->display();
    Candidate::printSeparator();

    if (confirm("  Xac nhan xoa thi sinh nay?")) {
        hashTable.remove(examID);
        modified = true;
        cout << "  [OK] Da xoa thi sinh '" << examID << "'.\n";
    } else {
        cout << "  Huy bo thao tac xoa.\n";
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  3. TRA CỨU THEO MÃ
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::handleSearchByID() {
    cout << "\n--- TRA CUU THEO MA DU THI ---\n";
    string examID = inputLine("  Nhap Ma du thi: ");
    if (examID.empty()) return;

    auto t0 = high_resolution_clock::now();
    Candidate* found = hashTable.findByID(examID);
    auto t1 = high_resolution_clock::now();
    double ms = duration<double,milli>(t1-t0).count();

    if (!found) {
        cout << "  [KHONG TIM THAY] Ma '" << examID << "' khong co trong he thong.\n";
    } else {
        cout << "\n  Thong tin thi sinh:\n";
        Candidate::printHeader();
        found->display();
        Candidate::printSeparator();
        cout << "  Thoi gian tim kiem: " << fixed << setprecision(4) << ms << " ms\n";
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  4. TRA CỨU THEO TÊN
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::handleSearchByName() {
    cout << "\n--- TRA CUU THEO TEN ---\n";
    string keyword = inputLine("  Nhap ten (hoac mot phan ten): ");
    if (keyword.empty()) return;

    auto t0 = high_resolution_clock::now();
    vector<Candidate> results = hashTable.findByName(keyword);
    auto t1 = high_resolution_clock::now();
    double ms = duration<double,milli>(t1-t0).count();

    cout << "\n  Tim thay " << results.size() << " ket qua:\n";
    if (!results.empty()) {
        Candidate::printHeader();
        for (const Candidate& c : results) c.display();
        Candidate::printSeparator();
    }
    cout << "  Thoi gian tim kiem: " << fixed << setprecision(4) << ms << " ms\n";
}

// ═══════════════════════════════════════════════════════════════════════════════
//  5. HIỂN THỊ DANH SÁCH SẮP XẾP THEO TÊN A→Z
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::handleDisplaySorted() {
    cout << "\n--- DANH SACH THI SINH SAP XEP THEO TEN (A->Z) ---\n";
    if (hashTable.getTotalCount() == 0) {
        cout << "  (Chua co thi sinh nao)\n"; return;
    }

    auto t0 = high_resolution_clock::now();
    vector<Candidate> all = hashTable.getAllCandidates();
    vector<Candidate> sorted = CandidateSorter::sortByName(all);
    auto t1 = high_resolution_clock::now();
    double ms = duration<double,milli>(t1-t0).count();

    cout << "\n  Tong so: " << sorted.size() << " thi sinh\n\n";
    // Dòng header (STT + bảng)
    cout << "+------+------------+--------------------------------+--------+--------------+----------------------+\n";
    cout << "| STT  | Ma du thi  | Ho va ten                      | Gioi   | Ngay sinh    | Que quan             |\n";
    cout << "+------+------------+--------------------------------+--------+--------------+----------------------+\n";

    int stt = 1;
    for (const Candidate& c : sorted) {
        cout << "| " << left << setw(4) << stt++ << " | "
             << setw(10) << c.examID  << " | "
             << setw(30) << c.fullName << " | "
             << setw(6)  << c.gender   << " | "
             << setw(12) << c.birthDate << " | "
             << setw(20) << c.hometown  << " |\n";
    }
    cout << right;
    cout << "+------+------------+--------------------------------+--------+--------------+----------------------+\n";

    cout << "\n  Thuat toan: Merge Sort | Thoi gian: "
         << fixed << setprecision(4) << ms << " ms\n";
}

// ═══════════════════════════════════════════════════════════════════════════════
//  6. HIỂN THỊ NHÓM THEO CHỮ CÁI ĐẦU
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::handleDisplayGroups() {
    cout << "\n--- NHOM THEO CHU CAI DAU ---\n";
    cout << "  1. Hien thi tat ca nhom\n";
    cout << "  2. Hien thi mot nhom cu the\n";
    int choice = inputInt("  Chon: ", 1, 2);

    if (choice == 1) {
        GroupManager::displayAllGroups(hashTable);
    } else {
        string letterStr = inputLine("  Nhap chu cai (A-Z): ");
        if (!letterStr.empty())
            GroupManager::displayGroup(hashTable, letterStr[0]);
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  7. PHÂN PHÒNG THI
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::handleAssignRooms() {
    cout << "\n--- PHAN PHONG THI ---\n";
    if (hashTable.getTotalCount() == 0) {
        cout << "  (Chua co thi sinh nao de phan phong)\n"; return;
    }
    cout << "  Tong so thi sinh: " << hashTable.getTotalCount() << "\n";
    int n = inputInt("  Nhap so phong thi n (1-100): ", 1, 100);

    auto t0 = high_resolution_clock::now();
    vector<Room> rooms = RoomManager::assignRooms(hashTable, n);
    auto t1 = high_resolution_clock::now();
    double ms = duration<double,milli>(t1-t0).count();

    RoomManager::displayRooms(rooms);
    cout << "\n  Thuat toan: Round-Robin | Thoi gian: "
         << fixed << setprecision(4) << ms << " ms\n";
}

// ═══════════════════════════════════════════════════════════════════════════════
//  8. LƯU FILE
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::handleSave() {
    cout << "\n--- LUU DU LIEU ---\n";
    cout << "  Dang luu vao: " << fileManager.getFilePath() << "\n";
    int saved = fileManager.saveToFile(hashTable);
    if (saved >= 0) {
        modified = false;
        cout << "  [OK] Da luu " << saved << " thi sinh thanh cong!\n";
    } else {
        cout << "  [LOI] Khong the luu file!\n";
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  9. TẢI FILE
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::handleLoad() {
    cout << "\n--- TAI DU LIEU TU FILE ---\n";
    if (hashTable.getTotalCount() > 0) {
        if (!confirm("  He thong dang co du lieu. Ban co muon tai de ghi de khong?"))
            return;
    }

    // Xoá dữ liệu hiện tại: xoá từng thí sinh khỏi hash table
    vector<Candidate> all = hashTable.getAllCandidates();
    for (const Candidate& c : all)
        hashTable.remove(c.examID);

    // Nạp lại từ file
    int loaded = fileManager.loadFromFile(hashTable);
    if (loaded >= 0) {
        modified = false;
        cout << "  [OK] Da tai " << loaded << " thi sinh tu file.\n";
    } else {
        cout << "  [LOI] Khong the doc file!\n";
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  10. THỐNG KÊ
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::handleStats() {
    if (hashTable.getTotalCount() == 0) {
        cout << "  (Chua co du lieu de thong ke)\n"; return;
    }
    hashTable.printStats();
}

// ═══════════════════════════════════════════════════════════════════════════════
//  RUN – Vòng lặp menu chính
// ═══════════════════════════════════════════════════════════════════════════════
void CandidateManager::run() {
    while (true) {
        displayMenu();
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:  handleAdd();            break;
            case 2:  handleDelete();         break;
            case 3:  handleSearchByID();     break;
            case 4:  handleSearchByName();   break;
            case 5:  handleDisplaySorted();  break;
            case 6:  handleDisplayGroups();  break;
            case 7:  handleAssignRooms();    break;
            case 8:  handleSave();           break;
            case 9:  handleLoad();           break;
            case 10: handleStats();          break;
            case 0:
                cout << "\n  Tam biet! Hen gap lai.\n";
                return;
            default:
                cout << "  Lua chon khong hop le. Vui long chon 0-10.\n";
        }
    }
}
