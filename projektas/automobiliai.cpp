#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// struktura kurioje saugomi visi automobilio duomenys
struct Automobilis {
    string marke;       // automobilio marke
    string modelis;     // modelis
    int metai;          // pagaminimo metai
    int turis;           // variklio turis
    int galia;          // galia
    string tipas;       // tipas
    float kaina;        // kaina
};

// vektoriaus saugykla visiems automobiliams
vector<Automobilis> automobiliai;


// spausdina viena automobili ekrane
void spausdintiAutomobili(const Automobilis& a, int nr) {
    cout << "-------------------------------------" << endl;
    cout << "  nr.      : " << nr << endl;
    cout << "  marke    : " << a.marke << endl;
    cout << "  modelis  : " << a.modelis << endl;
    cout << "  metai    : " << a.metai << endl;
    cout << "  turis     : " << a.turis << " cc" << endl;
    cout << "  galia    : " << a.galia << " ag" << endl;
    cout << "  tipas    : " << a.tipas << endl;
    cout << "  kaina    : " << fixed << setprecision(2) << a.kaina << " eur" << endl;
}

// duomenu irasymas ir nuskaitymas is txt
// issaugo visus automobilius i faila "automobiliai.txt"
void issaugotiIFaila() {
    ofstream failas("automobiliai.txt");
    if (!failas) {
        cout << "klaida: nepavyko atidaryti failo irasymui!" << endl;
        return;
    }
    // eina per kiekviena automobili ir iraso i faila
    for (int i = 0; i < automobiliai.size(); i++) {
        Automobilis a = automobiliai[i];
        failas << a.marke << "\n"
               << a.modelis << "\n"
               << a.metai << "\n"
               << a.turis << "\n"
               << a.galia << "\n"
               << a.tipas << "\n"
               << a.kaina << "\n";
    }
    failas.close();
}

// nuskaito automobilius is failo kai programa paleidziama
void nuskaitytiIsFailo() {
    ifstream failas("automobiliai.txt");
    if (!failas) {
        // jei failo nera nieko nedaro bus ikelti pradiniai duomenys
        return;
    }
    automobiliai.clear(); // isvalo sena sarasa
    Automobilis a;
    // skaito po viena automobili kol baigiasi failas
    while (getline(failas, a.marke)) {
        getline(failas, a.modelis);
        failas >> a.metai >> a.turis >> a.galia;
        failas.ignore();
        getline(failas, a.tipas);
        failas >> a.kaina;
        failas.ignore();
        automobiliai.push_back(a);
    }
    failas.close();
}

// uzpildo pradinius 15 automobiliu jei failas neegzistuoja
void uzpildytiPradinius() {
    // patikriname ar jau yra duomenu
    ifstream patikrinimas("automobiliai.txt");
    if (patikrinimas.good()) {
        patikrinimas.close();
        return; // jei failas jau yra - nepildome is naujo
    }
    patikrinimas.close();

    // pradiniai 15 automobilio irasu
    automobiliai = {
        {"honda",   "del sol",       1993, 1600, 125, "jdm",     8500},
        {"honda",   "del sol vtec",  1995, 1600, 160, "jdm",     9200},
        {"honda",   "civic ek",    1999, 1600, 130, "nejdm",  7800},
        {"toyota",  "supra mk4",     1994, 3000, 320, "jdm",    45000},
        {"nissan",  "skyline r34",   1999, 2600, 280, "jdm",    60000},
        {"nissan",  "silvia s15",    1999, 2000, 250, "jdm",    22000},
        {"mazda",   "rx-7 fd",       1993, 1300, 255, "jdm",    28000},
        {"mazda",   "mx-5 na",       1990, 1600, 115, "jdm",     9000},
        {"honda",   "civic eg",      1992, 1600, 158, "jdm",    11000},
        {"honda",   "integra dc2",   1996, 1800, 190, "jdm",    14000},
        {"subaru",  "impreza gc8",   1997, 2000, 280, "jdm",    18000},
        {"mitsubishi", "lancer evo", 2003, 2000, 276, "jdm",    19500},
        {"toyota",  "ae86 trueno",   1985, 1600, 128, "jdm",    16000},
        {"nissan",  "180sx",         1991, 1800, 205, "jdm",    13000},
        {"honda",   "nsx",           1991, 3000, 274, "jdm",    55000}
    };
    issaugotiIFaila();
    cout << "sukurti 15 pradiniu irasu." << endl;
}

