#include "main.h"

//int g_iWindowWidth = 608;
//int g_iWindowHeight = 606;
int g_iWindowWidth = NUMROW;
int g_iWindowHeight = NUMCOL;

int g_W, g_A, g_S, g_D, g_Q, g_E;
bool g_bShift = false;
glm::ivec2 g_MousePos;
glm::quat g_Rotation;
glm::quat *g_RotationPtr = &g_Rotation;
Camera g_Camera;
Camera *g_CameraPtr = &g_Camera;
//g_CameraPoint = g_Camera;
glm::vec3 g_InitialCameraPosition;
glm::quat g_InitialCameraRotation;
glm::vec3 *g_InitialCameraPositionPtr = &g_InitialCameraPosition;
glm::quat *g_InitialCameraRotationPtr = &g_InitialCameraRotation;
int g_frameCount = 0;
int g_fps = 0;
static int g_timecount = 0;
bool g_changeSpecies = false;
//int g_numUpdated = 0;

int maxTimeTillImageChange = MaxTimeTillImageChange;


static unsigned long xq = 123456789, yq = 362436069, zq = 521288629;

//unsigned long xorshf96(int range) {          //period 2^96-1
//	unsigned long t;
//	float midval = 0;
//	int zq1 = 0;
//	xq ^= xq << 16;
//	xq ^= xq >> 5;
//	xq ^= xq << 1;
//
//	t = xq;
//	xq = yq;
//	yq = zq;
//	zq = t ^ xq ^ yq;
//	zq1 = zq;
//	if (zq1 < 0) zq1 = zq1 * -1;
//
//	midval = (float)zq1 / (float)2147483647;
//
//	return (int) (midval* range);
//}
//
const int randmax = MAXINT;
std::random_device rseed;
int runseed = rseed();

std::mt19937 rgen(runseed); // mersenne_twister   - gives psudo random number from randon seed
//std::mt19937 rgen(156); // mersenne_twister - gives stream psudo random numbers from fixed seen - same ever time - for debug
std::uniform_int_distribution<int> idist(0, (randmax));
//std::uniform_int_distribution<int> idist(0, (numVerts - 1));

SDL_Window *mainwindow; /* Our window handle */
SDL_GLContext maincontext; /* Our opengl context handle */
// SDL_Renderer* renderer; /*create renderer */
 SpeciesArrayStruct Species;
 PLANEDATA plane;

int numprocessedGbl;
//int numSpecies;
Shader* shader;
static Plane* planeptr;
static SpeciesList* speciesptr;
//Rainbow* gblRainbow;
static SpeciesMgmnt*  speciesHold;
//vector<vector< PLOCSTRUCT>> pData;
//PLANEDATA plane;
#include "Plane.h"
#include "sphere.h"

std::string XXXerror;

ImageToDisplay	*images;
//std::vector<std::string> vFileNames;

#include <Windows.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>


//SDL_bool sdlCondition = SDL_FALSE;
//SDL_mutex *lock;
//SDL_cond *cond;
//inline const char * const BoolToString(bool b)
//{
//	return b ? "true" : "false";
//}

std::string ZeroPadNumber(int width, int num)
{
	std::ostringstream ss;
	ss << std::setw(width) << std::setfill('0') << num;
	return ss.str();
}

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
{
	std::vector<std::string>   result;
	std::string                line;
	std::getline(str, line);

	std::stringstream          lineStream(line);
	std::string                cell;

	while (std::getline(lineStream, cell, ','))
	{
		result.push_back(cell);
	}
	// This checks for a trailing comma with no data after it.
	if (!lineStream && cell.empty())
	{
		// If there was a trailing comma then add an empty element.
		result.push_back("");
	}
	return result;
}

std::string GetLastErrorStdStr()
{
	DWORD error = GetLastError();
	if (error)
	{
		LPVOID lpMsgBuf;
		DWORD bufLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			error,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);
		if (bufLen)
		{
			LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
			std::string result(lpMsgStr, lpMsgStr + bufLen);

			LocalFree(lpMsgBuf);

			return result;
		}
	}
	return std::string();
}
void ReshapeGL(int w, int h)
{
	if (h == 0)
	{
		h = 1;
	}
	g_iWindowWidth = w;
	g_iWindowHeight = h;
	g_Camera.SetViewport(0, 0, w, h);
	g_Camera.SetProjectionRH(60.0f, w / (float)h, 0.1f, 500.0f);
}

int randomRange(int range)
{
	//return (int)(((double)idist(rgen) / (double)randmax) * (double)range);
	if (range == 0) range = 1;
	//return rand() % range;


	unsigned long t;
	float midval = 0;
	int zq1 = 0;
	xq ^= xq << 16;
	xq ^= xq >> 5;
	xq ^= xq << 1;

	t = xq;
	xq = yq;
	yq = zq;
	zq = t ^ xq ^ yq;
	zq1 = zq;
	if (zq1 < 0) zq1 = zq1 * -1;

	midval = (float)zq1 / (float)2147483647;

	return (int)(midval* range);

	//return xorshf96(range);

};

//int randomRange(int range)
//{
//	if (range <= 0) range = 1;
//	static std::mt19937 rgen(std::random_device{}());
//	static std::uniform_int_distribution<int> dist;
//	dist.param(std::uniform_int_distribution<int>::param_type(0, range - 1));
//	return dist(rgen);
//}

void InitGL(int argc, char* argv[])
{
	std::cout << "Initialize OpenGL..." << std::endl;



	if (SDL_Init(SDL_INIT_VIDEO) < 0) { /* Initialize SDL's Video subsystem */
		std::cout << "Unable to initialize SDL";
		//return 1;
	}
	/* Request opengl 4.4 context. */
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	/* Turn on double buffering with a 24bit Z buffer.
	* You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	/* Create our window  */
	//mainwindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	//	700, 700, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	mainwindow = SDL_CreateWindow(PROGRAM_NAME, 0, 30,
		g_iWindowWidth, g_iWindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	// SDL_SetWindowBordered(mainwindow, (SDL_bool)false);  // sets window bordeless

	SDL_SetWindowTitle(mainwindow,
		PROGRAM_NAME);

	if (!mainwindow){ /* Die if creation failed */
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		//		return 1;
	}
	/* We must call SDL_CreateRenderer in order for draw calls to affect this window. */
	// renderer = SDL_CreateRenderer(mainwindow, -1, 0);
	/* Create our opengl context and attach it to our window */
	maincontext = SDL_GL_CreateContext(mainwindow);
	GLenum rev;
	glewExperimental = GL_TRUE;
	rev = glewInit();
	if (GLEW_OK != rev){
		std::cout << "Error: " << glewGetErrorString(rev) << std::endl;
		exit(1);
	}
	else {
		std::cout << "GLEW Init: Success!" << std::endl;
	}
	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	SDL_GL_SetSwapInterval(1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glMatrixMode(GL_MODELVIEW);

	std::cout << "Initialize OpenGL Success!" << std::endl;
}

char* concat(const char* s1, const char* s2) {
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);
	char* result = (char*)malloc(len1 + len2 + 1);
	if (!result) return NULL;
	memcpy(result, s1, len1);
	memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	return result;
}


//char* concat(char *s1, char *s2)
//{
//
//	int r = 0; int s1Size = 0; int s2Size = 0;
//	s1Size = strlen(s1);
//	s2Size = strlen(s2);
//	char *result = (char*)malloc(strlen(s1) + strlen(s2) + 1);//+1 for the zero-terminator
//
//	r = strlen(result);
//	//in real code you would check for errors in malloc here
//	strcpy_s(result, (s1Size + s2Size + 1), s1);
//
//	strcat_s(result, (s1Size + s2Size + 1), s2);
//
//	r = strlen(result);
//
//
//	return result;
//}

void InitGLEW()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "There was a problem initializing GLEW. Exiting..." << std::endl;
		exit(-1);
	}
	// Check for 3.3 support.
	// I've specified that a 3.3 forward-compatible context should be created.
	// so this parameter check should always pass if our context creation passed.
	// If we need access to deprecated features of OpenGL, we should check
	// the state of the GL_ARB_compatibility extension.
	if (!GLEW_VERSION_3_3)
	{
		std::cerr << "OpenGL 3.3 required version support not present." << std::endl;
		exit(-1);
	}

#ifdef _WIN32
	if (WGLEW_EXT_swap_control)
	{
		wglSwapIntervalEXT(0); // Disable vertical sync
	}
#endif
}

CELLLOC getRloc(CELLLOC Cin, int range, CELLLOC direction)
{
	CELLLOC  out;
	//if ((plane.speciesList->currPos->data.childXdir == 0) && (plane.speciesList->currPos->data.childYdir == 0))
	if ((direction.xLoc == 0) && (direction.yLoc == 0))
	{
		out.xLoc = Cin.xLoc + randomRange(range) - (range / 2);
		out.yLoc = Cin.yLoc + randomRange(range) - (range / 2);
	}
	else
	{
		out.xLoc = Cin.xLoc + (randomRange(range)* direction.xLoc);
		out.yLoc = Cin.yLoc + (randomRange(range) * direction.yLoc);
	}
	//out.xLoc = Cin.xLoc + randomRange(range) - (range / 2) + plane.speciesList->currPos->data.childXdir;
	//out.yLoc = Cin.yLoc + randomRange(range) - (range / 2) + plane.speciesList->currPos->data.childYdir;
	//out.xLoc = plane.speciesList->currPos->data.childXdir + out.xLoc;
	//out.yLoc = plane.speciesList->currPos->data.childYdir + out.yLoc;
	// wrap around edges
	if (out.xLoc >= plane.numCol)
	{
		//out.xLoc = plane.numCol - out.xLoc;
		out.xLoc = out.xLoc - plane.numCol;
	}
	else
	{
		if (out.xLoc < 0)
		{
			out.xLoc = plane.numCol + out.xLoc;
		}
	}
	if (out.yLoc >= plane.numRow)
	{
		out.yLoc = out.yLoc - plane.numRow;
	}
	else
	{
		if (out.yLoc < 0)
		{
			out.yLoc = plane.numRow + out.yLoc;
		}
	}
	return out;
}

