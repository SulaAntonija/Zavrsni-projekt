#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"
//6 organizacija izvornog koda

void naslov() {
	printf("\t** BILJESKE **\n\n");
}

int izbornik() {
	int opcija;

	do {

		int broj = BrojacDat(); //4
		int StatBr = StatDat();
		static OBAVEZE* PoljeObaveza = NULL; //9  //5
		PoljeObaveza = zauzimanje(broj);
		UnosPolje(PoljeObaveza, broj);

		printf("\n\t1. Dodaj biljesku\n\n");  //8
		printf("\t2. Izbrisi biljesku\n\n");
		printf("\t3. Uredi postojecu biljesku\n\n");
		printf("\t4. Prikaz biljeska\n\n");
		printf("\t5. Pronadji biljesku\n\n");
		printf("\t6. Izbrisi sve biljeske\n\n");

		printf("\t7. Izadji iz programa\n\n");
		printf("\t8. sortiraj\n\n");
		printf("\nOdabir opcije: ");
		scanf("%d", &opcija);




		switch (opcija) {
		case 1:
			dodaj();
			break;
		case 2:
			IzbrisiObavezu(PoljeObaveza, broj);
			break;
		case 3:
			UrediObavezu(PoljeObaveza, broj);
			break;
		case 4:
			prikaz();
			break;
		case 5:
			pronadji(PoljeObaveza, broj);
			break;

		case 6:
			IzbrisiDatoteku();
			break;

		case 7:
			system("cls");
			printf("\tIzlazenje iz programa!\n\n\n");
			free(PoljeObaveza); //14
			exit(0);
		case 8:
			qsort(PoljeObaveza, broj, sizeof(OBAVEZE), SortirajBiljeske);
			printf("\nBiljeske su sortirane po abecednom redu.\n");
			break;

		default:
			break;
		}

	} while (opcija != 8);
	return opcija;

}


void stvori_datoteku() { //11

	FILE* mapa = NULL;
	mapa = fopen(datoteka, "a");

	if (mapa == NULL) {
		perror("Problem: "); //19
		exit(EXIT_FAILURE);
	}
	fclose(mapa);

	FILE* mapa2 = NULL;
	mapa2 = fopen("br.txt", "a");

	if (mapa2 == NULL) {
		perror("Problem: "); //19
		exit(EXIT_FAILURE);
	}
	fclose(mapa2); //16

	FILE* mapa3 = NULL;
	mapa3 = fopen("statistika.txt", "a");


	if (mapa3 == NULL) {
		perror("Problem: "); //19
		exit(EXIT_FAILURE);
	}
	fclose(mapa3);
}


int BrojacDat() {
	int br = 0;
	FILE* Brf = NULL;

	Brf = fopen("br.txt", "r+");
	if (Brf == NULL) {
		perror("Problem kod stvaranje datoteke za brojac"); //19
	}


	fscanf(Brf, "%d", &br);
	fclose(Brf); //16
	return br;
}

int StatDat() {
	int br = 0;
	FILE* Brf = NULL;

	Brf = fopen("statistika.txt", "r+");
	if (Brf == NULL) {
		perror("Problem kod otvaranja datoteke za statistiku"); //19
	}


	fscanf(Brf, "%d", &br);
	fclose(Brf);
	return br;
}

void dodaj() {
	system("cls");

	FILE* fp = NULL;
	fp = fopen(datoteka, "a");

	if (fp == NULL) {
		perror("dodavanje obaveza error"); //19
		exit(EXIT_FAILURE);

	}



	BrObaveze = BrojacDat();

	BrObaveze++;
	printf("\nUnesite biljesku broj %d.", BrObaveze);

	FILE* x = NULL;
	x = fopen("br.txt", "r+");
	if (x == NULL) {
		perror("Zapisivanje u br.txt error"); //19
	}
	rewind(x); //17
	fprintf(x, "%d", BrObaveze);
	fclose(x);


	printf("\nUnesite biljesku: ");
	char obaveza[200]; //12
	getchar();
	scanf("%199[^\n]", obaveza);
	fprintf(fp, "%d. %s\n\n", BrObaveze, obaveza);


	fclose(x);
	fclose(fp);
	system("cls");
}



