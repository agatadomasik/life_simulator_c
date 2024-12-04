#include <iostream>
#include <stdlib.h>
#include <random>
#include "Zwierze.h"
#include "Swiat.h"
using namespace std;

extern bool is_alive;
extern vector<string> events;

bool czyZwierze(string s) {
    if (s == "Wilk" || s == "Owca" || s == "Lis" || s == "Zolw" || s == "Antylopa" || s == "Czlowiek") return true;
    return false;
}

bool czyOdpiera(Organizm* o) {
    if (o->getNazwa() == "Zolw") return true;
    return false;
}

bool czyUcieka(Organizm* o) {
    if (o->getNazwa() == "Antylopa") return true;
    return false;
}

void Zwierze::akcja(char c) {
    do {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1, 4);
        int n = dis(gen);
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


void Zwierze::kolizja(Organizm* other) {
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
                            events.push_back("Narodziny [" + this->getNazwa() + "]");
                            break;
                        }
                    }
                }
                else if (n == 2) {
                    if (x > 0) {
                        if (swiat->czyPuste(x - 1, y)) {
                            swiat->dodajOrganizm(this->rozmnozSie(x - 1, y));
                            events.push_back("Narodziny [" + this->getNazwa() + "]");
                            break;
                        }
                    }
                }
                else if (n == 3) {
                    if (y < swiat->getM() - 1) {
                        if (swiat->czyPuste(x, y + 1)) {
                            swiat->dodajOrganizm(this->rozmnozSie(x, y + 1));
                            events.push_back("Narodziny [" + this->getNazwa() + "]");
                            break;
                        }
                    }
                }
                else if (n == 4) {
                    if (y > 0) {
                        if (swiat->czyPuste(x, y - 1)) {
                            swiat->dodajOrganizm(this->rozmnozSie(x, y - 1));
                            events.push_back("Narodziny [" + this->getNazwa() + "]");
                            break;
                        }
                    }
                }

                //Sprawdzanie pol wokol other
                if (n == 1) {
                    if (x < swiat->getN() - 1) {
                        if (swiat->czyPuste(other->getX() + 1, other->getY())) {
                            swiat->dodajOrganizm(this->rozmnozSie(x + 1, y));
                            events.push_back("Narodziny [" + this->getNazwa() + "]");
                            break;
                        }
                    }
                }
                else if (n == 2) {
                    if (x > 0) {
                        if (swiat->czyPuste(other->getX() - 1, other->getY())) {
                            swiat->dodajOrganizm(this->rozmnozSie(x - 1, y));
                            events.push_back("Narodziny [" + this->getNazwa() + "]");
                            break;
                        }
                    }
                }
                else if (n == 3) {
                    if (y < swiat->getM() - 1) {
                        if (swiat->czyPuste(other->getX(), other->getY() + 1)) {
                            swiat->dodajOrganizm(this->rozmnozSie(x, y + 1));
                            events.push_back("Narodziny [" + this->getNazwa() + "]");
                            break;
                        }
                    }
                }
                else if (n == 4) {
                    if (y > 0) {
                        if (swiat->czyPuste(other->getX(), other->getY() - 1)) {
                            swiat->dodajOrganizm(this->rozmnozSie(x, y - 1));
                            events.push_back("Narodziny [" + this->getNazwa() + "]");
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
                if (!czyUcieka(other)) {
                    if (other->getNazwa() == "Czlowiek") is_alive = 0;
                    if (czyZwierze(other->getNazwa())) events.push_back( "[" + nazwa + "] zabija [" + other->getNazwa() + "]");
                    else {
                        events.push_back("[" + nazwa + "] zjada [" + other->getNazwa() + "]");
                        other->kolizja(this);
                    }
                    swiat->usunOrganizm(other);
                    swiat->usunOrganizm(this);
                    this->setX(other->getX());
                    this->setY(other->getY());
                    swiat->dodajOrganizm(this);
                }
                else {
                    swiat->usunOrganizm(this);
                    this->setX(other->getX());
                    this->setY(other->getY());
                    other->kolizja(this);
                    swiat->dodajOrganizm(this);
                }
            }
            else other->kolizja(this);
        }
        else {
            events.push_back("[" + other->getNazwa() + "] zabija [" + nazwa + "]");
            if (nazwa == "Czlowiek") is_alive = 0;
            swiat->usunOrganizm(this);
        }
    }

}