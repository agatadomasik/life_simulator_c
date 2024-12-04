#pragma once
#include "Zwierze.h"

class Owca : public Zwierze {

public:
	Owca(int a, int b, Swiat* s);
	void rysowanie() override;
	Organizm* rozmnozSie(int a, int b) override;
};