void CreateSeeds(int maxSeeds, bool rainbowon, int currSpecies) // creates seen updates world object and places in lifelist
{
	
		std::cout << "species num  " << currSpecies << " of   " << NUMSPECIES << " species  getting seeded  " << std::endl;


	CELLLOC tmploc;
	bool localptr = FALSE;
	int red, green, blue;
	if (plane.ptr == NULL)
	{
		localptr = TRUE;
		glBindVertexArray(plane.vboID);
		glBindBuffer(GL_ARRAY_BUFFER,plane.vertexBuffer);
		plane.ptr = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	//if (plane.pData[NUMCOL / 2][NUMROW / 2].Alive == TRUE) maxSeeds++;
	if (ActivateImgSpecNum)
	{
		maxSeeds = maxSeeds * 5;
	}
	if (SingleCenterSeed) maxSeeds = 1;
	for (int i = 0; i < maxSeeds; i++)
	{
		if ((i == 0) && SingleCenterSeed)
		{
			tmploc.xLoc = NUMCOL / 2;
			tmploc.yLoc = NUMROW / 2;
		}
		else
		{
			tmploc.xLoc = randomRange(plane.numCol - 2);
			tmploc.yLoc = randomRange(plane.numRow - 2);
		}
		if (Species.speciesarray[currSpecies].data.showBaseColor)
		{
			red = Species.speciesarray[currSpecies].data.baseColorRed;
			green = Species.speciesarray[currSpecies].data.baseColorGreen;
			blue = Species.speciesarray[currSpecies].data.baseColorBlue;
		}
		else
		{
			if (rainbowon)
			{
				red = Species.speciesarray[currSpecies].rainbow->data.r; 
				green = Species.speciesarray[currSpecies].rainbow->data.g; 
				blue = Species.speciesarray[currSpecies].rainbow->data.b;
				Species.speciesarray[currSpecies].rainbow->NextColor();
			}
			else
			{
				red = randomRange(255);
				green = randomRange(255);
				blue = randomRange(255);
			}
		}
		//Species.speciesarray[speciesin].lifelist->workCell = tmploc;
		//tmploc.xLoc = NUMCOL / 2;
		//tmploc.yLoc = NUMROW / 2;
		for (int i = 0; i < Species.speciesarray[currSpecies].data.clusterSize; i++)
		{
			if (plane.pData[tmploc.xLoc][tmploc.yLoc].Alive == FALSE)
			{
				plane.pData[tmploc.xLoc][tmploc.yLoc].Alive = TRUE;
				plane.pData[tmploc.xLoc][tmploc.yLoc].Col.r = red;
				plane.pData[tmploc.xLoc][tmploc.yLoc].Col.g = green;
				plane.pData[tmploc.xLoc][tmploc.yLoc].Col.b = blue;
				plane.pData[tmploc.xLoc][tmploc.yLoc].Col.a = 1;
				plane.pData[tmploc.xLoc][tmploc.yLoc].numMateAtmps = 0;
				plane.pData[tmploc.xLoc][tmploc.yLoc].speciedNum = currSpecies;
				Species.speciesarray[currSpecies].lifelist->addNew(tmploc, currSpecies);
				planeptr->showCol(tmploc, currSpecies);
				if (Species.reflection)
				{
					planeptr->CreateReflect(tmploc, currSpecies);
				}
			}
			tmploc.xLoc = tmploc.xLoc + randomRange(Species.speciesarray[currSpecies].data.seedXrange) - (Species.speciesarray[currSpecies].data.seedXrange / 2);
			tmploc.yLoc = tmploc.yLoc + randomRange(Species.speciesarray[currSpecies].data.seedYrange) - (Species.speciesarray[currSpecies].data.seedYrange / 2);
			if (tmploc.xLoc >=plane.numCol) tmploc.xLoc = tmploc.xLoc -plane.numCol;
			else if (tmploc.xLoc < 0) tmploc.xLoc =plane.numCol - 1 + tmploc.xLoc;
			if (tmploc.yLoc >=plane.numRow) tmploc.yLoc = tmploc.yLoc -plane.numRow;
			else if (tmploc.yLoc < 0) tmploc.yLoc =plane.numRow - 1 + tmploc.yLoc;
		}
	}

	if (localptr)
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}


void AgeCells(Rainbow *rainbowin, int numCellsToUpdate, int currSpecies)
{
	CELLLOC aLoc;
	CELLLOC MateLoc;
	CELLLOC ChildLoc;
	int x = 0, y = 0, i = 0; //count = 1;
	bool mateFound = false;
	bool childLocFound = false;
	bool alive = false;
	bool newdecade = false;
	//for (int j = 0; j < numCellsToUpdate; j++)                  //for (int j = 0; j < numtoprocess; j++)
	while ((Species.speciesarray[currSpecies].lifelist->activeLifeCount < 2) || (Species.speciesarray[currSpecies].lifelist->start == NULL) || (Species.speciesarray[currSpecies].ChangeSpecies == TRUE))
	{
		//std::cout << "ID " << currSpecies << " mutate or less that 2 alive  " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << " alive " << std::endl;
		//int zzz;
		//zzz = 101;
		//if (zzz == 102)

		speciesptr->RandSpecies(currSpecies, g_timecount);// , TRUE, (SPECIESSUB)randomRange(SPECIESSUBcount));
		Species.speciesarray[currSpecies].ChangeSpecies = FALSE;
		CreateSeeds(Species.speciesarray[currSpecies].data.numseeds, Species.speciesarray[currSpecies].data.RainbowOn, currSpecies);
		if ((Species.speciesarray[currSpecies].lifelist->activeLifeCount < 2) || (Species.speciesarray[currSpecies].lifelist->start == NULL))
		{
			Sleep(200);
		}
	}
	while (TRUE)
	{
		//	std::cout << "x3active life count" << Species.speciesarray[Species.currpos].lifelist->activeLifeCount << " calculated " << xxi << std::endl;
		//std::cout << "currspecies " << currspecies << " activeLifeCount " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << " xxcurrpos " << Species.speciesarray[currSpecies].lifelist->xxcurrpos << " top" << std::endl;
		aLoc = Species.speciesarray[currSpecies].lifelist->currPos->CellLoc;
		x = aLoc.xLoc;
		y = aLoc.yLoc;
		newdecade = FALSE;
		alive = false;
		mateFound = false;
		childLocFound = false;
		plane.pData[x][y].Age++;
		alive = (plane.pData[x][y].Age < Species.speciesarray[currSpecies].data.death);
		if (alive)
		{
			if (plane.pData[x][y].Age == plane.pData[x][y].AgeDecade * 10)
			{
				plane.pData[x][y].AgeDecade++;
				newdecade = true;
			}
			//else
			//{
			//	newdecade = false;
			//}
			if (Species.speciesarray[currSpecies].data.heightgrowth > 0)
			{
				if (plane.shape == SPHERE) plane.sphere->sShowHeight(Species.speciesarray[currSpecies].lifelist->currPos->CellLoc, currSpecies);
				else planeptr->pshowHeight(Species.speciesarray[currSpecies].lifelist->currPos->CellLoc, Species.speciesarray[currSpecies].data.decadeHeightShow, currSpecies);
			}
			//if ((alive) && (!NUMAROUNDAB || newdecade))
			//{
			//	alive = ((alive) && (planeptr->ColorAndNumAroundOK(aLoc, Species.speciesarray[currSpecies].data.Range, Species.speciesarray[currSpecies].data.maxNumaround, Species.speciesarray[currSpecies].data.overPop)));

			//}
			if (alive && (plane.pData[x][y].Age > Species.speciesarray[currSpecies].data.fstart) && (plane.pData[x][y].Age < Species.speciesarray[currSpecies].data.fend))
			{
				i = 0;
				CELLLOC direction;
				direction.xLoc = Species.speciesarray[currSpecies].data.childXdir * -1;
				direction.yLoc = Species.speciesarray[currSpecies].data.childYdir * -1;
				while ((!mateFound) && (i < Species.speciesarray[currSpecies].data.timeToFindMate))
				{
					i++;
					MateLoc = getRloc(aLoc, Species.speciesarray[currSpecies].data.mateRange, direction);
					if ((plane.pData[MateLoc.xLoc][MateLoc.yLoc].Alive == TRUE))
					{
						if ((Species.speciesarray[currSpecies].data.mateWithOtherSpecies) || (Species.speciesarray[plane.pData[MateLoc.xLoc][MateLoc.yLoc].speciedNum].data.mateWithOtherSpecies) || (plane.pData[MateLoc.xLoc][MateLoc.yLoc].speciedNum == currSpecies))
							mateFound = true;
					}
				}
				// if a mate has been found and childloc empty - create a child.
				if ((mateFound))
				{
					plane.pData[x][y].numMateAtmps = 0;
					i = 0;
					direction.xLoc = Species.speciesarray[currSpecies].data.childXdir;
					direction.yLoc = Species.speciesarray[currSpecies].data.childYdir;
					if ((plane.pData[x][y].Age == Species.speciesarray[currSpecies].data.death / 2))
					{
						// spread uout even if 0 on x or y direction
						if (direction.xLoc == 0)
						{
							if (randomRange(100) < 50)
							{
								direction.xLoc = 1;
							}
							else
							{
								direction.xLoc = -1;
							}
							direction.yLoc = 0;
						}
						else
						{
							if (direction.yLoc == 0)
							{
								if (randomRange(100) < 50)
								{
									direction.yLoc = 1;
								}
								else
								{
									direction.yLoc = -1;
								}
								direction.xLoc = 0;
							}
						}
					}
					while ((!childLocFound) && (i < Species.speciesarray[currSpecies].data.timeToFindMate))
					{
						i++;
						ChildLoc = getRloc(aLoc, Species.speciesarray[currSpecies].data.childRange, direction);
						if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Alive == FALSE) childLocFound = true;
						if (ActivateImgSpecNum)
						{
							if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].ImgSpecNum != plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].speciedNum)
							{
								childLocFound = false;
							}
						}
					}
					if (childLocFound)
					{
						if ((Species.speciesarray[currSpecies].data.showBaseColor) || (Species.speciesarray[currSpecies].data.RainbowOn))
						{
							if (Species.speciesarray[currSpecies].data.showBaseColor)
							{
								plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = Species.speciesarray[currSpecies].data.baseColorRed;
								plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = Species.speciesarray[currSpecies].data.baseColorGreen;
								plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = Species.speciesarray[currSpecies].data.baseColorBlue;
							}
							else
							{
								plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = rainbowin->data.r;
								plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = rainbowin->data.g;
								plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = rainbowin->data.b;
								rainbowin->NextColor();
							}

						}
						else
						{
							if (randomRange(100) < Species.speciesarray[currSpecies].data.mutationPcnt) 
							{
								if (ShowImage)
								{
									if (images->image1Current)
									{
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = images->displayImage1[ChildLoc.xLoc][ChildLoc.yLoc].colour.r;
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = images->displayImage1[ChildLoc.xLoc][ChildLoc.yLoc].colour.g;
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = images->displayImage1[ChildLoc.xLoc][ChildLoc.yLoc].colour.b;
									}
									else
									{
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = images->displayImage2[ChildLoc.xLoc][ChildLoc.yLoc].colour.r;
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = images->displayImage2[ChildLoc.xLoc][ChildLoc.yLoc].colour.g;
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = images->displayImage2[ChildLoc.xLoc][ChildLoc.yLoc].colour.b;
									}
								}
								else
								{
									if (Species.speciesarray[currSpecies].data.RainbowOn)
									{
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = rainbowin->data.r;
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = rainbowin->data.g;
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = rainbowin->data.b;
										rainbowin->NextColor();
									}
									else
										if (Species.speciesarray[currSpecies].data.showBaseColor)
										{
											plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = Species.speciesarray[currSpecies].data.baseColorRed;
											plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = Species.speciesarray[currSpecies].data.baseColorGreen;
											plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = Species.speciesarray[currSpecies].data.baseColorBlue;
										}
										else
										{
											if (randomRange(100) < Species.speciesarray[currSpecies].data.mutationPcnt)
											{
												plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = randomRange(255);
												plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = randomRange(255);
												plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = randomRange(255);
											}
											else
											{ // merge parents - soimtimnes avg color - sometimes focus
												if (randomRange(100) < Species.speciesarray[currSpecies].data.mutationFocusPcnt) // 75)
																																 // avg color
												{
													plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = (plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r + plane.pData[x][y].Col.r) / 2;
													plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = (plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g + plane.pData[x][y].Col.g) / 2;
													plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = (plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b + plane.pData[x][y].Col.b) / 2;
												}
												else
												{ // focus color
													if ((plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r + plane.pData[x][y].Col.r) > 255)
													{
														plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = max(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r, plane.pData[x][y].Col.r)
															+ (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r - plane.pData[x][y].Col.r) / 20);
													}
													else
													{
														plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = min(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r, plane.pData[x][y].Col.r)
															- (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r - plane.pData[x][y].Col.r) / 20);
													}
													if ((plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g + plane.pData[x][y].Col.g) > 255)
													{
														plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = max(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g, plane.pData[x][y].Col.g)
															+ (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g - plane.pData[x][y].Col.g) / 20);
													}
													else
													{
														plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = min(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g, plane.pData[x][y].Col.g)
															- (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g - plane.pData[x][y].Col.g) / 20);
													}
													if ((plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b + plane.pData[x][y].Col.b) > 255)
													{
														plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = max(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b, plane.pData[x][y].Col.b)
															+ (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b - plane.pData[x][y].Col.b) / 20);
													}
													else
													{
														plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = min(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b, plane.pData[x][y].Col.b)
															- (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b - plane.pData[x][y].Col.b) / 20);
													}
												}
											}

										}
								}
							}
							else
							{ // merge parents - soimtimnes avg color - sometimes focus
								if (randomRange(100) < Species.speciesarray[currSpecies].data.mutationFocusPcnt) // 75)
																												 // avg color
								{
									plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = (plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r + plane.pData[x][y].Col.r) / 2;
									plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = (plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g + plane.pData[x][y].Col.g) / 2;
									plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = (plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b + plane.pData[x][y].Col.b) / 2;
								}
								else
								{ // focus color
									if ((plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r + plane.pData[x][y].Col.r) > 255)
									{
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = max(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r, plane.pData[x][y].Col.r)
											+ (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r - plane.pData[x][y].Col.r) / 20);
									}
									else
									{
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = min(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r, plane.pData[x][y].Col.r)
											- (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.r - plane.pData[x][y].Col.r) / 20);
									}
									if ((plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g + plane.pData[x][y].Col.g) > 255)
									{
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = max(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g, plane.pData[x][y].Col.g)
											+ (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g - plane.pData[x][y].Col.g) / 20);
									}
									else
									{
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = min(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g, plane.pData[x][y].Col.g)
											- (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.g - plane.pData[x][y].Col.g) / 20);
									}
									if ((plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b + plane.pData[x][y].Col.b) > 255)
									{
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = max(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b, plane.pData[x][y].Col.b)
											+ (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b - plane.pData[x][y].Col.b) / 20);
									}
									else
									{
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = min(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b, plane.pData[x][y].Col.b)
											- (abs(plane.pData[MateLoc.xLoc][MateLoc.yLoc].Col.b - plane.pData[x][y].Col.b) / 20);
									}
								}
							}
						}
						// make sure they all in range
						//if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b > 255) plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = 255;
						//if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b < 0) plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = 10;
						//if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r > 255) plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = 255;
						//if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r < 0) plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = 10;
						//if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g > 255) plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = 255;
						//if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g < 0) plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = 10;
						plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Alive = TRUE;
						plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Age = 0;
						plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].AgeDecade = 1;
						plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].numMateAtmps = 0;
						plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].speciedNum = currSpecies;
						//plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].surrounded = false;
						if (NUMAROUNDAB)
						{
							//int xxyxx = planeptr->numAround(ChildLoc, Species.speciesarray[currSpecies].Range, Species.speciesarray[currSpecies].maxNumaround);
							if (!planeptr->ColorAndNumAroundOK(aLoc, Species.speciesarray[currSpecies].data.Range, Species.speciesarray[currSpecies].data.maxNumaround, Species.speciesarray[currSpecies].data.overPop))
							{
								plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Alive = false;
								//std::cout << "ID " << currSpecies << " now dead  " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << " numaroundxxy " << xxyxx  <<  std::endl;
								if (Species.speciesarray[currSpecies].data.BlackDeath)
								{
									plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.a = 1;
									plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = 0;
									plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = 0;
									plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = 0;
								}
								else
								{
									plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].avgColor;
								}
								planeptr->showCol(ChildLoc, currSpecies);
							}
							else
							{
								if ((plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r > 220) && (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g > 220) && (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b > 220))
								{
									plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r / 2;
									plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g / 2;
									plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b / 2;
								}
								else
									if ((plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r < 30) && (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g < 30) && (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b < 30))
									{
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r * 2;
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g * 2;
										plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b * 2;
									}
								//{ // old protecft from white or black
								//	plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].avgColor;
								//	if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r < plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g)
								//		if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r < plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b)
								//			plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r / 2;
								//		else
								//			if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b < plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g)
								//				plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b / 2;
								//			else
								//				if (plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g < plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r)
								//					plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g / 2;
								//				else
								//				{
								//					int tmp1 = randomRange(30);
								//					if (tmp1 < 10)
								//						plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.r - (10 + randomRange(50));
								//					else
								//						if (tmp1 < 20)
								//							plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.g - (10 + randomRange(50));
								//						else
								//							plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b = plane.pData[ChildLoc.xLoc][ChildLoc.yLoc].Col.b - (10 + randomRange(50));
								//				}
								//}
								Species.speciesarray[currSpecies].lifelist->addNew(ChildLoc, currSpecies);
								planeptr->showCol(ChildLoc, currSpecies);
								if (Species.reflection)
								{
									planeptr->CreateReflect(ChildLoc, currSpecies);
								}
							}
						}
						else
						{
							Species.speciesarray[currSpecies].lifelist->addNew(ChildLoc, currSpecies);
							planeptr->showCol(ChildLoc, currSpecies);

							if (Species.reflection)
							{
								planeptr->CreateReflect(ChildLoc, currSpecies);
							}
						}
					}
				}
			}
		}
		else //its dead
		{
			plane.pData[x][y].Alive = FALSE;
			if (!Species.speciesarray[currSpecies].data.BlackDeath)
			{
				plane.pData[x][y].Col = plane.pData[x][y].avgColor;
				planeptr->showCol(aLoc, currSpecies);
			}
			else
			{
				plane.pData[x][y].Col.r = 0;
				plane.pData[x][y].Col.g = 0;
				plane.pData[x][y].Col.b = 0;
				plane.pData[x][y].Col.a = 1;
				planeptr->showCol(aLoc, currSpecies);
			}
			plane.pData[x][y].Age = 0;
			plane.pData[x][y].AgeDecade = 1;
			if (plane.shape == SPHERE) plane.sphere->sShowHeight(aLoc, currSpecies); else planeptr->pshowHeight(aLoc, Species.speciesarray[currSpecies].data.decadeHeightShow, currSpecies);
			Species.speciesarray[currSpecies].lifelist->delCurrent(currSpecies);
		}
		if (Species.speciesarray[currSpecies].killUsAll)
		{
			//
			speciesHold->killSpecies(currSpecies);
			Species.speciesarray[currSpecies].killUsAll = false;
			CreateSeeds(Species.speciesarray[currSpecies].data.numseeds, Species.speciesarray[currSpecies].data.RainbowOn, currSpecies);
		}
		//if (ActivateImgSpecNum)
		//{
		//	if (Species.speciesarray[currSpecies].lifelist->activeLifeCount < (NUMVERTS / NUMSPECIES) * 0.1)
		//	{
		//		int tmpxxx = 0;
		//		tmpxxx = NUMVERTS / NUMSPECIES;
		//		std::cout << "ID " << currSpecies << " activeLifeCount   " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << " alive " << std::endl;
		//		CreateSeeds(Species.speciesarray[currSpecies].data.numseeds+10, Species.speciesarray[currSpecies].data.RainbowOn, currSpecies);
		//	}
		//}
		while (((Species.speciesarray[currSpecies].lifelist->activeLifeCount < 2) || (Species.speciesarray[currSpecies].lifelist->start == NULL) || (Species.speciesarray[currSpecies].ChangeSpecies)) && !Species.speciesarray[currSpecies].spLocked)
		{
			//std::cout << "ID " << currSpecies << " mutate or less that 2 alive  " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << " alive " << std::endl;
			speciesptr->RandSpecies(currSpecies, g_timecount); // , TRUE, (SPECIESSUB)randomRange(SPECIESSUBcount));
			Species.speciesarray[currSpecies].ChangeSpecies = FALSE;
			CreateSeeds(Species.speciesarray[currSpecies].data.numseeds, Species.speciesarray[currSpecies].data.RainbowOn, currSpecies);
			if ((Species.speciesarray[currSpecies].lifelist->activeLifeCount < 5) || (Species.speciesarray[currSpecies].lifelist->start == NULL))
			{
				if (Species.speciesarray[currSpecies].spLocked)
				{
					std::cout << "ID " << currSpecies << " mutate or less that 2 alive  " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << " alive " << std::endl;
				}
				else
				{
					//std::cout << "ID " << currSpecies << " mutate or less that 2 alive sleep  " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << " alive " << std::endl;
					//Sleep(250);   zzzzzzzzzzzzzzzzzzzzzz
				}

			}
		}
		//SDL_LockMutex(lock);
		while (Species.speciesarray[currSpecies].sdlCondition) {
			//std::cout << "ID " << currSpecies << " paused ***   " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << " alive " << std::endl;
			//printf("\n paused ***  \n");
			Species.speciesarray[currSpecies].spLocked = true;
			Species.speciesarray[currSpecies].spLockedPaused = true;
			SDL_CondWait(Species.speciesarray[currSpecies].cond, Species.speciesarray[currSpecies].lock);
			Species.speciesarray[currSpecies].spLocked = false;
			Species.speciesarray[currSpecies].spLockedPaused = false;
			//std::cout << "ID " << currSpecies << " AWAKE ***   " << Species.speciesarray[currSpecies].lifelist->activeLifeCount << " alive " << std::endl;
			Species.speciesarray[currSpecies].lifelist->goFirst();
		}
		Species.speciesarray[currSpecies].lifelist->goNext();
	}
}

