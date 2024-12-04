#pragma once
#include <vector>
#include "Organizm.h"
#include "Czlowiek.h"


class Swiat {
private:
	int N;
	int M;
	Organizm*** organizmy;

public:
	Swiat(int a, int b);
	void rysujSwiat(int x, int y);
	void dodajOrganizm(Organizm* o);
	void usunOrganizm(Organizm* o);
	Organizm*** getOrganizmy();
	int getN();
	int getM();
	int ileOrganizmow();
	bool czyPuste(int x, int y);
	void wyczysc();
	void setN(int a);
	void setM(int a);
	void wykonajTure(vector<Organizm*> tmp, char* z, Czlowiek* c1);
	~Swiat();
};