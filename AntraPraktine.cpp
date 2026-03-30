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

        switch (pasirinkimas) {

            case 1: {
                // tikrinama ar sarase dar yra laisvos vietos naujam mokiniui
                if (mokiniuKiekis >= MAX_MOKINIU) {
                    cout << "negalima prideti daugiau nei 100 mokiniu\n";
                    break;
                }

                char vardas[30];
                cout << "ivesk mokinio varda (be tarpu): ";
                cin >> vardas;

                // tikrinama ar mokinys tokiu vardu jau neegzistuoja sarase
                if (rastiMokini(vardai, mokiniuKiekis, vardas) != -1) {
                    cout << "toks mokinys jau yra sarase\n";
                    break;
                }

                // simboliu kopijavimas i pagrindini vardu masyva
                int i = 0;
                while (vardas[i] != '\0' && i < 29) {
                    vardai[mokiniuKiekis][i] = vardas[i];
                    i++;
                }
                vardai[mokiniuKiekis][i] = '\0';

                int n;
                cout << "Kiek pazymiu (0-10): ";
                cin >> n;

                // uztikrinama kad pazymiu kiekis nevirsytu leistinu ribu
                if (n < 0) n = 0;
                if (n > 10) n = 10;

                kiekPazymiu[mokiniuKiekis] = n;

                // pazymiu suvedimas i dvimati masyva su reiksmiu tikrinimu
                for (int j = 0; j < n; j++) {
                    cout << "Ivesk " << (j + 1) << "-aji pazymi (1-10): ";
                    cin >> pazymiai[mokiniuKiekis][j];

                    if (pazymiai[mokiniuKiekis][j] < 1) pazymiai[mokiniuKiekis][j] = 1;
                    if (pazymiai[mokiniuKiekis][j] > 10) pazymiai[mokiniuKiekis][j] = 10;
                }

                mokiniuKiekis++;
                cout << "Mokinys pridetas\n";
                break;
            }

            case 2: {
                // patikra ar sarasas nera tuscias pries bandant ji rodyti
                if (mokiniuKiekis == 0) {
                    cout << "Sarasas tuscias\n";
                    break;
                }

                // ciklas kuris isspausdina visus vardus ir turimu pazymiu kiekius
                cout << "\nVISI MOKINIAI\n";
                for (int i = 0; i < mokiniuKiekis; i++) {
                    cout << (i + 1) << ") " << vardai[i] << " (pazymiu: " << kiekPazymiu[i] << ")\n";
                }
                break;
            }

            case 3: {
                if (mokiniuKiekis == 0) {
                    cout << "sarasas tuscias\n";
                    break;
                }

                char ieskomas[30];
                cout << "Ivesk mokinio varda: ";
                cin >> ieskomas;

                // ieskoma konkretaus asmens vieta masyve pagal varda
                int idx = rastiMokini(vardai, mokiniuKiekis, ieskomas);
                if (idx == -1) {
                    cout << "Mokinys nerastas\n";
                    break;
                }

                // isvedami visi rasto mokinio pazymiai jei jis ju turi
                cout << "Mokinys: " << vardai[idx] << "\nPazymiai: ";
                if (kiekPazymiu[idx] == 0) {
                    cout << "(nera)\n";
                } else {
                    for (int j = 0; j < kiekPazymiu[idx]; j++) {
                        cout << pazymiai[idx][j] << " ";
                    }
                    cout << "\n";
                }
                break;
            }

            case 4: {
                if (mokiniuKiekis == 0) {
                    cout << "Sarasas tuscias\n";
                    break;
                }

                char ieskomas[30];
                cout << "Ivesk mokinio varda: ";
                cin >> ieskomas;

                int idx = rastiMokini(vardai, mokiniuKiekis, ieskomas);
                if (idx == -1) {
                    cout << "Mokinys nerastas\n";
                    break;
                }

                if (kiekPazymiu[idx] == 0) {
                    cout << "Sis mokinys neturi pazymiu\n";
                    break;
                }

                // vartotojas pasirenka kuri konkretu pazymi is eiles nori pakeisti
                int kelintas;
                cout << "Kuri pazymi keisti? (1-" << kiekPazymiu[idx] << "): ";
                cin >> kelintas;

                if (kelintas < 1 || kelintas > kiekPazymiu[idx]) {
                    cout << "Neteisingas numeris\n";
                    break;
                }

                int naujas;
                cout << "Ivesk nauja pazymi (1-10): ";
                cin >> naujas;

                if (naujas < 1) naujas = 1;
                if (naujas > 10) naujas = 10;

                // atnaujinama reiksme pazymiu masyve nurodytoje vietoje
                pazymiai[idx][kelintas - 1] = naujas;
                cout << "Pazymys atnaujintas\n";
                break;
            }

            case 5: {
                if (mokiniuKiekis == 0) {
                    cout << "Sarasas tuscias\n";
                    break;
                }

                char ieskomas[30];
                cout << "Ivesk mokinio varda, kuri salinti: ";
                cin >> ieskomas;

                int idx = rastiMokini(vardai, mokiniuKiekis, ieskomas);
                if (idx == -1) {
                    cout << "Mokinys nerastas\n";
                    break;
                }

                // elementu poslinkis i kaire kad butu uzimta istrinto mokinio vieta
                for (int i = idx; i < mokiniuKiekis - 1; i++) {
                    // perkopijuojamas sekantis vardas i dabartine vieta
                    int k = 0;
                    while (vardai[i + 1][k] != '\0') {
                        vardai[i][k] = vardai[i + 1][k];
                        k++;
                    }
                    vardai[i][k] = '\0';

                    // perkeliamas pazymiu skaicius ir visi pazymiai
                    kiekPazymiu[i] = kiekPazymiu[i + 1];
                    for (int j = 0; j < MAX_PAZYMIU; j++) {
                        pazymiai[i][j] = pazymiai[i + 1][j];
                    }
                }

                // sumazinamas bendras mokiniu skaicius sarase
                mokiniuKiekis--;
                cout << "Mokinys pasalintas\n";
                break;
            }

            case 0:
                cout << "Iki!\n";
                break;

            default:
                cout << "Tokio pasirinkimo nera\n";
                break;
        }

    } while (pasirinkimas != 0);

    return 0;
}