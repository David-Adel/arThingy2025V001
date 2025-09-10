//#ifndef MAIN_H
//#define MAIN_H
//#include <string>
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//#include <filesystem>
using std::vector;
//#include <process.h>
//#include <ctime>
#include <random>
//#include <cmath>
#include <algorithm>
#include <time.h>
using std::max;
using std::min;

#include  <io.h>
#include  <stdio.h>
#include  <stdlib.h>
//#define GLEW_STATIC
#include <GL/glew.h>
#ifdef _WIN32
#include <GL/wglew.h> // For wglSwapInterval
#endif
#include <SDL_opengl.h>
#include <SDL.h>
#include <../FreeImage/Dist/x32/FreeImage.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>
#include <stdio.h>
#include <sys/stat.h>

#include <thread>

//  Avoid showing up the console window
// #pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#define PROGRAM_NAME "The Art of Self Organization 1200X1200 species 6  max age 100 random species"
//const int processor_count = std::thread::hardware_concurrency();
const int NUMCOL = 1200; //x
const int NUMROW = 1200; //y
const int NUMVERTS = NUMROW * NUMCOL;
const int NUMIDX  = (NUMROW + 1)*(NUMCOL + 1) * 2 * 3;
const int MAXSPECIES = 10;
const int NUMSPECIES = 06; // processor_count - 1;
const int MAXMUTATETIME = 120;
const int MAXTIMEIMAGELOADSP = 60;
const bool NUMAROUNDAB = true;
const bool SPHEREALOWED = true;
const int NUMSAVESPECIES = 1000;
const int MaxTimeTillImageChange = 60;
const int  MaxTimeTillBaseColorChange = 10;
const int MaxAge = 100;
const int Maxheight = 2;
const int CenterSeed = false;
static bool SingleCenterSeed = false;
static bool DUPESPECIES = false;
static bool ActivateImgSpecNum = false;
static bool RegularClear = FALSE;

static bool IMAGEACTIVE = false;
//const bool IMAGEACTIVE = true;
//static bool baseColorLocked = true;
static  bool ShowImage = false;
static bool fullscreenactive = false;
static bool gblBlackDeath = false;
static bool first10SpreciesActive = true;

// used to maintain the keys ?? and ?? to go next and prev species from currently loaded
//static bool serialNextSpecies = false;
//static int serialNextSpeciesPosition = 0;
//static int serialNextSpeciesMax = 0;
//static bool serialNextSpecitesDirectionPlus = true;


//static bool SpeciesLockSelected = false;
//static int speciesLockedToNum = 0;
//const bool SAMERANGE = TRUE;
static int clown1 = 0;
static int clown2 = 0;
static int clowntime = 0;
//// Location / Normals
#define X_POS 0
#define Y_POS 1
#define Z_POS 2
//// Texture Coordinates
//#define U_POS 0
//#define V_POS 1
//// Colors
#define R_POS 0
#define G_POS 1
#define B_POS 2
#define A_POS 3
//
//#define POSITION_ATTRIBUTE 0
//#define NORMAL_ATTRIBUTE 2
//#define DIFFUSE_ATTRIBUTE 3
//#define SPECULAR_ATTRIBUTE 4
//#define TEXCOORD0_ATTRIBUTE 8
//#define TEXCOORD1_ATTRIBUTE 9
//#define TEXCOORD2_ATTRIBUTE 10
//#define getrandom( min, max ) (SHORT)((rand() % (int)(((max) + 1) - \
//                               (min))) + (min))
#define BUFFER_OFFSET(offset) ((void*)(offset))
#define MEMBER_OFFSET(s,m) ((char*)NULL + (offsetof(s,m))
enum SHAPE { PLANE, SPHERE, SHAPETYPEcount }; // PLANE, SPHERE
//enum SPECIESTYPE { DEAD, FUNGUS, PLANT, HERBAVOR, CARNAVOR, SPECIESTYPEcount }; // DEAD, FUNGUS, PLANT, HERBAVOR, CARNAVOR, CELTYPEcount
//enum SPECIESSUB { MUATAIONTIMING, SEED, AGEnFERTILITY, HEIGHT, COLORFOBIAnNUMAROUND, NUMAROUND, MATE, CHILDDIR, CHILD, CHILDRANGE, BASE, SPECIESSUBcount };
typedef struct Vertex
{
	glm::vec3 location; // x,y,z coordinate of vertex
	glm::vec4 colour; // the color of the node in r g b a (a is the transperancy if turned on)
	//	glm::vec3 normal; // vector of the normal direction used to smothen or sharpen edges of shapes i think - currently all 0
	//	glm::vec2 tex;   // no idea yest but somthing to do with tecturs when u ise em
	//	GLubyte padding[16];// the set of data passed to open GL = think padding is correct for performance but not usre
}Vertex;
typedef struct LOCSTRUCT { int x, y, z; } LOCSTRUCT; // a location in x y z 
typedef struct COLORSTRUCT { int r, g, b, a; } COLORSTRUCT;  // basic color structure rgba

