#pragma once
#include "Zwierze.h"

class Wilk : public Zwierze {

public:
	Wilk(int a, int b, Swiat* s);
	void rysowanie() override;
	Organizm* rozmnozSie(int a, int b) override;
};