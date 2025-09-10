#include "SpeciesMgmnt.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


class CSVRow
{
public:
	std::string const& operator[](std::size_t index) const
	{
		return m_data[index];
	}
	std::size_t size() const
	{
		return m_data.size();
	}
	void readNextRow(std::istream& str)
	{
		std::string         line;
		std::getline(str, line);

		std::stringstream   lineStream(line);
		std::string         cell;

		m_data.clear();
		while (std::getline(lineStream, cell, ','))
		{
			m_data.push_back(cell);
		}
		// This checks for a trailing comma with no data after it.
		if (!lineStream && cell.empty())
		{
			// If there was a trailing comma then add an empty element.
			m_data.push_back("");
		}
	}
private:
	std::vector<std::string>    m_data;
};

std::istream& operator>>(std::istream& str, CSVRow& data)
{
	data.readNextRow(str);
	return str;
}


SpeciesMgmnt::SpeciesMgmnt()
{


	/*if (CreateDirectory("speciesHold", NULL))*/
        // Pseudocode plan:
        // 1. The error is caused by passing a narrow string literal ("speciesHold") to CreateDirectory, which expects a wide string (LPCWSTR).
        // 2. On Windows, CreateDirectory is a macro that maps to CreateDirectoryW (wide) if UNICODE is defined, or CreateDirectoryA (ANSI) otherwise.
        // 3. To fix, either:
        //    a) Use wide string literals (L"speciesHold") everywhere CreateDirectory is called, or
        //    b) Use the ANSI version explicitly: CreateDirectoryA, or
        //    c) Convert std::string to std::wstring and pass .c_str().
        // 4. The simplest fix is to use L"speciesHold" for the string literal and update all similar calls in this file.

        if (CreateDirectory(L"speciesHold", NULL))
        {
            // Directory created
            std::cout << std::endl << "speciesHold Directory created " << std::endl;
        }
        else
            if (ERROR_ALREADY_EXISTS == GetLastError())
            {
                // Directory already exists
                std::cout << std::endl << "speciesHold Directory exists " << std::endl;
            }
            else
            {
                // Failed for some other reason
                std::cout << std::endl << "speciesHold Directory create failed " << std::endl;
            }
	{
		// Directory created
		std::cout << std::endl << "speciesHold Directory created " << std::endl;
	}
	//else
	//	if (ERROR_ALREADY_EXISTS == GetLastError())
	//	{
	//		// Directory already exists
	//		std::cout << std::endl << "speciesHold Directory exists " << std::endl;
	//	}
	//	else
	//	{
	//		// Failed for some other reason
	//		std::cout << std::endl << "speciesHold Directory create failed " << std::endl;
	//	}
	//CreateSpeciesDIR();
	speciesTmpSave.resize(NUMSAVESPECIES);
	allSavedSpecies.resize(NUMSAVESPECIES);
	std::string parentDirectory = "./speciesHold/";
	std::string fimeName = "000";
	std::string fullFileAndDir = "speciesHold/";
	struct stat buffer; int x = 0; bool tmp = false;
	for (int i = 0; i < NUMSAVESPECIES; i++)
	{
		
		fimeName = ZeroPadNumber(3, i);
		fullFileAndDir = parentDirectory + fimeName + ".csv";
		
		std::cout << "filename(" << fullFileAndDir << ") to be loaded (" << i << ")\n";

		// Check for existence.
		//if ((_access("crt_ACCESS.C", 0)) != -1)
		//if ((_access(fullFileAndDir, 0)) != -1)
		//{
		//	printf_s("File crt_ACCESS.C exists.\n");

		//	// Check for write permission.
		//	// Assume file is read-only.
		//	if ((_access("crt_ACCESS.C", 2)) == -1)
		//		printf_s("File crt_ACCESS.C does not have write permission.\n");
		//}


		x = stat(fullFileAndDir.c_str(), &buffer);
	
		//return (x == 0);
		if (fileExixts(fullFileAndDir))
		//if (x ==  0) // 
		{
			allSavedSpecies[i].dirActive = true;
			std::ifstream       file(fullFileAndDir);
			CSVRow              row;
			bool LoadFirst = false;
			while (file >> row)
			{
				//std::cout << "4th Element(" << row[3] << ")\n";

				if (LoadFirst) SpeciesLoadRow(i, stoi(row[0]), row[3]); else LoadFirst = !LoadFirst;

			}
			allSavedSpecies[i].speciesSave.fileNumber = i;
		}
		else
		{
			std::cout << "empty (" << i  << ")\n";
		}

	}
}



