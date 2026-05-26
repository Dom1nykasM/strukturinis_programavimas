#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using namespace chrono;

// globalus skaitikliai
long long isrinkimoLyginimai = 0;
long long isrinkimoSukeitimai = 0;
long long salajinioLyginimai = 0;
long long salajinioPerkelijmai = 0;

//  isrinkimo rikiavimas
void isrinkimoRikiavimas(vector<int>& masyvas) {
    int n = masyvas.size();
    for (int i = 0; i < n - 1; i++) {
        int maziausiasIndeksas = i;
        for (int j = i + 1; j < n; j++) {
            isrinkimoLyginimai++;
            if (masyvas[j] < masyvas[maziausiasIndeksas])
                maziausiasIndeksas = j;
        }
        if (maziausiasIndeksas != i) {
            swap(masyvas[i], masyvas[maziausiasIndeksas]);
            isrinkimoSukeitimai++;
        }
    }
}

//  salajinis rikiavimas
void sujungti(vector<int>& masyvas, int kaire, int vidurys, int desine) {
    vector<int> kaireDalis(masyvas.begin() + kaire, masyvas.begin() + vidurys + 1);
    vector<int> desineDalis(masyvas.begin() + vidurys + 1, masyvas.begin() + desine + 1);

    int i = 0, j = 0, k = kaire;
    while (i < (int)kaireDalis.size() && j < (int)desineDalis.size()) {
        salajinioLyginimai++;
        if (kaireDalis[i] <= desineDalis[j]) {
            masyvas[k++] = kaireDalis[i++];
        } else {
            masyvas[k++] = desineDalis[j++];
        }
        salajinioPerkelijmai++;
    }
    while (i < (int)kaireDalis.size())  { masyvas[k++] = kaireDalis[i++];  salajinioPerkelijmai++; }
    while (j < (int)desineDalis.size()) { masyvas[k++] = desineDalis[j++]; salajinioPerkelijmai++; }
}

void salajinisRikiavimas(vector<int>& masyvas, int kaire, int desine) {
    if (kaire < desine) {
        int vidurys = kaire + (desine - kaire) / 2;
        salajinisRikiavimas(masyvas, kaire, vidurys);
        salajinisRikiavimas(masyvas, vidurys + 1, desine);
        sujungti(masyvas, kaire, vidurys, desine);
    }
}

//  duomenu generavimo funkcijos
vector<int> generuotiAtsitiktinius(int n, int sekla = 42) {
    mt19937 atsitiktinumas(sekla);
    uniform_int_distribution<int> pasiskirstymas(1, 100000);
    vector<int> masyvas(n);
    for (auto& x : masyvas) x = pasiskirstymas(atsitiktinumas);
    return masyvas;
}

// jau surikiuoti duomenys (didejimo tvarka)
vector<int> generuotiSurikiuotus(int n) {
    vector<int> masyvas(n);
    for (int i = 0; i < n; i++) masyvas[i] = i + 1;
    return masyvas;
}

// atvirksciai surikiuoti duomenys (mazejimo tvarka)
vector<int> generuotiAtvirksciai(int n) {
    vector<int> masyvas(n);
    for (int i = 0; i < n; i++) masyvas[i] = n - i;
    return masyvas;
}

//  pagalbines funkcijos
void spausdintiRezultatus(const string& pavadinimas,
                          long long lyginimai,
                          long long sukeitimai,
                          const string& suketimuEtikete,
                          double mikrosekundes) {
    cout << "\n=== " << pavadinimas << " ===\n";
    cout << "  laikas      " << mikrosekundes << " mks\n";
    cout << "  palyginimai " << lyginimai << "\n";
    cout << "  " << suketimuEtikete << " " << sukeitimai << "\n";
}

void testuotiAbu(const string& duomenuTipas, vector<int> originalus) {
    cout << "\n--- " << duomenuTipas << " ---\n";

    // isrinkimo rikiavimas
    isrinkimoLyginimai = isrinkimoSukeitimai = 0;
    vector<int> masyvas1 = originalus;

    auto pradzia1 = high_resolution_clock::now();
    isrinkimoRikiavimas(masyvas1);
    auto pabaiga1 = high_resolution_clock::now();

    double isrinkimoLaikas =
        duration_cast<microseconds>(pabaiga1 - pradzia1).count();

    spausdintiRezultatus("isrinkimo rikiavimas",
                         isrinkimoLyginimai,
                         isrinkimoSukeitimai,
                         "sukeitimai",
                         isrinkimoLaikas);

    // salajinis rikiavimas
    salajinioLyginimai = salajinioPerkelijmai = 0;
    vector<int> masyvas2 = originalus;

    auto pradzia2 = high_resolution_clock::now();
    salajinisRikiavimas(masyvas2, 0, (int)masyvas2.size() - 1);
    auto pabaiga2 = high_resolution_clock::now();

    double salajinioLaikas =
        duration_cast<microseconds>(pabaiga2 - pradzia2).count();

    spausdintiRezultatus("salajinis rikiavimas",
                         salajinioLyginimai,
                         salajinioPerkelijmai,
                         "perkelimai",
                         salajinioLaikas);
}

//  pagrindinis blokas
int main() {
    const vector<int> dydžiai = {5000, 10000, 50000};

    for (int n : dydžiai) {
        cout << "\n*** masyvo dydis " << n << " ***\n";

        testuotiAbu("nesurikiuoti duomenys",      generuotiAtsitiktinius(n));
        testuotiAbu("atvirksciai surikiuoti",      generuotiAtvirksciai(n));
        testuotiAbu("jau surikiuoti",              generuotiSurikiuotus(n));
    }

    return 0;
}




