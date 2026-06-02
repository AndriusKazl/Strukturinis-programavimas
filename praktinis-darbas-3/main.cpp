#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;
const int max_items = 20;
const double PVM_mokestis = 0.21;
const string restorano_vardas = "Geriausias restoranas";

struct menuPatiekaloTipas {
    string menuPatiekalas;
    double menuKaina;
};
int getData(menuPatiekaloTipas menuSarasas[], int maxDydis) {
    ifstream inFile("menu.txt");
    if (!inFile.is_open()) {
        cerr <<"Klaida: nepavyko atidaryti failo menu.txt"<<endl;
        return 0;
    }
    int count = 0;
    string line;
    while (getline(inFile, line) && count < maxDydis) {
        if (line.empty()) continue;
        size_t lastSpace = line.rfind(' ');
        if (lastSpace == string::npos) continue;
        string name = line.substr(0, lastSpace);
        string priceStr = line.substr(lastSpace + 1);

        try {
            double kaina = stod(priceStr);
            menuSarasas[count].menuPatiekalas = name;
            menuSarasas[count].menuKaina = kaina;
            count ++;
        }
        catch (...) {
            cerr <<"Ispejimas: Nepavyko nuskaityti eilutes: "<< line <<endl;
        }
    }
    inFile.close();
    return count;

}

void rodytMenu(const menuPatiekaloTipas menuSarasas[], int itemCount) {
    cout<<"\n";
    cout<<"=======================================================\n";
    cout<<"Sveiki atvyke i restorana \""<<restorano_vardas<<"\"\n";
    cout<<"========================================================\n";
    cout<<"   Nr.    Patiekalas                           Kaina\n";
    cout<<"========================================================\n";

    for (int i=0; i<itemCount; i++) {
        cout<<" "<<setw(2)<<left<<(i+1)<<". "
            <<setw(34) << left << menuSarasas[i].menuPatiekalas
            << setw(5) << right << fixed << setprecision(2)
            <<menuSarasas[i].menuKaina <<" EUR\n";
    }
    cout<<"========================================================\n";
    cout<<"\nKaip uzsakyt:\n";
    cout<<"  - iveskite patiekalo numeri (1-" << itemCount <<")\n";
    cout<<"  - Po to iveskite porciju skaiciu\n";
    cout<<" - Noredami baigti uzsakyma, iveskite 0\n\n";
}
void spausdintiCeki(const menuPatiekaloTipas menuSarasas[], const int kiekis[], int itemCount) {
    ofstream outFile("cekis.txt");
    if (!outFile.is_open()) {
        cerr<<"Klaida: nepavyko sukurti failo cekis.txt"<<endl;
    }
    double subtotal = 0.0;
    auto printLine = [&](const string& text) {
        cout <<text;
        if (outFile.is_open()) outFile <<text;
    };
    printLine("========================================================\n");
    printLine("   Sveiki atvyke i restorana \""+ restorano_vardas+"\"\n");
    printLine("========================================================\n");

    for (int i=0; i < itemCount; i++) {
        if (kiekis[i] <=0) continue;
        double lineTotal = kiekis[i] * menuSarasas[i].menuKaina;
        subtotal += lineTotal;

        ostringstream line;
        if (kiekis[i] > 1) {
            line << " " << setw(2) << left << kiekis[i] <<"X "
            <<setw(32)<< left << menuSarasas[i].menuPatiekalas
            << setw(7) << right <<fixed <<setprecision(2) << lineTotal << "EUR\n";
        } else {
            line <<"    "
            <<setw(32) <<left << menuSarasas[i].menuPatiekalas
            <<setw(7) << right << fixed <<setprecision(2)<< lineTotal<<" EUR\n";
        }
        printLine(line.str());
    }
    double pvm = subtotal * PVM_mokestis;
    double total = subtotal + pvm;

    ostringstream summary;
    summary << "========================================================\n";
    summary << " " << setw(36) << left << "Tarpine suma"
            << setw(7)<<right<<fixed<<setprecision(2)<<subtotal<<" EUR\n";
    summary << " "<<setw(36)<<left<<" Mokesciai (21%)"
            << setw(7)<<right<<fixed<<setprecision(2)<<pvm     <<" EUR\n";
    summary <<"========================================================\n";
    summary <<" "<<setw(36)<<left <<"Galutine suma"
            <<setw(7)<<right<<fixed<<setprecision(2)<<total    <<" EUR\n";
    summary <<"========================================================\n";
    summary <<"                Aciu! Geros dienos!\n";

    printLine(summary.str());

    if (outFile.is_open()) {
        outFile.close();
        cout<<"\nSaskaita issaugota faile: cekis.txt\n";
    }
}

int main() {
    menuPatiekaloTipas menuSarasas[max_items];
    int kiekis[max_items] = {};

    int itemCount = getData(menuSarasas, max_items);
    if (itemCount ==0) {
        cerr <<"Meniu tuscias arba failas nepasiekiamas. Programa baigiama.\n";
        return 1;
    }
    rodytMenu(menuSarasas, itemCount);

    while (true) {
        int choice;
        cout << "Iveskite patiekalo numeri (0 - baigti): ";
        cin>>choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout<<"Neteisingas ivedimas. Bandykite dar karta.\n";
            continue;
        }
        if (choice == 0) break;
         if (choice < 1 || choice>itemCount) {
         cout<<"Nera tokio patiekalo. Pasirinkite nuo 1 iki "<<itemCount << ".\n";
         continue;
         }

         int porcijos;
         cout<<"porciju skaicius: ";
         cin>>porcijos;

         if (cin.fail()|| porcijos <1) {
             cin.clear();
             cin.ignore(1000, '\n');
             cout<<"Porcijus skaicius turi buti teigiamas skaicius.\n";
             continue;
         }
         kiekis[choice - 1] += porcijos;
         cout<<"prideta: "<<porcijos <<" x " <<menuSarasas[choice - 1].menuPatiekalas<<"\n\n";
    }

    cout<<"\n";
    spausdintiCeki(menuSarasas, kiekis, itemCount);

    return 0;
}
