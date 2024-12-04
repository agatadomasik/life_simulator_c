#pragma once
#include "Zwierze.h"

class Lis : public Zwierze {

public:
	Lis(int a, int b, Swiat* s);
	void rysowanie() override;
	Organizm* rozmnozSie(int a, int b) override;
	void akcja(char c) override;
};