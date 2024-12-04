#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Czlowiek.h"
#include "Swiat.h"
using namespace std;

bool power = false;
int wait = 0;

extern vector<string> events;

Czlowiek::Czlowiek(int a, int b, Swiat* s) {
	nazwa = "Czlowiek";
	sila = 5;
	inicjatywa = 4;
	x = a;
	y = b;
	swiat = s;
    wiek = 0;
    tura = 0;
}

void Czlowiek::rysowanie() {
	cout << "C";
}


Organizm* Czlowiek::rozmnozSie(int a, int b) {
	return new Czlowiek(a, b, swiat);
}

void Czlowiek::akcja(char c) {
    if (!power) {
        if (c == 77) {
            tura++;
            //cout << "prawo" << endl;
            if (x < swiat->getN() - 1) {
                if (swiat->czyPuste(x + 1, y)) {
                    swiat->usunOrganizm(this);
                    x++;
                    swiat->dodajOrganizm(this);
                    
                    //break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x + 1][y]);
                    //break;
                }
            }
        }
        else if (c == 75) {
            tura++;
            //cout << "lewo" << endl;
            if (x > 0) {
                if (swiat->czyPuste(x - 1, y)) {
                    swiat->usunOrganizm(this);
                    x--;
                    swiat->dodajOrganizm(this);
                    //break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x - 1][y]);
                    //break;
                }
            }
        }
        else if (c == 80) {
            tura++;
            //cout << "dol" << endl;
            if (y < swiat->getM() - 1) {
                if (swiat->czyPuste(x, y + 1)) {
                    swiat->usunOrganizm(this);
                    y++;
                    swiat->dodajOrganizm(this);
                    //break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x][y + 1]);
                    //break;
                }
            }
        }
        else if (c == 0x48) {
            if (y > 0) {
                tura++;
                //cout << "gora" << endl;
                if (swiat->czyPuste(x, y - 1)) {
                    swiat->usunOrganizm(this);
                    y--;
                    swiat->dodajOrganizm(this);
                    //break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x][y - 1]);
                    //break;
                }
            }
        }
    }

    //SZYBKOSC ANTYLOPY
    else {
        if (c == 77) {
            tura++;
            //cout << "prawo" << endl;
            if (x < swiat->getN() - 2) {
                if (swiat->czyPuste(x + 2, y)) {
                    swiat->usunOrganizm(this);
                    x+=2;
                    swiat->dodajOrganizm(this);
                    //break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x + 2][y]);
                    //break;
                }
            }
        }
        else if (c == 75) {
            tura++;
            //cout << "lewo" << endl;
            if (x > 1) {
                if (swiat->czyPuste(x - 2, y)) {
                    swiat->usunOrganizm(this);
                    x-=2;
                    swiat->dodajOrganizm(this);
                    //break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x - 2][y]);
                    //break;
                }
            }
        }
        else if (c == 80) {
            tura++;
            //cout << "dol" << endl;
            if (y < swiat->getM() - 2) {
                if (swiat->czyPuste(x, y + 2)) {
                    swiat->usunOrganizm(this);
                    y+=2;
                    swiat->dodajOrganizm(this);
                    //break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x][y + 2]);
                    //break;
                }
            }
        }
        else if (c == 0x48) {
            tura++;
            if (y > 0) {
                //cout << "gora" << endl;
                if (swiat->czyPuste(x, y - 2)) {
                    swiat->usunOrganizm(this);
                    y-=2;
                    swiat->dodajOrganizm(this);
                    //break;
                }
                else {
                    kolizja(swiat->getOrganizmy()[x][y - 2]);
                    //break;
                }
            }
        }
    }

    if ((tura == -6 || tura == -5) && c != -32) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1, 2);
        int n = dis(gen);
        if (n == 1)power = false;
        else power = true;
        //events.push_back("n->" + to_string(n));
    }

    if (tura == -5 && c != -32) {
        events.push_back("Szybkosc antylopy dezaktywowana");
        power = false;
    }

    //if (tura == 10) tura = 0;

    if (c == ' ' && tura >= 0) {
            cout << "Szybkosc antylopy aktywowana"<<endl;
            events.push_back("Szybkosc antylopy aktywowana");
            power = true;
            tura = -10;
        }
}

int Czlowiek::getTura() { return tura; }

void Czlowiek::setTura(int a) { tura = a; }