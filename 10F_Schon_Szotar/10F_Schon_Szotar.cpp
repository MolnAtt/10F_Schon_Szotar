#include <iostream>
#include <vector>
#include <string>

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
	int (*hasitofuggveny)(string); // a hasitofuggveny deklarációja C#-ban Func<string, int> hasitofuggveny

	Szotar(int m, int (*fuggvenyneve)(string)) // két bemenet, a méret és a hasítófüggvény, amit a user megad
	{
		this-> meret = m;
		this-> hasitofuggveny = fuggvenyneve; 
		// vector<int> v(5, 7); // 5 hosszú vektor csupa 7-esekkel feltöltve
		this-> hasitotabla = new vector<vector<Elem>>(m, vector<Elem>()); // m hosszú tömb, mindegyik cellájában van egy üres Elemvektor.
		 // a new nem egy vektorbanavektort ad vissza, hanem egy vektorbanavektor CÍMÉT!

	}

	void Add(string kulcs, int ertek)
	{
		vector<int> hely = helye(kulcs, ertek);
		int i = hely[0];
		int j = hely[1];
		// megnézzük, hogy olyat akar-e hozzáadni a felhasználó, ami már esetleg benne van-e. Ha igen, nem csinálunk semmit, ha nincs még benne, akkor hozzáadjuk.
		if (j < hasitotabla->at(i).size()) // a torlódó lista méreténél kisebb a "j" a helybõl
		{
			// updateelni kell mert van már ilyen
			hasitotabla->at(i)[j].ertek = ertek;
		}
		else
		{
			hasitotabla->at(i).push_back(Elem(kulcs, ertek));
		}
	}

	void diagnosztika()
	{
		cerr << "-------------- meret: "<< meret << "-----------------\n";
		for (int i = 0; i < meret; i++)
		{
			cerr << "[" << i << "]: " << to_string(hasitotabla->at(i)) << endl;
		}
		cerr << "--------------------------------------\n";
	}

private:

	string to_string(vector<Elem>& vektor)
	{
		string s = "";
		for (auto& elem : vektor)
		{
			s += "(" + elem.kulcs + ", " + std::to_string(elem.ertek) + ")  ";
		}
		return s;
	}

	vector<int> helye(string kulcs, int ertek)
	{
		int i = hasitofuggveny(kulcs);

		int j = 0;
		int torlodo_lista_merete = hasitotabla->at(i).size();
		while (j < torlodo_lista_merete && hasitotabla->at(i)[j].kulcs != kulcs) // addig növelgeti j-t, míg meg nem találja vagy a végére nem ér
			j++;

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
	// c#-ban így nézett volna ki:
	// Szotar szotar = new Szotar(10, s => telefonszam[s.size() - 1] - 48);

	// Elem elem("bla", 5); // lámlám, itt ilyet nem lehet

	szotar.diagnosztika();
	szotar.Add("3619876532", 153);
	szotar.diagnosztika();
	szotar.Add("3619876534", 183);
	szotar.diagnosztika();
	szotar.Add("3619876535", 123);
	szotar.diagnosztika();
	szotar.Add("3619876539", 85);
	szotar.diagnosztika();

	szotar.Add("3619876532", 87);
	szotar.diagnosztika();

	szotar.Add("3619876539", 187);
	szotar.diagnosztika();

	cerr << "A torlodassal volt problema!";


}


