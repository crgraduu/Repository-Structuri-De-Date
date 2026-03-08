#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct masina {
    int id;
    int cai;
    char* model;
    float pret;
    char categorie;
};

struct masina initializare(int id, int cai, const char* model, float pret, char categorie)
{
    struct masina m;

    m.id = id;
    m.cai = cai;

    m.model = (char*)malloc(strlen(model) + 1);
    strcpy_s(m.model, strlen(model)+1, model);

    m.pret = pret;
    m.categorie = categorie;

    return m;
}

void afisare(struct masina m)
{
    printf("ID: %d\n", m.id);
    printf("Cai putere: %d\n", m.cai);
    printf("Model: %s\n", m.model);
    printf("Pret: %.2f\n", m.pret);
    printf("Categorie: %c\n", m.categorie);
}

void modifica_Atribut(struct masina* m, float pretNou)
{
    m->pret = pretNou;
}

void dezalocare(struct masina* m)
{
    free(m->model);
    m->model = NULL;
}

int main()
{
    struct masina s = initializare(204, 250, "BMW Seria 3", 35000, 'B');

    struct masina s2 = initializare(200, 240, "Audi A4", 32000, 'B');

    afisare(s);

    afisare(s2);

    modifica_Atribut(&s, 32000);

    printf("\nDupa modificare:\n");
    afisare(s);

    dezalocare(&s);

    return 0;
}
