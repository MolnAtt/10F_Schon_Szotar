#include <iostream>
#include <vector>

using namespace std;



class Szotar // most nem generikus t�pusokkal foglalkozunk! 
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


	vector<vector<Elem>>* hasitotabla; // ez nem A has�t�t�bla, hanem a leend�beli has��t�bla C�ME!!

	// hasitofuggveny bej�v� param�ter kell legyen
	// t�bla m�rete is kell!

	int meret;
	int (*hasitofuggveny)(string); // a hasitofuggveny deklar�ci�ja

	Szotar(int m, int (*fuggvenyneve)(string))
	{
		hasitofuggveny = fuggvenyneve; 

		// vector<int> v(5, 7); // 5 hossz� vektor csupa 7-esekkel felt�ltve
		hasitotabla = new vector<vector<Elem>>(m, vector<Elem>()); // m hossz� t�mb, mindegyik cell�j�ban van egy �res Elemvektor.
		 // a new nem egy vektorbanavektort ad vissza, hanem egy vektorbanavektor C�M�T!

	}

	void Add(string kulcs, int ertek)
	{
		vector<int> hely = helye(kulcs, ertek);
		// megn�zz�k, hogy olyat akar-e hozz�adni a felhaszn�l�, ami m�r esetleg benne van-e. Ha igen, nem csin�lunk semmit, ha nincs m�g benne, akkor hozz�adjuk.
		if (hely[1]<hasitotabla->at(hely[0]).size()) // a torl�d� lista m�ret�n�l kisebb a "j" a helyb�l
		{
			// el�sz�r ilyenkor
		}
		else
		{
			// j� lenne, ha itt m�r meglenne az i �rt�ke! (has�t�sb�l)
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

		return vector<int>{i, j}; // i a sorszam, ez biztos van, j pedig vagy az elem, ha volt benne, vagy a lista m�rete, ha nem volt benne
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
		return j < torlodo_lista_merete; // eld�nt�s programoz�si t�tel

	}


};

int hash_utolso(string telefonszam)
{
	return telefonszam[telefonszam.size() - 1] - 48;
}

int main()
{
    cout << "Hello World!\n";

	// el�re deklar�lt f�ggv�ny �tad�sa c++-ban
	// Szotar szotar(10, &hash_utolso);

	// lambda-kifejez�s c++-ban: ("-> int" elhagyhat�)
	Szotar szotar(10, [](string telefonszam) -> int {return telefonszam[telefonszam.size() - 1] - 48; });
	// Elem elem("bla", 5); // l�ml�m, itt ilyet nem lehet

	szotar.Add("3619876532", 153);

}


