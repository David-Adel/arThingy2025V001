#pragma once
#include "main.h"

	class ImageSave
	{
	public:
		//static GLTexture loadPNG(std::string filePath);
		static void ScreenShot(SDL_Window* window, const char *filenam);
	};


	typedef struct colstr
	{
		glm::vec4 colour; // the color of the node in r g b a (a is the transperancy if turned on)
	}colstr;
	class ImageToDisplay
	{
	public:
		int maxTimeBaseColorChange = MaxTimeTillBaseColorChange;
		bool firstPass = false;
		bool newImage = FALSE;
		bool showimage = FALSE;
		bool imageFound = FALSE;
		int maxTimeImageLoadSP = MAXTIMEIMAGELOADSP;
		int timeImageLoadSP = 0;
		bool image1Current = true;
		int maxTimeTillImageChange = MaxTimeTillImageChange;
		int timeTillBaseColorChange = 0;
		int timeTillImageChange = 0;
		int prevLoadedImageNum = 0;

		 vector<vector< colstr >> displayImage1;
		 vector<vector< colstr >> displayImage2;
		//static vector<vector< colstr >> loadImage;
		 std::vector<std::string> vFileNames;

		 int GetImages();
		 void read_img(char *name, int width, int height);
		 void Init(int width, int height);
		 void nextImageLoad();
		virtual ~ImageToDisplay();
	};




