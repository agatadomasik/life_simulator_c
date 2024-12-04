#pragma once
#include "Roslina.h"

class Mlecz : public Roslina {

public:
	Mlecz(int a, int b, Swiat* s);
	void rysowanie() override;
	Organizm* rozmnozSie(int a, int b) override;
	void akcja(char c) override;
}; 
