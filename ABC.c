motor getMotorByCod(nod* rad, char* cod)
{
	motor m;
	m.cod = NULL;
	m.putere = 0;
	m.litri = 0;
	m.combustibil = 0;
	if (rad == NULL) {
		return m;
	}
	if (rad) {
		if (strcmp(rad->info.cod, cod) == 0) 
			return rad->info;
		m = getMotorByCod(rad->st, cod);
		if (m.cod != NULL) {
			return m;
		}
		return getMotorByCod(rad->dr, cod);
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
int inaltime(nod* rad)
{
	if (rad)
		return 1 + maxim(inaltime(rad->st), inaltime(rad->dr));
	else return 0;
}
int main() {
	nod* rad = citireArboreDinFisier("motoare.txt");
	afisareArbore(rad);
	afisarePreordine(rad);
	printf("Inaltime arbore:%d\n", inaltime(rad));
	printf("Numar motoare:%d\n\n", numarNoduri(rad));
	afisareMotor(getMotorByCod(rad, "B47"));
	dezalocare(&rad);
	return 0;
}
//N47, 2.0, 186, D
//B47, 2.0, 196, D
//M57, 3.0, 250, D
//B58, 3.0, 300, B
//N57, 3.0, 280, D
//B38, 1.5, 140, B