void prikaz() {
	system("cls");
	FILE* fp = NULL;
	fp = fopen(datoteka, "r");

	if (fp == NULL) {
		perror("citanje biljeska error");  //19
	}


	else {


		char c;
		c = fgetc(fp);
		while (c != EOF) {
			printf("%c", c);
			c = fgetc(fp);
		}

		fseek(fp, 0, SEEK_END); //17
		int size = ftell(fp); //17
		if (size == 0) {
			printf("\nNema unesenih biljeska! Probajte upisati novu biljesku..");
		}

		printf("\n\n\n");
		system("pause");
		system("cls");
		fclose(fp);
	}
}

void IzbrisiDatoteku() {
	char YesNo;
	do {
		printf("\nJeste li sigurni da zelite izbrisati postojecu listu, te stvoriti novu? y/n: ");
		scanf(" %c", &YesNo);
	} while (YesNo != 'n' && YesNo != 'N' && YesNo != 'y' && YesNo != 'Y');


	if (YesNo == 'y' || YesNo == 'Y') {
		FILE* fp = NULL;
		fp = fopen(datoteka, "w");

		if (fp == NULL) {
			perror("Problem kod brisanja datoteke");
		}
		fclose(fp);


		FILE* x = NULL;
		x = fopen("br.txt", "w");
		if (x == NULL) {
			perror("Brisanje br.txt");
		}
		fprintf(x, "%d", 0);
		fclose(x);

		FILE* y = NULL;
		y = fopen("statistika.txt", "w");
		if (y == NULL) {
			perror("Brisanje statistike");
		}
		fclose(y);
	}
	system("cls");
}




OBAVEZE* zauzimanje(int broj) {
	OBAVEZE* polje = NULL;
	polje = (OBAVEZE*)calloc(broj, sizeof(OBAVEZE)); //14
	if (polje == NULL) {
		return NULL;
		perror("Zauzimanje polja");
	}
	else {
		return polje;
	}

}

void UnosPolje(OBAVEZE* ob, int broj) {

	FILE* fp = NULL;
	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		perror("otvaranje datoteke kod unosa podataka u polje");
	}



	int i;
	for (i = 0; i < broj; i++) {
		fscanf(fp, "%d%*c %199[^\n]", &(ob + i)->br, (ob + i)->obaveza);
	}




	fclose(fp);
}

void IzbrisiObavezu(OBAVEZE* p, int broj) {
	int num, i;
	char YesNo;
	system("cls");

	do {
		printf("\nJeste li sigurni da zelite izbrisati obavezu, pritisnite n za povratak! y/n: ");
		scanf(" %c", &YesNo);
	} while (YesNo != 'n' && YesNo != 'N' && YesNo != 'y' && YesNo != 'Y');


	if (YesNo == 'y' || YesNo == 'Y') {
		system("cls");
		FILE* pp = NULL;
		pp = fopen(datoteka, "r");
		if (pp == NULL) {
			perror("Problem kod citanja sadrzaja datoteke");
		}
		else {
			printf("\n\n");
			char c;
			c = fgetc(pp);
			while (c != EOF) {
				printf("%c", c);
				c = fgetc(pp);
			}

			fseek(pp, 0, SEEK_END);
			int size = ftell(pp);
			if (size == 0) {
				printf("\nNema unesenih obaveza! Probajte upisati koju obavezu..");
			}

			fclose(pp);

			if (size != 0) {
				do {

					printf("\nUnesite broj obaveze koji zelite izbrisati: ");
					scanf("%d", &num);

					if (num > broj || num <= 0) {
						printf("\nNe postoji obaveza pod tim brojem!");
					}
				} while (num > broj || num <= 0);
				/*
								char zaStat;
								int noviBrojac = StatDat();
								printf("\nJeste li odradili vasu obavezu? y/n: ");
								scanf(" %c", &zaStat);
								if (zaStat == 'y' || zaStat == 'Y') {
									FILE* stat = NULL;
									stat = fopen("statistika.txt", "r+");
									if (stat == NULL) {
										perror("Problem kod statistike datoteke");
									}
									noviBrojac++;
									rewind(stat);
									fprintf(stat, "%d", noviBrojac);
									fclose(stat);
								}
								printf("\n");
				*/

				for (i = num - 1; i < broj - 1; i++) {
					p[i] = p[i + 1];
				}

				broj--;
				FILE* fp = NULL;
				fp = fopen("br.txt", "r+");
				if (fp == NULL) {
					exit(EXIT_FAILURE);
				}
				rewind(fp);
				fprintf(fp, "%d", broj);
				fclose(fp);



				FILE* np = NULL;
				np = fopen(datoteka, "w+");
				if (np == NULL) {
					exit(EXIT_FAILURE);
				}
				for (i = 0; i < broj; i++) {
					(p + i)->br = i + 1;
					fprintf(np, "%d. %s\n\n", (p + i)->br, (p + i)->obaveza);
				}
				fclose(np);
				system("cls");
			}
			if (size == 0) {
				printf("\n");
				system("pause");
			}
		}
		system("cls");
	}
	system("cls");
}

