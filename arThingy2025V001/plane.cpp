//x is latitude is column
//y is longitide is row
#include "main.h"

void  Plane::CreateReflect(CELLLOC LOCin, int currSpecies) // suposed to drop copies in 3 other quadrants - broken
{
//	COLORSTRUCT tmpCol;
	PLOCSTRUCT tmpData;
	CELLLOC tmploc;
	tmpData = plane.pData[LOCin.xLoc][LOCin.yLoc];//  lifeList->workCell->cData.Col;
	int tmpx = LOCin.xLoc;
	int tmpy = LOCin.yLoc;

	if (tmpx < (plane.numCol / 2))
	{
		if (plane.pData[tmpx + ((plane.numCol) / 2)][tmpy].Alive == FALSE)
		{
			tmploc.xLoc = (tmpx + (plane.numCol / 2));
			tmploc.yLoc = tmpy;
			
			
			//speciesList->currPos->lifelist->workCell = tmploc;
			plane.pData[tmploc.xLoc][tmploc.yLoc].Age = 0; 
			plane.pData[tmploc.xLoc][tmploc.yLoc].AgeDecade = 0; 
			plane.pData[tmploc.xLoc][tmploc.yLoc].avgColor = plane.pData[LOCin.xLoc][LOCin.yLoc].Col;
			plane.pData[tmploc.xLoc][tmploc.yLoc].Col = plane.pData[LOCin.xLoc][LOCin.yLoc].Col;
			plane.pData[tmploc.xLoc][tmploc.yLoc].numMateAtmps = 0;
			plane.pData[tmploc.xLoc][tmploc.yLoc].speciedNum = currSpecies;
			//plane.pData[tmploc.xLoc][tmploc.yLoc].surrounded = FALSE;
			plane.pData[tmploc.xLoc][tmploc.yLoc].Alive = plane.pData[LOCin.xLoc][LOCin.yLoc].Alive;
			//plane.pData[tmploc.xLoc][tmploc.yLoc].Alive = plane.pData[LOCin.xLoc][LOCin.yLoc].Alive;
			Species.speciesarray[currSpecies].lifelist->addNew(tmploc, currSpecies);
			showCol(tmploc, currSpecies);
		}
	}
	else
	{
		if (plane.pData[plane.numCol - tmpx][tmpy].Alive == FALSE)
		{
			tmploc.xLoc = plane.numCol - tmpx;
			tmploc.yLoc = tmpy;
			plane.pData[tmploc.xLoc][tmploc.yLoc].Age = 0;
			plane.pData[tmploc.xLoc][tmploc.yLoc].AgeDecade = 0;
			plane.pData[tmploc.xLoc][tmploc.yLoc].avgColor = plane.pData[LOCin.xLoc][LOCin.yLoc].Col;
			plane.pData[tmploc.xLoc][tmploc.yLoc].Col = plane.pData[LOCin.xLoc][LOCin.yLoc].Col;
			plane.pData[tmploc.xLoc][tmploc.yLoc].numMateAtmps = 0;
			plane.pData[tmploc.xLoc][tmploc.yLoc].speciedNum = currSpecies;
			//plane.pData[tmploc.xLoc][tmploc.yLoc].surrounded = FALSE;
			plane.pData[tmploc.xLoc][tmploc.yLoc].Alive = plane.pData[LOCin.xLoc][LOCin.yLoc].Alive;
			Species.speciesarray[currSpecies].lifelist->addNew(tmploc, currSpecies);
			showCol(tmploc, currSpecies);
		}
	}
	if (tmpy <(plane.numRow / 2))
	{
		if (plane.pData[tmpx][tmpy + (plane.numRow / 2)].Alive == FALSE)
		{
			tmploc.xLoc = tmpx ;
			tmploc.yLoc = tmpy + (plane.numRow / 2);
			plane.pData[tmploc.xLoc][tmploc.yLoc].Age = 0;
			plane.pData[tmploc.xLoc][tmploc.yLoc].AgeDecade = 0;
			plane.pData[tmploc.xLoc][tmploc.yLoc].avgColor = plane.pData[LOCin.xLoc][LOCin.yLoc].Col;
			plane.pData[tmploc.xLoc][tmploc.yLoc].Col = plane.pData[LOCin.xLoc][LOCin.yLoc].Col;
			plane.pData[tmploc.xLoc][tmploc.yLoc].numMateAtmps = 0;
			plane.pData[tmploc.xLoc][tmploc.yLoc].speciedNum = currSpecies;
			//plane.pData[tmploc.xLoc][tmploc.yLoc].surrounded = FALSE;
			plane.pData[tmploc.xLoc][tmploc.yLoc].Alive = plane.pData[LOCin.xLoc][LOCin.yLoc].Alive;
			Species.speciesarray[currSpecies].lifelist->addNew(tmploc, currSpecies);
			showCol(tmploc, currSpecies);
		}
	}
	else
	{
		if (plane.pData[tmpx][plane.numRow - tmpy].Alive == FALSE)
		{
			
			tmploc.xLoc = tmpx;
			tmploc.yLoc = plane.numRow - tmpy;
			plane.pData[tmploc.xLoc][tmploc.yLoc].Age = 0;
			plane.pData[tmploc.xLoc][tmploc.yLoc].AgeDecade = 0;
			plane.pData[tmploc.xLoc][tmploc.yLoc].avgColor = plane.pData[LOCin.xLoc][LOCin.yLoc].Col;
			plane.pData[tmploc.xLoc][tmploc.yLoc].Col =  plane.pData[LOCin.xLoc][LOCin.yLoc].Col;
			plane.pData[tmploc.xLoc][tmploc.yLoc].numMateAtmps = 0;
			plane.pData[tmploc.xLoc][tmploc.yLoc].speciedNum = currSpecies;
			//plane.pData[tmploc.xLoc][tmploc.yLoc].surrounded = FALSE;
			plane.pData[tmploc.xLoc][tmploc.yLoc].Alive = plane.pData[LOCin.xLoc][LOCin.yLoc].Alive;
			Species.speciesarray[currSpecies].lifelist->addNew(tmploc, currSpecies);
			showCol(tmploc, currSpecies);
		}
	}
}

