#pragma once
#include "Zwierze.h"

class Zolw : public Zwierze {

public:
	Zolw(int a, int b, Swiat* s);
	void rysowanie() override;
	Organizm* rozmnozSie(int a, int b) override;
	void akcja(char c) override;
	void kolizja(Organizm* other) override;
};
