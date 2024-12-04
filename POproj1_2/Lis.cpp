#include <iostream>
#include <random>
#include "Lis.h"
#include "Swiat.h"
using namespace std;

extern vector<string> events;

Lis::Lis(int a, int b, Swiat* s) {
	nazwa = "Lis";
	sila = 3;
	inicjatywa = 7;
	x = a;
	y = b;
	swiat = s;
    wiek = 0;
}

void Lis::rysowanie() {
	cout << "L";
}


Organizm* Lis::rozmnozSie(int a, int b) {
	return new Lis(a, b, swiat);
}


void Lis::akcja(char c) {
    
    if ((x<swiat->getN()-1 && swiat->getOrganizmy()[x + 1][y]->getSila() <= sila) || (x > 0 && swiat->getOrganizmy()[x - 1][y]->getSila() <= sila) ||
        (y < swiat->getM() - 1 && swiat->getOrganizmy()[x][y + 1]->getSila() <= sila) || (y > 0 && swiat->getOrganizmy()[x][y - 1]->getSila() <= sila)) {
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
                        if (swiat->getOrganizmy()[x + 1][y]->getSila() <= sila) {
                            kolizja(swiat->getOrganizmy()[x + 1][y]);
                            break;
                        }
                        else events.push_back("[Lis] wyczuwa silniejszy organizm");
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
                        if (swiat->getOrganizmy()[x - 1][y]->getSila() <= sila) {
                            kolizja(swiat->getOrganizmy()[x - 1][y]);
                            break;
                        }
                        else events.push_back("[Lis] wyczuwa silniejszy organizm");

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
                        if (swiat->getOrganizmy()[x][y + 1]->getSila() <= sila) {
                            kolizja(swiat->getOrganizmy()[x][y + 1]);
                            break;
                        }
                        else events.push_back("[Lis] wyczuwa silniejszy organizm");
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
                        if (swiat->getOrganizmy()[x][y - 1]->getSila() <= sila) {
                            kolizja(swiat->getOrganizmy()[x][y - 1]);
                            break;
                        }
                        else events.push_back("[Lis] wyczuwa silniejszy organizm");
                    }
                }
            }
        } while (true);
    }
    else events.push_back("[Lis] nie ma gdzie sie poruszyc");
}