#include "stdafx.h"
#include "pathfinding.h"
#include <queue>
using namespace std;

int ReturnIndex(int x, int y, int width)
{
	return x + y * width;
}

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY, const unsigned char * pMap, const int nMapWidth, const int nMapHeight, int * pOutBuffer, const int nOutBufferSize)
{

	int size = nMapWidth * nMapHeight;
	vector<bool> visited(size);
	vector<int> backtrace(size, -1);
	int startPosition = ReturnIndex(nStartX, nStartY, nMapWidth);
	int targetPosition = ReturnIndex(nTargetX, nTargetY, nMapWidth);
	queue<int> nodes;
	nodes.push(startPosition);
	int nodesInDepth = 1;
	int currentDepth = 1;
	visited[startPosition] = true;

	while (!nodes.empty())
	{
		int currentNode = 0;
		
		//nodes within the current depth
		if (nodesInDepth == 0)
		{
			//adds all nodes in the queue and also adds on depth in our depth counter
			nodesInDepth = nodes.size();
			currentDepth++;
		}
		int node = nodes.front();
		nodes.pop();
		nodesInDepth--;

		if (currentDepth > nOutBufferSize)
		{			
			//Cannot find a path within the allowed buffer size, the depth of the path is larger that the buffer.
			return INT_MAX;
		}
		//Check that we have found the target and it is within the bounds of the map
		if ((node + 1 == targetPosition) && ((node + 1) % nMapWidth != 0) || ((node - 1 == targetPosition) && (node % nMapWidth != 0)) || (node - nMapWidth == targetPosition && node - nMapWidth > 0) || (node + nMapWidth == targetPosition && node + nMapWidth < size))
		{
			backtrace[targetPosition] = node;
			int i = targetPosition;

			vector <int> path(nOutBufferSize);
			int path_len = 0;

			while (backtrace[i] != -1) {
				path[path_len++] = i;
				i = backtrace[i];
			}

			int test = 0;
			//Write to output buffer
			for (int j = path_len - 1; j >= 0; j--) {
				pOutBuffer[test] = path[j];
				test++;

			}
			if (path_len == 0)
				return -1;
			return path_len;

		}
		//right neighbor
		if ((node + 1) % nMapWidth != 0)
		{
			currentNode = node + 1;
			if (visited[currentNode] == false && pMap[currentNode] == 1)
			{
				nodes.push(currentNode);
				visited[currentNode] = true;
				backtrace[currentNode] = node;
			}
		}
		//left neighbor
		if (node % nMapWidth != 0)
		{
			currentNode = node - 1;
			if (visited[currentNode] == false && pMap[currentNode] == 1)
			{
				nodes.push(currentNode);
				visited[currentNode] = true;
				backtrace[currentNode] = node;
			}
		}
		//Up
		if (node - nMapWidth > 0)
		{
			currentNode = node - nMapWidth;
			if (visited[currentNode] == false && pMap[currentNode] == 1)
			{
				nodes.push(currentNode);
				visited[currentNode] = true;
				backtrace[currentNode] = node;
			}
		}
		//Down
		if (node + nMapWidth < size)
		{
			currentNode = node + nMapWidth;
			if (visited[currentNode] == false && pMap[currentNode] == 1)
			{
				nodes.push(currentNode);
				visited[currentNode] = true;
				backtrace[currentNode] = node;
			}
		}

	}
	//No path is possible
	return -1;
}


