#include "../include/Candidate.h"
#include <iomanip>
#include <iostream>
using namespace std;

// ─── Độ rộng cột (ký tự) ─────────────────────────────────────────────────────
static const int W_ID    = 10;
static const int W_NAME  = 30;
static const int W_GEN   = 6;
static const int W_BIRTH = 12;
static const int W_HOME  = 20;

void Candidate::printSeparator() {
    cout << "+" << string(W_ID+2,'-')
         << "+" << string(W_NAME+2,'-')
         << "+" << string(W_GEN+2,'-')
         << "+" << string(W_BIRTH+2,'-')
         << "+" << string(W_HOME+2,'-') << "+" << endl;
}

void Candidate::printHeader() {
    printSeparator();
    cout << "| " << left << setw(W_ID)   << "Ma du thi"
         << " | "       << setw(W_NAME)  << "Ho va ten"
         << " | "       << setw(W_GEN)   << "Gioi"
         << " | "       << setw(W_BIRTH) << "Ngay sinh"
         << " | "       << setw(W_HOME)  << "Que quan"
         << " |" << endl;
    printSeparator();
}

void Candidate::display() const {
    cout << "| " << left << setw(W_ID)   << examID
         << " | "       << setw(W_NAME)  << fullName
         << " | "       << setw(W_GEN)   << gender
         << " | "       << setw(W_BIRTH) << birthDate
         << " | "       << setw(W_HOME)  << hometown
         << " |" << endl;
}

string Candidate::toFileString() const {
    return examID + "|" + fullName + "|" + gender + "|" + birthDate + "|" + hometown;
}
