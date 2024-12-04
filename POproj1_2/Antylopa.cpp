#include <iostream>
#include <random>
#include "Antylopa.h"
#include "Swiat.h"
using namespace std;

bool czyOdpiera(Organizm* o);
bool czyZwierze(string s);
extern bool is_alive;

Antylopa::Antylopa(int a, int b, Swiat* s) {
    nazwa = "Antylopa";
    sila = 4;
    inicjatywa = 4;
    x = a;
    y = b;
    swiat = s;
    wiek = 0;
}

void Antylopa::rysowanie() {
    cout << "A";
}

Organizm* Antylopa::rozmnozSie(int a, int b) {
    return new Antylopa(a, b, swiat);
}


void Antylopa::akcja(char c) {
    do {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1, 4);
        int n = dis(gen);
        if (n == 1) {
            if (x < swiat->getN() - 2) {
                if (swiat->czyPuste(x + 2, y)) {
                    swiat->usunOrganizm(this);
                    x+=2;
                    swiat->dodajOrganizm(this);
                    break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x + 2][y]);
                    break;
                }
            }
        }
        else if (n == 2) {
            if (x > 1) {
                if (swiat->czyPuste(x - 2, y)) {
                    swiat->usunOrganizm(this);
                    x-=2;
                    swiat->dodajOrganizm(this);
                    break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x - 2][y]);
                    break;
                }
            }
        }
        else if (n == 3) {
            if (y < swiat->getM() - 2) {
                if (swiat->czyPuste(x, y + 2)) {
                    swiat->usunOrganizm(this);
                    y+=2;
                    swiat->dodajOrganizm(this);
                    break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x][y + 2]);
                    break;
                }
            }
        }
        else if (n == 4) {
            if (y > 1) {
                if (swiat->czyPuste(x, y - 2)) {
                    swiat->usunOrganizm(this);
                    y-=2;
                    swiat->dodajOrganizm(this);
                    break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x][y - 2]);
                    break;
                }
            }
        }
    } while (true);
}



void Antylopa::kolizja(Organizm* other) {
    //ROZMNA¯ANIE
    if (this->nazwa == other->getNazwa()) {
        if (swiat->czyPuste(x + 2, y) || swiat->czyPuste(x - 2, y) || swiat->czyPuste(x, y + 2) || swiat->czyPuste(x, y - 2)
            || swiat->czyPuste(other->getX() + 2, other->getY()) || swiat->czyPuste(other->getX() - 2, other->getY()) ||
            swiat->czyPuste(other->getX(), other->getY() + 2) || swiat->czyPuste(other->getX(), other->getY() - 2)) {
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
            if (!czyOdpiera(other)) {
                if (czyZwierze(other->getNazwa())) cout << endl << "[" << nazwa << "] zabija [" << other->getNazwa() << "]" << endl;
                else {
                    cout << endl << "[" << nazwa << "] zjada [" << other->getNazwa() << "]" << endl;
                    other->kolizja(this);
                }
                if (other->getNazwa() == "Czlowiek") is_alive = 0;
                swiat->usunOrganizm(other);
                swiat->usunOrganizm(this);
                this->setX(other->getX());
                this->setY(other->getY());
                swiat->dodajOrganizm(this);
            }
            else other->kolizja(this);
        }
        else if (czyZwierze(other->getNazwa())) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis(1, 2);
            int n = dis(gen);
            if (n == 1) {
                cout << endl << "[" << other->getNazwa() << "] zabija [" << nazwa << "]" << endl;
                swiat->usunOrganizm(this);

            }
            else {
                if (swiat->getOrganizmy()[x][y] == this) {
                    this->akcja('a');
                    cout << endl << "[" << nazwa << "] ucieka przed [" << other->getNazwa() << "]" << endl;
                }

            }

        }
        else (other->kolizja(this));
    }

}