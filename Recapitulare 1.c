#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

struct BMW {
	int id;
	int kw;
	char* model;
	float pret;
	char pachet;
};

typedef struct BMW BMW;

struct BMW initializare(int id, int kw, char* model, float pret, char pachet) {
	struct BMW a;
	a.id = id;
	a.kw = kw;
	a.model = (char*)malloc(strlen(model) + 1);
	strcpy_s(a.model, strlen(model) + 1, model);
	a.pret = pret;
	a.pachet = pachet;
	return a;
}

void afisare(BMW a) {
	printf("BMW Seria %d\n", a.id);
	printf("Putere in KW %d\n", a.kw);
	printf("Model %s\n", a.model);
	printf("Pret %.2f\n", a.pret);
	printf("Pachet %c\n", a.pachet);
}

void modificaPachetSiPret(BMW* a, char pachet, float pret ) {
	a->pachet = pachet;
	a->pret = pret;
}

void dezalocare(BMW* a) {
	free(a->model);
	a->model = NULL;
}

int main() {
	struct BMW a;
	a = initializare(3, 140, "G20", 22000, 'S');
	afisare (a);
	modificaPachetSiPret(&a, 'M', 25000);
	afisare(a);
	dezalocare(&a);
	return 0;
}
