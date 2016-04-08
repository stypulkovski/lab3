#include "Slav.h"
// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>
#include <algorithm>

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);
void sexMap2Vec(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);
	sexMap2Vec(slavs, n);
	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	
	for(int i=0; i<n; i++) {
		vectorOfSlavs.push_back(&slavs[i]);
	}
	for(int i=0; i<n; i++) {
		int x = rand() % n; // zakres 0-5.
		if(x!=i)
			swap(vectorOfSlavs[i],vectorOfSlavs[x]);
	}

	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze

	for(vector<Slav *>::iterator vosIt = vectorOfSlavs.begin();
		vosIt != vectorOfSlavs.end(); ++vosIt) {
			cout << (*vosIt)->description() << endl;
	}
		

	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	
	for(int i=0; i<n; i++) {
		setOfSlavs.insert(vectorOfSlavs.back());
		vectorOfSlavs.pop_back();
	}
	
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	
	for(set<Slav *>::iterator sosIt = setOfSlavs.begin();
		sosIt != setOfSlavs.end(); ++sosIt) {
		mapOfSlavs[*sosIt++] = *sosIt--;
		setOfSlavs.erase(sosIt);
		setOfSlavs.erase(++sosIt);
		
	}
	
	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	
	for(map<Slav *, Slav *>::iterator mosIt = mapOfSlavs.begin();
		mosIt != mapOfSlavs.end(); ++mosIt) {
		cout << (*mosIt).first->description() << " oraz "
		<< (*mosIt).second->description() << endl;
	}
	
	REPORT_CONTAINERS;
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	
	for(int i=0; i<n; i++) {
		queueOfSlavs.push(&slavs[i]);
	}
	
	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.
	
	for(int i=0; i<n; i++) {
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.
	
	for(int i=0; i<n; i++) {
		while(!stackOfSlavs.empty()) {
			cout << stackOfSlavs.top()->description() << endl;
			stackOfSlavs.pop();
		}
	}

	REPORT_ADAPTERS;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}

void sexMap2Vec(Slav * slavs, int n)
{
	map <sex, vector <Slav *>> sexSlavsMap;
	for(int i=0;i<n;i++) {
		if(slavs[i].sexOfSlav()==M)
			sexSlavsMap[M].push_back(&slavs[i]);
		if(slavs[i].sexOfSlav()==F)
			sexSlavsMap[F].push_back(&slavs[i]);
		}
	cout << "Podzia� wzgl�dem p�ci: " << endl;
	for(vector <Slav *> ::iterator ssmIt=sexSlavsMap[M].begin();
		ssmIt != sexSlavsMap[M].end(); ssmIt++) {
			cout << "M: " << (**ssmIt).name() << endl;
		}
	for(vector <Slav *> ::iterator ssmIt=sexSlavsMap[F].begin();
		ssmIt != sexSlavsMap[F].end(); ssmIt++) {
			cout << "F: " << (**ssmIt).name() << endl;
		}
}