SpeciesMgmnt::~SpeciesMgmnt()
{
}

void SpeciesMgmnt::ReloadSpeciesfromDisk()
{

	std::string parentDirectory = "./speciesHold/";
	std::string specDirectory = "000";
	std::string fullFileAndDir = "speciesHold/";
	struct stat buffer; int x = 0;
	for (int i = 0; i < NUMSAVESPECIES; i++)
	{

		specDirectory = ZeroPadNumber(3, (i + 1));
		fullFileAndDir = parentDirectory + specDirectory + ".csv";

		std::cout << "filename(" << fullFileAndDir << ") to be loaded (" << i << ")\n";
		x = stat(fullFileAndDir.c_str(), &buffer);
		//return (x == 0);
		if (x == 0) // if (fileExixts(fullFileAndDir))
		{
			allSavedSpecies[i].dirActive = true;
			std::ifstream       file(fullFileAndDir);
			CSVRow              row;
			bool LoadFirst = false;
			while (file >> row)
			{
				//std::cout << "4th Element(" << row[3] << ")\n";

				if (LoadFirst) SpeciesLoadRow(i, stoi(row[0]), row[3]); else LoadFirst = !LoadFirst;

			}
			allSavedSpecies[i].speciesSave.fileNumber = i ;
		}
		else
		{
			std::cout << "empty (" << i << ")\n";
		}

	}
}


//void SpeciesMgmnt::CreateSpeciesDIR()
//{
//	
//	std::string parentDirectory = "speciesHold/";
//	std::string specDirectory = "000";
//	std::string fullFileAndDir = "speciesHold/000";
//	for (int i = 0; i < NUMSAVESPECIES; i++)
//	{
//		specDirectory = ZeroPadNumber(3, i+1);
//		fullFileAndDir = parentDirectory + specDirectory;
//
//		if (CreateDirectory(fullFileAndDir.c_str(), NULL))
//		{
//			// Directory created
//			std::cout << std::endl << fullFileAndDir << std::endl;
//		}
//		else
//			if (ERROR_ALREADY_EXISTS == GetLastError())
//			{
//				// Directory already exists
//				std::cout << std::endl << fullFileAndDir << std::endl;
//			}
//			else
//			{
//				// Failed for some other reason
//				std::cout << std::endl << fullFileAndDir << std::endl;
//			}
//	}
//}

