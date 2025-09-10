#ifndef SPHERE_H
#define SPHERE_H
// prevent multiple inclusions of header file

// names for  spherical coordinates: theta θ is latitude(col or x)  
//                                   phi ϕ is longitude(row or y).
//									 r for radius

//#include "main.h"

class Plane;



typedef struct SLOCSTRUCT 
{
//	Cell *cell;
//	CELLTYPE Type;
//	int cellDisplayPos;
	float r;
	float theta;
	float phi;
	float cosTheta;
	float cosPhi;
	float sinTheta;
	float sinPhi;
	float trueX;
	float trueY;
	float trueZ;
} SLOCSTRUCT;

class Sphere
{
private:
	
 // an array of vetrexes that will be loaded into openGL

public:
	int initialR = 0;
	int rotationx = 0;
	int rotationy = 0;
	vector<vector< SLOCSTRUCT> > sData;
int multiplier = 0;
int latitudePoints; 
int longitudePoints;
int numIDX = 0;


Sphere(int latPtsInit, int longPtsInit, int initialRin) 
{
	const float pi = (float)3.14159265; // For portability across platforms	
	int x,y;  // these are locations in x/y grid
		latitudePoints = latPtsInit; //x
		longitudePoints = longPtsInit; // y
		//EdgeConnect = true;
		//numVerts = latitudePoints*longitudePoints; //total num verts// example We're making a grid, by 10 so 100 verts and 100 squares
		//numIdx = (latitudePoints + 1)*(longitudePoints + 1) * 2 * 3; //3 points per triang;le, 2 Triangles per square and 100 squares so 600 indexes
		//index.resize(numIdx);
		//verts.resize(numVerts);
		initialR = initialRin;
		// fill out array to build empty sphere vector
		sData.resize(latitudePoints);
		for (int i = 0; i < latitudePoints; ++i) sData[i].resize(longitudePoints);
		// load initial data all DEAD
		//// remember http://www.math.uri.edu/~bkaskosz/flashmo/sphcoords/ to add a of formula and mabe even a random
		for(x=0; x<latitudePoints; ++x)
		{
			for (y = 0; y<longitudePoints; ++y)
			{	
				sData[x][y].phi = ((float)y / (float)longitudePoints) * pi; // radians 0 to PI
				sData[x][y].theta = ((float)x / (float)latitudePoints) * pi * 2; // radians 0 to PI * 2
				sData[x][y].r = (float)initialR;
				sData[x][y].sinTheta = sin(sData[x][y].theta);
				sData[x][y].cosTheta = cos(sData[x][y].theta);
				sData[x][y].sinPhi = sin(sData[x][y].phi);
				sData[x][y].cosPhi = cos(sData[x][y].phi);
				sData[x][y].trueX = sData[x][y].r*sData[x][y].sinPhi*sData[x][y].cosTheta;
				sData[x][y].trueY = sData[x][y].r*sData[x][y].sinPhi*sData[x][y].sinTheta;
				sData[x][y].trueZ = sData[x][y].r*sData[x][y].cosPhi;
			}
		}
	};
void sShowHeight(CELLLOC locIn,  int currspecies);

};

#endif