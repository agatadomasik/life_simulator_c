#pragma once
#include <iostream>
//#include "Swiat.h"
using namespace std;

class Swiat;

class Organizm {
protected:
	string nazwa;
	int sila;
	int inicjatywa;
	int x;
	int y;
	int wiek;
	Swiat* swiat;
public:
	virtual void akcja(char c) = 0;
	virtual void kolizja(Organizm* other) = 0;
	virtual void rysowanie() = 0;
	int getX();
	int getY();
	int getSila();
	int getInicjatywa();
	string getNazwa();
	int getWiek();
	void setX(int a);
	void setY(int b);
	void setSila(int a);
	void zwiekszWiek();
	void setWiek(int a);
	void clean();
};