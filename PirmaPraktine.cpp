#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// apvalinimo formule
double round2(double value) {
    return round(value * 100.0) / 100.0;
}

int main() {

    const double GBP_Bendras   = 0.8729;
    const double GBP_Pirkti    = 0.8600;
    const double GBP_Parduoti  = 0.9220;

    const double USD_Bendras   = 1.1793;
    const double USD_Pirkti    = 1.1460;
    const double USD_Parduoti  = 1.2340;

    const double INR_Bendras   = 104.6918;
    const double INR_Pirkti    = 101.3862;
    const double INR_Parduoti  = 107.8546;

    int pasirinkimas;
    int valiuta;
    double kiekis;
    double rezultatas = 0;

    // meniu pasirinkimai
    cout << "keitykla\n";
    cout << "1-palygint kursa\n";
    cout << "2-pirkti valiuta\n";
    cout << "3-parduoti valiuta\n";
    cout << "pasirinkite veiksma: ";
    cin >> pasirinkimas;

    cout << "\npasirinkite valiuta:\n";
    cout << "1-GBP\n";
    cout << "2-USD\n";
    cout << "3-INR\n";
    cout << "iveskite veiksmo skaiciu:";
    cin >> valiuta;

    if (pasirinkimas == 1) {
        // kursu palyginimai
        if (valiuta == 1)
            cout << "1eur = " << GBP_Bendras << " GBP\n";
        else if (valiuta == 2)
            cout << "1eur = " << USD_Bendras << " USD\n";
        else if (valiuta == 3)
            cout << "1eur = " << INR_Bendras << " INR\n";
        else
            cout << "neteisingas pasirinkimas.\n";
    }
    else if (pasirinkimas == 2) {
        // valiutos pirkimas (is EUR i kita valiuta)
        cout << "iveskite uz kiek euru norite pirkti: ";
        cin >> kiekis;

        if (valiuta == 1)
            rezultatas = kiekis * GBP_Pirkti;
        else if (valiuta == 2)
            rezultatas = kiekis * USD_Pirkti;
        else if (valiuta == 3)
            rezultatas = kiekis * INR_Pirkti;
        else {
            cout << "neteisinga ivestis\n";
            return 0;
        }

        cout << "gausite: " << fixed << setprecision(2)
             << round2(rezultatas) << endl;
    }
    else if (pasirinkimas == 3) {
        // valiutos pardavimas (is kitos valiutos i EUR)
        cout << "iveskite kiek norite parduoti valiutos: ";
        cin >> kiekis;

        if (valiuta == 1)
            rezultatas = kiekis / GBP_Parduoti;
        else if (valiuta == 2)
            rezultatas = kiekis / USD_Parduoti;
        else if (valiuta == 3)
            rezultatas = kiekis / INR_Parduoti;
        else {
            cout << "neteisinga ivestis\n";
            return 0;
        }

        cout << "gausite: " << fixed << setprecision(2)
             << round2(rezultatas) << " EUR" << endl;
    }
    else {
        cout << "neteisinga ivestis\n";
    }

    return 0;
}




