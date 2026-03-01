// Structuri De Date 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct masina {
	int id;
	int cai;
	char* model;
	float pret;
	char categorie;
};

struct masina initializare(int id, int cai, const char* model, float pret, char categorie)
{
	masina m;

	m.id = id;
	m.cai = cai;

	m.model = new char[strlen(model) + 1];
	strcpy_s(m.model, strlen(model) + 1,  model);

	m.pret = pret;
	m.categorie = categorie;

	return m;
}

void afisare(struct masina m) 
{
	printf("ID: %d\n", m.id);
	printf("Cai putere: %d\n", m.cai);
	printf("Model: %s\n", m.model);
	printf("Pret: %.2f\n", m.pret);
	printf("Categorie: %c\n", m.categorie);
	//afisarea tuturor atributelor.
}

void modifica_Atribut(struct masina* m, float pretNou) 
{
	m->pret = pretNou;
	//modificarea unui atribut
}

void dezalocare(masina& m) {
	delete[] m.model;
	m.model = nullptr;
	//dezalocare campuri alocate dinamic
}

int main() 
{

		struct masina s = initializare(204, 250, "BMW Seria 3", 35000, 'B');

		afisare(s);

		modifica_Atribut(&s, 32000);

		printf("\nDupa modificare:\n");
		afisare(s);

		dezalocare(s);

		return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
