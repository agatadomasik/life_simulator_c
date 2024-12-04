#pragma once
#include "Roslina.h"

class BarszczSosnowskiego : public Roslina {

public:
	BarszczSosnowskiego(int a, int b, Swiat* s);
	void rysowanie() override;
	Organizm* rozmnozSie(int a, int b) override;
	void akcja(char c) override;
	void kolizja(Organizm* other) override;
};