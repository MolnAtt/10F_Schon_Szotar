#include <iostream>
#include <vector>
#include <string>

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
	int (*hasitofuggveny)(string); // a hasitofuggveny deklar�ci�ja C#-ban Func<string, int> hasitofuggveny

	Szotar(int m, int (*fuggvenyneve)(string)) // k�t bemenet, a m�ret �s a has�t�f�ggv�ny, amit a user megad
	{
		this-> meret = m;
		this-> hasitofuggveny = fuggvenyneve; 
		// vector<int> v(5, 7); // 5 hossz� vektor csupa 7-esekkel felt�ltve
		this-> hasitotabla = new vector<vector<Elem>>(m, vector<Elem>()); // m hossz� t�mb, mindegyik cell�j�ban van egy �res Elemvektor.
		 // a new nem egy vektorbanavektort ad vissza, hanem egy vektorbanavektor C�M�T!

	}

	void Add(string kulcs, int ertek)
	{
		vector<int> hely = helye(kulcs, ertek);
		int i = hely[0];
		int j = hely[1];
		// megn�zz�k, hogy olyat akar-e hozz�adni a felhaszn�l�, ami m�r esetleg benne van-e. Ha igen, nem csin�lunk semmit, ha nincs m�g benne, akkor hozz�adjuk.
		if (j < hasitotabla->at(i).size()) // a torl�d� lista m�ret�n�l kisebb a "j" a helyb�l
		{
			// updateelni kell mert van m�r ilyen
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
		while (j < torlodo_lista_merete && hasitotabla->at(i)[j].kulcs != kulcs) // addig n�velgeti j-t, m�g meg nem tal�lja vagy a v�g�re nem �r
			j++;

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
	// c#-ban �gy n�zett volna ki:
	// Szotar szotar = new Szotar(10, s => telefonszam[s.size() - 1] - 48);

	// Elem elem("bla", 5); // l�ml�m, itt ilyet nem lehet

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


