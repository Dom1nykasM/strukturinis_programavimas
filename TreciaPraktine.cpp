#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Struktūra vienam meniu patiekalui saugoti
struct menuItemType {
    string menuItem;   // patiekalo pavadinimas
    double menuPrice;  // patiekalo kaina (2 skaitmenys po kablelio)
};

// Užpildo menuList masyvą duomenimis iš failo menu.txt
// Grąžina įkeltų patiekalų skaičių
int getData(menuItemType menuList[], int maxSize) {
    ifstream failas("menu.txt"); // atidarome faila skaitymui

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

    cout << "\nSveiki atvyke i restorana \"pusryciai?\"\n\n";

    // spausdina visa meniu su numeriais ir kainomis
    cout << left << setw(30) << "Patiekalo pavadinimas" << right << setw(10) << "Kaina (EUR)" << endl;
    cout << string(42, '-') << endl;
    for (int i = 0; i < kiekis; i++) {
        cout << i + 1 << ". " << left << setw(28) << menuList[i].menuItem
             << right << setw(8) << menuList[i].menuPrice << "EUR" << endl;
    }

    pasirinktuKiekis = 0;

    }