int SpeciesProc(void* SpeciesCurrpos)
{
	srand(time(NULL));
	int currSpecies; 
	//currSpecies = *(int*)SpeciesCurrpos;
	currSpecies = (int)SpeciesCurrpos;
	speciesptr->insEnd(currSpecies);
	Sleep(100);
	Vertex *ptr = plane.ptr; //  (Vertex*)MYptr; //global pointer to memory in graphics card
	//char    *MyID = (char*)pMyID;
	int i = 1;
	//i = pData[in.xLoc][in.yLoc].cellDisplayPos;
	int numtoprocess = 1000;
	//Species.speciesarray[currSpecies].lifelist = new LifeList();
	//Species.speciesarray[currSpecies].lifelist->species = currSpecies;
	Rainbow* rainbow;
	rainbow = new Rainbow;
	rainbow->speciesNum = currSpecies;
	//Sleep(50 + (currSpecies*10));
	speciesptr->RandSpecies(currSpecies, 1);// TRUE, (SPECIESSUB)1);
	CreateSeeds(Species.speciesarray[currSpecies].data.numseeds, Species.speciesarray[currSpecies].data.RainbowOn, currSpecies);
	Sleep(10 + (currSpecies *10));
	for (int j = 0; j < 200000; j++)
	{
		//for (size_t i = 0; i < (400 * 400); i++)
		//{
		//	*(&(ptr + i)->colour[R_POS]) = 1.0f;
		//	*(&(ptr + i)->colour[G_POS]) = 0.0f;
		//	*(&(ptr + i)->colour[B_POS]) = 0.0f;
		//	*(&(ptr + i)->colour[A_POS]) = 1.0f;
		//}
		//std::cout << "flush done "  << std::endl;
		//glBindVertexArray(plane.vboID);
		//glBindBuffer(GL_ARRAY_BUFFER, plane.vertexBuffer);
		//plane.ptr = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		AgeCells(rainbow, numtoprocess, currSpecies);
		std::cout << "100000000 updated " << std::endl;
		//numprocessedGbl = numprocessedGbl + numtoprocess;
		//glUnmapBuffer(GL_ARRAY_BUFFER);
		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindVertexArray(0);
	}
	//char    MyCell, OldCell;
	//WORD    MyAttrib, OldAttrib;
	//char    BlankCell = 0x20;
	//COORD   Coords, Delta;
	//COORD   Old = { 0, 0 };
	//DWORD   Dummy;
	//char    *MyID = (char*)pMyID;
	//// Generate update increments and initial 
	//// display coordinates.
	//srand((unsigned int)*MyID * 3);
	//Coords.X = getrandom(0, csbiInfo.dwSize.X - 1);
	//Coords.Y = getrandom(0, csbiInfo.dwSize.Y - 1);
	//Delta.X = getrandom(-3, 3);
	//Delta.Y = getrandom(-3, 3);
	//// Set up "happy face" & generate color 
	//// attribute from thread number.
	//if (*MyID > 16)
	//	MyCell = 0x01;          // outline face 
	//else
	//	MyCell = 0x02;          // solid face 
	//MyAttrib = *MyID & 0x0F;   // force black background 
	//do
	//{
	//	// Wait for display to be available, then lock it.
	//	WaitForSingleObject(hScreenMutex, INFINITE);
	//	// If we still occupy the old screen position, blank it out. 
	//	ReadConsoleOutputCharacter(hConsoleOut, &OldCell, 1,
	//		Old, &Dummy);
	//	ReadConsoleOutputAttribute(hConsoleOut, &OldAttrib, 1,
	//		Old, &Dummy);
	//	if ((OldCell == MyCell) && (OldAttrib == MyAttrib))
	//		WriteConsoleOutputCharacter(hConsoleOut, &BlankCell, 1,
	//		Old, &Dummy);
	//	// Draw new face, then clear screen lock 
	//	WriteConsoleOutputCharacter(hConsoleOut, &MyCell, 1,
	//		Coords, &Dummy);
	//	WriteConsoleOutputAttribute(hConsoleOut, &MyAttrib, 1,
	//		Coords, &Dummy);
	//	ReleaseMutex(hScreenMutex);
	//	// Increment the coordinates for next placement of the block. 
	//	Old.X = Coords.X;
	//	Old.Y = Coords.Y;
	//	Coords.X += Delta.X;
	//	Coords.Y += Delta.Y;
	//	// If we are about to go off the screen, reverse direction 
	//	if (Coords.X < 0 || Coords.X >= csbiInfo.dwSize.X)
	//	{
	//		Delta.X = -Delta.X;
	//		Beep(400, 50);
	//	}
	//	if (Coords.Y < 0 || Coords.Y > csbiInfo.dwSize.Y)
	//	{
	//		Delta.Y = -Delta.Y;
	//		Beep(600, 50);
	//	}
	//}
	//// Repeat while RunMutex is still taken. 
	//while (WaitForSingleObject(hRunMutex, 75L) == WAIT_TIMEOUT);
	return 99;
}

