#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

// ============================================================
// STRUCT - automobilio duomenų struktūra
// ============================================================
struct Car {
    int id;
    string marke;
    string modelis;
    int metai;
    double kaina;
    int rida;
};

// ============================================================
// PAGALBINĖS FUNKCIJOS
// ============================================================

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getNextId(const vector<Car>& cars) {
    int maxId = 0;
    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].id > maxId) maxId = cars[i].id;
    }
    return maxId + 1;
}

// ============================================================
// FAILO OPERACIJOS
// ============================================================

vector<Car> loadFromFile(const string& filename) {
    vector<Car> cars;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "[!] Nepavyko atidaryti failo: " << filename << "\n";
        return cars;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;

        Car c;
        string token;
        int field = 0;

        for (int i = 0; i <= line.size(); i++) {
            if (i == line.size() || line[i] == ';') {
                switch (field) {
                    case 0: c.id       = stoi(token); break;
                    case 1: c.marke    = token;       break;
                    case 2: c.modelis  = token;       break;
                    case 3: c.metai    = stoi(token); break;
                    case 4: c.kaina    = stod(token); break;
                    case 5: c.rida     = stoi(token); break;
                }
                token.clear();
                field++;
            } else {
                token += line[i];
            }
        }

        if (field >= 6) {
            cars.push_back(c);
        }
    }

    file.close();
    return cars;
}

void saveToFile(const string& filename, const vector<Car>& cars) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "[!] Nepavyko atidaryti failo rašymui.\n";
        return;
    }

    for (int i = 0; i < cars.size(); i++) {
        file << cars[i].id      << ";"
             << cars[i].marke   << ";"
             << cars[i].modelis << ";"
             << cars[i].metai   << ";"
             << fixed << setprecision(2) << cars[i].kaina << ";"
             << cars[i].rida    << "\n";
    }

    file.close();
}

// ============================================================
// READ - peržiūra
// ============================================================

void printHeader() {
    cout << "\n"
         << left
         << setw(5)  << "ID"
         << setw(14) << "Marke"
         << setw(14) << "Modelis"
         << setw(7)  << "Metai"
         << setw(12) << "Kaina (EUR)"
         << setw(10) << "Rida (km)"
         << "\n";
    cout << string(62, '-') << "\n";
}

void printCarRow(const Car& c) {
    cout << left
         << setw(5)  << c.id
         << setw(14) << c.marke
         << setw(14) << c.modelis
         << setw(7)  << c.metai
         << setw(12) << fixed << setprecision(2) << c.kaina
         << setw(10) << c.rida
         << "\n";
}

void displayAll(const vector<Car>& cars) {
    if (cars.empty()) {
        cout << "[i] Sarasas tuscias.\n";
        return;
    }
    printHeader();
    for (int i = 0; i < cars.size(); i++) {
        printCarRow(cars[i]);
    }
    cout << "\nIs viso: " << cars.size() << " automobilis(-iu)\n";
}

void displayOne(const vector<Car>& cars) {
    int id;
    cout << "Iveskite automobilio ID: ";
    cin >> id;
    clearInput();

    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].id == id) {
            printHeader();
            printCarRow(cars[i]);
            return;
        }
    }
    cout << "[!] Automobilis su ID " << id << " nerastas.\n";
}

// ============================================================
// CREATE - sukūrimas
// ============================================================

void addCar(vector<Car>& cars, const string& filename) {
    Car c;
    c.id = getNextId(cars);

    cout << "\n--- Naujo automobilio ivedimas ---\n";

    cout << "Marke: ";
    getline(cin, c.marke);

    cout << "Modelis: ";
    getline(cin, c.modelis);

    cout << "Metai: ";
    cin >> c.metai;

    cout << "Kaina (EUR): ";
    cin >> c.kaina;

    cout << "Rida (km): ";
    cin >> c.rida;
    clearInput();

    cars.push_back(c);
    saveToFile(filename, cars);
    cout << "[+] Automobilis pridetas (ID: " << c.id << ").\n";
}

