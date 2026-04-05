#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
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
	fgets(buffer, 100, file);
	char* aux;
	Masina m;
	aux = strtok(buffer, sep);
	m.id = atoi(aux);
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m.model = malloc(strlen(aux) + 1);
	strcpy_s(m.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m.numeSofer, strlen(aux) + 1, aux);

	m.serie = *strtok(NULL, sep);
	return m;
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

Masina* citireVectorMasiniFisier(const char* Fisier, int* nrMasini) {
	FILE* f = fopen(Fisier, "r");
	if (!f) {
		printf("Eroare la deschiderea fisierului!\n");
		return NULL;
	}

	Masina* vector = NULL;
	*nrMasini = 0;

	while (!feof(f)) {
		Masina m = citireMasinaDinFisier(f);
		if (m.model == NULL) {
			break;
		}

		vector = (Masina*)realloc(vector, ((*nrMasini) + 1) * sizeof(Masina));
		vector[*nrMasini] = m;

		(*nrMasini)++;
	}

	fclose(f);
	return vector;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	if (*vector != NULL) {
		for (int i = 0; i < *nrMasini; i++) {
			free((*vector)[i].model);
			free((*vector)[i].numeSofer);
		}
		free(*vector);
		*vector = NULL;
		*nrMasini = 0;
	}
}

int main() 
{
	FILE* f = fopen("masini.txt", "r");
	int nrMasini = 0;

	Masina* vector = citireVectorMasiniFisier("masini.txt", &nrMasini);

	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(vector[i]);
	}

	dezalocareVectorMasini(&vector, &nrMasini);

	return 0;
}
