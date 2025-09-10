#ifndef PLANE_H
#define PLANE_H
#include "Main.h"

// prevent multiple inclusions of header file

class sphere;

//extern PLANEDATA plane;

class Plane
{
private:

public:
	//PLANEDATA plane;
	//float multiplier;
	//int maxTimeToMutate = 30;
	//int numRow = 0;
	//int numCol = 0;
	//int numVerts = numCol*numRow; //total num verts// example We're making a grid, by 10 so 100 verts and 100 squares
	//int numIdx = (numRow + 1)*(numCol + 1) * 2 * 3; //3 points per triang;le, 2 Triangles per square and 100 squares so 600 indexes
	//bool EdgeConnect = FALSE;
	//SHAPE shape = PLANE;
	//SHAPE shapeNext;
	////bool sphereActive = false;
	//bool changeshape = false;
	//int RowsChanged = 0;
	////bool shapeChanging = FALSE;
	//Sphere *sphere = NULL;
	//vector <Vertex> verts;
	//vector <int> index;
	//vector<vector< PLOCSTRUCT>> pData;
	//GLuint vboID; // Vertex Buffer Object ID // a GL pointer that will point at the vertex data
	//GLuint indexVBOID; // Index Buffer Object ID // a GL pointer that will point at the indeax aray
	//Vertex* ptr; //global pointer to memory in graphics card
	//GLuint vertexBuffer;
	//SpeciesList* speciesList;
	//int rotatex = 0;
	//int rotatey = 0;
	//int numPlaneIDX = 0;
	//int numSphereIDX = 0;
	//int lastShapeChange = 0;
	
	void CreateReflect(CELLLOC LOCin, int currSpecies);
	void buildGrid(int numRow, int numCol, bool EdgeConnectin);
	void initVBO(Shader *shader);
	void showCol(CELLLOC in, int currSpecies);
	void pshowHeight(CELLLOC in, bool DecageGrowth, int currSpecies);
	bool ColorAndNumAroundOK(CELLLOC in, int range, int maxNum, int maxColor);
	void clearDead();

	Plane( int numColin,int numRowin, bool EdgeConnectin) // build world aray full of initialized black cells
	{
		plane.numRow = numRowin;
		plane.numCol = numColin;
		plane.EdgeConnect = EdgeConnectin;
		plane.numVerts = plane.numCol*plane.numRow; //total num verts// example We're making a grid, by 10 so 100 verts and 100 squares
		plane.numIdx = (plane.numRow + 1)*(plane.numCol + 1) * 2 * 3; //3 points per triang;le, 2 Triangles per square and 100 squares so 600 indexes
		int x, y;
		// fill out array to build empty world vector
		//plane.verts.resize(plane.numVerts);
		//plane.index.resize(plane.numIdx);
		//plane.pData.resize(plane.numRow);
		//for (int i = 0; i <plane.numRow; ++i) plane.pData[i].resize(plane.numCol);
		// load initial data all DEAD
		for (x = 0; x<plane.numCol; ++x)
		{
			for (y = 0; y<plane.numRow; ++y)
			{
				plane.pData[x][y].Alive = FALSE;
				plane.pData[x][y].cellDisplayPos = x + (y*plane.numRow);
				plane.pData[x][y].Age = 0;
				plane.pData[x][y].AgeDecade = 0;
				plane.pData[x][y].Col.r = 0;
				plane.pData[x][y].Col.g = 0;
				plane.pData[x][y].Col.b = 0;
				plane.pData[x][y].Col.a = 1;
				plane.pData[x][y].avgColor = plane.pData[x][y].Col;
			}
		}
		buildGrid(plane.numCol, plane.numRow, plane.EdgeConnect);
		Sphere* sphere;
		sphere = new Sphere(numColin, numRowin, 6);
		plane.sphere = sphere;
		//speciesList = new SpeciesList;  // create the list of species for this grid.
	}// simple  constructor
};

#endif
