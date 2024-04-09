/*Sinulla on roolipeliss‰ kokonaislukuvektori (std::vector) kokonaislukuja, jotka kuvaavat vihollisten
hitpointseja (HP). Onnistuneen loitsusi ansiosta jokaista HP:ta tulisi v‰hent‰‰ 100:lla (tai asettaa 0:aan,
jos HP on t‰ll‰ hetkell‰ 100 tai alempi).
K‰yt‰ v‰hennyksen toteutukseen std::for_each -algoritmia. for_each haluaa saada alkioille teht‰v‰n
operaation parametrina; toteuta se seuraavilla eri tavoilla:
a. erillisen‰ funktiona
b. funktio-objektina (tutustu tarvittaessa)
c. lambda-funktiona
d. nimettyn‰ lambda-funktiona
J‰rjest‰ lopuksi vektori suurimmasta pienimp‰‰n k‰ytt‰en std::sort-funktiota. Anna j‰rjestyskriteeri
(laskeva j‰rjestys) sort:lle lambda-funktiona.*/

#include <iostream>
#include <vector>
#include <algorithm>
 
void ReduceHP(int& hp) {
	if (hp > 100) {
		hp -= 100;
	}
	else {
		hp = 0;
	}
}

class Reduce_HP {
public: 
	void operator() (int& hp) const { 
		if (hp > 100) {
			hp -= 100;
		}
		else {
			hp = 0;
		}
	}
};


int main() {
	std::vector<int> HPs = { 100, 213, 87, 5, 120 };

	std::cout << "HPt alussa: ";
	auto print = [](const int& n) { std::cout << n << ' '; };
	std::for_each(HPs.cbegin(), HPs.cend(), print);

	// a. erillisen‰ funktiona:
	/*std::for_each(HPs.begin(), HPs.end(), ReduceHP);*/

	// b. funktio-objektina: 
	/*for_each(HPs.begin(), HPs.end(), Reduce_HP());*/

	// c. lambda-funktiona:
	/*std::for_each(HPs.begin(), HPs.end(), [](int& hp) {
		if (hp > 100) {
			hp -= 100;
		}
		else {
			hp = 0;
		}
	});*/

	// d. nimettyn‰ lambda funktiona:
	auto reduce_hp = [](int& hp) {
		if (hp > 100) {
			hp -= 100;
		}
		else {
			hp = 0;
		}
	};
	for_each(HPs.begin(), HPs.end(), reduce_hp);

	std::cout << "\nHPt lopussa: ";
	std::for_each(HPs.cbegin(), HPs.cend(), print);

	std::cout << "\nHPt suurimmasta pieninp‰‰n: ";
	std::sort(HPs.begin(), HPs.end(), [](int a, int b) { return a > b; });
	std::for_each(HPs.cbegin(), HPs.cend(), print);
	std::cout << std::endl;

	return 0;
}