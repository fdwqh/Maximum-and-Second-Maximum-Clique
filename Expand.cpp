#include"Maxclique.h"

bool UGraph::conflict(int v, const vector<int> &colorClass)
{
	for (int i = 0; i < colorClass.size(); i++)
	{
		int w = colorClass[i];
		if (A[v][w]) return true;
	}
	return false;
}

void UGraph::colorSort(vector<int> C, vector<int> ColOrd, vector<int> &P, 
	vector<int> &color, vector<vector<int>> &colorClass)
{
	int colors = 0;
	int m = ColOrd.size();
	for (int i = 0; i < m; i++) colorClass[i].clear();
	for (int i = 0; i < m; i++)
	{
		int v = ColOrd[i];
		int k = 0;
		while (conflict(v, colorClass[k])) k++;
		colorClass[k].push_back(v);
		colors = max(colors, k + 1);
	}
	P.clear();
	int i = 0;
	for(int k = 0; k < colors; k++)
		for (int j = 0; j < colorClass[k].size(); j++)
		{
			int v = colorClass[k][j];
			P.push_back(v);
			color[i++] = k + 1;
		}
}

void UGraph::expand(vector<int> C, vector<int> P, vector<int> ColOrd, 
	const vector<int> &cor)
{ // P: color order, ColOrd: core order
	int m = ColOrd.size();
	vector<int> color(m);
	vector<vector<int>> colorClass(m);
	colorSort(C, ColOrd, P, color, colorClass);
	for (int i = m - 1; i >= 0; i--)
	{
		int v = P[i];
		if (C.size() + color[i] <= SMax) return; //pruning
		C.push_back(v);
		vector<int> newP;
		vector<int> newColOrd;
		for (int j = 0; j <= i; j++)
		{
			int u = P[j];
			if (A[u][v] && cor[u] >= SMax) newP.push_back(u); //pruning
			int w = ColOrd[j];
			if (A[v][w] && cor[w] >= SMax) newColOrd.push_back(w);
		}
		if (newP.empty()) updateSolution(C);
		else expand(C, newP, newColOrd, cor);
		C.pop_back();
		P.erase(P.begin() + i);
		remove(ColOrd.begin(), ColOrd.end(), v); ColOrd.pop_back();
	}
}