typedef struct PLOCSTRUCT
{
	// LOCSTRUCT Loc; // location of cell in 3 d world - Z is the radius in a sphere 
//	SPECIESTYPE Type;
	COLORSTRUCT Col; //color of cell
	COLORSTRUCT avgColor; /// average color calculated in numaround.
	bool Alive = false;
	int Age;       // age of cell 
	//bool surrounded = false; // no room to place child to skip for a bit.
	int numMateAtmps = 0; // the number of mating attempts is set to 0 on creating and when sourounded is changed
	int AgeDecade = 1;
	int  speciedNum = -1;
	int ImgSpecNum = -1;
	int cellDisplayPos; // display position for graphics card
} PLOCSTRUCT;
typedef	struct CELLLOC
{
	int xLoc;
	int yLoc;
}CELLLOC;
#include "sphere.h"
typedef struct PLANEDATA
{
	int maxTimeToMutate = MAXMUTATETIME;
	int numRow = NUMROW;
	int numCol = NUMCOL;
	int numVerts = numCol*numRow; //total num verts// example We're making a grid, by 10 so 100 verts and 100 squares
	int numIdx = (numRow + 1)*(numCol + 1) * 2 * 3; //3 points per triang;le, 2 Triangles per square and 100 squares so 600 indexes
	bool EdgeConnect = FALSE;
	SHAPE shape = PLANE;
	SHAPE shapeNext = PLANE;
	//bool sphereActive = false;
	bool changeshape = false;
	int RowsChanged = 0;   // used for changing shape
	Sphere *sphere = NULL;  // pointer to sphre specific data - may need to localize for mt
	//vector <Vertex> verts;
	Vertex verts[NUMVERTS];
	//vector <int> index;
	int index[NUMIDX];
	PLOCSTRUCT pData[NUMCOL][NUMROW];

	//vector<vector< PLOCSTRUCT>> pData;
	GLuint vboID; // Vertex Buffer Object ID // a GL pointer that will point at the vertex data
	GLuint indexVBOID; // Index Buffer Object ID // a GL pointer that will point at the indeax aray
	Vertex* ptr; //global pointer to memory in graphics card
	GLuint vertexBuffer;
    //SpeciesList* speciesList;
	int rotatex = 0;
	int rotatey = 0;
	int numPlaneIDX = 0;
	int numSphereIDX = 0;
	int lastShapeChange = 0;
	Plane *gblPlanePtr = NULL;
}PLANEDATA;
#include "lifelist.h"
#include "rainbow.h"

typedef	struct specdata
{
	int fileNumber = 0;
	bool decadeHeightShow = FALSE; //001
	int clusterSize = 10; //002
	int numseeds = 20;	 //003
	int seedXrange = 4;	//003
	int seedYrange = 4;	//005
	int maxTimeTillMutate = MAXMUTATETIME;  //006
	int timeTillMutate = maxTimeTillMutate; //007
	int maxNumaround = 100;  //008
	bool mateWithOtherSpecies = false; //009
	int baseColorRed; //010
	int baseColorGreen; //011
	int baseColorBlue = 0; //012
	bool showBaseColor = false; //013
	int overPop = 36000; // 014 a max value that is used to decide if a cell is "too different"  currently it looks at all cells Range away totaling the diff between colors
	int Range = 2; // 015 used above to calculate range to use for overpop calculation
	int mateRange = 2; // 016 when fining 2 cells to mate how far away to look for mate
	int childRange = 2; // 017 how far away to look for empty loc to  to place child
	int childXdir = 0; //018
	int childYdir = 0; // 019
	int timeToFindMate = 3; //020  how many times to look for a mate - note this is also used to number of times to find a loc for the child - needs to be seperated
	int mutationPcnt = 80; // 021 currently the point at which a random mutation occurs - higher num less often
	int fstart = 10;   // 022 fertility start - at this age the cell will start looking for a mate
	int fend = 150; // 023 fertility end - at this point the cell will stop looking for a mate
	int death = 200; // 024 the age at which the cell will die  ********** this will need to move to an energy level
	float heightgrowth = 0; //025
	//bool reflecton = false; //026
	int mutationFocusPcnt = 25; //028
	int timeAlive = 0; //028
	bool RainbowOn = false; //029
	bool BlackDeath = true; //030
	bool showAvgColor = false; //31
}specdata;

typedef	struct SPECIESDATA
{
	SDL_bool sdlCondition = SDL_FALSE;
	SDL_mutex *lock;
	SDL_cond *cond;
	int SpeciesId; // sequential id for species 
	int SpeciesIdSame = 0;
	bool spLocked;
	bool spLockedPaused = false;
	HANDLE handle;
	bool ChangeSpecies = FALSE;
	bool killUsAll = FALSE;
	int numseedsMin = 2;
	int numseedsMax = 10;
	int clusterSizeMin = 2;
	int clusterSizeMax = 10;
	int seedXrangeMin = 2;
	int seedXrangeMax = 10;
	int seedYrangeMin = 2;
	int seedYrangeMax = 10;
	specdata data;

	LifeList* lifelist;
	Rainbow* rainbow;
}SPECIESDATA;
typedef struct SpeciesArrayStruct
{
	//int currpos = 0;
	bool reflection = false;
	bool rainBowLocked = false;
	bool baseColorLocked = false;
	int numspecies = NUMSPECIES;
	int maxSpecies = NUMSPECIES;
//	SPECIESDATA speciesarray[NUMSPECIES];
	SPECIESDATA speciesarray[MAXSPECIES];
}SpeciesArrayStruct;
extern SpeciesArrayStruct Species;


#include "SpeciesList.h"

#include "Shader.h"
extern PLANEDATA plane;
#include "Plane.h"
#include "SpeciesMgmnt.h"

//extern SpeciesMgmnt*  speciesHold;

//const float pi = (float)3.14159265; // For portability across platforms



#include "Camera.h"

extern  Plane* planeptr;
extern  SpeciesList* speciesptr;

static 	bool GBLCOLORFOBIA = TRUE;
static bool GBLNUMAROUND = TRUE;

#include "Image.h"
//extern void SpeciesProc(void *MYptr);
//extern int SpeciesProc(void* SpeciesCurrpos);

#include "SpeciesMgmnt.h"

//#endif