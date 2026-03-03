//
// Created by Andrius on 3/3/2026.
//
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// Valiutų kursai
const double GBP_BENDRAS   = 0.8729;
const double GBP_PIRKTI    = 0.8600;
const double GBP_PARDUOTI  = 0.9220;

const double USD_BENDRAS   = 1.1793;
const double USD_PIRKTI    = 1.1460;
const double USD_PARDUOTI  = 1.2340;

const double INR_BENDRAS   = 104.6918;
const double INR_PIRKTI    = 101.3862;
const double INR_PARDUOTI  = 107.8546;

// Pagalbinės funkcijos
void spausdintiLinija() {
    cout << "----------------------------------------" << endl;
}

string gauti_valiutos_pavadinima(int pasirinkimas) {
    switch (pasirinkimas) {
        case 1: return "GBP";
        case 2: return "USD";
        case 3: return "INR";
        default: return "";
    }
}

void gauti_kursus(int valiuta, double &bendras, double &pirkti, double &parduoti) {
    switch (valiuta) {
        case 1:
            bendras  = GBP_BENDRAS;
            pirkti   = GBP_PIRKTI;
            parduoti = GBP_PARDUOTI;
            break;
        case 2:
            bendras  = USD_BENDRAS;
            pirkti   = USD_PIRKTI;
            parduoti = USD_PARDUOTI;
            break;
        case 3:
            bendras  = INR_BENDRAS;
            pirkti   = INR_PIRKTI;
            parduoti = INR_PARDUOTI;
            break;
    }
}

int pasirinkti_valiuta() {
    int pasirinkimas;
    cout << "\nPassirinkite valiuta:" << endl;
    cout << "  1. GBP - Didziosios Britanijos svaras" << endl;
    cout << "  2. USD - JAV doleris" << endl;
    cout << "  3. INR - Indijos rupija" << endl;
    cout << "Jusu pasirinkimas: ";

    while (!(cin >> pasirinkimas) || pasirinkimas < 1 || pasirinkimas > 3) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Neteisingas pasirinkimas! Bandykite dar karta (1-3): ";
    }
    return pasirinkimas;
}

double ivesti_suma() {
    double suma;
    cout << "Iveskite suma: ";
    while (!(cin >> suma) || suma <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Netinkama suma! Iveskite teigiama skaiciu: ";
    }
    return suma;
}

// 1. Valiutos kurso palyginimas
void palyginti_kursus() {
    spausdintiLinija();
    cout << "   VALIUTOS KURSO PALYGINIMAS" << endl;
    spausdintiLinija();

    int valiuta = pasirinkti_valiuta();
    string pavadinimas = gauti_valiutos_pavadinima(valiuta);

    double bendras, pirkti, parduoti;
    gauti_kursus(valiuta, bendras, pirkti, parduoti);

    cout << fixed << setprecision(4);
    spausdintiLinija();
    cout << "  Valiuta    : " << pavadinimas << endl;
    cout << "  Bendras    : 1 EUR = " << bendras  << " " << pavadinimas << endl;
    cout << "  Pirkti     : 1 EUR = " << pirkti   << " " << pavadinimas << endl;
    cout << "  Parduoti   : 1 " << pavadinimas << " = " << parduoti << " EUR" << endl;
    spausdintiLinija();
}

// 2. Valiutos pirkimas (mokami EUR, gaunama pasirinkta valiuta)
void pirkti_valiuta() {
    spausdintiLinija();
    cout << "        VALIUTOS PIRKIMAS" << endl;
    cout << "  (Mokate EUR, gaunate pasirinkta valiuta)" << endl;
    spausdintiLinija();

    int valiuta = pasirinkti_valiuta();
    string pavadinimas = gauti_valiutos_pavadinima(valiuta);

    double bendras, pirkti, parduoti;
    gauti_kursus(valiuta, bendras, pirkti, parduoti);

    cout << "\nUz kiek norite pirkti?" << endl;
    double suma = ivesti_suma();

    double rezultatas = suma * pirkti;

    cout << fixed << setprecision(2);
    spausdintiLinija();
    cout << "  Perkate uz : " << suma << " EUR" << endl;
    cout << "  Kursas     : 1 EUR = " << pirkti << " " << pavadinimas << endl;
    cout << "  Gaunate    : " << rezultatas << " " << pavadinimas << endl;
    spausdintiLinija();
}

// 3. Valiutos pardavimas (parduodama valiuta, gaunami EUR)
void parduoti_valiuta() {
    spausdintiLinija();
    cout << "       VALIUTOS PARDAVIMAS" << endl;
    cout << "  (Parduodate valiuta, gaunate EUR)" << endl;
    spausdintiLinija();

    int valiuta = pasirinkti_valiuta();
    string pavadinimas = gauti_valiutos_pavadinima(valiuta);

    double bendras, pirkti, parduoti;
    gauti_kursus(valiuta, bendras, pirkti, parduoti);

    cout << "\nKiek " << pavadinimas << " norite parduoti?" << endl;
    double suma = ivesti_suma();

    double rezultatas = suma / parduoti;

    cout << fixed << setprecision(2);
    spausdintiLinija();
    cout << "  Parduodate : " << suma << " " << pavadinimas << endl;
    cout << "  Kursas     : 1 " << pavadinimas << " = " << parduoti << " EUR" << endl;
    cout << "  Gaunate    : " << rezultatas << " EUR" << endl;
    spausdintiLinija();
}

int main() {
    int pasirinkimas;

    cout << "========================================" << endl;
    cout << "         VALIUTOS KEITYKLA              " << endl;
    cout << "    Pagrindine valiuta: EUR (Euras)      " << endl;
    cout << "========================================" << endl;

    do {
        cout << "\nPasirinkite veiksma:" << endl;
        cout << "  1. Valiutos kurso palyginimas" << endl;
        cout << "  2. Pirkti valiuta (EUR -> valiuta)" << endl;
        cout << "  3. Parduoti valiuta (valiuta -> EUR)" << endl;
        cout << "  0. Iseiti" << endl;
        cout << "Jusu pasirinkimas: ";

        while (!(cin >> pasirinkimas) || pasirinkimas < 0 || pasirinkimas > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Neteisingas pasirinkimas! Bandykite dar karta (0-3): ";
        }

        switch (pasirinkimas) {
            case 1: palyginti_kursus();  break;
            case 2: pirkti_valiuta();    break;
            case 3: parduoti_valiuta();  break;
            case 0:
                cout << "\nIkisusimato! Programa baigia darba." << endl;
                break;
        }

    } while (pasirinkimas != 0);

    return 0;
}