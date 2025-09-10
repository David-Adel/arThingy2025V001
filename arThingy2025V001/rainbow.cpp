#include "main.h"



void Rainbow::SetStart(int rIn, int gIn, int bIn, int stageIn)
{
	data.r = rIn;
	data.g = gIn;
	data.b = bIn;
	data.stage = stageIn;
}


//void Rainbow::NextRC()
//{
//	if (rbCycleCount >= rbCycleMax )
//	{
//		//if (data.stage == 0 ) {	data.stage = 1; data.r=255; data.g=0;data.b=0; }
//		NextColor();
//		rbCycleCount = 1;
//		if (rbGrow) 
//		{	rbCycleMax = rbCycleMax + rbGrowthAmount;
//			if (rbCycleMax > rbGrowthMax)
//			{	rbCycleMax=rbGrowthInitVal;}
//		}
//	}
//	else { rbCycleCount++;}	
//};
void Rainbow::NextColor()
{	// if (DEBUGON) { 	*debugFile <<"Rainbow::NextColor(RAINBOW &data)"; cin >> ch ;} 
	if (data.stage == 0 ) { data.stage = 1; data.r=255; data.g=0;data.b=0; }
	//bool nextColor = true;
	rbCount++;
	rbCycleCount = Species.speciesarray[speciesNum].lifelist->activeLifeCount/100;
	if (rbCount >= rbCycleCount)
	{
		rbCount = 0;
		//Species.speciesarray[speciesNum].
		//Species.speciesarray[speciesNum].lifelist->activeLifeCount
		//if (rbCycleCount > 200) rbCycleCount = 1; else rbCycleCount++;
		switch (data.stage)
		{

		case 1: ////Start with Red and ramp up Green. stage 1
			data.g++;
			if (data.g >= 255) { data.stage = 2; }
			break;
		case 2: ////When Green is max, ramp down red to zero. stage 2
			data.r--;
			if (data.r <= 0) { data.stage = 3; }
			break;
		case 3: ////When red is zero, ramp up blue. stage 3
			data.b++;
			if (data.b >= 255) { data.stage = 4; }
			break;
		case 4: //////When blue is max, ramp down green to zero. stage 4
			data.g--;
			if (data.g <= 0) { data.stage = 5; }
			break;
		case 5: //When green is zero, ramp up red. stage 5
			data.r++;
			if (data.r >= 255) { data.stage = 6; }
			break;
		case 6: ///When red is is max, ramp down blue to zero. stage 6	
			data.b--;
			if (data.b <= 0) 
			{
				data.stage = 1; rbCycleCount = rbCycleCount + rbGrowthAmount;
			}//take us back to the start
			break;
		}
	}
}
// all greater than
bool wayToSortrgb(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.b > j.b)
		return true;
	else
		return false;

}
bool wayToSortrbg(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.g > j.g)
		return true;
	else
		return false;

}
bool wayToSortgrb(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.b > j.b)
		return true;
	else
		return false;

}
bool wayToSortgbr(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.r > j.r)
		return true;
	else
		return false;

}
bool wayToSortbrg(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.g > j.g)
		return true;
	else
		return false;

}
bool wayToSortbgr(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.r > j.r)
		return true;
	else
		return false;

}
// second inverted now less than true
bool wayToSortrgb2i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.b > j.b)
		return true;
	else
		return false;

}
bool wayToSortrbg2i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.g > j.g)
		return true;
	else
		return false;

}
bool wayToSortgrb2i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.b > j.b)
		return true;
	else
		return false;

}
bool wayToSortgbr2i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.r > j.r)
		return true;
	else
		return false;

}
bool wayToSortbrg2i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.g > j.g)
		return true;
	else
		return false;

}
bool wayToSortbgr2i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.r > j.r)
		return true;
	else
		return false;

}
// Third inverted now less than true
bool wayToSortrgb3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.b < j.b)
		return true;
	else
		return false;

}
bool wayToSortrbg3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.g < j.g)
		return true;
	else
		return false;

}
bool wayToSortgrb3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.b < j.b)
		return true;
	else
		return false;

}
bool wayToSortgbr3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.r < j.r)
		return true;
	else
		return false;

}
bool wayToSortbrg3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.g < j.g)
		return true;
	else
		return false;

}
bool wayToSortbgr3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.r < j.r)
		return true;
	else
		return false;

}
// second and Third inverted now less than true
bool wayToSortrgb2N3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.b < j.b)
		return true;
	else
		return false;

}
bool wayToSortrbg2N3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.g < j.g)
		return true;
	else
		return false;

}
bool wayToSortgrb2N3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.b < j.b)
		return true;
	else
		return false;

}
bool wayToSortgbr2N3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.r < j.r)
		return true;
	else
		return false;

}
bool wayToSortbrg2N3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.g < j.g)
		return true;
	else
		return false;

}
bool wayToSortbgr2N3i(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.r < j.r)
		return true;
	else
		return false;

}
// FIRST inverted
bool wayToSortrgbii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.b > j.b)
		return true;
	else
		return false;

}
bool wayToSortrbgii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.g > j.g)
		return true;
	else
		return false;

}
bool wayToSortgrbii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.b > j.b)
		return true;
	else
		return false;

}
bool wayToSortgbrii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.r > j.r)
		return true;
	else
		return false;

}
bool wayToSortbrgii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.g > j.g)
		return true;
	else
		return false;

}
bool wayToSortbgrii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.r > j.r)
		return true;
	else
		return false;

}
// second inverted now less than true
bool wayToSortrgb2iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.b > j.b)
		return true;
	else
		return false;

}
bool wayToSortrbg2iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.g > j.g)
		return true;
	else
		return false;

}
bool wayToSortgrb2iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.b > j.b)
		return true;
	else
		return false;

}
bool wayToSortgbr2iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.r > j.r)
		return true;
	else
		return false;

}
bool wayToSortbrg2iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.g > j.g)
		return true;
	else
		return false;

}
bool wayToSortbgr2iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.r > j.r)
		return true;
	else
		return false;

}
// Third inverted now less than true
bool wayToSortrgb3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.b < j.b)
		return true;
	else
		return false;

}
bool wayToSortrbg3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.g < j.g)
		return true;
	else
		return false;

}
bool wayToSortgrb3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.b < j.b)
		return true;
	else
		return false;

}
bool wayToSortgbr3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.b > j.b)
		return true;
	else
		if (i.b < j.b)
			return false;
	if (i.r < j.r)
		return true;
	else
		return false;

}
bool wayToSortbrg3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.r > j.r)
		return true;
	else
		if (i.r < j.r)
			return false;
	if (i.g < j.g)
		return true;
	else
		return false;

}
bool wayToSortbgr3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.g > j.g)
		return true;
	else
		if (i.g < j.g)
			return false;
	if (i.r < j.r)
		return true;
	else
		return false;

}
// second and Third inverted now less than true
bool wayToSortrgb2N3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.b < j.b)
		return true;
	else
		return false;

}
bool wayToSortrbg2N3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.g < j.g)
		return true;
	else
		return false;

}
bool wayToSortgrb2N3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.b < j.b)
		return true;
	else
		return false;

}
bool wayToSortgbr2N3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.r < j.r)
		return true;
	else
		return false;

}
bool wayToSortbrg2N3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.r < j.r)
		return true;
	else
		if (i.r > j.r)
			return false;
	if (i.g < j.g)
		return true;
	else
		return false;

}
bool wayToSortbgr2N3iii(SORTCOLOR i, SORTCOLOR j)
{
	if (i.b < j.b)
		return true;
	else
		if (i.b > j.b)
			return false;
	if (i.g < j.g)
		return true;
	else
		if (i.g > j.g)
			return false;
	if (i.r < j.r)
		return true;
	else
		return false;

}

