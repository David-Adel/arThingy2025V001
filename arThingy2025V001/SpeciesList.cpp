#include "main.h"
class SpeciesMgmnt;

class Camera;
int randomRange(int range);
//void ChageShape(SHAPE newShape, Plane* planeIn);
//void KeyboardGL(unsigned char c, int x, int y);
class LifeList;
//class Plane * planeptr;
//void CreateSeeds(Plane* planeIn, int maxSeeds, bool rainbowon, int speciesin);
void ChageShape();
void NextFav();
class SpeciesMgmnt;
//extern SpeciesList* speciesptr;
void SpeciesList::insEnd(int speciesNum) //insert at end - except now it inserts at start
{ // if (DEBUGON) { 	*debugFile <<"SpeciesList::insEnd(LifeList *LifeListPTR)"; cin >> ch ;} 
	//Species.speciesarray[Species.numspecies] = *sdata;
	Species.speciesarray[speciesNum].lifelist = new LifeList(speciesNum);
	Species.speciesarray[speciesNum].rainbow = new Rainbow;
	Species.speciesarray[speciesNum].rainbow->speciesNum = speciesNum;
	Species.speciesarray[speciesNum].SpeciesId = speciesNum;
	//Species.numspecies++;
}
void SpeciesList::delCurrent()//::delCurrent() //(delete current pos)
{

	std::cout << "Species cant be deleted";
	
}
//void SpeciesList::goFirst()
//{
//	Species.currpos = 0;
//
//} // go to srt of list
//void SpeciesList::goLast()
//{ 
//	Species.currpos = Species.numspecies;
//} // go to end of list

