#pragma once
#include "main.h"

std::string ZeroPadNumber(int width, int num);
#include <iostream>
#include <fstream>
//#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

inline bool fileExixts(const std::string& name) {
	struct stat buffer;
	int x = 0;
	x = stat(name.c_str(), &buffer);
	return (x == 0);
}

class SpeciesMgmnt
{
public:



	struct speciesSaveDir
	{
		bool dirActive = false;
		specdata speciesSave;
	};
	
	vector <speciesSaveDir> allSavedSpecies;
	vector <specdata> speciesTmpSave ;
	int allSavedSpeciesPointer = -1;
	int allSavedSpeciesNumActive = 0;
	
	SpeciesMgmnt();
	~SpeciesMgmnt();
//	void SpeciesMgmnt::CreateSpeciesDIR();
	void killSpecies(int speciesIn);
	void SpeciesSave(int speciesIn, SDL_Window *mainwindow);
	void SpeciesLoadRow(int speciesSaveNum, int ValID, std::string ValueString);
	void LoadSpeciesToKeys(bool LoadLow);
	void LoadAll(bool LoadLow);
//	void SpeciesMgmnt::LoadNextOrPrev(bool next);
	void printScreen(SDL_Window *mainwindow);
	void ReloadSpeciesfromDisk();
};

