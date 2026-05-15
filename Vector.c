#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

struct Dacia {
	int id;
	int kw;
	char* model;
	float pret;
};

typedef struct Dacia Dacia;

Dacia initializare(int id, int kw, char* model, float pret) {
	struct Dacia a;
	a.id = id;
	a.kw = kw;
	a.model = (char*)malloc(strlen(model) + 1);
	strcpy_s(a.model, strlen(model) + 1, model);
	a.pret = pret;
	return a;
}

Dacia copie(Dacia a)
{
	return initializare(a.id, a.kw, a.model, a.pret);
}

void afisare(Dacia a) {
	printf("ID %d\n", a.id);
	printf("Putere %d\n", a.kw);
	printf("Model %s\n", a.model);
	printf("Pret %.2f\n", a.pret);
}

void modificaPret(Dacia* a, float pret ) {
	a->pret = pret;
}

void afisareVector(Dacia* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++)
		afisare(*(vector + i));
}

void copiazaDupaModel(Dacia* v, int nrElemente, char* model, Dacia** vectorNou, int* dimensiune)
{
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++)
		if (strcmp(v[i].model, model) == 0)
			(*dimensiune)++;
	(*vectorNou) = malloc(sizeof(Dacia) * (*dimensiune));
	(*dimensiune) = 0;
	for (int i = 0; i < nrElemente; i++)
		if (strcmp(v[i].model, model) == 0)
		{
			(*vectorNou)[*dimensiune] = copie(v[i]);
			(*dimensiune)++;
		}
}

void dezalocare(Dacia** vector, int* nr) {
	for (int i = 0; i < *nr; i++)
		free((*vector)[i].model);
	free(*vector);
	*nr = 0;
	*vector = NULL;
}

int main() {
	int nr = 3;
	Dacia* vector= (Dacia*)malloc(sizeof(Dacia)*nr);
	vector[0] = initializare(5, 85, "Bigster", 25000);
	vector[1] = copie(vector[0]);
	modificaPret(&vector[1], 23000);
	vector[2] = initializare(4, 80, "Duster", 19000);
	afisareVector(vector, nr);
	Dacia* vectorNou;
	int dim = 0;
	copiazaDupaModel(vector, nr, "Bigster", &vectorNou, &dim);
	afisareVector(vectorNou, dim);
	dezalocare(&vectorNou, &dim);
	dezalocare(&vector, &nr);
	return 0;
}
