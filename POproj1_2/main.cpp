#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream> 
#include <conio.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include "Swiat.h"
#include "Wilk.h"
#include "Owca.h"
#include "Trawa.h"
#include "WilczeJagody1.h"
#include "Guarana.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"
#include "BarszczSosnowskiego.h"
#include "Mlecz.h"
#include "Czlowiek.h"

using namespace std;

bool is_alive = 1;
extern bool power;

vector<string> events;

void gotoxy(int x, int y);

void hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void zapisz(vector<Organizm*>& w, const string& filename, int N, int M, int tura) {
	ofstream f(filename);
	if (f.good()) {
		f << N << " " << M << endl;
		f << w.size() << " " << events.size() << " " << tura << " " << power << endl;
		for (int i = 0; i < w.size();i++) {
			f << w[i]->getNazwa() << " " << w[i]->getX() << " " << w[i]->getY() << " " << w[i]->getWiek() << endl;
		}
		for (int i = 0; i < events.size(); i++) {
			f << events[i] << endl;
		}
		f.close();
		events.push_back("Zapisano");
	}
	else events.push_back("Nie udalo sie otworzyc pliku");
}

void wczytaj(const string& filename, Swiat*& s, int* N, int* M) {
	ifstream f(filename);
	if (f.good()) {
		f >> *N >> *M;
		s = new Swiat(*N, *M);
		int size1, size2, tura;
		bool pow;
		f.ignore();
		f >> size1 >> size2 >> tura >> pow;
		power = pow;
		f.ignore();
		for (int i = 0; i < size1; i++) {
			string nazwa;
			int sila, inicjatywa, x, y, wiek;
			f >> nazwa >> x >> y >> wiek;
			f.ignore();
			Organizm* org = nullptr;
			if (nazwa == "Czlowiek") {
				org = new Czlowiek(x, y, s);
			}
			if (nazwa == "Lis") {
				org = new Lis(x, y, s);
			}
			else if (nazwa == "Wilk") {
				org = new Wilk(x, y, s);
			}
			else if (nazwa == "Owca") {
				org = new Owca(x, y, s);
			}
			else if (nazwa == "Antylopa") {
				org = new Antylopa(x, y, s);
			}
			else if (nazwa == "Zolw") {
				org = new Zolw(x, y, s);
			}
			else if (nazwa == "Trawa") {
				org = new Trawa(x, y, s);
			}
			else if (nazwa == "Mlecz") {
				org = new Mlecz(x, y, s);
			}
			else if (nazwa == "BarszczSosnowskiego") {
				org = new BarszczSosnowskiego(x, y, s);
			}
			else if (nazwa == "WilczeJagody") {
				org = new WilczeJagody(x, y, s);
			}
			else if (nazwa == "Guarana") {
				org = new Guarana(x, y, s);
			}
			org->setWiek(wiek);
			s->dodajOrganizm(org);

		}
		events.clear();
		for (int i = 0; i < size2; i++) {
			string str;
			getline(f, str);
			events.push_back(str);
		}
		events.push_back("wczytano");
		f.close();
	}
	else(events.push_back("Nie udalo sie otworzyc pliku"));
}

void legenda(int x, int y)
{
	gotoxy(x, y);
	cout << "Agata Domasik 193577";
	y++;
	gotoxy(x, y);
	cout << "C <- Czlowiek";
	y++;
	gotoxy(x, y);
	cout << "W <- Wilk";
	y++;
	gotoxy(x, y);
	cout << "O <- Owca";
	y++;
	gotoxy(x, y);
	cout << "L <- Lis";
	y++;
	gotoxy(x, y);
	cout << "Z <- Zolw";
	y++;
	gotoxy(x, y);
	cout << "A <- Antylopa";
	y++;
	gotoxy(x, y);
	cout << "T <- Trawa";
	y++;
	gotoxy(x, y);
	cout << "M <- Mlecz";
	y++;
	gotoxy(x, y);
	cout << "G <- Guarana";
	y++;
	gotoxy(x, y);
	cout << "J <- WilczeJagody";
	y++;
	gotoxy(x, y);
	cout << "B <- BarszczSosnowskiego";
	y++;
	gotoxy(x, y);
}