void Plane::buildGrid(int numCol, int numRow, bool EdgeConnectin)
{
	int i = 0;
	float z = 0;
	plane.EdgeConnect = EdgeConnectin;
	for (int y = 0; y < numRow; y++)
	{
		for (int x = 0; x < numCol; x++)
		{
			plane.verts[i].location[X_POS] = (((GLfloat)x * 16 / (GLfloat)numCol)) - 8;
			plane.verts[i].location[Y_POS] = (((GLfloat)y * 16 / (GLfloat)numRow)) - 8;
			plane.verts[i].location[Z_POS] = 0;
			plane.verts[i].colour[R_POS] = 0.0;
			plane.verts[i].colour[G_POS] = 0.0;
			plane.verts[i].colour[B_POS] = 0.0;
			plane.verts[i].colour[A_POS] = 0.0;
			i++;
		}
	}

	//}

	// Index Array (define our triangles)
	//  The plane looks like this for a 3/3
	//  6      7      8
	//  +------+------+
	//  |      |      |
	//  |      |      |
	//3 +------+------+5
	//  |      |      |
	//  |      |      |
	//  +------+------+
	//  0      1      2
	// w width
	//int w = numCol; // the width of the square
	int idx = 0;

	for (int y = 0; y < numRow; y++)
	{
		for (int x = 0; x < numCol; x++)
		{
			if ((x < (numCol - 1)) && (y < (numRow - 1)))
			{
				// create the two triangle that form this square
				plane.index[idx] = (GLuint)(x + (y*numRow)); plane.index[idx + 1] = (GLuint)(x + 1 + (y*numRow)); plane.index[idx + 2] = (GLuint)(x + 1 + (y + 1)*numRow);
				idx = idx + 3;
				plane.index[idx] = (GLuint)(x + (y*numRow)); plane.index[idx + 1] = (GLuint)(x + 1 + (y + 1)*numRow); plane.index[idx + 2] = (GLuint)(x + (y + 1)*numRow);
				idx = idx + 3;
			}
		}
	}
	plane.numPlaneIDX = idx;
	for (int y = 0; y<numRow; y++)
	{
		for (int x = 0; x < numCol; x++)
		{
			if ((x == (numCol - 1)) || (y == (numRow - 1)))
			if ((x == numCol - 1) && (y != numRow - 1))   // we are at the end of an X row so we add tiangles to X start ( 0 )
			{
				plane.index[idx] = (GLuint)(x + (y*numRow)); plane.index[idx + 1] = (GLuint)(0 + (y*numRow)); plane.index[idx + 2] = (GLuint)(0 + (y + 1)*numRow);
				idx = idx + 3;
				plane.index[idx] = (GLuint)(x + (y*numRow)); plane.index[idx + 1] = (GLuint)(0 + (y + 1)*numRow); plane.index[idx + 2] = (GLuint)(x + (y + 1)*numRow);
				idx = idx + 3;
			}
			else 
			if (x != numCol - 1) // we are at the end of Y so add triangles to start Y ( 0 )
			{
				plane.index[idx] = (GLuint)(x + (y*numRow)); plane.index[idx + 1] = (GLuint)(x + 1 + (y*numRow)); plane.index[idx + 2] = (GLuint)(x + 1 + (0)*numRow);
				idx = idx + 3;
				plane.index[idx] = (GLuint)(x + (y*numRow)); plane.index[idx + 1] = (GLuint)(x + 1 + (0)*numRow); plane.index[idx + 2] = (GLuint)(x + (0)*numRow);
				idx = idx + 3;
			}
			else // we at corner
			{
				fprintf(stderr, "Error:  or maby just fix \n");
				plane.index[idx] = (GLuint)(x + (y*numRow)); plane.index[idx + 1] = (GLuint)(0 + (y*numRow)); plane.index[idx + 2] = (GLuint)(0 + (0)*numRow);
				idx = idx + 3;
				plane.index[idx] = (GLuint)(x + (y*numRow)); plane.index[idx + 1] = (GLuint)(0 + (0)*numRow); plane.index[idx + 2] = (GLuint)(x + (0)*numRow);
				idx = idx + 3;
			}
		}
	}
	plane.numSphereIDX = idx;
}

