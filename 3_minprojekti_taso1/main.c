/*Taso 1 suoran tunnistaminen
Pakassa on 52 pelikorttia. Kortit ovat nelj�� eri maata (hertta, ruutu, risti, pata) ja 13:a eri numeroarvoa
(2-14). Yksitt�inen kortti voidaan siis esitt�� kokonaisluvulla 0..51. Kokonaisluvun perusteella voidaan
helposti laskea sek� ko. kortin maa ett� numeroarvo.
Pokerik�si koostuu viidest� pakasta otetusta kortista. Er�s k�sityyppi on �suora�, jolloin k�dest� l�ytyv�t
viiden per�kk�isen numeroarvon kortit, esim. 5, 8, 7, 6, 4 (korttien j�rjestyksell� ei siis ole v�li�). Jos
kaikki kortit sattuvat my�s olemaan samaa maata, on kyseess� �v�risuora�. Huomaa, ett� �ss�n
numeroarvo voi olla joko 14 tai 1.
Tutustu testiohjelmaan straight.c, joka k�y l�pi kaikki 5 kortin permutaatiot. Testiohjelma kutsuu
jokaiselle permutaatiolle funktiota is_straight, joka saa parametrinaan 5-alkioisen taulukon, jossa on ko.
korttien numeroarvot 2�14. Funktio palauttaa arvon 1, jos numeroarvoista voidaan j�rjest�� suora,
muuten 0.
Toteuta is_straight-funktio. Er�s vaihtoehto on j�rjest�� kortit ensin suuruusj�rjestykseen, jonka
j�lkeen on helppo testata, muodostavatko ne suoran. �ss� (1 tai 14) pit�� testata erikoistapauksena.
Merkitse yl�s ohjelman k�ytt�m� suoritusaika.*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

inline int is_straight(int* k);

int main() {

	/*

	K�yd��n l�pi kaikki viiden kortin permutaatiot, ja lasketaan
	kuin monta suoraa (v�risuoraa tai tavallista) l�ytyy.

	Ks. Wikipedia http://en.wikipedia.org/wiki/Poker_probability :

	Royal flush     4      combinations
	Straight flush  36     combinations
	Straight        10,200 combinations

	Koska 5 korttia voi olla 5 x 4 x 3 x 2 x 1 = 120 j�rjestyksess�,
	pit�isi suoria l�yty� (10200 + 36 + 4) x 120 = 1228800 kappaletta.
	*/

	int k0, k1, k2, k3, k4; /* Pakan kortit, 0..51*/
	int k[5]; /* Korttien numeroarvot, 2..14*/
	int suoria; /* Suorien lkm*/
	clock_t t1, t2;

	t1 = clock();
	suoria = 0;
	for (k0 = 0; k0 < 52; ++k0) {
		for (k1 = 0; k1 < 52; ++k1) {
			if (k1 == k0)continue;
			for (k2 = 0; k2 < 52; ++k2) {
				if (k2 == k0 || k2 == k1)continue;
				for (k3 = 0; k3 < 52; ++k3) {
					if (k3 == k0 || k3 == k1 || k3 == k2)continue;
					for (k4 = 0; k4 < 52; ++k4) {
						if (k4 == k0 || k4 == k1 || k4 == k2 || k4 == k3)continue;

						/*
						  Lasketaan korttien numeroarvot ja
						  tarkistetaan onko suora.
						*/
						k[0] = (k0 % 13) + 2;
						k[1] = (k1 % 13) + 2;
						k[2] = (k2 % 13) + 2;
						k[3] = (k3 % 13) + 2;
						k[4] = (k4 % 13) + 2;
						if (is_straight(k))
							++suoria;
					}
				}
			}
		}
	}
	t2 = clock();
	printf("Suoria     : %d kpl (oikea arvo 1228800)\n", suoria);
	printf("Aikaa kului: %.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

	// release aika: n 13 sek, debug: 33 sek

	return 0;
}


/*
  Parametrina 5 pelikortin numeroarvoa k, 2..14 (ei v�ltt�m�tt�
  numeroj�rjesteyksess�).

  Palauttaa 1, jos numeroarvot voidaan j�rjest�� siten, ett�
  ne muodostavat suoran (esim. 4,5,6,7,8).

  Huom! �ss�� (arvo 14) voidaan k�ytt�� suorissa my�s arvona 1
  (esim. 1,2,3,4,5).
*/

int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

inline int is_straight(int* k) {
	qsort(k, 5, sizeof(int), compare); // sort from small to high

	if (k[4] == 14) {
		if ((k[0] == 10 && k[1] == 11 && k[2] == 12 && k[3] == 13) || (k[0] == 2 && k[1] == 3 && k[2] == 4 && k[3] == 5)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		// ei �ss��
		int testRank = k[0] + 1;

		int i;
		for (i = 1; i < 5; i++) {
			if (k[i] != testRank) return 0;

			testRank++;
		}
		return 1;
	}
}