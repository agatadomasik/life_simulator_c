#include <iostream>
#include <random>
#include "Zolw.h"
#include "Swiat.h"
using namespace std;

bool czyZwierze(string s);
extern bool is_alive;
extern vector<string> events;


Zolw::Zolw(int a, int b, Swiat* s) {
	nazwa = "Zolw";
	sila = 2;
	inicjatywa = 1;
	x = a;
	y = b;
	swiat = s;
    wiek = 0;
}

void Zolw::rysowanie() {
	cout << "Z";
}


Organizm* Zolw::rozmnozSie(int a, int b) {
	return new Zolw(a, b, swiat);
}

void Zolw::akcja(char c) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 4);
    int n = dis(gen);
    if (n == 1) {
        events.push_back( "[Zolw] sie porusza" );
       
        do {
            n = dis(gen);
            if (n == 1) {
                if (x < swiat->getN() - 1) {
                    if (swiat->czyPuste(x + 1, y)) {
                        swiat->usunOrganizm(this);
                        x++;
                        swiat->dodajOrganizm(this);
                        break;
                    }
                    else {
                        kolizja(swiat->getOrganizmy()[x + 1][y]);
                        break;
                    }
                }
            }
            else if (n == 2) {
                if (x > 0) {
                    if (swiat->czyPuste(x - 1, y)) {
                        swiat->usunOrganizm(this);
                        x--;
                        swiat->dodajOrganizm(this);
                        break;
                    }
                    else {
                        kolizja(swiat->getOrganizmy()[x - 1][y]);
                        break;
                    }
                }
            }
            else if (n == 3) {
                if (y < swiat->getM() - 1) {
                    if (swiat->czyPuste(x, y + 1)) {
                        swiat->usunOrganizm(this);
                        y++;
                        swiat->dodajOrganizm(this);
                        break;
                    }
                    else {
                        kolizja(swiat->getOrganizmy()[x][y + 1]);
                        break;
                    }
                }
            }
            else if (n == 4) {
                if (y > 0) {
                    if (swiat->czyPuste(x, y - 1)) {
                        swiat->usunOrganizm(this);
                        y--;
                        swiat->dodajOrganizm(this);
                        break;
                    }
                    else {
                        kolizja(swiat->getOrganizmy()[x][y - 1]);
                        break;
                    }
                }
            }
        } while (true);
    }
}



void Zolw::kolizja(Organizm* other) {

    //ROZMNA¯ANIE
    if (this->nazwa == other->getNazwa()) {
        if (swiat->czyPuste(x + 1, y) || swiat->czyPuste(x - 1, y) || swiat->czyPuste(x, y + 1) || swiat->czyPuste(x, y - 1)
            || swiat->czyPuste(other->getX() + 1, other->getY()) || swiat->czyPuste(other->getX() - 1, other->getY()) ||
            swiat->czyPuste(other->getX(), other->getY() + 1) || swiat->czyPuste(other->getX(), other->getY() - 1)) {
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

                //Sprawdzanie pol wokol other
                if (n == 1) {
                    if (x < swiat->getN() - 1) {
                        if (swiat->czyPuste(other->getX() + 1, other->getY())) {
                            swiat->dodajOrganizm(this->rozmnozSie(x + 1, y));
                            break;
                        }
                    }
                }
                else if (n == 2) {
                    if (x > 0) {
                        if (swiat->czyPuste(other->getX() - 1, other->getY())) {
                            swiat->dodajOrganizm(this->rozmnozSie(x - 1, y));
                            break;
                        }
                    }
                }
                else if (n == 3) {
                    if (y < swiat->getM() - 1) {
                        if (swiat->czyPuste(other->getX(), other->getY() + 1)) {
                            swiat->dodajOrganizm(this->rozmnozSie(x, y + 1));
                            break;
                        }
                    }
                }
                else if (n == 4) {
                    if (y > 0) {
                        if (swiat->czyPuste(other->getX(), other->getY() - 1)) {
                            swiat->dodajOrganizm(this->rozmnozSie(x, y - 1));
                            break;
                        }
                    }
                }
            } while (true);
        }
    }


    //WALKA
    else {
        if (sila >= other->getSila()) {
            if (czyZwierze(other->getNazwa())) cout << "[" << nazwa << "] zabija [" << other->getNazwa() << "]        " << endl;
            else {
                events.push_back( "[" + nazwa + "] zjada [" + other->getNazwa() + "]");
                other->kolizja(this);
            }
            if (other->getNazwa() == "Czlowiek") is_alive = 0;
            swiat->usunOrganizm(other);
            swiat->usunOrganizm(this);
            this->setX(other->getX());
            this->setY(other->getY());
            swiat->dodajOrganizm(this);
        }
        else {
            if (other->getSila() >= 5) {
                events.push_back("[" + other->getNazwa() + "] zabija [" + nazwa + "]");
                swiat->usunOrganizm(this);
            }
            else events.push_back("[Zolw] odpiera atak [" + other->getNazwa() + "]");
        }
    }


}