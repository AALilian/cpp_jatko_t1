/*16. Varaa niin paljon (tai niin monta kertaa) muistia new:llä, että muistinvaraus ei onnistu. Mikä poikkeus
tästä aiheutuu (ota poikkeus kiinni)? Miten paljon muistia tuli varata?
Pitäisikö muistinvarauksen epäonnistumiseen varautua ohjelmoitaessa?*/

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

	// tulee bad_alloc -poikkeus, eli allocation failure, muistia tuli varata 19289604096 * 4 = 77 158 416 384 tavua 
	// Pitäisikö muistinvarauksen epäonnistumiseen varautua ohjelmoitaessa? En tiiä... Mut ei välttämättä? Jos tulee muistinvarauksessa ongelmia, niin varmaan koodissa on jotain mätää 

	return 0;
}

/*17.Tutustu poikkeusten käytöstä käytyyn keskusteluun:
https://gamedev.stackexchange.com/questions/46424/try-catch-or-ifs-for-error-handling-in-c
Kannattaako poikkeuksia käyttää C++:ssa? Miksi tai miksi ei? */

// Miksi: "kun muut vaihtoehdot eivät käy järkeen", "when you don't care if you accidentally leak a little memory or fail to clean up a resource because you messed up the use of proper smart handles", 
// tekevät koodista luettavampaa, eivät tee koodista hitaampaa välttämättä nykyaikaisilla compliereilla?, koodin optimointi ei ole näin pienistä kiinni (tärkeämpää saada siitä toimivaa, luettavaa)

// Miksi ei: Hitaampia kuin esim. if laussseet?, lisäävät koodin määrää, tekevät koodista hauraampaa(esim. saa koodin näyttämään poikkeus -varmalta, vaikkei se sitä olisikaan), peliteollisuudessa osat konsoleiden compliers eivät
//  tue poikkeuksia kunnolla (->koodin uudelleen kirjoittaminen eri alustoille)