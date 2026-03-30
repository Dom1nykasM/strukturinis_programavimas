#include <iostream>
using namespace std;

const int MAX_MOKINIU = 100;
const int MAX_PAZYMIU = 10;

// si funkcija lygina du tekstus simbolis po simbolio ir ziuri ar jie sutampa
// grazina 1 jei tekstai identiski arba 0 jei randa bent viena skirtuma
int vienodiVardai(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return 1;
}

// si funkcija perziuri visa vardu masyva ir iesko mokinio pagal nurodyta varda
// grazina mokinio indeksa masyve arba minus viena jei tokio vardo neranda
int rastiMokini(char vardai[][30], int mokiniuKiekis, char ieskomas[]) {
    for (int i = 0; i < mokiniuKiekis; i++) {
        if (vienodiVardai(vardai[i], ieskomas) == 1) return i;
    }
    return -1;
}

// pagrindine funkcija kurioje prasideda programos vykdymas ir valdomas meniu
int main() {
    char vardai[MAX_MOKINIU][30];
    int pazymiai[MAX_MOKINIU][MAX_PAZYMIU];
    int kiekPazymiu[MAX_MOKINIU];

    int mokiniuKiekis = 0;

    // ciklas skirtas isvalyti masyvus pradzioje nustatant visas reiksmes i nuli
    for (int i = 0; i < MAX_MOKINIU; i++) {
        kiekPazymiu[i] = 0;
        for (int j = 0; j < MAX_PAZYMIU; j++) {
            pazymiai[i][j] = 0;
        }
    }

    int pasirinkimas;

    // ciklas kuris leidzia vartotojui rinktis veiksmus kol jis nepasirenka nulio
    do {
        cout << "\nMOKINIU PAZYMIU SISTEMA\n";
        cout << "1 - ivesti mokini ir pazymius\n";
        cout << "2 - perziureti visus mokinius\n";
        cout << "3 - perziureti konkretaus mokinio pazymius\n";
        cout << "4 - atnaujinti konkretu pazymi\n";
        cout << "5 - pasalinti mokini\n";
        cout << "0 - iseiti\n";
        cout << "pasirinkimas: ";
        cin >> pasirinkimas;
