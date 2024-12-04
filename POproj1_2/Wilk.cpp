#include <iostream>

#include "Wilk.h"
#include "Swiat.h"
using namespace std;

Wilk::Wilk(int a, int b, Swiat* s) {
	nazwa = "Wilk";
	sila = 9;
	inicjatywa = 5;
	x = a;
	y = b;
	swiat = s;
	wiek = 0;
}

void Wilk::rysowanie() {
	cout << "W";
}


Organizm* Wilk::rozmnozSie(int a, int b) {
    return new Wilk(a, b, swiat);
}