#ifndef FUNKCIJE_H
#define FUNKCIJE_H

typedef struct obaveze {
	int br;
	char obaveza[200];
}OBAVEZE;

static char* datoteka = "to do list.txt";
int BrObaveze;

void naslov();
int izbornik();
void stvori_datoteku();
int BrojacDat();
//int StatDat();
void dodaj();
void prikaz();
void IzbrisiDatoteku();
OBAVEZE* zauzimanje(int);
void UnosPolje(OBAVEZE*, int);
void IzbrisiObavezu(OBAVEZE*, int);
void UrediObavezu(OBAVEZE*, int);
//void statistika(int, int);
void pronadji(OBAVEZE*, int);



#endif //FUNKCIJE_H