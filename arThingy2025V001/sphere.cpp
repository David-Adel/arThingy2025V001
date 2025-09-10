#include "main.h"

//x is latitude is column
//y is longitide is row

void Sphere::sShowHeight(CELLLOC locIn, int currspecies)
{
	int i = 0,j=0;
	//int currspecies = Species.currpos;
	//int x=0,y=0;
	int x=locIn.xLoc;
	int y = locIn.yLoc;
	//int r = sData[x][y].r;
	if (plane.pData[x][y].Alive == FALSE)
	{
		sData[x][y].r = (float)initialR;
	}
	else
	{
		if (Species.speciesarray[currspecies].data.decadeHeightShow)
		{
			sData[x][y].r = initialR + ((float)plane.pData[x][y].AgeDecade * (float)10 * Species.speciesarray[currspecies].data.heightgrowth);
		}
		else
		{
			sData[x][y].r = initialR + ((float)plane.pData[x][y].Age  *  Species.speciesarray[currspecies].data.heightgrowth);
		}
	}

	sData[x][y].trueX = plane.sphere->sData[x][y].r*sData[x][y].sinPhi*sData[x][y].cosTheta;
	sData[x][y].trueY = sData[x][y].r*sData[x][y].sinPhi*sData[x][y].sinTheta;
	sData[x][y].trueZ = sData[x][y].r*sData[x][y].cosPhi;
//	i = plane.pData[x][y].cellDisplayPos;
	*(&(plane.ptr + plane.pData[x][y].cellDisplayPos)->location[X_POS]) = sData[x][y].trueX;
	*(&(plane.ptr + plane.pData[x][y].cellDisplayPos)->location[Y_POS]) = sData[x][y].trueY;
	*(&(plane.ptr + plane.pData[x][y].cellDisplayPos)->location[Z_POS]) = sData[x][y].trueZ;
}