// ============================================================
// UPDATE - redagavimas
// ============================================================

void updateCar(vector<Car>& cars, const string& filename) {
    int id;
    cout << "Iveskite redaguojamo automobilio ID: ";
    cin >> id;
    clearInput();

    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].id == id) {
            cout << "\n--- Redaguojamas automobilis (ID: " << id << ") ---\n";
            cout << "Nauja marke [" << cars[i].marke << "]: ";
            string input;
            getline(cin, input);
            if (!input.empty()) cars[i].marke = input;

            cout << "Naujas modelis [" << cars[i].modelis << "]: ";
            getline(cin, input);
            if (!input.empty()) cars[i].modelis = input;

            cout << "Nauji metai [" << cars[i].metai << "]: ";
            getline(cin, input);
            if (!input.empty()) cars[i].metai = stoi(input);

            cout << "Nauja kaina [" << cars[i].kaina << "]: ";
            getline(cin, input);
            if (!input.empty()) cars[i].kaina = stod(input);

            cout << "Nauja rida [" << cars[i].rida << "]: ";
            getline(cin, input);
            if (!input.empty()) cars[i].rida = stoi(input);

            saveToFile(filename, cars);
            cout << "[+] Automobilis atnaujintas.\n";
            return;
        }
    }
    cout << "[!] Automobilis su ID " << id << " nerastas.\n";
}

// ============================================================
// DELETE - šalinimas
// ============================================================

void deleteCar(vector<Car>& cars, const string& filename) {
    int id;
    cout << "Iveskite trinamo automobilio ID: ";
    cin >> id;
    clearInput();

    for (int i = 0; i < cars.size(); i++) {
        if (cars[i].id == id) {
            cout << "Ar tikrai norite istrinti: " << cars[i].marke << " " << cars[i].modelis << "? (t/n): ";
            char patvirtinimas;
            cin >> patvirtinimas;
            clearInput();

            if (patvirtinimas == 't' || patvirtinimas == 'T') {
                cars.erase(cars.begin() + i);
                saveToFile(filename, cars);
                cout << "[-] Automobilis istrintas.\n";
            } else {
                cout << "[i] Istrynimas atsauktas.\n";
            }
            return;
        }
    }
    cout << "[!] Automobilis su ID " << id << " nerastas.\n";
}

// ============================================================
// PAPILDOMA 1 - Rikiavimas
// ============================================================

void sortCars(vector<Car>& cars) {
    if (cars.empty()) { cout << "[i] Sarasas tuscias.\n"; return; }

    cout << "\nRikiuoti pagal:\n";
    cout << "  1. Kaina (nuo maziausios)\n";
    cout << "  2. Kaina (nuo didziausios)\n";
    cout << "  3. Metus (nuo naujausio)\n";
    cout << "  4. Rida (nuo maziausios)\n";
    cout << "Pasirinkimas: ";

    int pasirinkimas;
    cin >> pasirinkimas;
    clearInput();

    if (pasirinkimas == 1) {
        for (int i = 0; i < cars.size() - 1; i++) {
            for (int j = i + 1; j < cars.size(); j++) {
                if (cars[i].kaina > cars[j].kaina) swap(cars[i], cars[j]);
            }
        }
        cout << "[+] Surikiuota pagal kaina (maziausia pirma).\n";
    } else if (pasirinkimas == 2) {
        for (int i = 0; i < cars.size() - 1; i++) {
            for (int j = i + 1; j < cars.size(); j++) {
                if (cars[i].kaina < cars[j].kaina) swap(cars[i], cars[j]);
            }
        }
        cout << "[+] Surikiuota pagal kaina (didziausia pirma).\n";
    } else if (pasirinkimas == 3) {
        for (int i = 0; i < cars.size() - 1; i++) {
            for (int j = i + 1; j < cars.size(); j++) {
                if (cars[i].metai < cars[j].metai) swap(cars[i], cars[j]);
            }
        }
        cout << "[+] Surikiuota pagal metus (naujausi pirma).\n";
    } else if (pasirinkimas == 4) {
        for (int i = 0; i < cars.size() - 1; i++) {
            for (int j = i + 1; j < cars.size(); j++) {
                if (cars[i].rida > cars[j].rida) swap(cars[i], cars[j]);
            }
        }
        cout << "[+] Surikiuota pagal rida (maziausia pirma).\n";
    } else {
        cout << "[!] Nezinomas pasirinkimas.\n";
        return;
    }

    displayAll(cars);
}