void SpeciesMgmnt::SpeciesSave(int speciesIn, SDL_Window *mainwindow)
{
	specdata speciesHold;
	speciesHold = Species.speciesarray[speciesIn].data;	
	int i = 0;
	bool found = false;
	while ((!found) && (i<NUMSAVESPECIES))
	{
		if (!allSavedSpecies[i].dirActive)
		{
			found = true;
		}
		else
		{
			i++;
		}
	}
	if (i < NUMSAVESPECIES)
	{
		allSavedSpecies[i].dirActive = true;
		std::string specDirectory = "000";
		specDirectory = ZeroPadNumber(3, i);
		std::string fullFileAndDir = "./speciesHold/" + specDirectory + ".bmp";
		ImageSave::ScreenShot(mainwindow, fullFileAndDir.c_str());
		std::string CSVfilename = "./speciesHold/" + specDirectory + ".csv";
		std::ofstream outputFile;

		// create and open the .csv file
		outputFile.open(CSVfilename);

		outputFile << "Field ID" << "," << "Field Name" << "," << "Data Type" << "," << "Data Value" << std::endl;

		std::string A = "Field ID";
		std::string B = "Field Name";
		std::string C = "Data Type";
		std::string D = "Value";

		A = "001"; B = "bool"; C = "decadeHeightShow"; D = std::to_string(speciesHold.decadeHeightShow);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "002"; B = "int"; C = "clusterSize"; D = std::to_string(speciesHold.clusterSize);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "003"; B = "int"; C = "numseeds"; D = std::to_string(speciesHold.numseeds);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "004"; B = "int"; C = "seedXrange"; D = std::to_string(speciesHold.seedXrange);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "005"; B = "int"; C = "seedYrange"; D = std::to_string(speciesHold.seedYrange);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "006"; B = "int"; C = "maxTimeTillMutate"; D = std::to_string(speciesHold.maxTimeTillMutate);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "007"; B = "int"; C = "timeTillMutate"; D = std::to_string(speciesHold.timeTillMutate);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "008"; B = "int"; C = "maxNumaround"; D = std::to_string(speciesHold.maxNumaround);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "009"; B = "bool"; C = "mateWithOtherSpecies"; D = std::to_string(speciesHold.mateWithOtherSpecies);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "010"; B = "int"; C = "baseColorRed"; D = std::to_string(speciesHold.baseColorRed);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "011"; B = "int"; C = "baseColorGreen"; D = std::to_string(speciesHold.baseColorGreen);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "012"; B = "int"; C = "baseColorBlue"; D = std::to_string(speciesHold.baseColorBlue);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "013"; B = "bool"; C = "showBaseColor"; D = std::to_string(speciesHold.showBaseColor);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "014"; B = "int"; C = "overPop"; D = std::to_string(speciesHold.overPop);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "015"; B = "int"; C = "Range"; D = std::to_string(speciesHold.Range);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "016"; B = "int"; C = "mateRange"; D = std::to_string(speciesHold.mateRange);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "017"; B = "int"; C = "childRange"; D = std::to_string(speciesHold.childRange);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "018"; B = "int"; C = "childXdir"; D = std::to_string(speciesHold.childXdir);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "019"; B = "int"; C = "childYdir"; D = std::to_string(speciesHold.childYdir);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "020"; B = "int"; C = "timeToFindMate"; D = std::to_string(speciesHold.timeToFindMate);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "021"; B = "int"; C = "mutationPcnt"; D = std::to_string(speciesHold.mutationPcnt);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "022"; B = "int"; C = "fstart"; D = std::to_string(speciesHold.fstart);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "023"; B = "int"; C = "fend"; D = std::to_string(speciesHold.fend);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "024"; B = "int"; C = "death"; D = std::to_string(speciesHold.death);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "025"; B = "float"; C = "heightgrowth"; D = std::to_string(speciesHold.heightgrowth);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
//		A = "026"; B = "bool"; C = "reflecton"; D = std::to_string(speciesHold.reflecton);
//		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "027"; B = "int"; C = "mutationFocusPcnt"; D = std::to_string(speciesHold.mutationFocusPcnt);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "028"; B = "int"; C = "timeAlive"; D = std::to_string(0);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "029"; B = "bool"; C = "RainbowOn"; D = std::to_string(speciesHold.RainbowOn);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;
		A = "030"; B = "bool"; C = "BlackDeath"; D = std::to_string(speciesHold.BlackDeath);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;	
		A = "031"; B = "bool"; C = "showAvgColor"; D = std::to_string(speciesHold.showAvgColor);
		outputFile << A << "," << B << "," << C << "," << D << std::endl;

		outputFile.close();
	}
	else
	{
		std::cout << std::endl << NUMSAVESPECIES << "speciesHold Directories created so no more room " << std::endl;
		std::cout <<  "tell the idiot programmer u need more space " << std::endl;
	}
	////bool decadeHeightShow = FALSE; //001
	////int clusterSize = 2; //002
	////int numseeds = 20;	 //003
	////int seedXrange = 4;	//004
	////int seedYrange = 4;	//005
	////int maxTimeTillMutate = MAXMUTATETIME;  //006
	////int timeTillMutate = maxTimeTillMutate; //007
	////int maxNumaround = 100;  //008
	////bool mateWithOtherSpecies = false; //009
	////int baseColorRed; //010
	////int baseColorGreen; //011
	////int baseColorBlue; //012
	////bool showBaseColor = false; //013
	////int overPop = 36000; // 014 a max value that is used to decide if a cell is "too different"  currently it looks at all cells Range away totaling the diff between colors
	////int Range = 2; // 015 used above to calculate range to use for overpop calculation
	////int mateRange = 2; // 016 when fining 2 cells to mate how far away to look for mate
	////int childRange = 2; // 017 how far away to look for empty loc to  to place child
	////int childXdir = 0; //018
	////int childYdir = 0; // 019
	////int timeToFindMate = 3; //020  how many times to look for a mate - note this is also used to number of times to find a loc for the child - needs to be seperated
	////int mutationPcnt = 80; // 021 currently the point at which a random mutation occurs - higher num less often
	////int fstart = 10;   // 022 fertility start - at this age the cell will start looking for a mate
	////int fend = 150; // 023 fertility end - at this point the cell will stop looking for a mate
	////int death = 200; // 024 the age at which the cell will die  ********** this will need to move to an energy level
	////float heightgrowth = 0; //025
	////bool reflecton = false; //026
	////int mutationFocusPcnt = 25; //027
	////int timeAlive = 0; //028
	////bool RainbowOn = false; //029
	////bool BlackDeath = false; //030
}

