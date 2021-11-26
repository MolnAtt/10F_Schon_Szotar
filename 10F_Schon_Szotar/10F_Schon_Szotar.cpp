#include <iostream>
#include <vector>

using namespace std;



class Szotar // most nem generikus típusokkal foglalkozunk! 
{
public:
	struct Elem
	{
		string kulcs;
		int ertek;
		Elem(string k, int e)
		{
			this->kulcs = k;     
			this->ertek = e;
		}
	};


	vector<vector<Elem>>* hasitotabla; // ez nem A hasítótábla, hanem a leendõbeli hasíótábla CÍME!!

	// hasitofuggveny bejövõ paraméter kell legyen
	// tábla mérete is kell!

	int meret;
	int (*hasitofuggveny)(string); // a hasitofuggveny deklarációja

	Szotar(int m, int (*fuggvenyneve)(string))
	{
		hasitofuggveny = fuggvenyneve; 

		// vector<int> v(5, 7); // 5 hosszú vektor csupa 7-esekkel feltöltve
		hasitotabla = new vector<vector<Elem>>(m, vector<Elem>()); // m hosszú tömb, mindegyik cellájában van egy üres Elemvektor.
		 // a new nem egy vektorbanavektort ad vissza, hanem egy vektorbanavektor CÍMÉT!

	}

	void Add(string kulcs, int ertek)
	{
		vector<int> hely = helye(kulcs, ertek);
		// megnézzük, hogy olyat akar-e hozzáadni a felhasználó, ami már esetleg benne van-e. Ha igen, nem csinálunk semmit, ha nincs még benne, akkor hozzáadjuk.
		if (hely[1]<hasitotabla->at(hely[0]).size()) // a torlódó lista méreténél kisebb a "j" a helybõl
		{
			// elõször ilyenkor
		}
		else
		{
			// jó lenne, ha itt már meglenne az i értéke! (hasításból)
			hasitotabla->at(hely[0]).push_back(Elem(kulcs, ertek));
		}
	}

private:

	vector<int> helye(string kulcs, int ertek)
	{
		int i = hasitofuggveny(kulcs);

		int j = 0;
		int torlodo_lista_merete = hasitotabla->at(i).size();
		while (j < torlodo_lista_merete && hasitotabla->at(i)[j].kulcs != kulcs)
		{
			j++;
		}

		return vector<int>{i, j}; // i a sorszam, ez biztos van, j pedig vagy az elem, ha volt benne, vagy a lista mérete, ha nem volt benne
	}

	bool van_e_ilyen_kulcs(string kulcs)
	{
		int i = hasitofuggveny(kulcs);

		 // ez vektor!
		
		int j = 0;
		int torlodo_lista_merete = hasitotabla->at(i).size();
		while (j < torlodo_lista_merete && hasitotabla->at(i)[j].kulcs!=kulcs)
		{
			j++;
		}
		return j < torlodo_lista_merete; // eldöntés programozási tétel

	}


};

int hash_utolso(string telefonszam)
{
	return telefonszam[telefonszam.size() - 1] - 48;
}

int main()
{
    cout << "Hello World!\n";

	// elõre deklarált függvény átadása c++-ban
	// Szotar szotar(10, &hash_utolso);

	// lambda-kifejezés c++-ban: ("-> int" elhagyható)
	Szotar szotar(10, [](string telefonszam) -> int {return telefonszam[telefonszam.size() - 1] - 48; });
	// Elem elem("bla", 5); // lámlám, itt ilyet nem lehet

	szotar.Add("3619876532", 153);

}