void ChageShape()
{
	//int numtochange = 10;
	//if (true)
	//{
	// planeIn->changeshape = false;
	// planeIn->RowsChanged = 0;
	//}
	//else
	plane.shape = plane.shapeNext;
	for (int i = 0; i < NUMROW; i++)
	{
		
		CELLLOC tmploc;
		tmploc.yLoc = i;
		for (int x = 0; x < NUMCOL; x++)
		{
			tmploc.xLoc = x;
			if (plane.shape == SPHERE)
			{
				plane.sphere->sShowHeight(tmploc, plane.pData[tmploc.xLoc][tmploc.yLoc].speciedNum);
			}
			else
			{
				*(&(plane.ptr + plane.pData[tmploc.xLoc][tmploc.yLoc].cellDisplayPos)->location[X_POS]) = (((GLfloat)tmploc.xLoc * 16 / (GLfloat)plane.numCol)) - 8;
				*(&(plane.ptr + plane.pData[tmploc.xLoc][tmploc.yLoc].cellDisplayPos)->location[Y_POS]) = (((GLfloat)tmploc.yLoc * 16 / (GLfloat)plane.numCol)) - 8;

				if (plane.pData[x][plane.RowsChanged].Alive == TRUE)
				{

					*(&(plane.ptr + plane.pData[tmploc.xLoc][tmploc.yLoc].cellDisplayPos)->location[Z_POS]) =
						(float)plane.pData[tmploc.xLoc][tmploc.yLoc].Age * Species.speciesarray[plane.pData[tmploc.xLoc][tmploc.yLoc].speciedNum].data.heightgrowth;
				}
				else *(&(plane.ptr + plane.pData[tmploc.xLoc][tmploc.yLoc].cellDisplayPos)->location[Z_POS]) = 0;
			}
		}
		//plane.RowsChanged++;
		//if (plane.RowsChanged == plane.numRow)
		//{
		//	plane.changeshape = false;
		//	plane.RowsChanged = 0;
		//	i = numtochange;
		//	//plane.shapeChanging = false;
		//}
	}

	if (plane.shape == PLANE)
	{
		int maxheight = 0;
		for (size_t i = 0; i < MAXSPECIES; i++)
		{
			//maxheight = ((float)Species.speciesarray[i].data.death / (float)maxage) *(float)maxheighttmp;
			Species.speciesarray[i].data.heightgrowth = maxheight / Species.speciesarray[i].data.death;
			Species.speciesarray[i].data.decadeHeightShow = false;
		}
	}
	else
	{
		float  maxheight = (float)Maxheight;
		float agePercentOfmax = 0.00f;
		

		for (size_t i = 0; i < MAXSPECIES; i++)
		{
			//maxheight = ((float)Species.speciesarray[i].data.death / (float)maxage) *(float)maxheighttmp;
			agePercentOfmax = ((float)Species.speciesarray[i].data.death / (float)MaxAge) *(float)100.00f;
			maxheight = (Maxheight * agePercentOfmax)/100.00f;
			Species.speciesarray[i].data.heightgrowth = maxheight / (float)Species.speciesarray[i].data.death;
			Species.speciesarray[i].data.decadeHeightShow = false;
			Species.speciesarray[i].data.BlackDeath = false;
		}
	}

	plane.changeshape = false;
	plane.RowsChanged = 0;
}

