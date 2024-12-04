#pragma once
#include "Roslina.h"

class Trawa : public Roslina {

public:
	Trawa(int a, int b, Swiat* s);
	void rysowanie() override;
	Organizm* rozmnozSie(int a, int b) override;
};