#include <iostream>
#include <fstream>
#include <sstream>
#include "Organizm.h"
using namespace std;

int Organizm::getX() { return x; }
int Organizm::getY() { return y; }
string Organizm::getNazwa() { return nazwa; }
int Organizm::getSila() { if (this != NULL)return sila; else return 0; }
int Organizm::getInicjatywa() { return inicjatywa; }
void Organizm::setX(int a) { x = a; }
void Organizm::setY(int b) { y = b; }
void Organizm::setSila(int a) { sila = a; }
int Organizm::getWiek() { return wiek; }
void Organizm::zwiekszWiek() { wiek++; }
void Organizm::setWiek(int a) { wiek = a; }
void Organizm::clean() { delete swiat; }