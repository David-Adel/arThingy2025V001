#include "main.h"

void LifeList::addNew(CELLLOC cellLoc,int  currSpecies) //insert at end - except now it inserts at start
{ // if (DEBUGON) { 	*debugFile <<"LifeList::insEnd(Cell *cellPTR)"; cin >> ch ;} 
	if (start == NULL)
	{
		start = new node;
		start->CellLoc = cellLoc;
		start->next = NULL;
		start->prev = NULL;
		currPos = start;
		//std::cout << std::endl << "start = null " << Species.speciesarray[currSpecies].SpeciesId << " llcurrpos++ " << Species.speciesarray[currSpecies].lifelist->xxcurrpos << " lifecount " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << std::endl;

		activeLifeCount = 1;
	}
	else
	{
		if (currPos->prev == NULL)
		{
			node* temp1;
			temp1 = new node;
			temp1->next = start;
			temp1->CellLoc = cellLoc;
			currPos->prev = temp1;
			temp1->prev = NULL;
			start = temp1;
			activeLifeCount++;
			xxcurrpos++;
		}
		else
		{
			node *temp1, *temp2;
			temp1 = currPos->prev;
			temp2 = new node;
			temp2->next = currPos;
			temp2->prev = temp1;
			temp1->next = temp2;
			currPos->prev = temp2;
			temp2->CellLoc = cellLoc;
			activeLifeCount++;
			xxcurrpos++;
		}
		
	}
}


void LifeList::goNext()
{
	if (currPos->next == NULL)
	{
		goFirst();	
//		std::cout << std::endl << "go next first " << Species.speciesarray[Species.currpos].SpeciesId << " llcurrpos++ " << Species.speciesarray[Species.currpos].lifelist->xxcurrpos << " lifecount " << Species.speciesarray[Species.currpos].lifelist->activeLifeCount << std::endl;
	}
	else
	{
		currPos = currPos->next;
		xxcurrpos++;
	}
} // go to srt of list

void LifeList::delCurrent(int currSpecies)//::delCurrent() //(delete current pos)
{
//node *toDelete;
//	std::cout << std::endl << "dell curr " << Species.speciesarray[Species.currpos].SpeciesId << " llcurrpos++ " << Species.speciesarray[Species.currpos].lifelist->xxcurrpos << " lifecount " << Species.speciesarray[Species.currpos].lifelist->activeLifeCount << std::endl;
toDelete = currPos;
if (currPos != NULL) 
	{	if ((currPos->next == NULL) && (currPos->prev == NULL))
		{
// bad place to be
			//std::cout << "\n lifelist countwhen null null: " << activeLifeCount; // << " globalcnt" << gbls->gblcnt
//			std::cout << std::endl << "dell last ****** " << Species.speciesarray[currSpecies].SpeciesId <<  " lifecount " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << std::endl;

			activeLifeCount--;// = 0;
			delete(toDelete);
			currPos = NULL;
			start = currPos;
			xxcurrpos = 0;
		} 
		else
		{	if (currPos->next == NULL)
			{
				currPos = currPos->prev;
				currPos->next = NULL;
				xxcurrpos--;
			}
			else
			{	if (currPos->prev == NULL)
				{
				currPos = currPos->next;
				currPos->prev = NULL;
				start = currPos;
				xxcurrpos = 1;
				}
				else
				{
					currPos->next->prev = currPos->prev;
					currPos->prev->next = currPos->next;
					currPos = currPos->next;
					//xxcurrpos--;
				}
			}
			delete(toDelete);
			activeLifeCount--;
			//if (currPos == NULL) std::cout << "\n lifelist count: " << activeLifeCount; // << " globalcnt" << gbls->gblcnt;
		}
	}
	else
	{
		std::cout << std::endl << "bad bad dell null ****** " << Species.speciesarray[currSpecies].SpeciesId << " llcurrpos++ " << Species.speciesarray[currSpecies].lifelist->xxcurrpos << " lifecount " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << std::endl;
	}

}
void LifeList::goFirst() 
{ 
	if (start == NULL)
	{
		//std::cout << std::endl << "go first " << species << " llcurrpos++ " << Species.speciesarray[species].lifelist->xxcurrpos << " lifecount " << Species.speciesarray[species].lifelist->activeLifeCount << std::endl;

	}
	else
	{
		currPos = start;
		xxcurrpos = 0;
	}
} // go to srt of list
void LifeList::goLast(int currSpecies) {
	std::cout << std::endl << "go next " << Species.speciesarray[currSpecies].SpeciesId << " llcurrpos++ " << Species.speciesarray[currSpecies].lifelist->xxcurrpos << " lifecount " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << std::endl;
	while (currPos->next != NULL) currPos = currPos->next;} // go to end of list