void SpeciesMgmnt::SpeciesLoadRow(int speciesSaveNum, int ValID, std::string ValueString)
{
	switch (ValID)
	{
	case 1:
		allSavedSpecies[speciesSaveNum].speciesSave.decadeHeightShow = (bool)stoi(ValueString);
		break;
	case 2:
		allSavedSpecies[speciesSaveNum].speciesSave.clusterSize = stoi(ValueString);
		break;
	case 3:
		allSavedSpecies[speciesSaveNum].speciesSave.numseeds = stoi(ValueString);
		break;
	case 4:
		allSavedSpecies[speciesSaveNum].speciesSave.seedXrange = stoi(ValueString);
		break;
	case 5:
		allSavedSpecies[speciesSaveNum].speciesSave.seedYrange = stoi(ValueString);
		break;
	case 6:
		allSavedSpecies[speciesSaveNum].speciesSave.maxTimeTillMutate = stoi(ValueString);
		break;
	case 7:
		allSavedSpecies[speciesSaveNum].speciesSave.timeTillMutate = stoi(ValueString);
		break;
	case 8:
		allSavedSpecies[speciesSaveNum].speciesSave.maxNumaround = stoi(ValueString);
		break;
	case 9:
		allSavedSpecies[speciesSaveNum].speciesSave.mateWithOtherSpecies = (bool)stoi(ValueString);
		break;
	case 10:
		allSavedSpecies[speciesSaveNum].speciesSave.baseColorRed = stoi(ValueString);
		break;
	case 11:
		allSavedSpecies[speciesSaveNum].speciesSave.baseColorGreen = stoi(ValueString);
		break;
	case 12:
		allSavedSpecies[speciesSaveNum].speciesSave.baseColorBlue = stoi(ValueString);
		break;
	case 13:
		allSavedSpecies[speciesSaveNum].speciesSave.showBaseColor = (bool)stoi(ValueString);
		break;
	case 14:
		allSavedSpecies[speciesSaveNum].speciesSave.overPop = stoi(ValueString);
		break;
	case 15:
		allSavedSpecies[speciesSaveNum].speciesSave.Range = stoi(ValueString);
		break;
	case 16:
		allSavedSpecies[speciesSaveNum].speciesSave.mateRange = stoi(ValueString);
		break;
	case 17:
		allSavedSpecies[speciesSaveNum].speciesSave.childRange = stoi(ValueString);
		break;
	case 18:
		allSavedSpecies[speciesSaveNum].speciesSave.childXdir = stoi(ValueString);
		break;
	case 19:
		allSavedSpecies[speciesSaveNum].speciesSave.childYdir = stoi(ValueString);
		break;
	case 20:
		allSavedSpecies[speciesSaveNum].speciesSave.timeToFindMate = stoi(ValueString);
		break;
	case 21:
		allSavedSpecies[speciesSaveNum].speciesSave.mutationPcnt = stoi(ValueString);
		break;
	case 22:
		allSavedSpecies[speciesSaveNum].speciesSave.fstart = stoi(ValueString);
		break;
	case 23:
		allSavedSpecies[speciesSaveNum].speciesSave.fend = stoi(ValueString);
		break;
	case 24:
		allSavedSpecies[speciesSaveNum].speciesSave.death = stoi(ValueString);
		break;
	case 25:
		allSavedSpecies[speciesSaveNum].speciesSave.heightgrowth = stof(ValueString);
		break;
	//case 26:
	//	allSavedSpecies[speciesSaveNum].speciesSave.reflecton = (bool)stoi(ValueString);
		break;
	case 27:
		allSavedSpecies[speciesSaveNum].speciesSave.mutationFocusPcnt = stoi(ValueString);
		break;
	case 28:
		allSavedSpecies[speciesSaveNum].speciesSave.timeAlive = 0; // stoi(ValueString);
		break;
	case 29:
		allSavedSpecies[speciesSaveNum].speciesSave.RainbowOn = (bool)stoi(ValueString);
		break;
	case 30:
		allSavedSpecies[speciesSaveNum].speciesSave.BlackDeath = (bool)stoi(ValueString);
		break;
	case 31:
		allSavedSpecies[speciesSaveNum].speciesSave.showAvgColor = (bool)stoi(ValueString);
		break;

	default:
		break;
	}

}


