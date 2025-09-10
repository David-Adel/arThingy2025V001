#ifndef LIFELIST_H
#define LIFELIST_H
// #include "main.h"
// #include "C:\Users\David\Documents\Visual Studio 2010\Projects\aaa Utilities\cell\cell\cell.h"


typedef	struct node
{
	CELLLOC CellLoc;
	struct node *next,*prev;
}node;

class LifeList
{

public: 
	//int cycleNo = 0; // number of cycles of this lifelist - will go neg and cycle
	//int LLreSets = 0; // number of rests per sec for this list
	CELLLOC workCell;
	CELLLOC deletedCell;
	node *currPos;
	node *start;
	node *toDelete;
	int activeLifeCount;
	int preActiveLifeCount = 0;
	int species;
	int xxcurrpos = 0;
	LifeList(int speciesin)
	{
		//cycleNo = 0;
		start=NULL;
		currPos = NULL;
		toDelete = NULL;
		activeLifeCount = 0;
		workCell.xLoc = 0; 
		workCell.yLoc = 0;
		deletedCell.xLoc = 0;
		deletedCell.yLoc = 0;
		species = speciesin;	
	};
	void addNew(CELLLOC cellLoc, int currSpecies);
	//void insHere(CELLLOC cellLoc);
	void delCurrent(int currSpecies);
	void goFirst();
	void goLast(int currSpecies);
	void goNext();
};
#endif