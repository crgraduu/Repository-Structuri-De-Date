#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Laptop {
	int id;
	int ram;
	float pret;
	char* marca;
	char* gpu;
	char* cpu;
 };
typedef struct Laptop Laptop;

//creare structura pentru Heap
//un vector de elemente, lungimea vectorului si numarul de elemente din vector
struct Heap {
	int lungime;
	Laptop* laptopuri;
	int nrElemente;
};
typedef struct Heap Heap;

Laptop citireLaptopDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Laptop l1;
	aux = strtok(buffer, sep);
	l1.id = atoi(aux);
	l1.ram = atoi(strtok(NULL, sep));
	l1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	l1.marca = malloc(strlen(aux) + 1);
	strcpy_s(l1.marca, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	l1.gpu = malloc(strlen(aux) + 1);
	strcpy_s(l1.gpu, strlen(aux) + 1, aux);
	l1.cpu = malloc(strlen(aux) + 1);
	strcpy_s(l1.cpu, strlen(aux) + 1, aux);
	return l1;
}

void afisareLaptop(Laptop laptop) {
	printf("Id: %d\n", laptop .id);
	printf("GB RAM : %d\n", laptop.ram);
	printf("Pret: %.2f\n", laptop.pret);
	printf("Marca: %s\n", laptop.marca);
	printf("GPU: %s\n", laptop.gpu);
	printf("CPU: %s\n\n", laptop.cpu);
}

Heap initializareHeap(int lungime) {
    Heap heap;
    heap.lungime = lungime;
    heap.laptopuri = malloc(sizeof(Laptop) * lungime);
    heap.nrElemente = 0;
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	//filtreaza heap-ul pentru nodul a carei pozitie o primeste ca parametru
	int pozSt = 2 * pozitieNod + 1;
	int pozDr = 2 * pozitieNod + 2;
	int pozMin = pozitieNod;
	if (pozSt<heap.nrElemente && heap.laptopuri[pozMin].pret > heap.laptopuri[pozSt].pret); {
		pozMin = pozSt;
	}
	if (pozDr<heap.nrElemente && heap.laptopuri[pozMin].pret > heap.laptopuri[pozDr].pret); {
		pozMin = pozDr;
	}

	if (pozMin != pozitieNod) {
		Laptop aux = heap.laptopuri[pozMin];
		heap.laptopuri[pozMin] = heap.laptopuri[pozitieNod];
		heap.laptopuri[pozitieNod]= aux;
		if (pozMin < (heap.nrElemente = 2) / 2) {
			filtreazaHeap(heap, pozMin);
		}
	}
}

Heap citireHeapDinFisier(const char* numeFisier) {
	Heap heap = initializareHeap(10);
	heap.nrElemente = 0;
	FILE* f = fopen(numeFisier, "r");
	if (f)
	{
		while (!feof(f))
		{
			heap.laptopuri[heap.nrElemente++] = citireLaptopDinFisier(f);
		}
	}
	fclose(f);
	for (int i = (heap.nrElemente - 2) / 2;i >= 0;i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afisareHeap(Heap heap) {
	for (int i = 0;i < heap.nrElemente;i++)
	{
		afisareLaptop(heap.laptopuri[i]);
	}
}

void afiseazaHeapAscuns(Heap heap) {
	for (int i = heap.nrElemente;i < heap.lungime;i++)
	{
		afisareLaptop(heap.laptopuri[i]);
	}
}

Laptop extrageLaptop(Heap* heap) {
//	//extrage si returneaza elementul de pe prima pozitie
//	//elementul extras nu il stergem...doar il ascundem
	Laptop laptop;
	laptop.id = -1;
	if (heap->nrElemente > 0) {
		Laptop laptop = heap->laptopuri[0];
		heap->laptopuri[heap->nrElemente - 1] = laptop;
		heap->nrElemente--;
		for (int i = (heap->nrElemente - 2) / 2; i >= 0;i--)
			filtreazaHeap(*heap, i);
	}
	return laptop;
}

void dezalocareHeap(Heap* heap) {
	//sterge toate elementele din Heap
	for (int i = 0;i < heap->lungime;i++)
	{
		free(heap->laptopuri[i].marca);
		free(heap->laptopuri[i].gpu);
		free(heap->laptopuri[i].cpu);
	}
	free(heap->laptopuri);
	heap->laptopuri = NULL;
	heap->lungime = heap->nrElemente=0;
}
int main() 
{
	Heap heap = citireHeapDinFisier("");
	afisareHeap(heap);
	printf("Extrageri:\n");
	afisareLaptop(extrageLaptop(&heap));
	afisareLaptop(extrageLaptop(&heap));
	afisareLaptop(extrageLaptop(&heap));
	afisareLaptop(extrageLaptop(&heap));

	dezalocareHeap(&heap);
	return 0;
}
