#pragma once
#include "Zwierze.h"

class Czlowiek : public Zwierze {
	int tura;
public:
	Czlowiek(int a, int b, Swiat* s);
	void rysowanie() override;
	Organizm* rozmnozSie(int a, int b) override;
	void akcja(char c) override;
	int getTura();
	void setTura(int a);
};