bool wayToSortBW(SORTCOLOR i, SORTCOLOR j)
{
	if ((i.b + i.r + i.g) < (j.r +j.b + j.g))
		return true;
	else
		return false;
}

bool wayToSortWB(SORTCOLOR i, SORTCOLOR j)
{
	if ((i.b + i.r + i.g) > (j.r + j.b + j.g))
		return true;
	else
		return false;
}


void  Rainbow::SetSpecies(ImageToDisplay* imageIn) //, bool specieslockon)
{
	int x = 0; int y = 0;
	int r = 0; int g = 0; int b = 0;
	int br = 0; int bg = 0; int bb = 0;
	int num0 = 0; int num1 = 0; int num2 = 0; int num3 = 0; int num4 = 0; int num5 = 0; int num6 = 0; int num7 = 0;
	int species = -1;
	//int speciesFound = 0;
	CELLLOC Cin;
	//Rainbow* rbTest;
	//rbTest = new Rainbow;

	vector<SORTCOLOR> sortarray;
	sortarray.resize(NUMCOL*NUMROW);
	//SortColor sortarray[NUMCOL*NUMROW];
	// Sorting the int vector
	//sort(sortarray.begin(), sortarray.end(), wayToSort);
	//int i = 0;
	//int j = 0;
	if (imageIn->image1Current)
	{
		for (int i = 0; i < NUMCOL; i++)
		{
			for (int j = 0; j < NUMROW; j++)
			{
				sortarray[(i*NUMCOL + j)].r = imageIn->displayImage1[i][j].colour.r;
				sortarray[(i*NUMCOL + j)].g = imageIn->displayImage1[i][j].colour.g;
				sortarray[(i*NUMCOL + j)].b = imageIn->displayImage1[i][j].colour.b;
				sortarray[(i*NUMCOL + j)].x = i;
				sortarray[(i*NUMCOL + j)].y = j;
				//std::cout << "i " << i << " j " << j << std::endl;
			}
		}
	}
	else
	{
		for (int i = 0; i < NUMCOL; i++)
		{
			for (int j = 0; j < NUMROW; j++)
			{
				sortarray[(i*NUMCOL + j)].r = imageIn->displayImage2[i][j].colour.r;
				sortarray[(i*NUMCOL + j)].g = imageIn->displayImage2[i][j].colour.g;
				sortarray[(i*NUMCOL + j)].b = imageIn->displayImage2[i][j].colour.b;
				sortarray[(i*NUMCOL + j)].x = i;
				sortarray[(i*NUMCOL + j)].y = j;
				//std::cout << "i " << i << " j " << j << std::endl;
			}
		}
	}
	int sortver = 0;


	sortver = rand() % 50;

	//if ((rand() % 100) < 50) sortver = 48; else sortver = 49;

	std::cout << " sortver  " << sortver << std::endl;


	switch (sortver)
	{
		// all greater than
	case 0:
		sort(sortarray.begin(), sortarray.end(), wayToSortrgb);
		break;
	case 1:
		sort(sortarray.begin(), sortarray.end(), wayToSortrbg);
		break;
	case 2:
		sort(sortarray.begin(), sortarray.end(), wayToSortbgr);
		break;
	case 3:
		sort(sortarray.begin(), sortarray.end(), wayToSortbrg);
		break;
	case 4:
		sort(sortarray.begin(), sortarray.end(), wayToSortgbr);
		break;
	case 5:
		sort(sortarray.begin(), sortarray.end(), wayToSortgrb);
		break;

		// second inverted less than
	case 6:
		sort(sortarray.begin(), sortarray.end(), wayToSortrgb2i);
		break;
	case 7:
		sort(sortarray.begin(), sortarray.end(), wayToSortrbg2i);
		break;
	case 8:
		sort(sortarray.begin(), sortarray.end(), wayToSortbgr2i);
		break;
	case 9:
		sort(sortarray.begin(), sortarray.end(), wayToSortbrg2i);
		break;
	case 10:
		sort(sortarray.begin(), sortarray.end(), wayToSortgbr2i);
		break;
	case 11:
		sort(sortarray.begin(), sortarray.end(), wayToSortgrb2i);
		break;
		// third inverted less than
	case 12:
		sort(sortarray.begin(), sortarray.end(), wayToSortrgb3i);
		break;
	case 13:
		sort(sortarray.begin(), sortarray.end(), wayToSortrbg3i);
		break;
	case 14:
		sort(sortarray.begin(), sortarray.end(), wayToSortbgr3i);
		break;
	case 15:
		sort(sortarray.begin(), sortarray.end(), wayToSortbrg3i);
		break;
	case 16:
		sort(sortarray.begin(), sortarray.end(), wayToSortgbr3i);
		break;
	case 17:
		sort(sortarray.begin(), sortarray.end(), wayToSortgrb3i);
		break;
		// second and third inverted less than
	case 18:
		sort(sortarray.begin(), sortarray.end(), wayToSortrgb2N3i);
		break;
	case 19:
		sort(sortarray.begin(), sortarray.end(), wayToSortrbg2N3i);
		break;
	case 20:
		sort(sortarray.begin(), sortarray.end(), wayToSortbgr2N3i);
		break;
	case 21:
		sort(sortarray.begin(), sortarray.end(), wayToSortbrg2N3i);
		break;
	case 22:
		sort(sortarray.begin(), sortarray.end(), wayToSortgbr2N3i);
		break;
	case 23:
		sort(sortarray.begin(), sortarray.end(), wayToSortgrb2N3i);
		break;

		// all greater than
	case 24:
		sort(sortarray.begin(), sortarray.end(), wayToSortrgbii);
		break;
	case 25:
		sort(sortarray.begin(), sortarray.end(), wayToSortrbgii);
		break;
	case 26:
		sort(sortarray.begin(), sortarray.end(), wayToSortbgrii);
		break;
	case 27:
		sort(sortarray.begin(), sortarray.end(), wayToSortbrgii);
		break;
	case 28:
		sort(sortarray.begin(), sortarray.end(), wayToSortgbrii);
		break;
	case 29:
		sort(sortarray.begin(), sortarray.end(), wayToSortgrbii);
		break;

		// second inverted less than
	case 30:
		sort(sortarray.begin(), sortarray.end(), wayToSortrgb2iii);
		break;
	case 31:
		sort(sortarray.begin(), sortarray.end(), wayToSortrbg2iii);
		break;
	case 32:
		sort(sortarray.begin(), sortarray.end(), wayToSortbgr2iii);
		break;
	case 33:
		sort(sortarray.begin(), sortarray.end(), wayToSortbrg2iii);
		break;
	case 34:
		sort(sortarray.begin(), sortarray.end(), wayToSortgbr2iii);
		break;
	case 35:
		sort(sortarray.begin(), sortarray.end(), wayToSortgrb2iii);
		break;
		// third inverted less than
	case 36:
		sort(sortarray.begin(), sortarray.end(), wayToSortrgb3iii);
		break;
	case 37:
		sort(sortarray.begin(), sortarray.end(), wayToSortrbg3iii);
		break;
	case 38:
		sort(sortarray.begin(), sortarray.end(), wayToSortbgr3iii);
		break;
	case 39:
		sort(sortarray.begin(), sortarray.end(), wayToSortbrg3iii);
		break;
	case 40:
		sort(sortarray.begin(), sortarray.end(), wayToSortgbr3iii);
		break;
	case 41:
		sort(sortarray.begin(), sortarray.end(), wayToSortgrb3iii);
		break;
		// second and third inverted less than
	case 42:
		sort(sortarray.begin(), sortarray.end(), wayToSortrgb2N3iii);
		break;
	case 43:
		sort(sortarray.begin(), sortarray.end(), wayToSortrbg2N3iii);
		break;
	case 44:
		sort(sortarray.begin(), sortarray.end(), wayToSortbgr2N3iii);
		break;
	case 45:
		sort(sortarray.begin(), sortarray.end(), wayToSortbrg2N3iii);
		break;
	case 46:
		sort(sortarray.begin(), sortarray.end(), wayToSortgbr2N3iii);
		break;
	case 47: 
		sort(sortarray.begin(), sortarray.end(), wayToSortgrb2N3i);
		break;

	case 48:
		sort(sortarray.begin(), sortarray.end(), wayToSortBW);
		break;

	case 49:
		sort(sortarray.begin(), sortarray.end(), wayToSortWB);
		break;



	default:
		std::cout << " bad bad bad  sortver " << sortver << std::endl;
		break;

		Sleep(500);
	}


	//printf("\n Starting pause random before cleanout \n");
	for (int i = 0; i < Species.numspecies; i++)
	{
		while (!Species.speciesarray[i].spLockedPaused)  ///waituntil  all species unlocked
		{
			std::cout << "spLockPaused false " << i << std::endl;
			Sleep(100);
		}
		Species.speciesarray[i].lifelist->goFirst();
		CELLLOC aLoc;
		while (Species.speciesarray[i].lifelist->start != NULL) // kill all memebers of species
		{
			//Species.speciesarray[speciesIn].lifelist->delCurrent(speciesIn);
			aLoc = Species.speciesarray[i].lifelist->currPos->CellLoc;
			x = aLoc.xLoc;
			y = aLoc.yLoc;
			if (!Species.speciesarray[i].data.BlackDeath)
			{
				plane.pData[x][y].Col = plane.pData[x][y].avgColor;
				plane.gblPlanePtr->showCol(aLoc, i);
			}
			else
			{
				plane.pData[x][y].Col.r = 0;
				plane.pData[x][y].Col.g = 0;
				plane.pData[x][y].Col.b = 0;
				plane.pData[x][y].Col.a = 1;
				plane.gblPlanePtr->showCol(aLoc, i);
			}
			plane.pData[x][y].Age = 0;
			plane.pData[x][y].AgeDecade = 1;
			plane.pData[x][y].Alive = FALSE;
			if (plane.shape == SPHERE) plane.sphere->sShowHeight(aLoc, i);
			else
			{
				plane.gblPlanePtr->pshowHeight(aLoc, Species.speciesarray[i].data.decadeHeightShow, i);
			}
			Species.speciesarray[i].lifelist->delCurrent(i);
		}
	}

	//COLORSTRUCT baseColorArray[NUMSPECIES];
	//for (int i = 0; i < NUMSPECIES; i++)
	//{
	//	baseColorArray[i].r = rand() % 256;
	//	baseColorArray[i].g = rand() % 256;
	//	baseColorArray[i].b = rand() % 256;
	//	baseColorArray[i].a = 1;
	//}

	int numPerSpecies = (NUMCOL*NUMROW) / Species.numspecies;
	int midNumPerSpecies = numPerSpecies / 2;
	COLORSTRUCT midColorArray[NUMSPECIES];
	for (int k = 0; k < Species.numspecies; k++)
	{
		midColorArray[k].r = sortarray[midNumPerSpecies + k*numPerSpecies].r;
		midColorArray[k].g = sortarray[midNumPerSpecies + k*numPerSpecies].g;
		midColorArray[k].b = sortarray[midNumPerSpecies + k*numPerSpecies].b;
	}
	bool showMidColor = ((rand() % 100) < 2);
	//if (showMidColor)
	//{
	//	std::cout << " showing mid color sortver " << sortver << std::endl;
	//}
	//else
	//{
	//	std::cout << " showing random color sortver " << sortver << std::endl;
	//}

	//Species.speciesarray[species].data.baseColorRed = (rand() % 256); // randomRange(256);
	//Species.speciesarray[species].data.baseColorGreen = (rand() % 256); // randomRange(256);
	//Species.speciesarray[species].data.baseColorBlue = (rand() % 256); // randomRange(256);


	


	for (int j = 0; j < Species.numspecies; j++)
	{
		species = j;
		COLORSTRUCT randcolor;
		randcolor.a = 1;
		randcolor.r = randomRange(256);
		randcolor.g = randomRange(256);
		randcolor.b = randomRange(256);
		Species.speciesarray[species].data.baseColorRed = randcolor.r;
		Species.speciesarray[species].data.baseColorGreen = randcolor.g;
		Species.speciesarray[species].data.baseColorBlue = randcolor.b;

//		std::cout <<" species " << species <<  " Species.speciesarray[species].data.baseColorRed  " << Species.speciesarray[species].data.baseColorRed << std::endl;

		for (int i = 0; i < numPerSpecies; i++)
		{

			//if ((rand() % 100) < 101)
			//COLORSTRUCT randcolor;
			//randcolor.a = 1;
			//randcolor.r - randomRange(256);
			//randcolor.g - randomRange(256);
			//randcolor.b - randomRange(256);
			{
				Cin.xLoc = sortarray[i + j*numPerSpecies].x;
				Cin.yLoc = sortarray[i + j*numPerSpecies].y;
				Species.speciesarray[species].lifelist->addNew(Cin, species);
				plane.pData[Cin.xLoc][Cin.yLoc].Alive = TRUE;
				plane.pData[Cin.xLoc][Cin.yLoc].speciedNum = species;
				//if (ActivateImgSpecNum == true)
				//{
				//	std::cout << "ActivateImgSpecNum " << ActivateImgSpecNum  << std::endl;

				//}
				//{
				//	plane.pData[Cin.xLoc][Cin.yLoc].ImgSpecNum = species;
				//}
				plane.pData[Cin.xLoc][Cin.yLoc].Age = rand() %Species.speciesarray[species].data.death;  // 100;
				plane.pData[Cin.xLoc][Cin.yLoc].ImgSpecNum = species;
				if ((!imageIn->firstPass) && ((Species.speciesarray[species].data.showBaseColor) || (imageIn->newImage)))
				{
					if (showMidColor)
					{
						plane.pData[Cin.xLoc][Cin.yLoc].Col.r = midColorArray[species].r;
						plane.pData[Cin.xLoc][Cin.yLoc].Col.g = midColorArray[species].g;
						plane.pData[Cin.xLoc][Cin.yLoc].Col.b = midColorArray[species].b;
					}
					else
					{
						plane.pData[Cin.xLoc][Cin.yLoc].Col.r = Species.speciesarray[species].data.baseColorRed;
						plane.pData[Cin.xLoc][Cin.yLoc].Col.g = Species.speciesarray[species].data.baseColorGreen;
						plane.pData[Cin.xLoc][Cin.yLoc].Col.b = Species.speciesarray[species].data.baseColorBlue;
					}
				}
				else
				{
					plane.pData[Cin.xLoc][Cin.yLoc].Col.r = sortarray[i + j*numPerSpecies].r;
					plane.pData[Cin.xLoc][Cin.yLoc].Col.g = sortarray[i + j*numPerSpecies].g;
					plane.pData[Cin.xLoc][Cin.yLoc].Col.b = sortarray[i + j*numPerSpecies].b;
				}
				plane.pData[Cin.xLoc][Cin.yLoc].avgColor = plane.pData[Cin.xLoc][Cin.yLoc].Col;
				plane.gblPlanePtr->showCol(Cin, species);
			}
		}
	}
	//imageIn->newImage = false;
}
	//if (false)
	//{
	//	int tst = 0;
	//	for (size_t i = 0; i < NUMROW; i++)
	//	{
	//		Cin.xLoc = i;
	//		for (size_t j = 0; j < NUMCOL; j++)
	//		{
	//			Cin.yLoc = j;
	//			if (imageIn->image1Current)
	//			{
	//				r = imageIn->displayImage1[i][j].colour.r;
	//				g = imageIn->displayImage1[i][j].colour.g;
	//				b = imageIn->displayImage1[i][j].colour.b;
	//			}
	//			else
	//			{
	//				r = imageIn->displayImage2[i][j].colour.r;
	//				g = imageIn->displayImage2[i][j].colour.g;
	//				b = imageIn->displayImage2[i][j].colour.b;
	//			}
	//			if ((r < 127.5) && (b > 127.5) && (g > 127.5))
	//			{
	//				species = 0;
	//				num0++;
	//				br = (rand() % 127) - 63;
	//				bg = (rand() % 127) + 127;
	//				bg = (rand() % 127) + 127;
	//			}
	//			else
	//				if ((r < 127.5) && (b < 127.5) && (g < 127.5))
	//				{
	//					species = 1;
	//					num1++;
	//					br = (rand() % 127) - 63;
	//					bg = (rand() % 127) - 63;
	//					bg = (rand() % 127) - 63;
	//				}
	//				else
	//					if ((r < 127.5) && (b < 127.5) && (g > 127.5))
	//					{
	//						species = 2;
	//						num2++;
	//						br = (rand() % 127);
	//						bg = (rand() % 127);
	//						bg = (rand() % 127) + 127;
	//					}
	//					else
	//						if ((r < 127.5) && (b > 127.5) && (g < 127.5))
	//						{
	//							species = 3;
	//							num3++;
	//							br = (rand() % 127);
	//							bg = (rand() % 127) + 127;
	//							bg = (rand() % 127);
	//						}
	//						else
	//							if ((r > 127.5) && (b > 127.5) && (g > 127.5))
	//							{
	//								species = 4;
	//								num4++;
	//								br = (rand() % 127) + 127;
	//								bg = (rand() % 127) + 127;
	//								bg = (rand() % 127) + 127;
	//							}
	//							else
	//								if ((r > 127.5) && (b < 127.5) && (g < 127.5))
	//								{
	//									species = 5;
	//									num5++;
	//									br = (rand() % 127) + 127;
	//									bg = (rand() % 127);
	//									bg = (rand() % 127);
	//								}
	//								else
	//									if ((r > 127.5) && (b < 127.5) && (g > 127.5))
	//									{
	//										species = 6;
	//										num6++;
	//										br = (rand() % 127) + 127;
	//										bg = (rand() % 127);
	//										bg = (rand() % 127) + 127;
	//									}
	//									else
	//										if ((r > 127.5) && (b > 127.5) && (g < 127.5))
	//										{
	//											species = 7;
	//											num7++;
	//											br = (rand() % 127) + 127;
	//											bg = (rand() % 127) + 127;
	//											bg = (rand() % 127);
	//										}
	//										else
	//										{
	//											std::cout << std::endl << "bad bad no species created " << std::endl;
	//										}
	//			if ((rand() % 100) < 30)
	//			{
	//				Species.speciesarray[species].lifelist->addNew(Cin, species);
	//				plane.pData[i][j].Alive = PLANT;
	//				plane.pData[i][j].speciedNum = species;
	//				plane.pData[i][j].Age = rand() % 50;
	//				if (Species.speciesarray[species].showBaseColor)
	//				{
	//					plane.pData[i][j].Col.r = br;
	//					plane.pData[i][j].Col.g = bg;
	//					plane.pData[i][j].Col.b = bb;
	//				}
	//				else
	//				{
	//					plane.pData[i][j].Col.r = r;
	//					plane.pData[i][j].Col.g = g;
	//					plane.pData[i][j].Col.b = b;
	//				}
	//				plane.pData[i][j].avgColor = plane.pData[i][j].Col;
	//				plane.gblPlanePtr->showCol(Cin, species);
	//			}
	//		}
	//	}
	//}
	//	std::cout  << "S0 " << num0 << " S1 " << num1 << " S2 " << num2 << " S3 " << num3 << " S4 " << num4 << " S5 " << num5 << " S5 " << num5 << " S6 " << num6 << " S7 " << num7 << std::endl;

	