//void Sphere::buildGrid(Vertex verts[], int index[])
//{
//	int i = 0;
//	for (int y = 0; y < longitudePoints; y++)
//	{
//		for (int x = 0; x < latitudePoints; x++)
//		{
//		verts[i].location[X_POS]	= 0.0 ;	
//		verts[i].location[Y_POS]	= 0.0;		
//		verts[i].location[Z_POS]	= 0.0;
//		verts[i].normal[X_POS]		= 0;	
//		verts[i].normal[Y_POS]		= 0;	
//		verts[i].normal[Z_POS]		= 0;
//		verts[i].tex[U_POS]			= 0;	
//		verts[i].tex[V_POS]			= 0; 
//		i++;
//		}
//	}
//	for (int i = 0; i < numVerts; i++)
//	{
//		verts[i].colour[R_POS] = 0.0;
//		verts[i].colour[G_POS] = 0.0;
//		verts[i].colour[B_POS] = 0.0;
//		verts[i].colour[A_POS] = 0.0;
//	}	
//	// Index Array (define our triangles)
//	//  The plane looks like this for a 3/3
//	// 6      7      8
//	// +------+------+
//	// |      |      |
//	// |      |      |
//   //3 +------+------+5
//	// |      |      |
//	// |      |      |
//	// +------+------+
//	// 0      1      2
//	// w width
//	//int w = numCol; // the width of the square
//	int idx = 0;
//	for (int y = 0; y<longitudePoints; y++)
//	{
//		for (int x = 0; x<latitudePoints; x++)
//		{
//			if ((x < (latitudePoints - 1)) & (y < (longitudePoints - 1)))
//			{
//				// create the two triangle that form this square
//				index[idx] = (GLuint)(x + (y*longitudePoints)); index[idx + 1] = (GLuint)(x + 1 + (y*longitudePoints)); index[idx + 2] = (GLuint)(x + 1 + (y + 1)*longitudePoints);
//				idx = idx+3;
//				index[idx] = (GLuint)(x + (y*longitudePoints)); index[idx + 1] = (GLuint)(x + 1 + (y + 1)*longitudePoints); index[idx + 2] = (GLuint)(x + (y + 1)*longitudePoints);
//				idx = idx+3;
//			}
//			else if (EdgeConnect)
//			{
//				if ((x == latitudePoints - 1) && (y != longitudePoints - 1))   // we are at the end of an X row so we add tiangles to X start ( 0 )
//				{
//					index[idx] = (GLuint)(x + (y*longitudePoints)); index[idx + 1] = (GLuint)(0 + (y*longitudePoints)); index[idx + 2] = (GLuint)(0 + (y + 1)*longitudePoints);
//					idx = idx+3;
//					index[idx] = (GLuint)(x + (y*longitudePoints)); index[idx + 1] = (GLuint)(0 + (y + 1)*longitudePoints); index[idx + 2] = (GLuint)(x + (y + 1)*longitudePoints);
//					idx = idx+3;
//				}
//				else if (x != latitudePoints - 1) // we are at the end of Y so add triangles to start Y ( 0 )
//				{
//					//index[idx] = (GLuint)(x + (y*longitudePoints)); index[idx+1] = (GLuint)(x+1 + (y*longitudePoints)); index[idx+2] = (GLuint)(x+1  + (0)*longitudePoints);
//					//idx = idx+3;
//					//index[idx] = (GLuint)(x + (y*longitudePoints)); index[idx+1] = (GLuint)(x+1 +  (0)*longitudePoints); index[idx+2] = (GLuint)(x + (0)*longitudePoints);
//					//idx = idx+3;
//				}
//				else // we at corner
//				{
//					//index[idx] = (GLuint)(x + (y*longitudePoints)); index[idx+1] = (GLuint)(0 + (y*longitudePoints)); index[idx+2] = (GLuint)(0  + (0)*longitudePoints);
//					//idx = idx+3;
//					//index[idx] = (GLuint)(x + (y*longitudePoints)); index[idx+1] = (GLuint)(0 +  (0)*longitudePoints); index[idx+2] = (GLuint)(x + (0)*longitudePoints);
//					//idx = idx+3;
//				}
//			}
//		}
//	}
//}
//void Sphere::setType( Cell *cell )
//{
//	int x,y =0;
//	x=cell->cData.Loc.x;
//	y=cell->cData.Loc.y;
//	sData[x][y].Alive = cell->cData.Alive;
//	sData[x][y].
//}; // set type

//float Sphere::numAround( Cell *cell, int range)
//{
//	int i,j,x,y =0;
//	float tot = 0;
//	int red,green,blue;
//	red = cell->cData.Col.r;
//	blue = cell->cData.Col.b;
//	green = cell->cData.Col.g;
//	x=cell->cData.Loc.x;
//	y=cell->cData.Loc.y;
//	for(i=x-range; i <=x+range; i++)
//		{	for(j=y-range; j <=y+range; j++)
//	{
//		if ((i >= 0) && (i < latitudePoints) && (j >= 0) && (j < longitudePoints))
//				{//fprintf( stdout, "i %i\n", i);fprintf( stdout, "j %i\n", j);
//					if (sData[i][j].Alive != DEAD) 
//						{	multiplier = abs(i-x) + abs(j-y);
//							if (multiplier == 0)
//								{ multiplier=1;}
//							tot = tot + 
//						 ((abs(sData[i][j].cell->cData.Col.r - red) + abs(sData[i][j].cell->cData.Col.b - blue) +abs(sData[i][j].cell->cData.Col.g - green))/multiplier) ;				
//						}
//					}
//			}
//	}
//	return(tot);
//}; 

//void Sphere::updtCell( Cell *cell)
//{
//	int x,y =0;
//	x=cell->cData.Loc.x;
//	y=cell->cData.Loc.y;
//	//z=cell->cData.Loc.z;
//	//pData[x][y].cell = cell;
//	sData[x][y].Alive = cell->cData.Alive;
//	sData[x][y].cell->cData = cell->cData;
//}; 
