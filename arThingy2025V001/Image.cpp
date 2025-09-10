#include "Image.h"
int randomRange(int range);
//char* concat(char *s1, char *s2);

char* concat(const char* s1, const char* s2);

	void ImageSave::ScreenShot(SDL_Window* window, const char *filenam)
	{
		int width = 0;
		int height = 0;

		glReadBuffer(GL_FRONT);
		SDL_GetWindowSize(window, &width, &height);
		SDL_GL_GetDrawableSize(window, &width, &height);
		BYTE* pixels = new BYTE[3 * width * height];


		glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, pixels);

		// Convert to FreeImage format & save to file
		FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, 0x0000FF, 0xFF0000, 0x00FF00, false);

		// const char *filename = "./saves/test2.bmp";
		//FreeImage_Save(FIF_BMP, image, filenam, 0);

		//const char *filename = "./saves/test2.jpg";
		FreeImage_Save(FIF_JPEG, image, filenam, 0);

		// Free resources
		FreeImage_Unload(image);
		delete[] pixels;
	}


	void ImageToDisplay::Init(int width, int height)
	{
		displayImage1.resize(height);
		for (int i = 0; i < height; i++)
		{
			displayImage1[i].resize(width);
		}
		displayImage2.resize(height);
		for (int i = 0; i < height; i++)
		{
			displayImage2[i].resize(width);
		}
	}


	ImageToDisplay::~ImageToDisplay()
	{
		
	}

    #include <windows.h>
    #include <string>
    #include <vector>

    // Helper function to convert std::string to std::wstring
    std::wstring StringToWString(const std::string& s) {
        int len;
        int slength = (int)s.length() + 1;
        len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
        std::wstring r(len, L'\0');
        MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, &r[0], len);
        // Remove the null terminator added by MultiByteToWideChar
        if (!r.empty() && r.back() == L'\0') r.pop_back();
        return r;
    }

    std::vector<std::string> GetFileNamesInDirectory(std::string directory) {
    // Change this line:
    //char* directory = "./images/";
    // Change this line:
    //char* directory = "./images/";

    // To this:
    //const char* directory = "./images/";
    // To this:
    //const char* directory = "./images/";
        std::vector<std::string> files;
        WIN32_FIND_DATA fileData;
        HANDLE hFind;

        std::wstring wDirectory = StringToWString(directory);

        if (!((hFind = FindFirstFileW(wDirectory.c_str(), &fileData)) == INVALID_HANDLE_VALUE)) {
            do {
                // Convert WCHAR filename to std::string
                int len = WideCharToMultiByte(CP_ACP, 0, fileData.cFileName, -1, NULL, 0, NULL, NULL);
                std::string fileName(len - 1, '\0');
                WideCharToMultiByte(CP_ACP, 0, fileData.cFileName, -1, &fileName[0], len, NULL, NULL);
                files.push_back(fileName);
            } while (FindNextFileW(hFind, &fileData));
            FindClose(hFind);
        }

        return files;
    }

	int ImageToDisplay::GetImages() 
	{
		//std::vector<std::string> vFileNames = GetFileNamesInDirectory("./images/*.jpg");
		vFileNames = GetFileNamesInDirectory("./images/*.jpg");
		for (int i = 0; i < (int)vFileNames.size(); i++) 
		{
			std::cout << vFileNames[i] << std::endl;
			if (vFileNames[i] == "image1.jpg")
			{
				clown1 = i;
			}
			if (vFileNames[i] == "image2.jpg")
			{
				clown2 = i;
			}
		}
		return 0;
	}


	void  ImageToDisplay::nextImageLoad()
	{
		//char* directory = "./images/";
    // Change this line in nextImageLoad():
    // char* directory = "./images/";
    const char* directory = "./images/";
		//int tstwidth, tstheignt;

		int imgNum = 0;
		int test = (int)vFileNames.size();
		imgNum = randomRange((int)vFileNames.size());
		//if (prevLoadedImageNum == clown1)
		//{
		//	imgNum = clown2;
		//}
		//else
		//{
		//	imgNum = randomRange(vFileNames.size());
		//}
		char* myfileName = (char *)alloca(vFileNames[imgNum].size() + 1);
		memcpy(myfileName, vFileNames[imgNum].c_str(), vFileNames[imgNum].size() + 1);
		char* mystring = concat(directory, myfileName);
    // Pseudocode plan:
    // 1. The error is caused by passing a const char* (directory) to a function expecting char* (concat).
    // 2. The concat function should accept const char* for both parameters, since it does not modify them.
    // 3. Update the concat function declaration and definition to use const char*.
    // 4. This allows passing both const and non-const char* arguments safely.


    // Update the function declaration at the top of Image.cpp:
    char* concat(const char *s1, const char *s2);

    // If the definition is in another file, update it there as well:
    
		std::cout << " loading " << myfileName << " but showing "   << vFileNames[prevLoadedImageNum].c_str()  << std::endl;
		prevLoadedImageNum = imgNum;
		ImageToDisplay::read_img(mystring, NUMCOL, NUMROW);
		//if (image1Current)
		//{
		//	plane.imgToDisplay = plane.imgToDisplay2;
		//	delete(plane.imgToDisplay1);
		//	plane.imgToDisplay1 = new ImageToDisplay;
		//	plane.imgToDisplay1->read_img(mystring, &tstwidth, &tstheignt);
		//}
		//else
		//{
		//	plane.imgToDisplay = plane.imgToDisplay1;
		//	delete(plane.imgToDisplay2);
		//	plane.imgToDisplay2 = new ImageToDisplay;
		//	plane.imgToDisplay2->read_img(mystring, &tstwidth, &tstheignt);
		//}

		//plane.imgTimeSinceChange = 0;
		delete(mystring);
		newImage = true;
		//baseColorLocked = true;
	}

	void ImageToDisplay::read_img(char *name, int width, int height)
	{
		FIBITMAP *image = nullptr;
		FIBITMAP *loadImage;
		int i, j, pnum;
		RGBQUAD aPixel;
		// FIF_TIFF for tiff
		if ((loadImage = FreeImage_Load(FIF_JPEG, name, 0)) == NULL)
		{

			std::cout << "arThingy.tiff  not found should be 400 by 400 pi" << &name << std::endl;
			imageFound = FALSE;
		}
		else
		{
			imageFound = TRUE;
			image = FreeImage_Rescale(
				loadImage,
				width,
				height,
				FILTER_BSPLINE
			);
			width = FreeImage_GetWidth(image);
			height = FreeImage_GetHeight(image);
			pnum = 0;
			for (i = 0; i < (height); i++)
			{
				for (j = 0; j < (width); j++)
				{
					FreeImage_GetPixelColor(image, i, j, &aPixel);
					if (image1Current)
					{
						displayImage1[i][j].colour.r = (aPixel.rgbRed);
						displayImage1[i][j].colour.g = (aPixel.rgbGreen);
						displayImage1[i][j].colour.b = (aPixel.rgbBlue);
					}
					else
					{
						displayImage2[i][j].colour.r = (aPixel.rgbRed);
						displayImage2[i][j].colour.g = (aPixel.rgbGreen);
						displayImage2[i][j].colour.b = (aPixel.rgbBlue);

					}
				}
			}
			image1Current = !image1Current;
		}
		FreeImage_Unload(image);
		FreeImage_Unload(loadImage);
	}
	
	//read_img
	 //pixel *read_img(char *name, int *width, int *height) {
	 //	FIBITMAP *image;
	 //	int i, j, pnum;
	 //	RGBQUAD aPixel;
	 //	pixel *data;
	 //
	 //	if ((image = FreeImage_Load(FIF_TIFF, name, 0)) == NULL) {
	 //		return NULL;
	 //	}
	 //	*width = FreeImage_GetWidth(image);
	 //	*height = FreeImage_GetHeight(image);
	 //
	 //	data = (pixel *)malloc((*height)*(*width)*sizeof(pixel *));
	 //	pnum = 0;
	 //	for (i = 0; i < (*height); i++) {
	 //		for (j = 0; j < (*width); j++) {
	 //			FreeImage_GetPixelColor(image, j, i, &aPixel);
	 //			data[pnum].r = (aPixel.rgbRed);
	 //			data[pnum].g = (aPixel.rgbGreen);
	 //			data[pnum].b = (aPixel.rgbBlue);
	 //			pnum++;
	 //		}
	 //	}
	 //	FreeImage_Unload(image);
	 //	return data;
	 //}//read_img

	 //write_img
	 //void write_img(char *name, pixel *data, int width, int height) {
	 //	FIBITMAP *image;
	 //	RGBQUAD aPixel;
	 //	int i, j;
	 //
	 //	image = FreeImage_Allocate(width, height, 24, 0, 0, 0);
	 //	if (!image) {
	 //		perror("FreeImage_Allocate");
	 //		return;
	 //	}
	 //	for (i = 0; i < height; i++) {
	 //		for (j = 0; j < width; j++) {
	 //			aPixel.rgbRed = data[i*width + j].r;
	 //			aPixel.rgbGreen = data[i*width + j].g;
	 //			aPixel.rgbBlue = data[i*width + j].b;
	 //
	 //			FreeImage_SetPixelColor(image, j, i, &aPixel);
	 //		}
	 //	}
	 //	if (!FreeImage_Save(FIF_TIFF, image, name, 0)) {
	 //		perror("FreeImage_Save");
	 //	}
	 //	FreeImage_Unload(image);
	 //}//write_img

	 //void write_img(char *name, pixel *data, int width, int height) {
	 //	FIBITMAP *image;
	 //	RGBQUAD aPixel;
	 //	int i, j;
	 //
	 //	image = FreeImage_Allocate(width, height, 24, 0, 0, 0);
	 //	if (!image) {
	 //		perror("FreeImage_Allocate");
	 //		return;
	 //	}
	 //	for (i = 0; i < height; i++) {
	 //		for (j = 0; j < width; j++) {
	 //			aPixel.rgbRed = data[i*width + j].r;
	 //			aPixel.rgbGreen = data[i*width + j].g;
	 //			aPixel.rgbBlue = data[i*width + j].b;
	 //
	 //			FreeImage_SetPixelColor(image, j, i, &aPixel);
	 //		}
	 //	}
	 //	if (!FreeImage_Save(FIF_TIFF, image, name, 0)) {
	 //		perror("FreeImage_Save");
	 //	}
	 //	FreeImage_Unload(image);
	 //}//write_img





	//GLTexture ImageLoader::loadPNG(std::string filePath)
	//{
	//	GLTexture texture = {}; //initialides structure to 0
	//	std::vector<unsigned char> in;
	//	std::vector<unsigned char> out;
	//	unsigned long width, height;
	//	if (IOManager::readFileToBuffer(filePath, in) == false)
	//	{
	//		fatalError("Failed to load " + filePath + " into buffer");
	//	}
	//	int errorCode = decodePNG(out, width, height, &(in[0]), in.size(), true);
	//	if (errorCode != 0)
	//	{
	//		fatalError("decodePNG failed errcode: " + std::to_string(errorCode) + " for file: " + filePath);
	//	}
	//	glGenTextures(1, &(texture.id));
	//	glBindTexture(GL_TEXTURE_2D, texture.id);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//	glBindTexture(GL_TEXTURE_2D, 0);//unbind texture
	//	texture.width = width;
	//	texture.height = height;
	//	return texture;
	//}
