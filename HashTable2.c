#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct motor
{
	char* cod;
	float litri;
	int putere;
	unsigned char combustibil;
};

typedef struct motor motor;
typedef struct nod nod;
//creare structura pentru un nod dintr-o lista simplu inlantuita
struct nod
{
	nod* prev;
	motor info;
	nod* next;
};

//creare structura pentru tabela de dispersie
// aceasta este un vector de liste
struct HashTable {
	int dim;
	nod** vector;
};
typedef struct HashTable HashTable;

motor citireMotorDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	motor m;
	char* aux = strtok(buffer,sep);
	m.cod = malloc(strlen(aux) + 1);
	strcpy_s(m.cod, strlen(aux) + 1, aux);
	m.litri = atof(strtok(NULL, sep));
	m.putere = atoi(strtok(NULL, sep));
	m.combustibil = *strtok(NULL, sep);
	return m;
}

void afisareMotor(motor m) {
	printf("Cod Motor: %s \n", m.cod);
	printf("Litri: %.1f \n", m.litri);
	printf("Putere: %d \n", m.putere);
	printf("Combustibil: %c \n", m.combustibil);
}

void afisareLista(nod* lista) {
	//afiseaza toate elemente din lista dublu inlantuita
	//prin apelarea functiei afisareCasa()
	nod* p = lista;
	while (p != NULL)
	{
		afisareMotor(p->info);
		p = p->next;
	}
}

void adaugaMotor(nod** lista, motor m) {
	//adauga la final in lista primita un motor primit ca parametru
	nod* nou = malloc(sizeof(nod));
	nou->info = m;
	nou->prev = NULL;
	nou->next = NULL;
	if (*lista == NULL)
	{
		*lista = nou;
	}
	else
	{
		nod* p = *lista;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
		nou->prev = p;
	}
}


HashTable initializareHashTable(int dimensiune) {
	//initializeaza vectorul de liste si seteaza fiecare lista ca fiind NULL;
	HashTable ht;
	ht.dim = dimensiune;
	ht.vector = (nod**)malloc(sizeof(nod*) * ht.dim);
	for (int i = 0; i < ht.dim; i++)
	{
		ht.vector[i] = NULL;
	}
	return ht;
}

int calculeazaHash(int putere, int dimensiune) {
	// este calculat hash-ul in functie de dimensiunea tabelei si un atribut
	return abs(putere % dimensiune);
}

void inserareMotorInTabela(HashTable hash, motor m) {
	//este folosit mecanismul CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva
	if (hash.vector == NULL || hash.dim <= 0)
		return;
	int poz = calculeazaHash(m.putere, hash.dim);
	adaugaMotor(&(hash.vector[poz]), m);
}

HashTable citireMotoareDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate casele din fisier
	//prin apelul repetat al functiei citireCasaDinFisier()
	// acestea sunt inserate intr-o tabela de dispersie initializata aici
	//ATENTIE - la final inchidem fisierul/stream-ul
	HashTable ht = initializareHashTable(5);
	FILE* file = fopen(numeFisier, "r");
	if (!file)
	{
		printf("EROARE LA DESCHIDEREA FISIERULUI");
		return ht;
	}
	while (!feof(file))
	{
		motor m = citireMotorDinFisier(file);
		inserareMotorInTabela(ht, m);
	}
	fclose(file);
	return ht;
}

void afisareTabela(HashTable ht) {
	//sunt afisate toate casele cu evidentierea clusterelor realizate
	for (int i = 0; i < ht.dim; i++)
	{
		printf("Cluster %d\n", i);
		if (ht.vector[i] == NULL)
			printf("Gol \n");
		else
			afisareLista(ht.vector[i]);
	}
}

void dezalocareTabela(HashTable* ht) {
	//sunt dezalocate toate casele din tabela de dispersie
	if (ht == NULL || ht->vector == NULL)
		return;
	for (int i = 0; i < ht->dim; i++)
	{
		nod* p = ht->vector[i];
		while (p != NULL)
		{
			nod* sterge = p;
			p = p->next;
			free(sterge->info.cod);
			free(sterge);
		}
	}
	free(ht->vector);
	ht->vector = NULL;
	ht->dim = 0;
}

float* calculeazaPutereMediePerClustere(HashTable ht, int* nrClustere) {
	//calculeaza puterea medie din fiecare cluster.
	//trebuie sa returnam un vector cu valorile medii per cluster.
	//lungimea vectorului este data de numarul de clustere populate
	if (ht.vector == NULL || ht.dim <= 0) {
		*nrClustere = 0;
		return NULL;
	}
	int clustere = 0;
	for (int i = 0; i < ht.dim; i++)
		if (ht.vector[i] != NULL)
			clustere++;
	if (clustere == 0)
	{
		*nrClustere = 0;
		return NULL;
	}
	float* medii = (float*)malloc(sizeof(float) * clustere);
	int indexVector = 0;
	for (int i = 0; i < ht.dim; i++)
	{
		int s = 0, ct = 0;
		if (ht.vector[i] != NULL)
		{
			nod* p = ht.vector[i];
			while (p != NULL)
			{
				s = s + p->info.putere;
				ct++;
				p = p->next;
			}

			medii[indexVector] = (float)s / ct;
			indexVector++;
		}
	}
	*nrClustere = clustere;
	return medii;
}

motor getMotorDupaCheie(HashTable ht,int putereCautata) {
	motor m;
	m.cod = NULL;
	m.litri = 0;
	m.putere = 0;
	m.combustibil = 0;
	//cauta motor dupa valoarea atributului cheie folosit in calcularea hash-ului
	int poz = calculeazaHash(putereCautata, ht.dim);
	nod* p = ht.vector[poz];
	while (p != NULL)
	{
		if (p->info.putere == putereCautata)
			return p->info;
		p = p->next;
	}
	return m;
}

int main() {
	HashTable tabela = citireMotoareDinFisier("motoare.txt");
	afisareTabela(tabela);
	int clustere = 0;
	float* medii = calculeazaPutereMediePerClustere(tabela, &clustere);
	if (medii != NULL)
	{
		for (int i = 0; i < clustere; i++) {
			printf("Clusterul populat %d are puterea medie: %.2f\n", i , medii[i]);
		}
		free(medii);
	}
	else {
		printf("Nu exista clustere populate sau tabela e vida.");
	}
	printf("Puterea motorului Cautat: \n");
	afisareMotor(getMotorDupaCheie(tabela, 186));
	dezalocareTabela(&tabela);
	return 0;
}
//N47, 2.0, 186, D
//B47, 2.0, 196, D
//M57, 3.0, 250, D
//B58, 3.0, 300, B
//N57, 3.0, 280, D
//B38, 1.5, 140, B
