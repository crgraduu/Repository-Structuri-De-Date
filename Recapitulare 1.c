#include<stdio.h>
#include<stdlib.h>

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
	a.model = malloc(strlen(model) + 1);
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

void modifica_Atribut(BMW a) {
}

void dezalocare(BMW *a) {

}

int main() {
	struct BMW a;
	a = initializare(3, 140, "G20", 25000, 'M');
	afisare (a);
	return 0;
}
