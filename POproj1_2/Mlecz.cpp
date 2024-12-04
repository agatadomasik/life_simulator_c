#include <iostream>
#include <random>
#include "Mlecz.h"
#include "Swiat.h"
using namespace std;

Mlecz::Mlecz(int a, int b, Swiat* s) {
	nazwa = "Mlecz";
	sila = 0;
	inicjatywa = 0;
	x = a;
	y = b;
	swiat = s;
    wiek = 0;
}

void Mlecz::rysowanie() {
	cout << "M";
}


Organizm* Mlecz::rozmnozSie(int a, int b) {
	return new Mlecz(a, b, swiat);
}



void Mlecz::akcja(char c) {
    for (int i = 0; i < 3; i++) {
        if (swiat->czyPuste(x + 1, y) || swiat->czyPuste(x - 1, y) || swiat->czyPuste(x, y + 1) || swiat->czyPuste(x, y - 1)) {
            do {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> dis(1, 4);
                int n = dis(gen);

                //Sprawdzanie pol wokol this
                if (n == 1) {
                    if (x < swiat->getN() - 1) {
                        if (swiat->czyPuste(x + 1, y)) {
                            swiat->dodajOrganizm(this->rozmnozSie(x + 1, y));
                            break;
                        }
                    }
                }
                else if (n == 2) {
                    if (x > 0) {
                        if (swiat->czyPuste(x - 1, y)) {
                            swiat->dodajOrganizm(this->rozmnozSie(x - 1, y));
                            break;
                        }
                    }
                }
                else if (n == 3) {
                    if (y < swiat->getM() - 1) {
                        if (swiat->czyPuste(x, y + 1)) {
                            swiat->dodajOrganizm(this->rozmnozSie(x, y + 1));
                            break;
                        }
                    }
                }
                else if (n == 4) {
                    if (y > 0) {
                        if (swiat->czyPuste(x, y - 1)) {
                            swiat->dodajOrganizm(this->rozmnozSie(x, y - 1));
                            break;
                        }
                    }
                }
            } while (true);
        }
    }
}