vector<Organizm*> sortInic(vector<Organizm*> w)
{
	for (int i = 0; i < w.size(); i++)
		for (int j = 1; j < w.size() - i; j++)
			if (w[j - 1]->getInicjatywa() < w[j]->getInicjatywa())
				swap(w[j - 1], w[j]);
			else if (w[j - 1]->getInicjatywa() == w[j]->getInicjatywa() && w[j - 1]->getWiek() < w[j]->getWiek())
				swap(w[j - 1], w[j]);
	return w;
}

void losuj(int arr[10][2], int N, int M) {
	random_device rd; 
	mt19937 gen(rd());
	std::uniform_int_distribution<> disN(0, N - 1);
	std::uniform_int_distribution<> disM(0, M - 1);

	for (int i = 0; i < 10; i++) {
		arr[i][0] = disN(gen);
		arr[i][1] = disM(gen);
	}
}

void generuj(int N, int M, Swiat* s) {
	for (int i = 0; i < 3; i++) {
		int tmp[10][2];
		losuj(tmp, N, M);
		Organizm** tab = new Organizm * [10];
		tab[0] = new Wilk(tmp[0][0], tmp[0][1], s);
		tab[1] = new Owca(tmp[1][0], tmp[1][1], s);
		tab[2] = new Lis(tmp[2][0], tmp[2][1], s);
		tab[3] = new Zolw(tmp[3][0], tmp[3][1], s);
		tab[4] = new Antylopa(tmp[4][0], tmp[4][1], s);
		tab[5] = new Trawa(tmp[5][0], tmp[5][1], s);
		tab[6] = new Mlecz(tmp[6][0], tmp[6][1], s);
		tab[7] = new Guarana(tmp[7][0], tmp[7][1], s);
		tab[8] = new WilczeJagody(tmp[8][0], tmp[8][1], s);
		tab[9] = new BarszczSosnowskiego(tmp[9][0], tmp[9][1], s);
		for (int i = 0; i < 10; i++) {
			s->dodajOrganizm(tab[i]);
		}
	}
}

void print(vector<string> w) {
	int n = w.size();
	if (n < 15) {  
		for (int i = n - 1; i >= 0; i--) {  
			cout << w[i] << endl;  
		}
	}
	else {  
		for (int i = n - 1; i >= n - 15; i--) {  
			 cout << w[i] << endl;  
		}
	}
}


int main() {
	hideCursor();
	int N;
	int M;

	do {
		cout << "Podaj szerokosc: ";
		cin >> N;
		system("cls");
	} while (N <= 0);
	do {
		cout << "Podaj wysokosc: ";
		cin >> M;
		system("cls");
	} while (M <= 0);

	char z = 0;
	Swiat* s = new Swiat(N, M);
	generuj(N, M, s);
	Czlowiek c1(0, 0, s);
	s->dodajOrganizm(&c1);

	do {
		system("cls");
		z = 0;
		vector<Organizm*> tmp;
		s->rysujSwiat(38, 2);
		legenda(2, 1);
		print(events);

		z = _getch();
		if (is_alive || (!is_alive && z == 13)) {
			for (int i = 0; i < N; i++)
				for (int j = 0; j < M; j++)
					if (s->getOrganizmy()[i][j] != NULL) {
						tmp.push_back(s->getOrganizmy()[i][j]);
						s->getOrganizmy()[i][j]->zwiekszWiek();
					}
		}
		tmp = sortInic(tmp);

		s->wykonajTure(tmp, &z, &c1);

		if (z == 's') {
			cout << "podaj nazwe pliku: ";
			string str;
			cin >> str;
			zapisz(tmp, str, N, M, c1.getTura());
		}

		else if (z == 'l') {
			cout << "podaj nazwe pliku: ";
			string str;
			cin >> str;
			wczytaj(str, s, &N, &M);
		}

	} while (z != 'q');

	delete s;
	system("cls");
}