// crud
// prideda nauja automobili i sarasa
void pridetiAutomobili() {
    Automobilis a;
    cout << "\n--- naujo automobilio pridejimas ---" << endl;
    cout << "iveskite marke: ";
    cin >> a.marke;
    cout << "iveskite modeli: ";
    cin >> a.modelis;
    cout << "iveskite gamybos metus: ";
    cin >> a.metai;
    cout << "iveskite variklio turis (cc): ";
    cin >> a.turis;
    cout << "iveskite galia (ag): ";
    cin >> a.galia;
    cout << "iveskite tipa (jdm / ne-jdm): ";
    cin >> a.tipas;
    cout << "iveskite kaina (eur): ";
    cin >> a.kaina;

    automobiliai.push_back(a); // deda i vektoriu
    issaugotiIFaila();          // issaugo i faila
    cout << "automobilis sekmingai pridetas!" << endl;
}

// parodo visus automobilius sarase
void rodytiVisus() {
    if (automobiliai.empty()) {
        cout << "sarasas tuscias." << endl;
        return;
    }
    cout << "\n=== visi automobiliai (" << automobiliai.size() << " vnt.) ===" << endl;
    for (int i = 0; i < automobiliai.size(); i++) {
        spausdintiAutomobili(automobiliai[i], i + 1);
    }
}

// parodo viena automobili pagal numeri sarase
void rodytiViena() {
    if (automobiliai.empty()) {
        cout << "sarasas tuscias." << endl;
        return;
    }
    int nr;
    cout << "iveskite automobilio numeri (1-" << automobiliai.size() << "): ";
    cin >> nr;
    // tikriname ar nurodytas skaicius yra teisingo diapazono
    if (nr < 1 || nr > automobiliai.size()) {
        cout << "neteisinga numer." << endl;
        return;
    }
    spausdintiAutomobili(automobiliai[nr - 1], nr);
}

// leidzia redaguoti egzistuojancio automobilio duomenis
void redaguotiAutomobili() {
    if (automobiliai.empty()) {
        cout << "sarasas tuscias." << endl;
        return;
    }
    rodytiVisus(); //parodo sarasa kad vartotojas matyu numerius
    int nr;
    cout << "\nkuri automobili noturis redaguoti? (1-" << automobiliai.size() << "): ";
    cin >> nr;
    if (nr < 1 || nr > automobiliai.size()) {
        cout << "neteisinga numeris." << endl;
        return;
    }

    // rodo esamus duomenis ir leidzia juos keisti
    Automobilis& a = automobiliai[nr - 1]; // nuoroda i objekta vektoriuje
    cout << "\nredaguojamas: " << a.marke << " " << a.modelis << endl;
    cout << "nauja marke (" << a.marke << "): ";
    cin >> a.marke;
    cout << "naujas modelis (" << a.modelis << "): ";
    cin >> a.modelis;
    cout << "nauji metai (" << a.metai << "): ";
    cin >> a.metai;
    cout << "naujas turis (" << a.turis << " cc): ";
    cin >> a.turis;
    cout << "nauja galia (" << a.galia << " ag): ";
    cin >> a.galia;
    cout << "naujas tipas (" << a.tipas << "): ";
    cin >> a.tipas;
    cout << "nauja kaina (" << a.kaina << " eur): ";
    cin >> a.kaina;

    issaugotiIFaila(); // issaugo pakeitimus
    cout << "automobilis sekmingai atnaujintas!" << endl;
}

// istrina automobili is saraso pagal numeri
void palintiAutomobili() {
    if (automobiliai.empty()) {
        cout << "sarasas tuscias." << endl;
        return;
    }
    rodytiVisus();
    int nr;
    cout << "\nkuri automobili trinti? (1-" << automobiliai.size() << "): ";
    cin >> nr;
    if (nr < 1 || nr > automobiliai.size()) {
        cout << "neteisinga numeris." << endl;
        return;
    }
    cout << "itrintas: " << automobiliai[nr - 1].marke << " " << automobiliai[nr - 1].modelis << endl;
    // erase panaikina elementa pagal pozicija vektoriuje
    automobiliai.erase(automobiliai.begin() + (nr - 1));
    issaugotiIFaila();
    cout << "automobilis sekmingai istrinas!" << endl;
}

// rikiavimas pagal kaina
// naudojam std::sort su savo palyginimo funkcija
bool palyginkainaAsc(const Automobilis& a, const Automobilis& b) {
    return a.kaina < b.kaina;
}

