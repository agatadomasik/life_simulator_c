#include <iostream>
#include <random>
#include "Owca.h"
#include "Swiat.h"
using namespace std;

Owca::Owca(int a, int b, Swiat* s) {
    nazwa = "Owca";
    sila = 4;
    inicjatywa = 4;
    x = a;
    y = b;
    swiat = s;
    wiek = 0;
}

void Owca::rysowanie() {
    cout << "O";
}

Organizm* Owca::rozmnozSie(int a, int b) {
    return new Owca(a, b, swiat);
}