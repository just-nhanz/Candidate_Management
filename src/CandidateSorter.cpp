#include "../include/CandidateSorter.h"
#include "../include/Utils.h"
using namespace std;

// ─── So sánh hai thí sinh theo tên (A→Z) ─────────────────────────────────────
//     Ưu tiên: Tên (từ cuối) → Họ tên đầy đủ nếu tên bằng nhau
bool CandidateSorter::compareByName(const Candidate& a, const Candidate& b) {
    string nameA = Utils::getFirstName(a.fullName);
    string nameB = Utils::getFirstName(b.fullName);
    if (nameA != nameB) return nameA < nameB;          // So sánh tên trước
    return a.fullName < b.fullName;                    // Nếu tên bằng → so sánh họ tên
}

// ─── Trộn hai nửa đã sắp xếp ─────────────────────────────────────────────────
void CandidateSorter::merge(vector<Candidate>& arr, int left, int mid, int right) {
    int  n1 = mid - left + 1;
    int  n2 = right - mid;

    vector<Candidate> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<Candidate> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compareByName(L[i], R[j])) arr[k++] = L[i++];
        else                            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// ─── Merge Sort đệ quy – O(n log n) ──────────────────────────────────────────
void CandidateSorter::mergeSort(vector<Candidate>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// ─── Public API: nhận bản sao, sắp xếp và trả về ────────────────────────────
vector<Candidate> CandidateSorter::sortByName(vector<Candidate> list) {
    if (!list.empty())
        mergeSort(list, 0, (int)list.size() - 1);
    return list;
}