//void DisplayGL()
//{
//	////////////////////////////////////////////// draw the sun
//	//int slices = 32;
//	//int stacks = 32;
//	//int numIndicies = (slices * stacks + slices) * 6;
//	//if (g_vaoSphere == 0)
//	//{
//	//	g_vaoSphere = SolidSphere(5, slices, stacks);
//	//}
//	//const glm::vec4 white(1);
//	//const glm::vec4 black(0);
//	//const glm::vec4 ambient(0.1f, 0.1f, 0.1f, 1.0f);
//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	//// Draw the sun using a simple shader.
//	//glBindVertexArray(g_vaoSphere);
//	//glUseProgram(shader->g_SimpleShaderProgram);
//	////glm::mat4 modelMatrix = glm::rotate(glm::radians(g_fSunRotation),  glm::vec3(0, 0, 20));
//	//glm::mat4 modelMatrix = glm::rotate(glm::radians(g_fSunRotation), glm::vec3(0, -1, 0)) * glm::translate(glm::vec3(90, 0, 0)); // *g_Rotation);
//	//glm::mat4 mvp = g_Camera.GetProjectionMatrix() * g_Camera.GetViewMatrix() * modelMatrix;
//	//GLuint uniformMVP = glGetUniformLocation(shader->g_SimpleShaderProgram, "MVP");
//	//glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, glm::value_ptr(mvp));
//	//glUniform4fv(shader->g_uniformColor, 1, glm::value_ptr(white));
//	//glDrawElements(GL_TRIANGLES, numIndicies, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
//	/////////////////////////////////////////////////////////
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//
//	glBindVertexArray(plane.vboID);
//	glUseProgram(shader->g_ShaderProgram);
//	//glm::vec4 tst1;
//	//tst1 = modelMatrix[3];
//	//tst1.w = 0;
//	//tst1 = tst1 * glm::vec4(-1);
//	//tst1 = glm::vec4(0.0, 0.0, 15.0, 1.0);
//	//tst1 = g_Camera.GetViewMatrix()[3];
//	//std::cout << "FPS " << fps << " Nodes Upd p/s " << gblNodesUpd << " actLL " << lifelist->activeLifeCount << " LL cycles " << lifelist->LLreSets << " num2process " << numtoprocess << std::endl;
//	//shader->g_uniformLightPosW = glGetUniformLocation(shader->g_ShaderProgram, "LightPosW");
//	//glUniform4fv(shader->g_uniformLightPosW, 1, glm::value_ptr(tst1));
//	//glUniform4fv(shader->g_uniformLightPosW, 1, glm::value_ptr((g_Camera.GetViewMatrix()[3] * glm::vec4(-1, -1, -1, 0))));
//
//	int idxToShow = plane.numPlaneIDX;
//	if ((plane.shape == SPHERE))// && (!plane->changeShape))
//	{
//		idxToShow = plane.numSphereIDX;
//	}
//	//if (plane->changeshape)
//	//{
//	//	//glBindVertexArray(plane->vboID);
//	//	//glBindBuffer(GL_ARRAY_BUFFER, plane->vertexBuffer);
//	//	////glBufferSubData(GL_ARRAY_BUFFER, 0, verts.size() *sizeof(Vertex)* numVerts, &verts[0]);
//	//	//plane->ptr = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//	//	ChageShape(plane);
//	//	//glUnmapBuffer(GL_ARRAY_BUFFER);
//	//	//glBindBuffer(GL_ARRAY_BUFFER, 0);
//	//	//glBindVertexArray(0);
//	//}
//	//if (g_Rotation.x != 0)
//	//{
//	//	std::cout << "g_Rotation.x " << g_Rotation.x  << std::endl;
//	//}
//	//if (g_Rotation.y != 0)
//	//{
//	//	std::cout << "g_Rotation.y " << g_Rotation.y << std::endl;
//	//}
//
//	shader->projection_matrix = g_CameraPtr->GetProjectionMatrix();
//	shader->model_matrix = glm::toMat4(g_Rotation);
//	glm::mat4 mvp = g_Camera.GetProjectionMatrix() * g_Camera.GetViewMatrix() * glm::toMat4(g_Rotation);
//	//mvp = g_Camera.GetProjectionMatrix() * g_Camera.GetViewMatrix() * glm::toMat4(g_Rotation);
//	glUniformMatrix4fv(shader->g_uniformMVP, 1, GL_FALSE, glm::value_ptr(mvp));
//	glm::vec4 eyePosW = glm::vec4(g_Camera.GetPosition(), 1);
//	glUniform4fv(shader->g_uniformEyePosW, 1, glm::value_ptr(eyePosW));
//	glDrawElements(GL_TRIANGLES, idxToShow, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
//	glUseProgram(0);
//	glBindVertexArray(0);
//	// drawFPS();
//
//	//	glutSwapBuffers();
//}

void DisplayGL()
{
	// Only clear if needed (usually always needed, but consider partial redraws for advanced cases)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind VAO and shader only if changed (if you have multiple VAOs/shaders)
	glBindVertexArray(plane.vboID);
	glUseProgram(shader->g_ShaderProgram);

	// Only update uniforms if camera or rotation changed
	static glm::mat4 lastMVP;
	glm::mat4 mvp = g_Camera.GetProjectionMatrix() * g_Camera.GetViewMatrix() * glm::toMat4(g_Rotation);
	if (mvp != lastMVP) {
		glUniformMatrix4fv(shader->g_uniformMVP, 1, GL_FALSE, glm::value_ptr(mvp));
		lastMVP = mvp;
	}
	static glm::vec4 lastEyePosW;
	glm::vec4 eyePosW = glm::vec4(g_Camera.GetPosition(), 1);
	if (eyePosW != lastEyePosW) {
		glUniform4fv(shader->g_uniformEyePosW, 1, glm::value_ptr(eyePosW));
		lastEyePosW = eyePosW;
	}

	int idxToShow = (plane.shape == SPHERE) ? plane.numSphereIDX : plane.numPlaneIDX;
	glDrawElements(GL_TRIANGLES, idxToShow, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	glUseProgram(0);
	glBindVertexArray(0);
}

void PerCycleCalcs()
{
	//for (size_t i = 0; i < Species.numspecies; i++)
	//{
	//	//SuspendThread(Species.speciesarray[i].handle);
	//}

	g_timecount++;
	float cameraSpeed = 1.0f;
	if (g_bShift)
	{
		cameraSpeed = 5.0f;
	}
	//g_Camera.Translate(glm::vec3(g_D - g_A, g_Q - g_E, g_S - g_W) * cameraSpeed * fDeltaTime);
	g_Camera.Translate(glm::vec3(g_D - g_A, g_Q - g_E, g_S - g_W) * cameraSpeed * 1000.0f);
	g_fps = g_frameCount;
	images->timeTillImageChange++;
	images->timeImageLoadSP++;
	images->timeTillBaseColorChange++;

	if (images->timeTillBaseColorChange > images->maxTimeBaseColorChange)
	{
		//if (randomRange(100) < 10)
		//{
		//	plane.gblPlanePtr->clearDead();//  HERE
		//	bool tempbool;
		//	tempbool = gblBlackDeath;
		//	gblBlackDeath = true;
		//	for (size_t i = 0; i < NUMSPECIES; i++)
		//	{
		//		Species.speciesarray[i].killUsAll = TRUE;
		//	}
		//	Sleep(150);
		//	plane.gblPlanePtr->clearDead();
		//	gblBlackDeath = tempbool;
		//}

		//plane.gblPlanePtr->clearDead();
		
		for (int i = 0; i < Species.numspecies; i++)
		{
			Species.speciesarray[i].data.baseColorRed = randomRange(256);
			Species.speciesarray[i].data.baseColorGreen = randomRange(256);
			Species.speciesarray[i].data.baseColorBlue = randomRange(256);
			int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
			if ((zzz > 650) || (zzz < 118))
			{
				Species.speciesarray[i].data.baseColorRed = randomRange(256);
				Species.speciesarray[i].data.baseColorGreen = randomRange(256);
				Species.speciesarray[i].data.baseColorBlue = randomRange(256);
			}
		}
		images->timeTillBaseColorChange = 0;
		printf("***** Base color changed ***** \n");
	}
	
	if ((images->timeImageLoadSP*2 > images->maxTimeImageLoadSP) || images->newImage)
	{
		if (ShowImage)
		{
			int xxmax = 0;

			if (images->newImage)
			{
				xxmax = 3;
				images->firstPass = true;
			}
			for (int xx = 0; xx < xxmax; xx++)
			{
				//printf("\n Starting pause random xxxxxxx \n");
				int i;
				for (i = 0; i < Species.numspecies; i++)
				{
					//std::cout << "ID" << i << " before locked alive:  " << Species.speciesarray[i].lifelist->activeLifeCount << std::endl;
					//****************
					int status;
					//SDL_mutex *mutex;
					//mutex = SDL_CreateMutex();
					//if (!mutex) {
						//fprintf(stderr, "Couldn't create mutex\n");
						//return;
					//}*/

					status = SDL_TryLockMutex(Species.speciesarray[i].lock);
					int xxx = 0;
					while (status != 0)
					{
						xxx++;
						if (xxx > 2)
						{
							fprintf(stderr, " TRYING to unlock Mutex\n ");
							SDL_UnlockMutex(Species.speciesarray[i].lock);
						}
						if (status == SDL_MUTEX_TIMEDOUT)
						{
							fprintf(stderr, " Mutex not available for locking right now BAD BAD BAD BAD BAD\n ");
						}
						else
						{
							fprintf(stderr, "Couldn't lock mutex\n BAD BAD BAD BAD BAD BAD BAD");
						}
						Sleep(100);
						fprintf(stderr, " stuck sleepoing ");
						status = SDL_TryLockMutex(Species.speciesarray[i].lock);
					}

					//if (status == 0) 
					//{
					//	//printf("UNLocked mutex ready\n");
					//	SDL_UnlockMutex(Species.speciesarray[i].lock);
					//}
					//else if (status == SDL_MUTEX_TIMEDOUT) {
					//	fprintf(stderr, " Mutex not available for locking right now BAD BAD BAD BAD BAD\n " );
					//}
					//else {
					//	fprintf(stderr, "Couldn't lock mutex\n BAD BAD BAD BAD BAD BAD BAD");
					//}
					//SDL_DestroyMutex(mutex);
					//********
					//if (SDL_LockMutex(Species.speciesarray[i].lock) != 0)
					//{
					//	std::cout << "error:" << SDL_GetError() << ": BAD BAD BAD BAD BAD" << std::endl;
					//	//printf("test:", SDL_GetError(), ":test: %s\n");
					//}
					Species.speciesarray[i].sdlCondition = SDL_TRUE;
					Species.speciesarray[i].spLocked = true;
					//std::cout << "ID" << i << " after locked alive:  " << Species.speciesarray[i].lifelist->activeLifeCount << std::endl;
					//Sleep(50);
				}
				for (i = 0; i < Species.numspecies; i++)
				{

					while (Species.speciesarray[i].spLockedPaused != true)
					{
						//std::cout << "ID" << i << " still alive " << Species.speciesarray[i].lifelist->activeLifeCount << std::endl;
						Sleep(150);
					}
				}
				// std::cout << " about to set species  " << std::endl;
				Species.speciesarray[0].rainbow->SetSpecies(images);
				//gblRainbow->SetSpecies(images);
				//printf("\n after set species \n");

				//Sleep(500);
				//void  Rainbow::SetSpecies(ImageToDisplay* imageIn)
				for (i = 0; i < Species.numspecies; i++)
				{
					Species.speciesarray[i].lifelist->goFirst();
					//Sleep(50);
					Species.speciesarray[i].sdlCondition = SDL_FALSE;
					SDL_CondSignal(Species.speciesarray[i].cond);
					SDL_UnlockMutex(Species.speciesarray[i].lock);
				}
				// printf(" freeing  pause randon yyy  \n");

				//Sleep(500);
				//std::cout << " about to show screen " << std::endl;
		
				images->maxTimeImageLoadSP = MAXTIMEIMAGELOADSP; // randomRange(MAXTIMEIMAGELOADSP);

				glBindVertexArray(plane.vboID);
				glBindBuffer(GL_ARRAY_BUFFER, plane.vertexBuffer);
				plane.ptr = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
				glUnmapBuffer(GL_ARRAY_BUFFER);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				DisplayGL();
				SDL_GL_SwapWindow(mainwindow);
				images->firstPass = false;

			}
			images->newImage = false;
			//baseColorLocked = false;
		}
		images->timeImageLoadSP = 0;
	}


	for (int ii = 0; ii < Species.numspecies; ii++)
	{
		Species.speciesarray[ii].data.timeAlive++;
		if ((Species.speciesarray[ii].data.timeAlive >= Species.speciesarray[ii].data.timeTillMutate) & !ShowImage)
		{
			//std::cout << " Species " << ii << " mutatsed after " << Species.speciesarray[ii].timeTillMutate << " secs " << Species.speciesarray[ii].lifelist->activeLifeCount << " alive " << " FPS " << g_fps << std::endl;
			Species.speciesarray[ii].ChangeSpecies = TRUE;
			//Species.speciesarray[i].timeAlive = 0;
		}
	}
	if (images->timeTillImageChange > images->maxTimeTillImageChange)
	{
		if (IMAGEACTIVE)     images->nextImageLoad();
		//images->timeTillImageChange = images->timeTillImageChange/2 + randomRange(images->maxTimeTillImageChange/2);
		images->maxTimeTillImageChange = MaxTimeTillImageChange / 2 + randomRange(MaxTimeTillImageChange / 2);
		images->timeTillImageChange = 0;
	}
	// std::cout << " xx species 0 will mutate in " << (Species.speciesarray[0].timeTillMutate - Species.speciesarray[0].timeAlive) << " secs " << " FPS " << g_fps << std::endl;
	//if ((randomRange(1000) < 10))
	//{
	//	if (plane.shape == PLANE)
	//	{
	//		plane.shapeNext = SPHERE;
	//		plane.changeshape = TRUE;
	//		plane.rotatex = randomRange(5) - 2;
	//		plane.rotatey = randomRange(5) - 2;
	//	}
	//	else
	//	{
	//		plane.shapeNext = PLANE;
	//		plane.changeshape = TRUE;
	//		plane.rotatex = 0;
	//		plane.rotatey = 0;
	//	}	
	//	ChageShape();
	//}
	//if (randomRange(100) < 20)
	//{
	//	if ((plane.shape == PLANE) )
	//	{
	//		//		KeyboardGL('r', 1, 1);
	//		plane.rotatex = 0;
	//		plane.rotatey = 0;
	//	}
	//	else
	//	{
	//		plane.rotatex = randomRange(5) - 2;
	//		plane.rotatey = randomRange(5) - 2;
	//	}
	//}
	//for (size_t i = 0; i < Species.numspecies; i++)
	//{
	//	//ResumeThread(Species.speciesarray[i].handle);
	//	if (Species.speciesarray[i].lifelist->activeLifeCount == Species.speciesarray[i].lifelist->preActiveLifeCount)
	//	{
	//		std::cout << " Species " << i << " NO CHANGE " << Species.speciesarray[i].lifelist->activeLifeCount << std::endl;
	//		Species.speciesarray[i].lifelist->preActiveLifeCount = Species.speciesarray[i].lifelist->activeLifeCount;
	//	}
	//}	
	//if ((g_fps > 50))
	//{
	//	if (g_fps > 100) numtoprocess = int((double)numtoprocess * 1.3);
	//	else numtoprocess = (int)((float)numtoprocess * 1.1);
	//}
	//else
	//{
	//	if (g_fps < 30)numtoprocess = int((double)numtoprocess * .7);
	//	else numtoprocess = (int)((double)numtoprocess * .9);
	//}
	//std::cout << "ID " << plane->speciesList->currPos->data.SpeciesId << " number alive: "  << plane->speciesList->currPos->lifelist->activeLifeCount << std::endl;
	//	std::cout << " Sp No" << plane->speciesList->currPos->data.SpeciesId << " fps " << g_fps << " num2run " << numtoprocess << " g_numUpdated " << g_numUpdated << " time" << g_timecount << std::endl;
	//if (plane->speciesList->currPos->data.Range > 2)
	//{
	//	std::cout << " ******** " << plane->speciesList->currPos->data.Range << std::endl;
	//}
	//else
	//{
	//	std::cout << std::endl;
	//}
}

// #include "imgui_sdl.h" 



void NextFav()
{
	std::cout << std::endl << "speciesHold->allSavedSpeciesPointer at start: " << speciesHold->allSavedSpeciesPointer << std::endl;
	speciesHold->allSavedSpeciesPointer = speciesHold->allSavedSpeciesPointer + 1;
	// //
	while (!speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].dirActive && (speciesHold->allSavedSpeciesPointer < NUMSAVESPECIES))
	{
		speciesHold->allSavedSpeciesPointer++;
	}

	if (speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].dirActive)
	{
		std::cout << std::endl << " ] move forward loading species number  " << speciesHold->allSavedSpeciesPointer << "file number " << speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].speciesSave.fileNumber << std::endl;
	}
	else
	{
		std::cout << std::endl << "Panic loaded empty specoies or ok now" << std::endl;
		speciesHold->allSavedSpeciesPointer = 0; // set pointer back to start
		//speciesHold->allSavedSpeciesNumActive = speciesHold->allSavedSpeciesPointer; // set the max 
	}
	for (size_t i = 0; i < NUMSPECIES; i++)
	{
		Species.speciesarray[i].data = speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].speciesSave;
		if (plane.shape == SPHERE)
		{
			Species.speciesarray[i].data.heightgrowth = (float)1 / Species.speciesarray[i].data.death;
		}
		else
		{
			Species.speciesarray[i].data.heightgrowth = 0.0;
		}

		if (Species.speciesarray[i].data.showBaseColor)
		{
			Species.speciesarray[i].data.baseColorRed = randomRange(256);
			Species.speciesarray[i].data.baseColorGreen = randomRange(256);
			Species.speciesarray[i].data.baseColorBlue = randomRange(256);
			int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
			if ((zzz > 650) || (zzz < 118))
			{
				Species.speciesarray[i].data.baseColorRed = randomRange(256);
				Species.speciesarray[i].data.baseColorGreen = randomRange(256);
				Species.speciesarray[i].data.baseColorBlue = randomRange(256);
			}
		}
	}

	//allSavedSpeciesNumActive
	//speciesHold->allSavedSpeciesPointer++;
	speciesptr->SpeciesLockSelected = true;
	speciesptr->speciesLockedToNum = 1;
}

