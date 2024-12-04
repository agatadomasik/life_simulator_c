#pragma once
#include "Roslina.h"

class Guarana : public Roslina {

public:
	Guarana(int a, int b, Swiat* s);
	void rysowanie() override;
	Organizm* rozmnozSie(int a, int b) override;
	void kolizja(Organizm* other) override;
};