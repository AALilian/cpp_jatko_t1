/*taso 2: suoran tunnistaminen hakutaulun avulla
Tehosta suoran tunnistamista hakutaulun avulla. Hakutaulusta voi nopeasti tarkistaa, muodostavatko
annetut kortit suoran.
Vihje toteutukseen:
Esitet‰‰n k‰den kaikkien korttien numeroarvot bittivektorina.
Bitti on p‰‰ll‰, jos ko. numeroarvo kuuluu k‰teen.
bitti 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
kortti| | | | A | K | Q | J | T | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
Luo siis ensin tyhj‰ bittivektori, jossa kaikki bitit ovat 0. K‰y sen j‰lkeen k‰den viiden kortin numeroarvot
l‰pi, ja aseta ko. numeroarvoa vastaava bitti p‰‰lle. K‰yt‰ lopuksi bittivektoria hakutaulun indeksointiin.
Hakutauluun on etuk‰teen talletettu arvo 1, jos ko. indeksia vastaava k‰si on suora, muuten 0.
Tutustu bittitason operaatioihin esim. t‰‰ll‰: https://en.wikipedia.org/wiki/Bitwise_operations_in_C.
Aja optimoitu ohjelma, ja vertaa suoritukseen kuluvaa aikaa alkuper‰iseen versioon. J‰t‰ hakutaulun
alustukseen k‰ytett‰v‰ aika huomioimatta.
Yrit‰ myˆs selvitt‰‰, miten paljon enemm‰n muistia optimoitu ohjelma k‰ytt‰‰. Mink‰ muistin osan
(stack, heap, koodi, tms.) kulutus lis‰‰ntyi?*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX 1228800

inline int is_straight(int* k);

static uint16_t lookup_table[MAX] = { 0 };

int main() {

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

	// debug: 9.7 sec, release: 3.7 sec

	// muistinkulutus
	// ei optimoitu : 581 KB
	// optimoitu : 3 MB

	return 0;
}


inline int is_straight(int* k) {

	unsigned int bittivektori = 0;

	for (int i = 0; i < 5; i++) {
		if (k[i] == 14) {
			bittivektori |= 0x2;
		}
		bittivektori |= (1 << k[i]);
	}

	if (lookup_table[bittivektori] == 1) {
		return 1;
	}
	else {
		for (int i = 10; i > 0; i--) {
			if ((bittivektori & (0x1F << i)) == (0x1F << i)) {
				// suora lˆydetty, asetetaan hakutauluun ja palautetaan 1
				lookup_table[bittivektori] = 1;

				return 1;
			}
		}
	}

	return 0;
}