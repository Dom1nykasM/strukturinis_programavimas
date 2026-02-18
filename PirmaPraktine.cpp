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