void UrediObavezu(OBAVEZE* p, int broj) {
	system("cls");
	char YesNo;
	do {
		printf("\nJeste li sigurni da zelite urediti obavezu, pritisnite n za povratak! y/n: ");
		scanf(" %c", &YesNo);
	} while (YesNo != 'n' && YesNo != 'N' && YesNo != 'y' && YesNo != 'Y');


	if (YesNo == 'y' || YesNo == 'Y') {

		int ObavezaBr;
		char NovaObaveza[200];
		system("cls");
		if (broj != 0) {


			prikaz();


			do {
				printf("\n\nUnesite broj obaveze koji zelite urediti: ");
				scanf("%d", &ObavezaBr);
				if (ObavezaBr > broj || ObavezaBr <= 0) {
					printf("\nNema obaveze pod tim brojem!\n");
				}
			} while (ObavezaBr > broj || ObavezaBr <= 0);

			ObavezaBr--;
			printf("\nPreuredite obavezu: %d. %s\n", (p + ObavezaBr)->br, (p + ObavezaBr)->obaveza);
			getchar();
			scanf("%199[^\n]", &NovaObaveza);

			strcpy((p + ObavezaBr)->obaveza, NovaObaveza);

			int i;
			FILE* np = NULL;
			np = fopen(datoteka, "w+");
			if (np == NULL) {
				exit(EXIT_FAILURE);
			}

			for (i = 0; i < broj; i++) {
				(p + i)->br = i + 1;
				fprintf(np, "%d. %s\n\n", (p + i)->br, (p + i)->obaveza);
			}

			fclose(np);
			prikaz();


		}
		else {
			printf("\nNema unesenih obaveza!\n");
			system("pause");
		}
	}
	system("cls");
}


void statistika(int stat, int broj) {
	system("cls");
	if (broj == 0) {
		printf("\nSve obaveze su gotove\n");
	}
	else {
		broj += stat;
		printf("\nOd ukupno %d obaveza odradili ste %d obaveza, odnosno %d%%\n\n", broj, stat, (stat * 100) / broj);
	}
	system("pause");
	system("cls");
}


void pronadji(OBAVEZE* p, int broj) {
	system("cls");

	char text[200];
	printf("\nUnesite sadrzaj trazene obaveze: ");
	getchar();
	scanf("%199[^\n]", text);

	for (int i = 0; i < broj; i++) {
		if (strstr((p + i)->obaveza, text) != NULL) {
			printf("\nPronadjena je obaveza: %d. %s\n", (p + i)->br, (p + i)->obaveza);
		}

	}
	printf("\n");
	system("pause");
	system("cls");
}
/*
void sortirajBiljeske(OBAVEZE* p, int broj) {
	int i, j;
	OBAVEZE temp;

	for (i = 0; i < broj - 1; i++) {
		for (j = 0; j < broj - i - 1; j++) {
			if (strcmp((p + j)->obaveza, (p + j + 1)->obaveza) > 0) {
				// Zamijeni mjesta
				temp = *(p + j);
				*(p + j) = *(p + j + 1);
				*(p + j + 1) = temp;
			}
		}
	}
}*/

/*
void sortirajBiljeske(OBAVEZE* p, int broj) {
	if (broj == 0) {
		printf("Nema unesenih biljeski za sortiranje.\n");
		return;
	}

	qsort(p, broj, sizeof(OBAVEZE), compareObaveze);

	printf("Biljeske su uspjesno sortirane po abecednom redu.\n");
}

int compareObaveze(const void* a, const void* b) {
	OBAVEZE* obavezaA = (OBAVEZE*)a;
	OBAVEZE* obavezaB = (OBAVEZE*)b;

	return strcmp(obavezaA->obaveza, obavezaB->obaveza);
}
*/
int SortirajBiljeske(const void* a, const void* b) {
	const OBAVEZE* biljeskaA = (const OBAVEZE*)a;
	const OBAVEZE* biljeskaB = (const OBAVEZE*)b;

	return strcmp(biljeskaA->obaveza, biljeskaB->obaveza);
}