void rikiuotiPagalKaina() {
    if (automobiliai.empty()) {
        cout << "sarasas tuscias." << endl;
        return;
    }
    // std::sort surikiuoja vektoriu pagal funkcija
    sort(automobiliai.begin(), automobiliai.end(), palyginkainaAsc);
    issaugotiIFaila();
    cout << "\nautomobiliai surikiuoti pagal kaina (maziausia pirma):" << endl;
    rodytiVisus();
}

// statistika-vidutine kaina, brangiausias, pigiausias
void rodytiStatistika() {
    if (automobiliai.empty()) {
        cout << "sarasas tuscias." << endl;
        return;
    }

    float suma = 0;
    float max_kaina = automobiliai[0].kaina;
    float min_kaina = automobiliai[0].kaina;
    string max_auto = automobiliai[0].marke + " " + automobiliai[0].modelis;
    string min_auto = automobiliai[0].marke + " " + automobiliai[0].modelis;
    int jdm_kiekis = 0;

    // eina per visus automobilius ir skaiciuoja statistika
    for (int i = 0; i < automobiliai.size(); i++) {
        suma += automobiliai[i].kaina;

        if (automobiliai[i].kaina > max_kaina) {
            max_kaina = automobiliai[i].kaina;
            max_auto = automobiliai[i].marke + " " + automobiliai[i].modelis;
        }
        if (automobiliai[i].kaina < min_kaina) {
            min_kaina = automobiliai[i].kaina;
            min_auto = automobiliai[i].marke + " " + automobiliai[i].modelis;
        }
        if (automobiliai[i].tipas == "jdm") {
            jdm_kiekis++;
        }
    }

    float vidurkis = suma / automobiliai.size();

    cout << "\n=== statistika ===" << endl;
    cout << "viso automobiliu   : " << automobiliai.size() << endl;
    cout << "jdm automobiliu    : " << jdm_kiekis << endl;
    cout << "ne-jdm automobiliu : " << automobiliai.size() - jdm_kiekis << endl;
    cout << "vidutine kaina     : " << fixed << setprecision(2) << vidurkis << " eur" << endl;
    cout << "brangiausias       : " << max_auto << " (" << max_kaina << " eur)" << endl;
    cout << "pigiausias         : " << min_auto << " (" << min_kaina << " eur)" << endl;
}

// parodo pagrindini meniu ekrane
void rodytiMeniu() {
    cout << "\n==============================" << endl;
    cout << "   automobiliu valdymo sistema" << endl;
    cout << "==============================" << endl;
    cout << " 1. rodyti visus automobilius" << endl;
    cout << " 2. rodyti viena automobili" << endl;
    cout << " 3. prideti nauja automobili" << endl;
    cout << " 4. redaguoti automobili" << endl;
    cout << " 5. istrinti automobili" << endl;
    cout << " 6. rikiuoti pagal kaina" << endl;
    cout << " 7. rodyti statistika" << endl;
    cout << " 0. baigti programa" << endl;
    cout << "------------------------------" << endl;
    cout << "pasirinkimas: ";
}

int main() {
    // bando nuskaityti duomenis is failo
    nuskaitytiIsFailo();
    // jei failo nebuvo - uzpildo pradiniais 15 irasu
    uzpildytiPradinius();
    // jei failas buvo tuscias ar neegzistavo dabar nuskaityti is naujo
    if (automobiliai.empty()) {
        nuskaitytiIsFailo();
    }

    int pasirinkimas;

    // pagrindinis ciklas, veikia kol vartotojas nepasirenka 0
    do {
        rodytiMeniu();
        cin >> pasirinkimas;

        // switch patikrina ka vartotojas pasirinko ir ivykdo reikiama funkcija
        switch (pasirinkimas) {
            case 1:
                rodytiVisus();
                break;
            case 2:
                rodytiViena();
                break;
            case 3:
                pridetiAutomobili();
                break;
            case 4:
                redaguotiAutomobili();
                break;
            case 5:
                palintiAutomobili();
                break;
            case 6:
                rikiuotiPagalKaina();
                break;
            case 7:
                rodytiStatistika();
                break;
            case 0:
                cout << "programa isjungiama" << endl;
                break;
            default:
                cout << "neteisinga pasirinkimas, bandykite dar karta." << endl;
        }

    } while (pasirinkimas != 0);

    return 0;
}




