#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct motor motor;
typedef struct nod nod;
struct motor {
	char* cod;
	float litri;
	int putere;
	char combustibil;
};
struct nod {
	nod* dr;
	nod* st;
	motor info;
};
motor citireMotorDinFisier(FILE* file) {
	motor m;
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux = strtok(buffer, sep);
	m.cod = (char*)malloc(strlen(aux) + 1);
	strcpy_s(m.cod, strlen(aux) + 1, aux);
	m.litri = atof(strtok(NULL, sep));
	m.putere = atoi(strtok(NULL, sep));
	m.combustibil = *strtok(NULL, sep);
	return m;
}
void afisareMotor(motor m) {
	printf("Cod Motor: %s \n", m.cod);
	printf("Capacitate Cilindrica in Litri: %.1f \n", m.litri);
	printf("Cai Putere: %d \n", m.putere);
	printf("Tip Combustibil: %c \n\n", m.combustibil);
}
motor initMotor(char* cod, float litri, int putere,char combustibil) {
	motor m;
	m.cod = (char*)malloc(strlen(cod) + 1);
	strcpy(m.cod, cod);
	m.litri = litri;
	m.putere = putere;
	m.combustibil = combustibil;
	return m;
}
int inaltime(nod* rad)
{
	if (rad)
		return 1 + maxim(inaltime(rad->st), inaltime(rad->dr));
	else return 0;
}
int diferentaInaltimi(nod* rad){
	if (rad)
		return inaltime(rad->st) - inaltime(rad->dr);
	else return 0;
}
void rotireStanga(nod** rad){
	nod* aux = (*rad)->dr;
	(*rad)->dr = aux->st;
	aux->st = (*rad);
	(*rad) = aux;
}
void rotireDreapta(nod** rad) {
	nod* aux = (*rad)->st;
	(*rad)->st = aux->dr;
	aux->dr = (*rad);
	(*rad) = aux;
}
void afisareArbore(nod* rad) {
	if (rad) {
		afisareArbore(rad->st);
		afisareMotor(rad->info);
		afisareArbore(rad->dr);
	}
}
void afisarePreordine(nod* rad){
	if (rad) {
		afisareMotor(rad->info);
		afisarePreordine(rad->st);
		afisarePreordine(rad->dr);
	}
}
void adaugaMotorInArbore(nod** rad, motor m){
	if (*rad == NULL) {
		nod* nou = malloc(sizeof(nod));
		nou->info = m;
		nou->dr = NULL;
		nou->st = NULL;
		*rad = nou;
	}
	else {
		if ((*rad)->info.putere > m.putere)
			adaugaMotorInArbore(&((*rad)->st), m);
		if ((*rad)->info.putere < m.putere)
			adaugaMotorInArbore(&((*rad)->dr), m);
	}
	int diferenta = diferentaInaltimi(*rad);
	if (diferenta == 2) {//dezechilibru pe stanga
		if(diferentaInaltimi((*rad)->st)==-1)
			rotireStanga(&(*rad)->st);
		rotireDreapta(rad);
	}
	if (diferenta == -2) {//dezechilibru pe dreapta
		if (diferentaInaltimi((*rad)->dr) == 1)
			rotireDreapta(&(*rad)->dr);
		rotireStanga(rad);
	}
}
int numarNoduri(nod* rad)
{
	if (rad)
		return numarNoduri(rad->st) + numarNoduri(rad->dr) + 1;
	else return 0;
}
int maxim(int a, int b)
{
	if (a > b) return a;
	else return b;
}
void dezalocare(nod** rad) {
	if (*rad) {
		dezalocare(&(*rad)->st);
		dezalocare(&(*rad)->dr);
		free((*rad)->info.cod);
		free(*rad);
		*rad = NULL;
	}
}
int main() {
	nod* rad = NULL;
	adaugaMotorInArbore(&rad, initMotor("N47", 2.0, 186, 'D'));
	adaugaMotorInArbore(&rad, initMotor("B47", 2.0, 196, 'D'));
	adaugaMotorInArbore(&rad, initMotor("M57", 3.0, 250, 'D'));
	adaugaMotorInArbore(&rad, initMotor("B58", 3.0, 300, 'B'));
	adaugaMotorInArbore(&rad, initMotor("N57", 3.0, 280, 'D'));
	adaugaMotorInArbore(&rad, initMotor("B38", 1.5, 140, 'B'));
	afisarePreordine(rad);
}