int main(int argc, char* argv[])


{
	
	const auto processor_count = std::thread::hardware_concurrency();
//	const int NUMSPECIES = processor_count-1;
	speciesHold = new SpeciesMgmnt;
	const char* SDL_GetError(void);
	srand(time(NULL));
	images = new ImageToDisplay;
	images->Init(NUMCOL, NUMROW);
	images->GetImages();
	images->nextImageLoad();
	images->nextImageLoad();
	int lastTime = 0;// currentTime;
	int currentTime = 0;
	bool quit = false;
	g_iWindowWidth = NUMCOL;
	g_iWindowHeight = NUMROW;
	ReshapeGL(g_iWindowWidth, g_iWindowHeight);
	SDL_Event event;
	plane.shape = PLANE;
	plane.maxTimeToMutate = MAXMUTATETIME;
	g_A = g_W = g_S = g_D = g_Q = g_E = 0;
	g_InitialCameraPosition = glm::vec3(0, 0, 13.845);
	g_Camera.SetPosition(g_InitialCameraPosition);
	g_Camera.SetRotation(g_InitialCameraRotation);
	InitGL(argc, argv);

	glShadeModel(GL_SMOOTH);
	shader = new Shader(1, 1, 1);
	planeptr = new Plane(NUMCOL, NUMROW, FALSE);
	planeptr->initVBO(shader);
	plane.gblPlanePtr = planeptr;
	glBindVertexArray(plane.vboID);
	glBindBuffer(GL_ARRAY_BUFFER, plane.vertexBuffer);
	plane.ptr = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	speciesptr = new SpeciesList;
	speciesptr->speciesWork = speciesHold;

// file testing end
	for (int i = 0; i < Species.maxSpecies; i++)
	 {
		Species.speciesarray[i].data.baseColorBlue = randomRange(256);
		Species.speciesarray[i].data.baseColorRed = randomRange(256);
		Species.speciesarray[i].data.baseColorGreen = randomRange(256);
		Species.speciesarray[i].handle = SDL_CreateThread(SpeciesProc, "SpeciesThread", (void*)i);
		Species.speciesarray[i].lock = SDL_CreateMutex();
		Species.speciesarray[i].cond = SDL_CreateCond();
		Sleep(10); 
	 }
	speciesHold->LoadAll(false);
	speciesptr->randomSpeciesFromFavs = false;
	while (!quit){
		//  Increase frame count
		g_frameCount++;
		glBindVertexArray(plane.vboID);
		glBindBuffer(GL_ARRAY_BUFFER, plane.vertexBuffer);
		plane.ptr = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 1000) //once per sec update
		{
			PerCycleCalcs();
			lastTime = currentTime;
			g_frameCount = 0;
		}

		if (plane.shape == SPHERE)
		{
			//glm::quat rotX = glm::angleAxis<float>(glm::radians((float)plane->rotatex) * 0.2f, glm::vec3(1, 0, 0));
			//glm::quat rotY = glm::angleAxis<float>(glm::radians((float)plane->rotatey) * 0.2f, glm::vec3(0, 1, 0));
			glm::quat rotX = glm::angleAxis<float>(glm::radians((float)plane.rotatex) * (0.1f ), glm::vec3(1, 0, 0));
			glm::quat rotY = glm::angleAxis<float>(glm::radians((float)plane.rotatey) * (0.1f ), glm::vec3(0, 1, 0));

			//glm::quat rotX = glm::angleAxis<float>(glm::radians((float)plane.rotatex) * (0.1f * (g_fps / 50.0f)), glm::vec3(1, 0, 0));
			//glm::quat rotY = glm::angleAxis<float>(glm::radians((float)plane.rotatey) * (0.1f * (g_fps / 50.0f)), glm::vec3(0, 1, 0));
			g_Rotation = (rotX * rotY) * g_Rotation;
		}
		else
		{
			g_Camera.SetPosition(g_InitialCameraPosition);
			g_Camera.SetRotation(g_InitialCameraRotation);
			g_Rotation = glm::quat();
		}
		//Display();
		DisplayGL();
		//if (*SDL_GetError() != *"")
		//{
		//	std::cout << "error:" << SDL_GetError() << ":" << std::endl;
		//	//printf("test:", SDL_GetError(), ":test: %s\n");
		//}
		//char* testit2 = "";
		SDL_GL_SwapWindow(mainwindow);
		//testit = SDL_GetError();
		//if (*SDL_GetError() != *"")
		//{
		//	std::cout << "error:" << SDL_GetError() <<  ":" << std::endl;
		//	//printf("test:", SDL_GetError(), ":test: %s\n");
		//}

	



		while (SDL_PollEvent(&event)){
			//if (*SDL_GetError() != *"")
			//{
			//	std::cout << "error:" << SDL_GetError() << ":" << std::endl;
			//	//printf("test:", SDL_GetError(), ":test: %s\n");
			//}
			if (event.type == SDL_QUIT){
				quit = true;
			}
			// ******
			int x = 0;
			bool tempbool = false;
			switch (event.type)
			{
				/* Look for a keypress */
			case SDL_KEYDOWN:
				/* Check the SDLKey values and move change the coords */
				switch (event.key.keysym.sym)
				{

				case SDLK_p:
					speciesptr->speciesWork->printScreen(mainwindow);
					break;


				case SDLK_h:
					SingleCenterSeed = !SingleCenterSeed;
					break;



				case SDLK_k:
					speciesHold->ReloadSpeciesfromDisk();
					break;

				case SDLK_u:
					DUPESPECIES = !DUPESPECIES;
					break;

				case SDLK_o:
					speciesptr->nextSpeciesFromFavs = !speciesptr->nextSpeciesFromFavs;
					break;

				case SDLK_g:
					if (ActivateImgSpecNum == false)
					{
						ActivateImgSpecNum = true;
					}
					else
					{
						ActivateImgSpecNum = false;
					}
					std::cout << "ActivateImgSpecNum " << ActivateImgSpecNum << std::endl;
					break;

				case SDLK_c:
					plane.gblPlanePtr->clearDead();
					break;

				case SDLK_l:
					Species.baseColorLocked = true;
					for (int i = 0; i < NUMSPECIES; i++)
					{
						Species.speciesarray[i].data.showBaseColor = true;
						Species.speciesarray[i].data.baseColorRed = randomRange(256);
						Species.speciesarray[i].data.baseColorGreen = randomRange(256);
						Species.speciesarray[i].data.baseColorBlue = randomRange(256);
					}
					break;
				case SDLK_n:
					Species.rainBowLocked = false;
					Species.baseColorLocked = false;
					//speciesptr->randomSpeciesFromFavs = false;
					speciesptr->SpeciesLockSelected = false;
					g_changeSpecies = true;
					if ((DUPESPECIES) || (speciesptr->randomSpeciesFromFavs == true))
					{
						if (DUPESPECIES)
						{
							Species.speciesarray[0].ChangeSpecies = TRUE;
							Sleep(500);
							for (size_t i = 1; i < NUMSPECIES; i++)
							{
								Species.speciesarray[i].ChangeSpecies = TRUE;
							}
						}
						else
						{
							int SpeciesToLoad = 0;
							for (size_t i = 1; i < NUMSPECIES; i++)
							{
								SpeciesToLoad = randomRange(NUMSAVESPECIES);
								Species.speciesarray[i].data = speciesptr->speciesWork->speciesTmpSave[SpeciesToLoad];
								Species.speciesarray[i].data.timeAlive = 0;
								Species.speciesarray[i].data.timeTillMutate = randomRange(plane.maxTimeToMutate);  //(plane.maxTimeToMutate / 2) + randomRange(plane.maxTimeToMutate / 2);
								std::cout << "ID " << Species.speciesarray[i].SpeciesId << "(randomSpeciesFromFavs) " << SpeciesToLoad << std::endl;
							}
						}
					}
					else
					{
						for (size_t i = 0; i < NUMSPECIES; i++)
						{
							Species.speciesarray[i].ChangeSpecies = TRUE;
						}
					}
					plane.gblPlanePtr->clearDead();
					break;
				case SDLK_r:
					Species.rainBowLocked = true;
					for (size_t i = 0; i < NUMSPECIES; i++)
					{
						Species.speciesarray[i].data.RainbowOn = TRUE;
					}
					break;



				case SDLK_b:
					gblBlackDeath = !gblBlackDeath;
					for (size_t i = 0; i < NUMSPECIES; i++)
					{
						Species.speciesarray[i].data.BlackDeath = gblBlackDeath;
					}
					break;

				case SDLK_d:

					tempbool = gblBlackDeath;
					gblBlackDeath = true;
					for (size_t i = 0; i < NUMSPECIES; i++)
					{
						Species.speciesarray[i].killUsAll = TRUE;
					}
					Sleep(150);
					plane.gblPlanePtr->clearDead();
					gblBlackDeath = tempbool;
					break;

				case SDLK_t:
					//if (Species.speciesarray[0].data.showBaseColor)
					{
						for (int i = 0; i < Species.numspecies; i++)
						{
							Species.speciesarray[i].data.baseColorRed = randomRange(256);
							Species.speciesarray[i].data.baseColorGreen = randomRange(256);
							Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
							if ((zzz > 650) || (zzz < 108))
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							}
						}
					}
					printf("\n Starting pause xxxxxxx \n");
					for (int i = 0; i < Species.numspecies; i++)
					{
						SDL_LockMutex(Species.speciesarray[i].lock);
						Species.speciesarray[i].sdlCondition = SDL_TRUE;
						Species.speciesarray[i].spLocked = true;
						Sleep(50);
					}
					Species.speciesarray[0].rainbow->SetSpecies(images);
					//gblRainbow->SetSpecies(images);
					images->timeImageLoadSP = 0;
					images->maxTimeImageLoadSP = MAXTIMEIMAGELOADSP;// randomRange(MAXTIMEIMAGELOADSP);
					//void  Rainbow::SetSpecies(ImageToDisplay* imageIn)
					for (int i = 0; i < Species.numspecies; i++)
					{
						Species.speciesarray[i].lifelist->goFirst();
						Sleep(50);
						Species.speciesarray[i].sdlCondition = SDL_FALSE;
						SDL_CondSignal(Species.speciesarray[i].cond);
						SDL_UnlockMutex(Species.speciesarray[i].lock);
					}
					printf(" freeing  pause yyy  \n");
					break;
				case SDLK_s: //sphere//
					if (plane.shape == PLANE)
					{
						plane.shapeNext = SPHERE;
						plane.changeshape = TRUE;

						//plane.rotatex = randomRange(3) - 1;
						//plane.rotatey = randomRange(3) - 1;

						plane.rotatex = 0; // randomRange(3) - 1;
						plane.rotatey = 1; // randomRange(3) - 1;
					}
					else
					{
						plane.shapeNext = PLANE;
						plane.changeshape = TRUE;
						plane.rotatex = 0;
						plane.rotatey = 0;
					}
					ChageShape();
					break; 
				case SDLK_i: // next image //
					images->nextImageLoad();
					images->timeTillImageChange = 0;
					break;
				case SDLK_f:  // Full screen//
				case SDLK_ESCAPE:
					int xx;
					if (fullscreenactive)
					{
						xx = SDL_SetWindowFullscreen(mainwindow, 0);
						fullscreenactive = false;
					}
					else
					{
						xx = SDL_SetWindowFullscreen(mainwindow, SDL_WINDOW_FULLSCREEN_DESKTOP); // SDL_WINDOW_FULLSCREEN);
						fullscreenactive = true;
					}
					break;

				case SDLK_z: // save current species to keys 1,2,3 ... 0 //
					for (size_t i = 0; i < NUMSPECIES; i++)
					{
						speciesHold->speciesTmpSave[i] = Species.speciesarray[i].data;
						speciesHold->speciesTmpSave[i].timeAlive = 0;
						speciesHold->speciesTmpSave[i].timeTillMutate = randomRange(plane.maxTimeToMutate); //(plane.maxTimeToMutate / 2) + randomRange(plane.maxTimeToMutate / 2);
					}
					break;


				case SDLK_x: //save species 0 to disk //
					speciesHold->SpeciesSave(0, mainwindow);
					break;

				case SDLK_q: // load first 10 species to keys 1, 2 ...0//
					speciesHold->LoadSpeciesToKeys(true);
					break;

				case SDLK_w: // load last  10 species to keys 1, 2 ...0//
					speciesHold->LoadSpeciesToKeys(false);
					break;

				case SDLK_a: // load from saved species //
					//speciesptr->SpeciesLockSelected = false;
					speciesHold->LoadAll(false);
					speciesptr->randomSpeciesFromFavs = true;
				break;

				case SDLK_j: // Dupe species Loaded from favs //
				//speciesptr->SpeciesLockSelected = false;
					speciesHold->LoadAll(false);
					speciesptr->randomSpeciesFromFavs = true;
					//int x = 0;
					x = randomRange(NUMSAVESPECIES);
					while (!speciesHold->allSavedSpecies[x].dirActive) //&& (speciesHold->allSavedSpeciesPointer < NUMSAVESPECIES))
					{
						//speciesHold->allSavedSpeciesPointer = ;
						x = randomRange(NUMSAVESPECIES);
					}
					//qe
					std::cout << std::endl << " J loaded from random fav  " << x << "file number " << speciesHold->allSavedSpecies[x].speciesSave.fileNumber << std::endl;


					for (size_t i = 0; i < NUMSPECIES; i++)
					{
						Species.speciesarray[i].data = speciesHold->allSavedSpecies[x].speciesSave;
						if (plane.shape == SPHERE)
						{
							Species.speciesarray[i].data.heightgrowth = (float)1 / Species.speciesarray[i].data.death;
						}
						else
						{
							Species.speciesarray[i].data.heightgrowth = 0.0;
						}

						if (Species.speciesarray[i].data.showBaseColor)
						{
							Species.speciesarray[i].data.baseColorRed = randomRange(256);
							Species.speciesarray[i].data.baseColorGreen = randomRange(256);
							Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
							if ((zzz > 650) || (zzz < 118))
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							}
						}
					}
					DUPESPECIES = true;
					break;

				case SDLK_RIGHTBRACKET: //  moves to next species //
					std::cout << std::endl << "speciesHold->allSavedSpeciesPointer at start: " << speciesHold->allSavedSpeciesPointer << std::endl;
					speciesHold->allSavedSpeciesPointer = speciesHold->allSavedSpeciesPointer + 1;
					// //
					while (!speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].dirActive && (speciesHold->allSavedSpeciesPointer < NUMSAVESPECIES))
					{
						speciesHold->allSavedSpeciesPointer++;
					}

					if (speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].dirActive)
					{
						std::cout << std::endl << " ] move forward loading species number  " << speciesHold->allSavedSpeciesPointer << "file number " << speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].speciesSave.fileNumber << std::endl;
					}
					else
					{
						std::cout << std::endl << "Panic loaded empty specoies or ok now"   << std::endl;
						speciesHold->allSavedSpeciesPointer = 0; // set pointer back to start
						//speciesHold->allSavedSpeciesNumActive = speciesHold->allSavedSpeciesPointer; // set the max 
					}