bool Plane::ColorAndNumAroundOK(CELLLOC in, int range, int maxNum, int maxColor ) //, int currSpecies)
{
	//int xxxTotalCells = 0;
	int i, j = 0;
	int num = 0;
	int tot = 0;
	int red, green, blue;
	int rTot = 0, gTot=0, bTot = 0, colorCount = 0;
	int currspecies; 
	currspecies = plane.pData[in.xLoc][in.yLoc].speciedNum;
	red = plane.pData[in.xLoc][in.yLoc].Col.r;
	green = plane.pData[in.xLoc][in.yLoc].Col.g;
	blue = plane.pData[in.xLoc][in.yLoc].Col.b;
	bool fastVersion = true;
	int maxX = in.xLoc + range; int minX = in.xLoc - range; int maxY = in.yLoc + range; int minY = in.yLoc - range;
	//bool mateWithOtherSoecies = false;
	//mateWithOtherSoecies = Species.speciesarray[currspecies].data.mateWithOtherSpecies;


	if (maxX >= plane.numCol)
	{ 
		//maxX = plane.numCol - 1; 
		fastVersion = FALSE; 
	}
	else
	if (minX < 0) 
	{/* minX = 0; */  
		fastVersion = FALSE; 
	}
	if (maxY >= plane.numRow) 
	{ /*maxY = plane.numRow - 1; */
		fastVersion = FALSE; 
	}
	else
	if (minY < 0) 
	{ /* minY = 0; */ 
		fastVersion = FALSE; 
	}
	
	int fullcount = 0;
	if (fastVersion)
	{
		for (j = minY; j <= maxY; j++)
			//for (i = minX; i <= maxX; i++)
		
		{
			//for (j = minY; j <= maxY; j++)	
			for (i = minX; i <= maxX; i++)
			{
				//xxxTotalCells++;
				fullcount++;
				if (plane.pData[i][j].Alive == TRUE)
				{
					//if ((currspecies == plane.pData[i][j].speciedNum) || (GTBLCOLORFOBIA) || (GBLNUMAROUND))
					{
						//if ((currspecies == plane.pData[i][j].speciedNum) || (GBLNUMAROUND)) num++;

						num++;
						rTot = rTot + plane.pData[i][j].Col.r;
						bTot = bTot + plane.pData[i][j].Col.b;
						gTot = gTot + plane.pData[i][j].Col.g;
						colorCount = colorCount + 1;


						//if ((currspecies == plane.pData[i][j].speciedNum) || mateWithOtherSoecies)  num++;
						//if ((currspecies == plane.pData[i][j].speciedNum) || (GBLCOLORFOBIA))
						//{
						//	rTot = rTot + plane.pData[i][j].Col.r;
						//	bTot = bTot + plane.pData[i][j].Col.b;
						//	gTot = gTot + plane.pData[i][j].Col.g;
						//	colorCount = colorCount + 1;
						//}
					}
				}
			}
		}
	}
	else
	{
		//maxX = in.xLoc + range;  minX = in.xLoc - range;  maxY = in.yLoc + range;  minY = in.yLoc - range;
		int x = 0; int y = 0;
		num = 0;
		rTot = 0; gTot = 0; bTot = 0;
		for (i = minX; i <= maxX; i++)
		{
			x = i;
			if (x < 0) x = NUMCOL + x;  if (x>= NUMCOL) x = x - NUMCOL;
			for (j = minY; j <= maxY; j++)
			{
				//xxxTotalCells++;
				fullcount++;
				y = j;
				if (y < 0) y = NUMROW + y;  if (y >= NUMROW) y = y - NUMROW;
				if (plane.pData[x][y].Alive == TRUE)
				{
					//if ((DUPESPECIES) || (currspecies == plane.pData[i][j].speciedNum) || (GTBLCOLORFOBIA) || (GBLNUMAROUND))
					{
						//if ((currspecies == plane.pData[i][j].speciedNum) || (GBLNUMAROUND)) num++;
						//if ((currspecies == plane.pData[i][j].speciedNum) || (GBLCOLORFOBIA))
						//if ((currspecies == plane.pData[x][y].speciedNum) || (GBLNUMAROUND)) num++;
						//if ((currspecies == plane.pData[x][y].speciedNum) || (GBLCOLORFOBIA))
							num++;
						{
							rTot = rTot + plane.pData[x][y].Col.r;
							bTot = bTot + plane.pData[x][y].Col.b;
							gTot = gTot + plane.pData[x][y].Col.g;
							colorCount++;
						}
					}
				}
			}
		}
	}
	if (colorCount == 0)
	{
		colorCount = 1;
	}	
	tot = abs((colorCount * red) - rTot) + abs((colorCount * blue) - bTot) + abs((colorCount * green) - gTot);
	plane.pData[in.xLoc][in.yLoc].avgColor.r = rTot / colorCount;
	plane.pData[in.xLoc][in.yLoc].avgColor.g = gTot / colorCount;
	plane.pData[in.xLoc][in.yLoc].avgColor.b = bTot / colorCount;
	//if (num > maxNum)
	//{
	//	std::cout << " AHHHHHHHHH SHIT " << " range " << range << " cells " << xxxTotalCells << " species " << currspecies << " num " << num << " maxNum " << maxNum << std::endl;
	//	if (currspecies == 0)
	//	{
	//		std::cout << " Eh too Brutis " << " species " << currspecies << " num " << num << " maxNum " << maxNum << std::endl;
	//	}


	//}
	//int tmp = tot * (fullcount / colorCount);

	if ((num <= maxNum) && ((tot * (fullcount / colorCount)) <= maxColor)) //(tot <= maxColor))
		return(TRUE);
	else
		return(FALSE);
};
void Plane::initVBO(Shader *shader)
{
	
	glGenVertexArrays(1, &plane.vboID);
	glBindVertexArray(plane.vboID);
	GLuint indexBuffer;
	glGenBuffers(1, &plane.vertexBuffer);
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, plane.vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, plane.verts.size() * sizeof(Vertex), &plane.verts[0], GL_DYNAMIC_DRAW);
	//int x = sizeof(plane.verts);
	glBufferData(GL_ARRAY_BUFFER, NUMVERTS * sizeof(Vertex), &plane.verts[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, plane.index.size() * sizeof(GLuint), &plane.index[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUMIDX * sizeof(GLuint), &plane.index[0], GL_STATIC_DRAW);
	glVertexAttribPointer(shader->positionAtribID, 3, GL_FLOAT, false, sizeof(Vertex), MEMBER_OFFSET(Vertex, location)));
	glEnableVertexAttribArray(shader->positionAtribID);
	glVertexAttribPointer(shader->colorAtribID, 4, GL_FLOAT, false, sizeof(Vertex), MEMBER_OFFSET(Vertex, colour)));
	glEnableVertexAttribArray(shader->colorAtribID);

	// Make sure we disable and unbind everything to prevent rendering issues later.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(shader->positionAtribID);
	glDisableVertexAttribArray(shader->colorAtribID);
}

