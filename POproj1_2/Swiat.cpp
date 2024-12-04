#include "Swiat.h"
#include "Czlowiek.h"
#include <iostream>
#include <vector>
#include<conio.h>
#include<Windows.h>

using namespace std;

extern bool is_alive;

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

Swiat::Swiat(int a, int b) {
	N = a;
	M = b;

	organizmy = new Organizm ** [N];
	for (int i = 0; i < N; i++) {
		organizmy[i] = new Organizm * [M];
		for (int j = 0; j < M; j++)
			organizmy[i][j] = NULL;
	}
}

void Swiat::rysujSwiat(int x, int y) {
	//gorna ramka
	gotoxy(x - 2, y - 1);
	cout << char(201);
	for (int i = 0; i < N * 2 + 1; i++) {
		cout << char(205);
	}
	cout << char(187);

	//dolna ramka
	gotoxy(x - 2, y + M);
	cout << char(200);
	for (int i = 0; i < N * 2 + 1; i++) {
		cout << char(205);
	}
	cout << char(188);

	//boki
	for (int i = 0; i < M; i++) {
		gotoxy(x - 2, y + i);
		cout << char(186);
		gotoxy(x + N * 2, y + i);
		cout << char(186);
	}

	//organizmy
	gotoxy(x, y);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (organizmy[j][i] == NULL) cout << "  ";
			else {
				organizmy[j][i]->rysowanie();
				cout << " ";
			}
		}
		gotoxy(x, y + i + 1);
	}
}

void Swiat::dodajOrganizm(Organizm* o) {
	int x = o->getX();
	int y = o->getY();
	if (x < N && y < M) organizmy[x][y] = o;
}

void Swiat::usunOrganizm(Organizm* o) {
	int x = o->getX();
	int y = o->getY();
	organizmy[x][y] = NULL;
}

int Swiat::getN() { return N; }
int Swiat::getM() { return M; }
Organizm*** Swiat::getOrganizmy() { return organizmy; }

bool Swiat::czyPuste(int x, int y) {
	if (x < N && y < M && x >= 0 && y >= 0) {
		if (organizmy[x][y] == NULL) return true;
	}
	return false;
}


void Swiat::wyczysc() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			organizmy[i][j] = NULL;
		}
}

void Swiat::setN(int a) { N = a; }

void Swiat::setM(int a) { M = a; }

void Swiat::wykonajTure(vector<Organizm*> tmp, char* z, Czlowiek* c1) {
	if ((is_alive && (*z == 77 || *z == 75 || *z == 80 || *z == 72 || *z == ' ') || (!is_alive && *z == 13))) {
		for (int i = 0; i < tmp.size(); i++) {
			if (tmp[i]->getNazwa() != "Czlowiek") {
				if (organizmy[tmp[i]->getX()][tmp[i]->getY()] == tmp[i]) tmp[i]->akcja(*z);
				else delete tmp[i];
			}
			else {
				tmp[i]->akcja(*z);
			}
		}
	}
}

Swiat::~Swiat() {
	delete[] organizmy;
}