#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina 
{
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};

typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) 
{
	char buffer[100];
	char sep[3] = ",\n";
	Masina m1 = { 0,0,0,NULL,NULL,0 };
	if (fgets(buffer, 100, file) == NULL)
	{
		printf("Eroare la citire din fisier!\n");
		return m1;
	}
	char* aux;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) 
{
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

int main() 
{
	FILE* f = fopen("masini.txt", "r");
  if (f == NULL)
	{
		printf("Nu s-a putut deschide fisierul!\n");
		return 1;
	}
	Masina m1;
	m1 = citireMasinaDinFisier(f);
	afisareMasina(m1);
	free(m1.model);
	free(m1.numeSofer);
	fclose(f);
	return 0;
}
