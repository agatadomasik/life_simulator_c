#pragma once
#pragma once
#include "Organizm.h"

class Roslina : public Organizm {

public:
	void akcja(char c) override;
	void kolizja(Organizm* other) override;
	virtual Organizm* rozmnozSie(int a, int b) = 0;
};