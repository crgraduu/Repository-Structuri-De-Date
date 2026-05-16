#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct casa
{
	int id;
	int nrCamere;
	float pret;
	char* strada;
	unsigned char zona;
};

typedef struct casa casa;
typedef struct nod nod;
//creare structura pentru un nod dintr-o lista simplu inlantuita
struct nod
{
	nod* prev;
	casa info;
	nod* next;
};

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	int dim;
	nod** vector;
};
typedef struct HashTable HashTable;

casa citireCasaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3]=",\n";
	fgets(buffer, 100, file);
	char* aux;
	casa c;
	c.id = atoi(strtok(buffer, sep));
	c.nrCamere = atoi(strtok(NULL, sep));
	c.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	c.strada = malloc(strlen(aux)+1);
	strcpy_s(c.strada, strlen(aux) + 1, aux);
	c.zona = *strtok(NULL, sep);
	return c;
}

void afisareCasa(casa c) {
	printf("ID: %d\n", c.id);
	printf("Numar de Camere: %d\n", c.nrCamere);
	printf("Pret: %.2f\n", c.pret);
	printf("Nume Strada: %s\n", c.strada);
	printf("Zona: %c\n", c.zona);
}

void afisareLista(nod* lista) {
	//afiseaza toate elemente din lista dublu inlantuita
	//prin apelarea functiei afisareCasa()
	nod* p = lista;
	while (p != NULL)
	{
		afisareCasa(p->info);
		p = p->next;
	}
}

void adaugaCasa(nod** lista, casa c) {
	//adauga la final in lista primita o casa primita ca parametru
	nod* nou = malloc(sizeof(nod));

	nou->info = c;
	nou->next = NULL;
	nou->prev = NULL;

	if (*lista == NULL) {
		*lista = nou;
	}
	else {
		nod* p = *lista;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
		nou->prev = p;
	}
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	//initializeaza vectorul de liste si seteaza fiecare lista ca fiind NULL;
	ht.dim = dimensiune;
	ht.vector = (nod**)malloc(sizeof(nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++)
	{
		ht.vector[i] = NULL;
	}
	return ht;
}

int calculeazaHash(int id, int dimensiune) {
	// este calculat hash-ul in functie de dimensiunea tabelei si un atribut
	return id % dimensiune;
}

void inserareCasaInTabela(HashTable hash, casa c) {
	//este folosit mecanismul CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva
	if (hash.vector == NULL || hash.dim <= 0)
		return;
	int pozitie = calculeazaHash(c.id, hash.dim);
	adaugaCasa(&(hash.vector[pozitie]), c);
}

HashTable citireCaseDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate casele din fisier
	//prin apelul repetat al functiei citireCasaDinFisier()
	// acestea sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul
	HashTable ht = initializareHashTable(5);
	FILE* file = fopen(numeFisier, "r");
	if (!file) {
		printf("Eroare la deschiderea fisierului %s\n", numeFisier);
		return ht;
	}
	while (!feof(file)) {
		casa c = citireCasaDinFisier(file);
		inserareCasaInTabela(ht, c);
	}
	fclose(file);
	return ht;
}

void afisareTabela(HashTable ht) {
	//sunt afisate toate casele cu evidentierea clusterelor realizate
	for (int i = 0; i < ht.dim; i++)
	{
		printf("Cluster [%d]\n", i);
		if (ht.vector[i] == NULL)
			printf("Gol\n");
		else
			afisareLista(ht.vector[i]);
	}
}

void dezalocareTabela(HashTable *ht) {
	//sunt dezalocate toate casele din tabela de dispersie
	if (ht == NULL || ht->vector == NULL)
		return;
	for (int i = 0; i < ht->dim; i++)
	{
		nod* p = ht->vector[i];
		while (p != NULL)
		{
			nod* deSters = p;
			p = p->next;
		}
	}
}
int main() {
	HashTable tabela = citireCaseDinFisier("case.txt");
	afisareTabela(tabela);
	dezalocareTabela(&tabela);
	return 0;
}
