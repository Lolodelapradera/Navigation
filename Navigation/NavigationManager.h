#pragma once
#include "Mapper.h"
#include <vector>
#include <string>

class XYZ
{
public:
	float X;
	float Y;
	float Z;

	XYZ()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}

	XYZ(double X, double Y, double Z)
	{
		this->X = (float)X;
		this->Y = (float)Y;
		this->Z = (float)Z;
	}
};

class NavigationManager
{
public:
	static NavigationManager* GetInstance();
	void LoadMap();
	void Release();
	void FreePathArr(XYZ* pathArr);

private:

	static NavigationManager* s_singletonInstance;
	void InitializeMaps(Mapper* manager, unsigned int mapId);

};