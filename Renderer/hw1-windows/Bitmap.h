/*
Class that allows rendered image to be outputted as a .bmp file
*/

#pragma once

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

class Bitmap {
public:
	Bitmap() {}
	Bitmap(int x, int y) { XRes = x; YRes = y; Pixel = new int[XRes*YRes];}
	~Bitmap()								{delete []Pixel;}

	bool SaveBMP(const char *filename);

	int GetXRes() const						{return XRes;}
	int GetYRes() const						{return YRes;}
	int &GetPixel(int x,int y)				{return Pixel[y*XRes+x];}
	void SetPixel(int x,int y,int pix)		{
		if (Pixel == 0) std::cout << "in null" << std::endl;
		Pixel[y*XRes+x] = pix;
	}

private:
	int XRes;
	int YRes;
	int *Pixel;
};

////////////////////////////////////////////////////////////////////////////////
