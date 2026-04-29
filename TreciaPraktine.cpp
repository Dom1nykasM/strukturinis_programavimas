#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// vienam patiekalui saugoti
struct menuItemType {
    string menuItem;   // patiekalo pavadinimas
    double menuPrice;  // patiekalo kaina (2 skaitmenys po kablelio)
};

// uzpildo menuList masyvą duomenimis iš failo menu.txt
// ismeta ikeltu patiekalu sk.
int getData(menuItemType menuList[], int maxSize) {
    ifstream failas("menu.txt"); // atidaro faila skaitymui

    if (!failas.is_open()) {
        cout << "nepavyko aidaryti failo :(" << endl;
        return 0;
    }

    int kiekis = 0;
    // skaito eilute po eilutes kol failas nesibaige ir masyvas nepilnas
    while (kiekis < maxSize && getline(failas, menuList[kiekis].menuItem)) {
        // po pavadinimo einancioje eiluteje skaito kaina
        failas >> menuList[kiekis].menuPrice;
        failas.ignore(); // ignoruoja Enter simboli po kainos
        kiekis++;
    }

    failas.close(); // uzdaro faila
    return kiekis;  // nurodo kiek patiekalu nuskaite
}

// parodo vartotojui visa meniu su kainomis ir leidzia pasirinkti patiekalus
// grazina pasirinktu patiekalu indeksus ir ju porciju kieki
void showMenu(menuItemType menuList[], int kiekis,
              int pasirinkimai[], double porcijos[], int &pasirinktuKiekis) {

    cout << fixed << setprecision(2); // nustatome 2 skaitmenis po kablelio

    cout << "\nSveiki atvyke i restorana \"pusryciai\"\n\n";

    // spausdina visa meniu su numeriais ir kainomis
    cout << left << setw(30) << "Patiekalo pavadinimas" << right << setw(10) << "Kaina (EUR)" << endl;
    cout << string(42, '-') << endl;
    for (int i = 0; i < kiekis; i++) {
        cout << i + 1 << ". " << left << setw(28) << menuList[i].menuItem
             << right << setw(8) << menuList[i].menuPrice << "EUR" << endl;
    }

    pasirinktuKiekis = 0;

    }
    int skirtinguKiekis;
    cout << "\nKiek skirtingu patiekalu norite uzsisakyti? ";
    cin >> skirtinguKiekis;

    // Kiekvienam pasirinktam patiekalui praso numerio ir porciju kiekio
    for (int i = 0; i < skirtinguKiekis; i++) {
        int numeris;
        double porcijuKiekis;

        cout << "Iveskite patiekalo numeri: ";
        cin >> numeris;

        // Patikrina ar numeris teisingas
        if (numeris < 1 || numeris > kiekis) {
            cout << "Neteisingas numeris" << endl;
            continue;
        }

        cout << "Iveskite porciju kieki: ";
        cin >> porcijuKiekis;

        pasirinkimai[pasirinktuKiekis] = numeris - 1; // isaugo indeksa (nuo 0)
        porcijos[pasirinktuKiekis] = porcijuKiekis;   // isaugo porciju kieki
        pasirinktuKiekis++;
    }
}

// Apskaiciuoja tarpine suma, pvm ir galutine suma
// Rezultata spausdina ekrane ir iraso i faila receipt.txt
void printCheck(menuItemType menuList[], int pasirinkimai[],
                double porcijos[], int pasirinktuKiekis) {

    ofstream kvitas("receipt.txt"); // atidaro kvito faila rasymui

    if (!kvitas.is_open()) {
        cout << "nepavyko sukurti failo receipt.txt" << endl;
        return;
    }

    cout << fixed << setprecision(2);
    kvitas << fixed << setprecision(2);

    // Antraste ekrane ir faile
    string antraste = "Sveiki atvyke i restorana \"pusryciai\"\n";
    cout << "\n" << antraste << "\n";
    kvitas << antraste << "\n";

    double tarpineSuma = 0.0;

    // spausdina kiekviena pasirinkta patiekala su kaina
    for (int i = 0; i < pasirinktuKiekis; i++) {
        int idx = pasirinkimai[i];
        double porcijuKiekis = porcijos[i];
        double eilutesSuma = menuList[idx].menuPrice * porcijuKiekis;
        tarpineSuma += eilutesSuma;

        // Jei daugiau nei 1 porcija rodo kieki pries pavadinima
        if (porcijuKiekis != 1.0) {
            // ekrano rodmenys
            cout << left << porcijuKiekis << " "
                 << setw(28) << menuList[idx].menuItem
                 << right << setw(8) << eilutesSuma << "EUR" << endl;
            // output failas
            kvitas << left << porcijuKiekis << " "
                   << setw(28) << menuList[idx].menuItem
                   << right << setw(8) << eilutesSuma << "EUR" << endl;
        } else {
            // ekranas
            cout << left << setw(30) << menuList[idx].menuItem
                 << right << setw(8) << eilutesSuma << "EUR" << endl;
            // failas
            kvitas << left << setw(30) << menuList[idx].menuItem
                   << right << setw(8) << eilutesSuma << "EUR" << endl;
        }
    }

    // apskaiciuoja pvm ir galutine suma
    double pvm = tarpineSuma * 0.21;
    double galutineSuma = tarpineSuma + pvm;

    cout << "\n";
    kvitas << "\n";

    // galutine suma ekrane ir faile
    cout << left << setw(30) << "Mokesciai (21%)"
         << right << setw(8) << pvm << "EUR" << endl;
    cout << left << setw(30) << "Galutine suma"
         << right << setw(8) << galutineSuma << "EUR" << endl;

    kvitas << left << setw(30) << "Mokesciai (21%)"
           << right << setw(8) << pvm << "EUR" << endl;
    kvitas << left << setw(30) << "Galutine suma"
           << right << setw(8) << galutineSuma << "EUR" << endl;

    kvitas.close(); // uzdaro kvito faila
    cout << "\nKvitas issaugotas faile receipt.txt" << endl;
}

int main() {
    const int MAX = 100; // maksimalus patiekalu skaicius masyve

    menuItemType menuList[MAX]; // masyvas visiems patiekalams
    int pasirinkimai[MAX];      // masyvas pasirinktu patiekalu indeksams
    double porcijos[MAX];       // masyvas porciju kiekiams
    int pasirinktuKiekis = 0;   // kiek patiekalu vartotojas pasirinko

    // nuskaito meniu is failo
    int kiekis = getData(menuList, MAX);

    if (kiekis == 0) {
        cout << "meniu tucias arba failas nerastas" << endl;
        return 1;
    }

    // rodo meniu ir gauna vartotojo pasirinkimus
    showMenu(menuList, kiekis, pasirinkimai, porcijos, pasirinktuKiekis);

    // apskaiciuoja ir spausdina kvita
    if (pasirinktuKiekis > 0) {
        printCheck(menuList, pasirinkimai, porcijos, pasirinktuKiekis);
    } else {
        cout << "nieko nepasirinkta" << endl;
    }

    return 0;
