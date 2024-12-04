#pragma once
#include "Organizm.h"

class Zwierze : public Organizm {

public:
	void akcja(char c) override; //przesuwa si� losowo na s�siednie pole
	void kolizja(Organizm* other) override; //rozmna�anie
	virtual Organizm* rozmnozSie(int a, int b) = 0;
};