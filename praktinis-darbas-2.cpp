#include <iostream>
#include <string>
using namespace std;

const int MAX_STUDENTU = 100;
const int MAX_GRADES = 10;

string names[MAX_STUDENTU];
int grades[MAX_STUDENTU][MAX_GRADES];
int gradeCount[MAX_STUDENTU];
int studentCount = 0;

void addStudent() {
    if (studentCount >= MAX_STUDENTU) {
        cout << "Mokiniu sarasas pilnas (max " << MAX_STUDENTU << ").\n";
        return;
    }

    cout << "Iveskite mokinio varda: ";
    cin.ignore();
    getline(cin, names[studentCount]);

    gradeCount[studentCount] = 0;

    int n;
    cout << "Kiek pazymiu ivesite? (max " << MAX_GRADES << "): ";
    cin >> n;
    if (n > MAX_GRADES) n = MAX_GRADES;

    for (int i = 0; i < n; i++) {
        cout << "  Pazymys " << (i + 1) << ": ";
        cin >> grades[studentCount][i];
        gradeCount[studentCount]++;
    }

    studentCount++;
    cout << "Mokinys pridetas.\n";
}

void showAll() {
    if (studentCount == 0) {
        cout << "Sarasas tuscias.\n";
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        cout << i + 1 << ". " << names[i] << " | Pazymiai: ";
        for (int j = 0; j < gradeCount[i]; j++) {
            cout << grades[i][j];
            if (j < gradeCount[i] - 1) cout << ", ";
        }
        cout << "\n";
    }
}

void showStudent() {
    if (studentCount == 0) {
        cout << "Sarasas tuscias.\n";
        return;
    }
    showAll();
    cout << "Pasirinkite mokinio numeri: ";
    int idx;
    cin >> idx;
    idx--;
    if (idx < 0 || idx >= studentCount) {
        cout << "Neteisingas pasirinkimas.\n";
        return;
    }
    cout << "Mokinys: " << names[idx] << "\n";
    cout << "Pazymiai: ";
    for (int j = 0; j < gradeCount[idx]; j++) {
        cout << grades[idx][j];
        if (j < gradeCount[idx] - 1) cout << ", ";
    }
    cout << "\n";
}

void updateGrade() {
    if (studentCount == 0) {
        cout << "Sarasas tuscias.\n";
        return;
    }
    showAll();
    cout << "Pasirinkite mokinio numeri: ";
    int idx;
    cin >> idx;
    idx--;
    if (idx < 0 || idx >= studentCount) {
        cout << "Neteisingas pasirinkimas.\n";
        return;
    }
    if (gradeCount[idx] == 0) {
        cout << "Sis mokinys neturi pazymiu.\n";
        return;
    }
    cout << "Pazymiai: ";
    for (int j = 0; j < gradeCount[idx]; j++) {
        cout << j + 1 << "=" << grades[idx][j] << " ";
    }
    cout << "\nKuri pazymi keisti? (numeris): ";
    int gidx;
    cin >> gidx;
    gidx--;
    if (gidx < 0 || gidx >= gradeCount[idx]) {
        cout << "Neteisingas pazymio numeris.\n";
        return;
    }
    cout << "Naujas pazymys: ";
    cin >> grades[idx][gidx];
    cout << "Pazymys atnaujintas.\n";
}

void removeStudent() {
    if (studentCount == 0) {
        cout << "Sarasas tuscias.\n";
        return;
    }
    showAll();
    cout << "Pasirinkite mokinio numeri, kuri norite pasalinti: ";
    int idx;
    cin >> idx;
    idx--;
    if (idx < 0 || idx >= studentCount) {
        cout << "Neteisingas pasirinkimas.\n";
        return;
    }
    cout << "Mokinys \"" << names[idx] << "\" pasalintas.\n";
    for (int i = idx; i < studentCount - 1; i++) {
        names[i] = names[i + 1];
        gradeCount[i] = gradeCount[i + 1];
        for (int j = 0; j < MAX_GRADES; j++) {
            grades[i][j] = grades[i + 1][j];
        }
    }
    studentCount--;
}

int main() {
    int choice;
    do {
        cout << "\n=== Mokiniu pazymiu sistema ===\n";
        cout << "1. Prideti mokini\n";
        cout << "2. Rodyti visus mokinius\n";
        cout << "3. Rodyti konkretu mokini\n";
        cout << "4. Atnaujinti pazymi\n";
        cout << "5. Pasalinti mokini\n";
        cout << "0. Iseiti\n";
        cout << "Pasirinkimas: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent();    break;
            case 2: showAll();       break;
            case 3: showStudent();   break;
            case 4: updateGrade();   break;
            case 5: removeStudent(); break;
            case 0: cout << "Programa baigta.\n"; break;
            default: cout << "Nezinomas pasirinkimas.\n";
        }
    } while (choice != 0);

    return 0;
}