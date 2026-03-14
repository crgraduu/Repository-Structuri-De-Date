#include<stdio.h>
#include<malloc.h>
#include<string.h>
using namespace std;
typedef struct masina masina;
struct masina {
	int id;
	int putere;
	char* model;
	float pret;
	char categorie;
};
struct masina initializare(int ident,int ptr,const char* mdl,float prt,char cat) 
{
	struct masina s;
	s.id = ident;
	s.putere = ptr;
	s.model = (char*)malloc(strlen(mdl) + 1);
	strcpy_s(s.model, strlen(mdl) + 1, mdl);
	s.pret = prt;
	s.categorie = cat;
	return s;
}

masina copiaza(masina s)
{
	return initializare(s.id, s.putere, s.model, s.pret, s.categorie);
}

void afiseaza( masina s) 
{
	printf("ID: %d\n", s.id);
	printf("Cai Putere: %d\n", s.putere);
	printf("Model: %s\n", s.model);
	printf("Pret: %6.2f\n", s.pret);
	printf("Categorie Permis: %c\n", s.categorie);
}

void afisareVector(masina* vector, int nrElemente)
{
	for (int i = 0; i < nrElemente; i++)
		afiseaza(*(vector + i));
}

struct masina* copiazaPrimeleElemente(masina* vector, int nrElem, int nrCopiate) 
{
	if (nrCopiate < nrElem) {
		struct masina* vectorNou =(masina*) malloc(sizeof(masina) * nrCopiate);
		   for (int i = 0; i < nrCopiate; i++) 
		   {
				vectorNou[i] = copiaza(vector[i]);
		   }
			return vectorNou;
		}
		else {
			return NULL;
		}
	}

void dezalocare(struct masina** vector, int* nrElem) {
	for (int i = 0; i < *nrElem; i++) {
		free((*vector)[i].model);
	}
	free(*vector);
	*nrElem = 0;
	*vector = NULL;
}


int main() 
{
	struct masina m1;
	m1 = initializare(1, 500, "Bentley", 95500, 'B');
	
	masina m2;
	m2=copiaza(m1);
	
	int nrmasini = 2;
	masina* vector = (masina*)malloc(sizeof(masina) * nrmasini); 
	vector[0] = copiaza(m1);
	vector[1] = copiaza(m2);
	afisareVector(vector, nrmasini);
	dezalocare(&vector, &nrmasini);
	return 0;
}
