#include <iostream>
#include <string>
#include <sstream>
#include <set>
using namespace std;

/*******************************************************/
/** Generic Templates */

/** Hash Function Objects Template */
template<typename Key_Type>
struct myHash {};

/** Pair Function Objects Template */
template<typename T1, typename T2>
struct Pair {};

/** Map Function Objects Template */
template<typename KEY, typename VALUE>
class HashMap {};

/*******************************************************/
/** Specializations */
template<>
struct myHash<string>
{
	size_t operator()(const string& s)
	{
		return s[0];
	}
};

template<>
struct Pair<string, string>
{
	string first;
	string second;
	friend ostream& operator<<(ostream& out, const Pair& pair)
	{
		out << pair.first << " -> " << pair.second;
		return out;
	}
};

template<>
struct Pair<string, set<string>>
{
	string first;
	set<string> second;
	friend ostream& operator<<(ostream& out, const Pair& pair)
	{
		out << pair.first << " ->";
		typename set<string>::iterator iter = pair.second.begin();
		while (iter != pair.second.end())
		{
			cout << " " << *iter++;
		}
		return out;
	}
};

/** Specialzed Map Function Objects Template */
#define DEFAULT_CAPACITY	5

template<typename VALUE>
class HashMap<string, VALUE>
{
private:
	size_t capacity;
	Pair<string, VALUE>* myPairs;
public:
	HashMap() : capacity(DEFAULT_CAPACITY),
		myPairs(new Pair<string, VALUE>[DEFAULT_CAPACITY]) {}
	~HashMap() = default;

	VALUE& operator[](const string& key)
	{
		// check load factor and maybe rehash...
		size_t hashIndex = myHash<string>()(key) % capacity;
		int k = -1;
		while (1)
		{
			if (myPairs[hashIndex].first.length() == 0)
			{
				myPairs[hashIndex].first = key;
				break;
			}
			if (myPairs[hashIndex].first == key) break;
			cout << endl << "Collision of " << key << " with " << myPairs[hashIndex].first;
			k = k + 2;
			hashIndex = (hashIndex + k) % capacity;
		}
		return myPairs[hashIndex].second;
	}
	friend ostream& operator<<(ostream& os, const HashMap& hmap)
	{
		for (size_t i = 0; i < hmap.capacity; ++i)
		{
			os << endl << " [" << i << ":";
			if (hmap.myPairs[i].first != "") os << hmap.myPairs[i];
			os << "]";
		}
		return os;
	}
};


int main()
{
	HashMap<string, string> pokemon;
	pokemon["Sharmander"] = "fire";
	pokemon["Squirtle"] = "water";

	cout << endl << "pokemon[\"Sharmander\"] = " << pokemon["Sharmander"];
	cout << endl << "pokemon[\"DogFace\"] = " << pokemon["DogFace"];

	pokemon["DogFace"] = "dog food";
	cout << endl << endl << "pokemon:" << pokemon;

	HashMap<string, set<string>> effectivies;
	effectivies["grass"] = { "water", "ground", "rock" };
	effectivies["fire"] = { "grass", "ice", "bug", "steel" };
	cout << endl << endl << "effectivies:" << effectivies;

	return 0;
}