void SpeciesList::RandSpecies(int speciesIn, int currTime) //, bool all, SPECIESSUB changeType )
{
	int maxage = MaxAge;
	float maxheight = 0;
	float maxheighttmp = 0;
	int z = 0;
	int x = 0;
	int y = 0;
	if ((SpeciesLockSelected == true) || (randomSpeciesFromFavs) || (nextSpeciesFromFavs) || (DUPESPECIES && (speciesIn != 0)))
	{

		if ((DUPESPECIES) && ((randomSpeciesFromFavs) || nextSpeciesFromFavs))
		{
			Species.speciesarray[speciesIn].data = Species.speciesarray[0].data;
			Species.speciesarray[speciesIn].data.timeAlive = 0;
			Species.speciesarray[speciesIn].data.timeTillMutate = randomRange(plane.maxTimeToMutate); //plane.maxTimeToMutate/2  + randomRange(plane.maxTimeToMutate / 2);
			std::cout << "ID " << Species.speciesarray[speciesIn].SpeciesId << " ((DUPESPECIES) && ((randomSpeciesFromFavs) || nextSpeciesFromFavs))"  <<  std::endl;
		}
		else
		{


			if ((SpeciesLockSelected == true) &&  !(randomSpeciesFromFavs || nextSpeciesFromFavs))
			{
				Species.speciesarray[speciesIn].data = Species.speciesarray[speciesLockedToNum].data;
				Species.speciesarray[speciesIn].data.timeAlive = 0;
				Species.speciesarray[speciesIn].data.timeTillMutate = randomRange(plane.maxTimeToMutate); // (plane.maxTimeToMutate / 2) + randomRange(plane.maxTimeToMutate / 2);
				std::cout << "ID " << Species.speciesarray[speciesIn].SpeciesId << " if (SpeciesLockSelected == true)" << std::endl;

			}
			else
			{
				if (randomSpeciesFromFavs)
				{
					int SpeciesToLoad = 0;
					SpeciesToLoad = randomRange(NUMSAVESPECIES);
					Species.speciesarray[speciesIn].data = speciesWork->speciesTmpSave[SpeciesToLoad];
					Species.speciesarray[speciesIn].data.timeAlive = 0;
					Species.speciesarray[speciesIn].data.timeTillMutate = randomRange(plane.maxTimeToMutate);  //(plane.maxTimeToMutate / 2) + randomRange(plane.maxTimeToMutate / 2);
					std::cout << "ID " << Species.speciesarray[speciesIn].SpeciesId << "(randomSpeciesFromFavs) " << SpeciesToLoad << std::endl;
				}
				else
				{
					if (nextSpeciesFromFavs)
					{
						NextFav();
						std::cout << "ID " << Species.speciesarray[speciesIn].SpeciesId << "(nextSpeciesFromFavs))" << std::endl;
					}
					else
					{
						std::cout << "bAD  bAD bAD bAD bAD bAD bAD bAD bAD bAD bAD bAD bAD bAD RandSpecies " << std::endl;
					}
				}
			}
		}
	}
	//else
	//	{
	//		if (SpeciesLockSelected == true)
	//		{
	//			Species.speciesarray[speciesIn].data = Species.speciesarray[speciesLockedToNum].data;
	//			Species.speciesarray[speciesIn].data.timeAlive = 0;
	//			Species.speciesarray[speciesIn].data.timeTillMutate = (plane.maxTimeToMutate / 2) + randomRange(plane.maxTimeToMutate / 2);
	//		}
	//		else
	//		{
	//			if (randomSpeciesFromFavs)
	//			{
	//				int SpeciesToLoad = 0;
	//				SpeciesToLoad = randomRange(NUMSAVESPECIES);
	//				Species.speciesarray[speciesIn].data = speciesWork->speciesTmpSave[SpeciesToLoad];
	//				Species.speciesarray[speciesIn].data.timeAlive = 0;
	//				Species.speciesarray[speciesIn].data.timeTillMutate = randomRange(plane.maxTimeToMutate); // (plane.maxTimeToMutate / 2) + randomRange(plane.maxTimeToMutate / 2);
	//				std::cout << "ID " << Species.speciesarray[speciesIn].SpeciesId << " Loaded from Favs species # " << SpeciesToLoad << std::endl;
	//			}
	//			else
	//			{
	//				Species.speciesarray[speciesIn].data = Species.speciesarray[0].data;
	//				Species.speciesarray[speciesIn].data.timeAlive = 0;
	//				Species.speciesarray[speciesIn].data.timeTillMutate = randomRange(plane.maxTimeToMutate); //(plane.maxTimeToMutate / 2) + randomRange(plane.maxTimeToMutate / 2);
	//			}
	//		}
	//	}
	//}
	//
	//
	//
	else
	{
		//if (randomSpeciesFromFavs && DUPESPECIES)
		//{
		//	//std::cout << std::endl << "speciesHold->allSavedSpeciesPointer at start: " << speciesHold->allSavedSpeciesPointer << std::endl;
		//	speciesHold->allSavedSpeciesPointer = speciesHold->allSavedSpeciesPointer + 1;
		//	// //
		//	while (!speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].dirActive && (speciesHold->allSavedSpeciesPointer < NUMSAVESPECIES))
		//	{
		//		speciesHold->allSavedSpeciesPointer++;
		//	}
		//	if (speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].dirActive)
		//	{
		//		std::cout << std::endl << " ] move forward loading species number  " << speciesHold->allSavedSpeciesPointer << "file number " << speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].speciesSave.fileNumber << std::endl;
		//	}
		//	else
		//	{
		//		std::cout << std::endl << "Panic loaded empty specoies or ok now" << std::endl;
		//		speciesHold->allSavedSpeciesPointer = 0; // set pointer back to start
		//		//speciesHold->allSavedSpeciesNumActive = speciesHold->allSavedSpeciesPointer; // set the max 
		//	}
		//	for (size_t i = 0; i < NUMSPECIES; i++)
		//	{
		//		Species.speciesarray[i].data = speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].speciesSave;
		//		if (plane.shape == SPHERE)
		//		{
		//			Species.speciesarray[i].data.heightgrowth = (float)1 / Species.speciesarray[i].data.death;
		//		}
		//		else
		//		{
		//			Species.speciesarray[i].data.heightgrowth = 0.0;
		//		}
		//		if (Species.speciesarray[i].data.showBaseColor)
		//		{
		//			Species.speciesarray[i].data.baseColorRed = randomRange(256);
		//			Species.speciesarray[i].data.baseColorGreen = randomRange(256);
		//			Species.speciesarray[i].data.baseColorBlue = randomRange(256);
		//			int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
		//			if ((zzz > 650) || (zzz < 118))
		//			{
		//				Species.speciesarray[i].data.baseColorRed = randomRange(256);
		//				Species.speciesarray[i].data.baseColorGreen = randomRange(256);
		//				Species.speciesarray[i].data.baseColorBlue = randomRange(256);
		//			}
		//		}
		//	}
		//	//allSavedSpeciesNumActive
		//	//speciesHold->allSavedSpeciesPointer++;
		//	speciesptr->SpeciesLockSelected = true;
		//	speciesptr->speciesLockedToNum = 1;
		//}
//  Mutation timing
Species.speciesarray[speciesIn].data.timeTillMutate = randomRange(plane.maxTimeToMutate);
		Species.speciesarray[speciesIn].data.timeAlive = 0;
		//if ((NUMSPECIES > 1) && (speciesIn == 0))
		//{
		//	Species.speciesarray[speciesIn].data.timeTillMutate = (plane.maxTimeToMutate) + randomRange(plane.maxTimeToMutate / 4);
		//}
// initial SEED
		Species.speciesarray[speciesIn].clusterSizeMin = randomRange(10);
		Species.speciesarray[speciesIn].clusterSizeMax = randomRange(30);
		Species.speciesarray[speciesIn].numseedsMin = randomRange(5);
		Species.speciesarray[speciesIn].numseedsMax = randomRange(10);
		Species.speciesarray[speciesIn].seedXrangeMin = randomRange(3);
		Species.speciesarray[speciesIn].seedXrangeMax = randomRange(10);
		Species.speciesarray[speciesIn].seedYrangeMin = randomRange(3);
		Species.speciesarray[speciesIn].seedYrangeMax = randomRange(10);
		Species.speciesarray[speciesIn].data.clusterSize = Species.speciesarray[speciesIn].clusterSizeMin + randomRange(Species.speciesarray[speciesIn].clusterSizeMax - Species.speciesarray[speciesIn].clusterSizeMin);
		Species.speciesarray[speciesIn].data.numseeds =  Species.speciesarray[speciesIn].numseedsMin + randomRange(Species.speciesarray[speciesIn].numseedsMax - Species.speciesarray[speciesIn].numseedsMin);
		Species.speciesarray[speciesIn].data.seedXrange = Species.speciesarray[speciesIn].seedXrangeMin + randomRange(Species.speciesarray[speciesIn].seedXrangeMax - Species.speciesarray[speciesIn].seedXrangeMin);
		Species.speciesarray[speciesIn].data.seedYrange = Species.speciesarray[speciesIn].seedYrangeMin + randomRange(Species.speciesarray[speciesIn].seedYrangeMax - Species.speciesarray[speciesIn].seedYrangeMin);

		if (NUMSPECIES < 5) //5
		{

			Species.speciesarray[speciesIn].data.clusterSize = Species.speciesarray[speciesIn].data.clusterSize * 2;
			Species.speciesarray[speciesIn].data.numseeds = Species.speciesarray[speciesIn].data.numseeds * 2;
			Species.speciesarray[speciesIn].data.seedXrange = Species.speciesarray[speciesIn].data.seedXrange * 2;
			Species.speciesarray[speciesIn].data.seedYrange = Species.speciesarray[speciesIn].data.seedYrange * 2;
		}
		
		
// AGE,  fertility, life and death color


		Species.speciesarray[speciesIn].data.showAvgColor = (randomRange(100) < 50);

		Species.speciesarray[speciesIn].data.BlackDeath = true; // (randomRange(100) < 90);
		//maxage = randomRange(MaxAge);
		Species.speciesarray[speciesIn].data.death = randomRange(MaxAge); // the age at which the cell will die  ********** this will need to move to an energy level
		Species.speciesarray[speciesIn].data.fend = Species.speciesarray[speciesIn].data.death - randomRange(Species.speciesarray[speciesIn].data.death/2); // fertility end - at this point the cell will stop looking for a mate
		Species.speciesarray[speciesIn].data.fstart = 1+ randomRange(Species.speciesarray[speciesIn].data.fend/2);   // fertility start - at this age the cell will start looking for a mate
		//if ((randomRange(100) < 50) && (Species.speciesarray[speciesIn].lifelist->activeLifeCount > 100))
		//{
		//	int tmpMultiplier = 10;
		//	for (int i = 0; i < Species.speciesarray[speciesIn].lifelist->activeLifeCount; i++)
		//	{			
		//		plane.pData[Species.speciesarray[speciesIn].lifelist->currPos->CellLoc.xLoc][Species.speciesarray[speciesIn].lifelist->currPos->CellLoc.yLoc].Age 
		//			= ((plane.pData[Species.speciesarray[speciesIn].lifelist->currPos->CellLoc.xLoc][Species.speciesarray[speciesIn].lifelist->currPos->CellLoc.yLoc].Age / tmpMultiplier) * tmpMultiplier);
		//		Species.speciesarray[speciesIn].lifelist->goNext();
		//	}
		//}
// HEIGHT
		if (plane.shape == SPHERE) maxheighttmp = 2.0f;
		else maxheighttmp = 0.0f;
		//if (randomRange(100)< 10)  maxheighttmp = 1.0f;
		if (maxheighttmp == 0) maxheight = 0;
		else maxheight = ((float)Species.speciesarray[speciesIn].data.death / (float)maxage) *(float) maxheighttmp;
		Species.speciesarray[speciesIn].data.heightgrowth = maxheight / Species.speciesarray[speciesIn].data.death;
		Species.speciesarray[speciesIn].data.decadeHeightShow = false;//  (randomRange(100) < 50);
// population control using number around and colorfobia.		
		int tmpxx = 0;
		if (randomRange(100)< 50 ) Species.speciesarray[speciesIn].data.Range =  randomRange(40) + 1;
		else Species.speciesarray[speciesIn].data.Range = randomRange(20) + 1;
		//Species.speciesarray[speciesIn].data.Range = 1;
		//Species.speciesarray[speciesIn].data.Range = randomRange(10) + 2;
		//Species.speciesarray[speciesIn].data.Range = 30;
		tmpxx = (int)pow(((Species.speciesarray[speciesIn].data.Range * 2) + 1), 2);
		if (randomRange(100) < 20) Species.speciesarray[speciesIn].data.overPop = randomRange(tmpxx * 200);
		else Species.speciesarray[speciesIn].data.overPop = randomRange(tmpxx * 1.5);

		Species.speciesarray[speciesIn].data.overPop =  randomRange(200 * tmpxx);// +100 * tmpxx;

		//Species.speciesarray[speciesIn].data.overPop = tmpxx*2000; //randomRange(tmpxx);// *10);
		if (randomRange(100) < 50) Species.speciesarray[speciesIn].data.maxNumaround = randomRange(tmpxx);
		else Species.speciesarray[speciesIn].data.maxNumaround = tmpxx / 2 + randomRange(tmpxx / 2);

		Species.speciesarray[speciesIn].data.maxNumaround = randomRange(tmpxx *1.5); //tmpxx * 2

		//Species.speciesarray[speciesIn].data.maxNumaround = tmpxx * 200;
		Species.speciesarray[speciesIn].data.mateWithOtherSpecies =  (randomRange(100) < 50); // 10
		Species.speciesarray[speciesIn].data.mateRange =1 +  randomRange(8); // 4; // when fining 2 cells to mate how far away to look for mate
// Child control
		if (randomRange(100) < 50)
		{
			Species.speciesarray[speciesIn].data.childRange = 2+ randomRange(3); // was 2  +
		}
		else
		{
			Species.speciesarray[speciesIn].data.childRange = 3+ randomRange(10);// 3; // how far away to look for empty loc to  to place child
		}
		if (((Species.speciesarray[speciesIn].data.childRange / 2)*2) == Species.speciesarray[speciesIn].data.childRange)  //make childrage an odd number
		{
			Species.speciesarray[speciesIn].data.childRange++;
		}
		//Species.reflection = true;
// child growth direction
		if ((randomRange(100) < 20 ))
		{
			Species.speciesarray[speciesIn].data.childXdir = randomRange(3) - 1;
			Species.speciesarray[speciesIn].data.childYdir = randomRange(3) - 1;
			//if (((Species.speciesarray[speciesIn].data.childXdir == 0) || (Species.speciesarray[speciesIn].data.childYdir == 0)) && !((Species.speciesarray[speciesIn].data.childXdir == 0) && (Species.speciesarray[speciesIn].data.childYdir == 0)))
			//{
			//	Species.speciesarray[speciesIn].data.childXdir = randomRange(3) - 1;
			//}
			if ((Species.speciesarray[speciesIn].data.childXdir == 0) && (Species.speciesarray[speciesIn].data.childYdir == 0)) 
			{
				Species.speciesarray[speciesIn].data.childXdir = randomRange(3) - 1;
				Species.speciesarray[speciesIn].data.childYdir = randomRange(3) - 1;
			}
		}
		else
		{
			Species.speciesarray[speciesIn].data.childXdir = 0;
			Species.speciesarray[speciesIn].data.childYdir = 0;
		}
// base color,  rainbow, mutation
		//Species.
		if (Species.rainBowLocked)
		{
			Species.speciesarray[speciesIn].data.RainbowOn = true;
		}
		else
		{
			Species.speciesarray[speciesIn].data.RainbowOn = (randomRange(100) < 10);
		}
		Species.speciesarray[speciesIn].rainbow->rbCycleCount = 1;
		Species.speciesarray[speciesIn].rainbow->rbCount = 0;
		Species.speciesarray[speciesIn].data.showBaseColor = ((Species.baseColorLocked) || (randomRange(100) < 5));
		Species.speciesarray[speciesIn].data.baseColorRed = randomRange(256);
		Species.speciesarray[speciesIn].data.baseColorGreen = randomRange(256);
		Species.speciesarray[speciesIn].data.baseColorBlue = randomRange(256);
		int zzz = Species.speciesarray[speciesIn].data.baseColorRed + Species.speciesarray[speciesIn].data.baseColorGreen + Species.speciesarray[speciesIn].data.baseColorBlue;
		if ((zzz > 650) || (zzz < 118))
		{
			Species.speciesarray[speciesIn].data.baseColorRed = randomRange(256);
			Species.speciesarray[speciesIn].data.baseColorGreen = randomRange(256);
			Species.speciesarray[speciesIn].data.baseColorBlue = randomRange(256);
		}
		if (randomRange(100) < 80)
		{
			Species.speciesarray[speciesIn].data.mutationPcnt = randomRange(50);
		}
		else
		{
			Species.speciesarray[speciesIn].data.mutationPcnt = randomRange(100);
		}
		;
		Species.speciesarray[speciesIn].data.mutationFocusPcnt = randomRange(100);
		if (speciesIn == 0)
		{
			Species.speciesarray[0].rainbow->rbCycleCount = 1;
			Species.speciesarray[0].rainbow->rbGrowthAmount = randomRange(20);
			if (DUPESPECIES)
			{
				for (int i = 1; i <= Species.numspecies; i++)
				{
					Species.speciesarray[i].ChangeSpecies = TRUE;

				}
				//std::cout << std::endl << "Dupe Species: ID " << speciesIn << " mutation " << Species.speciesarray[speciesIn].data.mutationPcnt << "  t2m  " << Species.speciesarray[speciesIn].data.timeTillMutate << " range " << Species.speciesarray[speciesIn].data.Range << " colR " << (Species.speciesarray[speciesIn].data.overPop / Species.speciesarray[speciesIn].data.Range) << " maxCol " << Species.speciesarray[speciesIn].data.overPop << " maxNuma  " << Species.speciesarray[speciesIn].data.maxNumaround << " gblNum " << GBLNUMAROUND << " gblCol " << GBLCOLORFOBIA;// << std::endl;
			}
			//if (randomRange(100) < 101) //70)
			//{
			//	if (randomRange(100) < -1) //10)
			//	{
			//		GBLCOLORFOBIA = (randomRange(100) > 50);
			//		GBLNUMAROUND = (randomRange(100) > 50);
			//	}
			//	else
			//	{
			//		GBLCOLORFOBIA = FALSE;
			//		GBLNUMAROUND = FALSE;
			//	}
			//}
			//else
			//{
			//	GBLCOLORFOBIA = TRUE;
			//	GBLNUMAROUND = TRUE;
			//}
			//for (int i = 1; i < NUMSPECIES; i++)
			//{
			//	if (GBLCOLORFOBIA && GBLNUMAROUND) Species.speciesarray[i].data.Range = Species.speciesarray[0].data.Range;
			//	if (GBLCOLORFOBIA)
			//	{
			//		Species.speciesarray[i].data.overPop = Species.speciesarray[0].data.overPop;
			//	}
			//	if (GBLNUMAROUND)
			//	{
			//		Species.speciesarray[i].data.maxNumaround = Species.speciesarray[0].data.maxNumaround;
			//	}
			//}
		}
		else
		{
			Species.speciesarray[speciesIn].rainbow->rbCycleCount = 1;
			Species.speciesarray[speciesIn].rainbow->rbGrowthAmount = randomRange(20);
		//	if (GBLCOLORFOBIA && GBLNUMAROUND)
		//		Species.speciesarray[speciesIn].data.Range = Species.speciesarray[0].data.Range;
		//	if (GBLCOLORFOBIA)
		//		Species.speciesarray[speciesIn].data.overPop = Species.speciesarray[0].data.overPop;
		//	if (GBLNUMAROUND)
		//		Species.speciesarray[speciesIn].data.maxNumaround = Species.speciesarray[0].data.maxNumaround;
		}

		//std::cout << std::endl << "ID " << Species.speciesarray[speciesIn].SpeciesId << " t2mutate  " << Species.speciesarray[speciesIn].timeTillMutate << " range " << Species.speciesarray[speciesIn].Range << " maxCol " << Species.speciesarray[speciesIn].overPop << " maxNuma  " << Species.speciesarray[speciesIn].maxNumaround << " gblNum " << GBLNUMAROUND << " gblCol " << GBLCOLORFOBIA << std::endl;
		std::cout << "ID " << Species.speciesarray[speciesIn].SpeciesId << "new species created" << std::endl;
	}

	if (false) //((randomRange(100) < 20) && (!ActivateImgSpecNum)) // || (Species.numspecies == 1) || DUPESPECIES) // kill them all
	{
		Species.speciesarray[speciesIn].lifelist->goFirst();
		CELLLOC aLoc;
		int xyx = Species.speciesarray[speciesIn].lifelist->activeLifeCount;
		while (Species.speciesarray[speciesIn].lifelist->start != NULL)
		{
			aLoc = Species.speciesarray[speciesIn].lifelist->currPos->CellLoc;
			x = aLoc.xLoc;
			y = aLoc.yLoc;
			if (!Species.speciesarray[speciesIn].data.BlackDeath)
			{
				plane.pData[x][y].Col = plane.pData[x][y].avgColor;
				plane.gblPlanePtr->showCol(aLoc, speciesIn);
			}
			else
			{
				{
					plane.pData[x][y].Col.r = 0;
					plane.pData[x][y].Col.g = 0;
					plane.pData[x][y].Col.b = 0;
					plane.pData[x][y].Col.a = 1;
					plane.gblPlanePtr->showCol(aLoc, speciesIn);
				}
			}
			plane.pData[x][y].Age = 0;
			plane.pData[x][y].AgeDecade = 1;
			plane.pData[x][y].Alive = FALSE;
			if (plane.shape == SPHERE) plane.sphere->sShowHeight(aLoc, speciesIn); else
			{
				plane.gblPlanePtr->pshowHeight(aLoc, Species.speciesarray[speciesIn].data.decadeHeightShow, speciesIn);
			}
			Species.speciesarray[speciesIn].lifelist->delCurrent(speciesIn);
		}
	}


	//if (speciesIn == 0)std::cout << "********************************************************************************* " << GBLCOLORFOBIA << std::endl;
	/*else std::cout << std::endl;*/
	//if ((randomRange(100) < 50) && (Species.speciesarray[speciesIn].lifelist->activeLifeCount > 20) && SPHEREALOWED && (speciesIn == 0))
	//{
	//	if ((plane.shape == PLANE) && (randomRange(100) < 20))
	//	{
	//		plane.shapeNext = SPHERE;
	//		plane.changeshape = TRUE;
	//		plane.rotatex = randomRange(3) - 1;
	//		plane.rotatey = randomRange(3) - 1;
	//	}
	//	else
	//	{
	//		plane.shapeNext = PLANE;
	//		plane.changeshape = TRUE;
	//		plane.rotatex = 0;
	//		plane.rotatey = 0;
	//	}
	//ChageShape();
	//}
	if (randomRange(100) < 20)
	{
		if ((plane.shape == PLANE))
		{
			//		KeyboardGL('r', 1, 1);
			plane.rotatex = 0;
			plane.rotatey = 0;
		}
		else
		{
			plane.rotatex = 0; // randomRange(3) - 1;
			plane.rotatey = 1; // randomRange(3) - 1;
		}
	}
	if (plane.shape == SPHERE)
	{
		Species.speciesarray[speciesIn].data.heightgrowth = (float)1.00f / (float)Species.speciesarray[speciesIn].data.death;
	}
	else
	{
		Species.speciesarray[speciesIn].data.heightgrowth = 0;
	}
	
	//Species.speciesarray[speciesIn].rainbow->rbCycleCount = 1;
	//std::cout << std::endl << "ID " << Species.speciesarray[speciesIn].SpeciesId <<  " time till mutate  " << Species.speciesarray[speciesIn].timeTillMutate << " overPop " << Species.speciesarray[speciesIn].overPop << " maxNumaround  " << Species.speciesarray[speciesIn].maxNumaround << " num threre " << Species.speciesarray[speciesIn].lifelist->activeLifeCount << std::endl;
	std::cout << std::endl << "ID " << Species.speciesarray[speciesIn].SpeciesId << " age " << Species.speciesarray[speciesIn].data.death <<" timeTillMutate " << Species.speciesarray[speciesIn].data.timeTillMutate << "Range " << Species.speciesarray[speciesIn].data.Range << " overPop " << Species.speciesarray[speciesIn].data.overPop << " maxNumaround  " << Species.speciesarray[speciesIn].data.maxNumaround << std::endl;
	//std::cout << "Species Chng " << Species.speciesarray[speciesIn].SpeciesId << " TTFM " << Species.speciesarray[speciesIn].timeToFindMate << " MxNumAround  " << Species.speciesarray[speciesIn].maxNumaround << " colofobic" << Species.speciesarray[speciesIn].overPop <<" time since last change: " << plane.lastShapeChange << std::endl;
	//std::cout << "ID" << Species.speciesarray[speciesIn].Id << "op " << Species.speciesarray[speciesIn].overPop << " R " << Species.speciesarray[speciesIn].Range << " MR " << Species.speciesarray[speciesIn].mateRange << " CR " << Species.speciesarray[speciesIn].childRange << " MP " << Species.speciesarray[speciesIn].mutationPcnt << " D " << Species.speciesarray[speciesIn].death << 
	//	" FE " << Species.speciesarray[speciesIn].fend << " FS " << Species.speciesarray[speciesIn].fstart << " NMF " << Species.speciesarray[speciesIn].maxNumMateFails << 
	//	" NMS " << Species.speciesarray[speciesIn].numMateFailSleeps << " RfO " << Species.speciesarray[speciesIn].reflecton 
	//	<< " RbO " << Species.speciesarray[speciesIn].RainbowOn << " CX " << Species.speciesarray[speciesIn].childXdir << " CY " << Species.speciesarray[speciesIn].childYdir << std::endl;
	//std::cout << " NMFails "  << Species.speciesarray[speciesIn].maxNumMateFails << " NMSeeps " << Species.speciesarray[speciesIn].numMateFailSleeps << std::endl;
	//std::cout <<   "ID " << Species.speciesarray[speciesIn].SpeciesId << " currTime " << (currTime + 1) << "Time till mutate " << Species.speciesarray[speciesIn].timeTillMutate  << std::endl;
	//std::cout << "ID " << Species.speciesarray[speciesIn].SpeciesId << " Cxdir " << Species.speciesarray[speciesIn].childXdir << " Cydir " << Species.speciesarray[speciesIn].childYdir << " childRange " << Species.speciesarray[speciesIn].childRange << std::endl;
	//const char* SPECIESSUBnames[] = { "ALL", "MUATAIONTIMING", "SEED", "AGE", "FERTILITY", "HEIGHT", "COLORFOBIA", "NUMAROUND", "MATE", "CHILD", "BASE", "SPECIESSUBcount" };
	//if (all)
	//	std::cout << " AAAAAAAAAAAAAAAALLLLLLLLLLLLLLL" << std::endl;
	//else 
	//std::cout << "ID " << Species.speciesarray[speciesIn].SpeciesId << " OFF " << " change type " << SPECIESSUBnames[changeType] << " change num " << changeType << std::endl;
	//std::cout << "ID " << Species.speciesarray[speciesIn].SpeciesId << " new species " << std::endl;
}