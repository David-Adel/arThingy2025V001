#ifndef SPECIESLIST_H
#define SPECIESLIST_H
#include "Main.h"


class SpeciesMgmnt;

class SpeciesList
{
public:
	bool SpeciesLockSelected = false;
	int speciesLockedToNum = -1;
	bool randomSpeciesFromFavs = true;
	bool nextSpeciesFromFavs = false;
	SpeciesMgmnt *speciesWork = NULL;//  = nullptr;
	int speciesNum = 0;
	SpeciesList()
	{
//		Species.currpos = 0;
		//Species.numspecies = 0;
		//start = NULL;
		//currPos = NULL;
		//work = NULL;
	};

	void insEnd(int speciesNum);
	//void insHere(LifeList *cLLData);
	void delCurrent();
	//void goFirst();
	//void goLast();
	void RandSpecies(int speciesIn, int currTime); // , bool all, SPECIESSUB changeType);
};

#endif