/*16. Varaa niin paljon (tai niin monta kertaa) muistia new:ll�, ett� muistinvaraus ei onnistu. Mik� poikkeus
t�st� aiheutuu (ota poikkeus kiinni)? Miten paljon muistia tuli varata?
Pit�isik� muistinvarauksen ep�onnistumiseen varautua ohjelmoitaessa?*/

#include <iostream>
#include <exception>

int main() {
	size_t total = 0;
	size_t i = 1024 * 1024;

	try {
		while (true) {
			int* allocate = new int[i];
			total += i;

			std::cout << "total: " << total << "\n";
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << "\n";
	}

	// tulee bad_alloc -poikkeus, eli allocation failure, muistia tuli varata 19289604096 * 4 = 77�158�416�384 tavua 
	// Pit�isik� muistinvarauksen ep�onnistumiseen varautua ohjelmoitaessa? En tii�... Mut ei v�ltt�m�tt�? Jos tulee muistinvarauksessa ongelmia, niin varmaan koodissa on jotain m�t�� 

	return 0;
}

/*17.Tutustu poikkeusten k�yt�st� k�ytyyn keskusteluun:
https://gamedev.stackexchange.com/questions/46424/try-catch-or-ifs-for-error-handling-in-c
Kannattaako poikkeuksia k�ytt�� C++:ssa? Miksi tai miksi ei? */

// Miksi: "kun muut vaihtoehdot eiv�t k�y j�rkeen", "when you don't care if you accidentally leak a little memory or fail to clean up a resource because you messed up the use of proper smart handles", 
// tekev�t koodista luettavampaa, eiv�t tee koodista hitaampaa v�ltt�m�tt� nykyaikaisilla compliereilla?, koodin optimointi ei ole n�in pienist� kiinni (t�rke�mp�� saada siit� toimivaa, luettavaa)

// Miksi ei: Hitaampia kuin esim. if laussseet?, lis��v�t koodin m��r��, tekev�t koodista hauraampaa(esim. saa koodin n�ytt�m��n poikkeus -varmalta, vaikkei se sit� olisikaan), peliteollisuudessa osat konsoleiden compliers eiv�t
//  tue poikkeuksia kunnolla (->koodin uudelleen kirjoittaminen eri alustoille)