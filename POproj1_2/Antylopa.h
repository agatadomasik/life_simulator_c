#pragma once
#include "Zwierze.h"

class Antylopa : public Zwierze {

public:
	Antylopa(int a, int b, Swiat* s);
	void rysowanie() override;
	Organizm* rozmnozSie(int a, int b) override;
	void akcja(char c) override;
	void kolizja(Organizm* other) override;
};