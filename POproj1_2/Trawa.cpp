#include <iostream>
#include "Trawa.h"
#include "Swiat.h"
using namespace std;

Trawa::Trawa(int a, int b, Swiat* s) {
	nazwa = "Trawa";
	sila = 0;
	inicjatywa = 0;
	x = a;
	y = b;
	swiat = s;
	wiek = 0;
}

void Trawa::rysowanie() {
	cout << "T";
}


Organizm* Trawa::rozmnozSie(int a, int b) {
	return new Trawa(a, b, swiat);
}