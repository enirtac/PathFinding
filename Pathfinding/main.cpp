// Pathfinding.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "pathfinding.h"
using namespace std;

int main()
{
	//unsigned char pMap[] = { 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1 };
	//int pOutBuffer[2];

	//int numberOfSteps = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 2);

	

	unsigned char pMap[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer[7];
	int numberOfSteps  = FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);

}
