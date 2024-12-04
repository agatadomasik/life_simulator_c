#include <iostream>
#include <vector>
#include <string>
#include "Guarana.h"
#include "Swiat.h"

using namespace std;

extern vector<string> events;

Guarana::Guarana(int a, int b, Swiat* s) {
	nazwa = "Guarana";
	sila = 0;
	inicjatywa = 0;
	x = a;
	y = b;
	swiat = s;
	wiek = 0;
}

void Guarana::rysowanie() {
	cout << "G";
}


Organizm* Guarana::rozmnozSie(int a, int b) {
	return new Guarana(a, b, swiat);
}

void Guarana::kolizja(Organizm* other) {
	other->setSila(other->getSila() + 3);
	events.push_back("Sila [" + other->getNazwa() + "] wynosi teraz " + to_string(other->getSila()) );
}