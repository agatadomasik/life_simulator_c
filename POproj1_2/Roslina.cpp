#include <iostream>
#include <random>
#include "Swiat.h"
#include "Roslina.h"

void Roslina::akcja(char c) {
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



void Roslina::kolizja(Organizm* other) {

}