void Plane::showCol(CELLLOC in, int currSpecies)
{
	int i; 
	i = plane.pData[in.xLoc][in.yLoc].cellDisplayPos;

	if (Species.speciesarray[currSpecies].data.showAvgColor == FALSE)
	{
		*(&(plane.ptr + i)->colour[R_POS]) = (float)plane.pData[in.xLoc][in.yLoc].Col.r / 255.0f;
		*(&(plane.ptr + i)->colour[G_POS]) = (float)plane.pData[in.xLoc][in.yLoc].Col.g / 255.0f;
		*(&(plane.ptr + i)->colour[B_POS]) = (float)plane.pData[in.xLoc][in.yLoc].Col.b / 255.0f;

	}
	else
	{

		*(&(plane.ptr + i)->colour[R_POS]) = (float)plane.pData[in.xLoc][in.yLoc].avgColor.r / 255.0f;
		*(&(plane.ptr + i)->colour[G_POS]) = (float)plane.pData[in.xLoc][in.yLoc].avgColor.g / 255.0f;
		*(&(plane.ptr + i)->colour[B_POS]) = (float)plane.pData[in.xLoc][in.yLoc].avgColor.b / 255.0f;

	}
	*(&(plane.ptr + i)->colour[A_POS]) = 1.0f;
	//if ((plane.pData[in.xLoc][in.yLoc].Alive == FALSE) && (Species.speciesarray[currSpecies].data.BlackDeath))
	//{
	//	*(&(plane.ptr + i)->colour[A_POS]) = 1.0f;
	//}
	//else *(&(plane.ptr + i)->colour[A_POS]) = 1.0f;

		//	ShowHeight(lastChangedCell,plane.ptr);
	}