#define PROGRAM_NAME "The Art of Self Organization 1400X1400 species 4  max age 100 random species num moved FORWARD  " 

					SDL_SetWindowTitle(mainwindow, PROGRAM_NAME);

					for (size_t i = 0; i < NUMSPECIES; i++)
					{
						Species.speciesarray[i].data = speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].speciesSave;
						if (plane.shape == SPHERE)
						{
							Species.speciesarray[i].data.heightgrowth = (float)1 / Species.speciesarray[i].data.death;
						}
						else
						{
							Species.speciesarray[i].data.heightgrowth = 0.0;
						}

						if (Species.speciesarray[i].data.showBaseColor)
						{
							Species.speciesarray[i].data.baseColorRed = randomRange(256);
							Species.speciesarray[i].data.baseColorGreen = randomRange(256);
							Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
							if ((zzz > 650) || (zzz < 118))
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							}
						}
					}

					//allSavedSpeciesNumActive
					//speciesHold->allSavedSpeciesPointer++;
					speciesptr->SpeciesLockSelected = true;
					speciesptr->speciesLockedToNum = 1;
					break;

				case SDLK_LEFTBRACKET: //  moves to prev species //

				//	NextFav();
				//	break;
					if (speciesHold->allSavedSpeciesPointer > 0) speciesHold->allSavedSpeciesPointer--;
					while (!speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].dirActive && (speciesHold->allSavedSpeciesPointer > 0))
					{
						speciesHold->allSavedSpeciesPointer--;
					}

					if (speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].dirActive)
					{
						std::cout << std::endl << " [ move back  loading species number  " << speciesHold->allSavedSpeciesPointer << "file number " << speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].speciesSave.fileNumber << std::endl;
					}
					else
					{
						std::cout << std::endl << "Panic loaded empty specoies or ok now" << std::endl;
						speciesHold->allSavedSpeciesPointer = NUMSAVESPECIES; // set pointer back to end 
						//speciesHold->allSavedSpeciesNumActive = speciesHold->allSavedSpeciesPointer; // set the max 
					}