// ============================================================
// PAPILDOMA 2 - Paieška
// ============================================================

void searchCars(const vector<Car>& cars) {
    if (cars.empty()) { cout << "[i] Sarasas tuscias.\n"; return; }

    cout << "\nPaieska pagal:\n";
    cout << "  1. Marke\n";
    cout << "  2. Metu intervala\n";
    cout << "  3. Kainos intervala\n";
    cout << "Pasirinkimas: ";

    int pasirinkimas;
    cin >> pasirinkimas;
    clearInput();

    vector<Car> rezultatai;

    if (pasirinkimas == 1) {
        cout << "Iveskite marke: ";
        string paieska;
        getline(cin, paieska);

        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].marke == paieska) {
                rezultatai.push_back(cars[i]);
            }
        }

    } else if (pasirinkimas == 2) {
        int nuo, iki;
        cout << "Nuo metu: ";
        cin >> nuo;
        cout << "Iki metu: ";
        cin >> iki;
        clearInput();

        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].metai >= nuo && cars[i].metai <= iki) {
                rezultatai.push_back(cars[i]);
            }
        }

    } else if (pasirinkimas == 3) {
        double nuo, iki;
        cout << "Nuo kainos (EUR): ";
        cin >> nuo;
        cout << "Iki kainos (EUR): ";
        cin >> iki;
        clearInput();

        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].kaina >= nuo && cars[i].kaina <= iki) {
                rezultatai.push_back(cars[i]);
            }
        }

    } else {
        cout << "[!] Nezinomas pasirinkimas.\n";
        return;
    }

    if (rezultatai.empty()) {
        cout << "[i] Pagal nurodytus kriterijus rezultatu nerasta.\n";
    } else {
        cout << "\nRasta rezultatu: " << rezultatai.size() << "\n";
        printHeader();
        for (int i = 0; i < rezultatai.size(); i++) {
            printCarRow(rezultatai[i]);
        }
    }
}

// ============================================================
// MENIU
// ============================================================

void printMenu() {
    cout << "\n========================================\n";
    cout << "   AUTOMOBILIU VALDYMO SISTEMA\n";
    cout << "========================================\n";
    cout << "  1. Rodyti visus automobilius\n";
    cout << "  2. Ieskoti pagal ID\n";
    cout << "  3. Prideti nauja automobili\n";
    cout << "  4. Redaguoti automobili\n";
    cout << "  5. Istrinti automobili\n";
    cout << "  6. Rikiuoti sarasa\n";
    cout << "  7. Paieska / filtravimas\n";
    cout << "  0. Iseiti\n";
    cout << "----------------------------------------\n";
    cout << "Pasirinkimas: ";
}

// ============================================================
// MAIN
// ============================================================

int main() {
    const string filename = "cars.txt";
    vector<Car> cars = loadFromFile(filename);

    cout << "[i] Uzkrauta " << cars.size() << " automobiliu is failo.\n";

    int pasirinkimas;
    do {
        printMenu();
        cin >> pasirinkimas;
        clearInput();

        switch (pasirinkimas) {
            case 1: displayAll(cars);            break;
            case 2: displayOne(cars);            break;
            case 3: addCar(cars, filename);      break;
            case 4: updateCar(cars, filename);   break;
            case 5: deleteCar(cars, filename);   break;
            case 6: sortCars(cars);              break;
            case 7: searchCars(cars);            break;
            case 0: cout << "Iki pasimatymo!\n"; break;
            default: cout << "[!] Nezinomas pasirinkimas.\n"; break;
        }

    } while (pasirinkimas != 0);

    return 0;
}