void Plane::pshowHeight(CELLLOC in, bool DecageGrowth, int currSpecies)
{

	
	if (DecageGrowth)
	{
		*(&(plane.ptr + plane.pData[in.xLoc][in.yLoc].cellDisplayPos)->location[Z_POS]) = (float)plane.pData[in.xLoc][in.yLoc].AgeDecade * 10 * Species.speciesarray[currSpecies].data.heightgrowth;
	}
	else
	{
		*(&(plane.ptr + plane.pData[in.xLoc][in.yLoc].cellDisplayPos)->location[Z_POS]) = (float)plane.pData[in.xLoc][in.yLoc].Age *  Species.speciesarray[currSpecies].data.heightgrowth;
		
	}
}

void Plane::clearDead()
{
	for (int xLoc = 0; xLoc < NUMROW; xLoc++)
	{
		for (int yLoc = 0; yLoc < NUMCOL; yLoc++)
		{
			if (!plane.pData[xLoc][yLoc].Alive)
			{
				int i = plane.pData[xLoc][yLoc].cellDisplayPos;
				*(&(plane.ptr + i)->colour[R_POS]) = 0.0f;// (float)plane.pData[xLoc][yLoc].Col.r / 255.0f;
				*(&(plane.ptr + i)->colour[G_POS]) = 0.0f;//(float)plane.pData[xLoc][yLoc].Col.g / 255.0f;
				*(&(plane.ptr + i)->colour[B_POS]) = 0.0f;//(float)plane.pData[xLoc][yLoc].Col.b / 255.0f;
			}
		}
	}
}