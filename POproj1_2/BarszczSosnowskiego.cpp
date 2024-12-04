#include <iostream>
#include <random>
#include "BarszczSosnowskiego.h"
#include "Swiat.h"
using namespace std;

bool czyZwierze(string s);
extern bool is_alive; 
extern vector<string> events;

BarszczSosnowskiego::BarszczSosnowskiego(int a, int b, Swiat* s) {
	nazwa = "BarszczSosnowskiego";
	sila = 10;
	inicjatywa = 0;
	x = a;
	y = b;
	swiat = s;
    wiek = 0;
}

void BarszczSosnowskiego::rysowanie() {
	cout << "B";
}


Organizm* BarszczSosnowskiego::rozmnozSie(int a, int b) {
	return new BarszczSosnowskiego(a, b, swiat);
}

void BarszczSosnowskiego::akcja(char c) {
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

    if (x < swiat->getN() - 1) {
        if (!swiat->czyPuste(x + 1, y)) {
            kolizja(swiat->getOrganizmy()[x + 1][y]);
        }
    }

    if (x > 0) {
        if (!swiat->czyPuste(x - 1, y)) {
            kolizja(swiat->getOrganizmy()[x - 1][y]);
        }
    }

    if (y < swiat->getM() - 1) {
        if (!swiat->czyPuste(x, y + 1)) {
            kolizja(swiat->getOrganizmy()[x][y + 1]);
        }
    }

    if (y > 0) {
        if (!swiat->czyPuste(x, y - 1)) {
            kolizja(swiat->getOrganizmy()[x][y - 1]);
        }
    }
}

void BarszczSosnowskiego::kolizja(Organizm* other) {
    if (czyZwierze(other->getNazwa())) {
        swiat->usunOrganizm(other);
        if (other->getNazwa() == "Czlowiek") is_alive = 0;
        events.push_back( "[BarszczSosnowskiego] zabija [" + other->getNazwa() + "]" );
    }
}