#define PROGRAM_NAME "The Art of Self Organization 1400X1400 species 4  max age 100 random species num moved back " 

					SDL_SetWindowTitle(mainwindow,PROGRAM_NAME);


					for (size_t i = 0; i < NUMSPECIES; i++)
					{
						Species.speciesarray[i].data = speciesHold->allSavedSpecies[speciesHold->allSavedSpeciesPointer].speciesSave;
						if (plane.shape == SPHERE)
						{
							Species.speciesarray[i].data.heightgrowth = (float)1 / Species.speciesarray[i].data.death;
						}
						else
						{
							Species.speciesarray[i].data.heightgrowth = 0.0;
						}

						if (Species.speciesarray[i].data.showBaseColor)
						{
							Species.speciesarray[i].data.baseColorRed = randomRange(256);
							Species.speciesarray[i].data.baseColorGreen = randomRange(256);
							Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
							if ((zzz > 650) || (zzz < 118))
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							}
						}
					}

					//allSavedSpeciesNumActive
					//speciesHold->allSavedSpeciesPointer--;
					speciesptr->SpeciesLockSelected = true;
					speciesptr->speciesLockedToNum = 1;
					break;

					//


				case SDLK_e: // load from images //
					IMAGEACTIVE = !IMAGEACTIVE;
					ShowImage = !ShowImage;
					break;


				case SDLK_m: // mirror //
					Species.reflection = !Species.reflection;
					break;


				case SDLK_1:

					for (size_t i = 0; i < NUMSPECIES; i++)
					{ 
						Species.speciesarray[i].data = speciesHold->speciesTmpSave[0];
						if (Species.speciesarray[0].data.showBaseColor)
						{
							Species.speciesarray[i].data.baseColorRed = randomRange(256);
							Species.speciesarray[i].data.baseColorGreen = randomRange(256);
							Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
							if ((zzz > 650) || (zzz < 118))
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							}
						 }					
					}
					speciesptr->SpeciesLockSelected = true;
					speciesptr->speciesLockedToNum = 0;
					break;

				case SDLK_2:
					//if (NUMSPECIES >= 2)
					{
						for (size_t i = 0; i < NUMSPECIES; i++)
						{
							Species.speciesarray[i].data = speciesHold->speciesTmpSave[1];
							if (Species.speciesarray[1].data.showBaseColor)
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
								if ((zzz > 650) || (zzz < 118))
								{
									Species.speciesarray[i].data.baseColorRed = randomRange(256);
									Species.speciesarray[i].data.baseColorGreen = randomRange(256);
									Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								}
							}
						}
						speciesptr->SpeciesLockSelected = true;
						speciesptr->speciesLockedToNum = 1;
					}
					break;

				case SDLK_3:

					//if (NUMSPECIES >= 3)
					{
						for (size_t i = 0; i < NUMSPECIES; i++)
						{
							Species.speciesarray[i].data = speciesHold->speciesTmpSave[2];
							if (Species.speciesarray[2].data.showBaseColor)
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
								if ((zzz > 650) || (zzz < 118))
								{
									Species.speciesarray[i].data.baseColorRed = randomRange(256);
									Species.speciesarray[i].data.baseColorGreen = randomRange(256);
									Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								}
							}
						}
						speciesptr->SpeciesLockSelected = true;
						speciesptr->speciesLockedToNum = 2;
					}
					break;
				case SDLK_4:

					//if (NUMSPECIES >= 4)
					{
						for (size_t i = 0; i < NUMSPECIES; i++)
						{
							Species.speciesarray[i].data = speciesHold->speciesTmpSave[3];
							if (Species.speciesarray[3].data.showBaseColor)
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
								if ((zzz > 650) || (zzz < 118))
								{
									Species.speciesarray[i].data.baseColorRed = randomRange(256);
									Species.speciesarray[i].data.baseColorGreen = randomRange(256);
									Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								}
							}
						}
						speciesptr->SpeciesLockSelected = true;
						speciesptr->speciesLockedToNum = 3;
					}
					break;
				case SDLK_5:
					//if (NUMSPECIES >= 5)
					{
						for (size_t i = 0; i < NUMSPECIES; i++)
						{
							Species.speciesarray[i].data = speciesHold->speciesTmpSave[4];
							if (Species.speciesarray[4].data.showBaseColor)
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
								if ((zzz > 650) || (zzz < 118))
								{
									Species.speciesarray[i].data.baseColorRed = randomRange(256);
									Species.speciesarray[i].data.baseColorGreen = randomRange(256);
									Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								}
							}
						}
						speciesptr->SpeciesLockSelected = true;
						speciesptr->speciesLockedToNum = 4;
					}
					break;
				case SDLK_6:

					//if (NUMSPECIES >= 6)
					for (size_t i = 0; i < NUMSPECIES; i++)
					{
						Species.speciesarray[i].data = speciesHold->speciesTmpSave[5];
						if (Species.speciesarray[5].data.showBaseColor)
						{
							Species.speciesarray[i].data.baseColorRed = randomRange(256);
							Species.speciesarray[i].data.baseColorGreen = randomRange(256);
							Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
							if ((zzz > 650) || (zzz < 118))
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
							}
						}
					}
					speciesptr->SpeciesLockSelected = true;
					speciesptr->speciesLockedToNum = 5;
					break;
				case SDLK_7:

					//if (NUMSPECIES >= 7)
					{
						for (size_t i = 0; i < NUMSPECIES; i++)
						{
							Species.speciesarray[i].data = speciesHold->speciesTmpSave[6];
							if (Species.speciesarray[6].data.showBaseColor)
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
								if ((zzz > 650) || (zzz < 118))
								{
									Species.speciesarray[i].data.baseColorRed = randomRange(256);
									Species.speciesarray[i].data.baseColorGreen = randomRange(256);
									Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								}
							}
						}
						speciesptr->SpeciesLockSelected = true;
						speciesptr->speciesLockedToNum = 6;
					}
					break;

				case SDLK_8:

					//if (NUMSPECIES >= 8)
					{
						for (size_t i = 0; i < NUMSPECIES; i++)
						{
							Species.speciesarray[i].data = speciesHold->speciesTmpSave[7];
							if (Species.speciesarray[7].data.showBaseColor)
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
								if ((zzz > 650) || (zzz < 118))
								{
									Species.speciesarray[i].data.baseColorRed = randomRange(256);
									Species.speciesarray[i].data.baseColorGreen = randomRange(256);
									Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								}
							}
						}
						speciesptr->SpeciesLockSelected = true;
						speciesptr->speciesLockedToNum = 7;
					}
					break;

				case SDLK_9:

					//if (NUMSPECIES >= 9)
					{
						for (size_t i = 0; i < NUMSPECIES; i++)
						{
							Species.speciesarray[i].data = speciesHold->speciesTmpSave[8];
							if (Species.speciesarray[8].data.showBaseColor)
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
								if ((zzz > 650) || (zzz < 118))
								{
									Species.speciesarray[i].data.baseColorRed = randomRange(256);
									Species.speciesarray[i].data.baseColorGreen = randomRange(256);
									Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								}
							}
						}
						speciesptr->SpeciesLockSelected = true;
						speciesptr->speciesLockedToNum = 8;
					}
					break;

				case SDLK_0:

					//if (NUMSPECIES >= 10)
					{
						for (size_t i = 0; i < 10; i++)
						{
							Species.speciesarray[i].data = speciesHold->speciesTmpSave[9];
							if (Species.speciesarray[9].data.showBaseColor)
							{
								Species.speciesarray[i].data.baseColorRed = randomRange(256);
								Species.speciesarray[i].data.baseColorGreen = randomRange(256);
								Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								int zzz = Species.speciesarray[i].data.baseColorRed + Species.speciesarray[i].data.baseColorGreen + Species.speciesarray[i].data.baseColorBlue;
								if ((zzz > 650) || (zzz < 118))
								{
									Species.speciesarray[i].data.baseColorRed = randomRange(256);
									Species.speciesarray[i].data.baseColorGreen = randomRange(256);
									Species.speciesarray[i].data.baseColorBlue = randomRange(256);
								}
							}
						}
						speciesptr->SpeciesLockSelected = true;
						speciesptr->speciesLockedToNum = 9;
					}
					break;
				default:
					break;
				}
			//	break;
			//default:
			//	//std::cout << " event.type:" << event.type << ":" << std::endl;
			//	break;
			}
			// std::cout << " event.type:" << event.type << ":" << std::endl;
			// *******
			if (event.type == SDL_WINDOWEVENT){
				//if (event.window.event = SDL_WINDOWEVENT_SIZE_CHANGED){
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
					int w, h;
					SDL_GetWindowSize(mainwindow, &w, &h);

					int tmp = w % 4;
					if (tmp != 0)
					{
						w = w - tmp;
						SDL_SetWindowSize(mainwindow, w, h);
					}
					ReshapeGL(w, h);
					//reshape
				}
			}
		}
		//if (*SDL_GetError() != *"")
		//{
		//	std::cout << "error:" << SDL_GetError() << ":" << std::endl;
		//	//printf("test:", SDL_GetError(), ":test: %s\n");
		//}
	}
	/* Delete our opengl context, destroy our window, and shutdown SDL */
	if (*SDL_GetError() != *"")
	{
		std::cout << "error:" << SDL_GetError() << ":" << std::endl;
		//printf("test:", SDL_GetError(), ":test: %s\n");
	}
	else
	{
		std::cout << "BAD error:" << SDL_GetError() << ":" << std::endl;
		
	}
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();
	return 0;

}