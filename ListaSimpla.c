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
typedef struct listaDubla listaDubla;

struct nod
{
	nod* prev;
	casa info;
	nod* next;
};

struct ListaDubla
{
	nod* prim;
	nod* ultim;
};

casa citireCasaDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	casa c;
	aux = strtok(buffer, sep);
	c.id = atoi(aux);
	c.nrCamere = atoi(strtok(NULL, sep));
	c.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	c.strada = malloc(strlen(aux) + 1);
	strcpy_s(c.strada, strlen(aux) + 1, aux);
	c.zona = *strtok(NULL, sep);
	return c;
}

void afisareCasa(casa c)
{
	printf("Id: %d\n", c.id);
	printf("Numar de camere : %d\n", c.nrCamere);
	printf("Pret: %.2f\n", c.pret);
	printf("Nume Strada: %s\n", c.strada);
	printf("Zona: %c\n\n", c.zona);
}

casa* citireVectorCaseFisier(const char* Fisier, int* nr) {
	FILE* f = fopen(Fisier, "r");
	if (!f) {
		printf("Eroare la deschiderea fisierului!\n");
		return NULL;
	}

	casa* vector = NULL;
	*nr = 0;

	while (!feof(f)) {
		casa c = citireCasaDinFisier(f);
		if (c.strada == NULL) {
			break;
		}

		vector = (casa*)realloc(vector, ((*nr) + 1) * sizeof(casa));
		vector[*nr] = c;

		(*nr)++;
	}

	fclose(f);
	return vector;
}

void adaugaCasa(nod* *lista, casa c)
{
	nod* nou = malloc(sizeof(nod));
	nou->info = c;
	nou->next = NULL;
	nou->prev = NULL;
	if (*lista == NULL)
		*lista = nou;
	else
	{
		nod* p = *lista;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = nou;
	}
}

void afisareListaCase(nod* lista) {
	nod* p = lista;
	while (p != NULL) {
		afisareCasa(p->info);
		p = p->next;
	}
}

void dezalocareVectorCase(casa** vector, int* nr) {
	if (*vector != NULL) {
		for (int i = 0; i < *nr; i++) {
			free((*vector)[i].strada);
		}
		free(*vector);
		*vector = NULL;
		*nr = 0;
	}
}

void dezalocareListaCase(nod** lista) {
	while (*lista) 
	{
		free((*lista)->info.strada);
		nod* p = *lista;
		*lista = (*lista)->next;
		free(p);
	}
}

int main()
{
	nod* capLista = NULL;
	FILE* f = fopen("case.txt", "r");
	int nr = 0;
	/*casa* vector = citireVectorCaseFisier("case.txt", &nr);
	
	for (int i = 0; i < nr; i++) {
		afisareCasa(vector[i]);
	}*/

	while (!feof(f)) {
		casa c = citireCasaDinFisier(f);
		adaugaCasa(&capLista, c);
	}
	fclose(f);
	afisareListaCase(capLista);
	dezalocareListaCase(&capLista);
	//dezalocareVectorCase(&vector, &nr);

	return 0;
}

//1,8,100000,Victoriei,B
//2,10,200000,Tineretului,A
//3,6,60000,Traian,C