void SpeciesMgmnt::killSpecies(int speciesIn)
{
	int x, y;
	Species.speciesarray[speciesIn].lifelist->goFirst();
	CELLLOC aLoc;
	int xyx = Species.speciesarray[speciesIn].lifelist->activeLifeCount;
	//for (int i = 0; i < xyx; i++)
	while (Species.speciesarray[speciesIn].lifelist->start != NULL)
	{
		//Species.speciesarray[speciesIn].lifelist->delCurrent(speciesIn);
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


void SpeciesMgmnt::LoadSpeciesToKeys(bool LoadLow)

{
	int direction = -1;
	int startpoint = NUMSAVESPECIES-1;
	int numLoaded = 0;
	
	if (LoadLow)
	{
		direction = 1;
		startpoint = 0;
	}
    int i = startpoint;
	while (numLoaded < 10)
	{
		if (allSavedSpecies[i].dirActive)
		{
			speciesTmpSave[numLoaded] = allSavedSpecies[i].speciesSave;
			numLoaded++;
		}
		i = i+ direction;
		if ((i >= NUMSAVESPECIES) || (i < 0)) i = startpoint;
	}
}

void SpeciesMgmnt::LoadAll(bool LoadLow)

{
	int direction = -1;
	int startpoint = NUMSAVESPECIES - 1;
	int numLoaded = 0;

	if (LoadLow)
	{
		direction = 1;
		startpoint = 0;
	}
	int i = startpoint;
	while (numLoaded < NUMSAVESPECIES)
	{
		if (allSavedSpecies[i].dirActive)
		{
			speciesTmpSave[numLoaded] = allSavedSpecies[i].speciesSave;
			speciesTmpSave[numLoaded].timeAlive = 0;
			speciesTmpSave[numLoaded].timeTillMutate =  MAXMUTATETIME/2 + randomRange(MAXMUTATETIME / 2);
			numLoaded++;
		}
		i = i + direction;
		if ((i >= NUMSAVESPECIES) || (i < 0)) i = startpoint;
	}
}

//void SpeciesMgmnt::LoadNextOrPrev(bool next)
//{
//	for (size_t i = 0; i < NUMSPECIES; i++)
//	{
//		Species.speciesarray[i].data = allSavedSpecies[i].speciesSave;
//
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
//	
//}


void SpeciesMgmnt::printScreen(SDL_Window *mainwindow)
{
	bool emptyFileFound = false;
	std::string parentDirectory = "./saves/";
	std::string fileName = "000000";
	//std::string fullFileAndDir = "./saves/000.bmp";
	std::string fullFileAndDir = "./saves/000000.jpg";
	struct stat buffer; int x = 0;
	int ii = 0;
	while (!emptyFileFound)
	{
		fileName = ZeroPadNumber(5, (ii + 1));
		//fullFileAndDir = parentDirectory + fileName + ".bmp";
		fullFileAndDir = parentDirectory + fileName + ".jpg";

		std::cout << "filename(" << fullFileAndDir << ") to be saved tested \n";
		x = stat(fullFileAndDir.c_str(), &buffer);
		//return (x == 0);
		if (x != 0) // if (fileExixts(fullFileAndDir))
		{
			emptyFileFound = true;
			std::cout << "filename(" << fullFileAndDir << ") to be saved saved \n";
			ImageSave::ScreenShot(mainwindow, fullFileAndDir.c_str());
		}
		else
		{
			std::cout << "filename(" << fullFileAndDir << ") allraedy exists \n";
			ii++;
		}
	}
}
//ScreenShot(mainwindow);
