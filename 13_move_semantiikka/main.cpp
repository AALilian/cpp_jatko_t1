/*Kirjoita ohjelma, joka luo kaksi std::string merkkijonoa, s1 ja s2. Sijoita s1:n arvoksi jokin merkkijono,
esim. îkissaî. s2 on aluksi tyhj‰.
a) Sijoita s1:n arvoksi s2. Tutki debuggerilla tilannetta ennen tai j‰lkeen sijoituksen. Yrit‰ lˆyt‰‰
std::string-olioiden sis‰lt‰ osoitin varsinaiseen merkkijonodataan. Mit‰ huomaat?
b) Sijoita s1:n arvoksi s2, mutta muuta s2 ensin rvalue-referenssiksi (std::move). Tutki debuggerilla
tilannetta ennen tai j‰lkeen sijoituksen. Yrit‰ lˆyt‰‰ std::string-olioiden sis‰lt‰ osoitin varsinaiseen
merkkijonodataan. Mit‰ huomaat?
c) Luo viel‰ merkkijonovektori (std::vector). Lis‰‰ luo std::string s3, jonka arvona on îkoiraî. Lis‰‰
s3 vektoriin (push_back) normaalisti, ja vaihtoehtoisesti muuttamalla s3 ensin rvalue-
referenssiksi (std::move). Tutki sijoituksia debuggerilla. Mit‰ huomaat?*/

#include <iostream>
#include <vector>

int main() {

	std::string s1 = "kissa";
	std::string s2;

	// a: s1 = s2; 
	// vaikka molempien arvo on sijoituksen j‰lkeen sama, s1 :lla ja s2:lla on edelleen eri osittajat / pointterit ja ne osoittavat eri kohtiin 

	// b: 
	// s1 = std::move(s2);
	//s2 = std::move(s1);
	// kun s2 sijoitetaan rvalueksi muutettu s1, s2 saa s1:n arvon ja alkaa osoittaa samaan kohtaan kuin s1. s1 j‰‰ tyhj‰ksi ja se ei osoita en‰‰ mihink‰‰n: s1 :lt‰ ryˆstet‰‰n sen sis‰lt‰m‰ data 

	// c: 
	std::vector<std::string> v;
	std::string s3 = "koira";
	//v.push_back(s3);
	v.push_back(std::move(s3));

	// normaalisti sijoittamalla vektoriin luodaan kopio s3: sta. Rvaluena s3 data menee vektorille, ja s3 itse j‰‰ tyhj‰ksi 


	return 0;
}