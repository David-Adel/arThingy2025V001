#ifndef RAINBOW_H
#define RAINBOW_H
#include "main.h"
#include <string>
int randomRange(int range); 
typedef struct RAINBOW {int stage, r, g, b;}RAINBOW;
typedef struct SORTCOLOR
{
	int r = 0;
	int g = 0;
	int b = 0;
	int x = 0;
	int y = 0;
}SORTCOLOR;
class ImageToDisplay;

class Rainbow
{
private:

public: 
int	rbCycleCount; // counter for cycles
//bool rbGrow = FALSE;
int rbCount = 0;
int rbGrowthAmount = 0;
int colorSelMethod = 0;
int speciesNum = 0;
//float rbGrowthInitVal = 20;
//float rbGrowthMax = 20;
//int rbCycleMax = 10;

//int randomRange(int range)
//{
//	//return (int)(((double)idist(rgen) / (double)randmax) * (double)range);
//	if (range == 0) range = 1;
//	return rand() % range;
//
//};

	RAINBOW data;
	Rainbow() ////Start with Red and ramp up Green. stage 1
	{
		int s = 0;

		
		data.stage=randomRange(6);
		s = data.stage;
		switch (s)
		{

		case 1: ////Start with Red and ramp up Green. stage 1
			data.r = 255;
			data.g = randomRange(255);
			data.b = 0;
			break;
		case 2: ////When Green is max, ramp down red to zero. stage 2
			data.r = randomRange(255);
			data.g = 255;
			data.b = 0;
			break;
		case 3: ////When red is zero, ramp up blue. stage 3
			data.r = 0;
			data.b = randomRange(255);
			data.g = 255;


			break;
		case 4: //////When blue is max, ramp down green to zero. stage 4
			data.r = 0;
			data.b = 255;
			data.g = randomRange(255);
			break;
		case 5: //When green is zero, ramp up red. stage 5
			data.r = randomRange(255);
			data.b = 255;
			data.g = 0;
			break;
		case 6: ///When red is is max, ramp down blue to zero. stage 6	
			data.r = 255;
			data.b = randomRange(255);
			data.g = 0;
			break;
		}
		
		
		
		
		data.stage = 1; data.r = 255; data.g = 0; data.b = 0;

	//rbGrowthCycleAmount = rbGrowthAmount;
		rbCycleCount = 1;
		// rbCycleCount; // counter for cycles
		// rbGrow = FALSE;
		// rbGrowthAmount = 1;
		// rbGrowthInitVal = 1;
		// rbGrowthMax = 500;
		// rbCycleMax = 10;
	};

void SetStart(int rIn, int gIn, int bIn, int stageIn);
void NextColor();
//void NextRC();
void SetSpecies(ImageToDisplay* imageIn);
};
#endif