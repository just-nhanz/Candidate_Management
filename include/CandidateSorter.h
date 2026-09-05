#ifndef CANDIDATESORTER_H
#define CANDIDATESORTER_H

#include "Candidate.h"
#include <vector>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════════
//  Class CandidateSorter – Sắp xếp danh sách thí sinh theo tên A→Z
//  Thuật toán: Merge Sort – O(n log n)
//  Tiêu chí: so sánh Tên (từ cuối) → nếu bằng thì so sánh Họ tên đầy đủ
// ═══════════════════════════════════════════════════════════════════════════════
class CandidateSorter {
public:
    // Sắp xếp và trả về danh sách mới (không thay đổi input)
    static vector<Candidate> sortByName(vector<Candidate> list);

    // So sánh hai thí sinh theo tên (dùng ngoài class nếu cần)
    static bool compareByName(const Candidate& a, const Candidate& b);

private:
    // Merge sort đệ quy
    static void mergeSort(vector<Candidate>& arr, int left, int right);
    // Trộn hai mảng đã sắp xếp
    static void merge(vector<Candidate>& arr, int left, int mid, int right);
};

#endif
