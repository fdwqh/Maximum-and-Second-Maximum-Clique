#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include "Vertex.h"
using namespace std;

#define MAXN 10005

class UGraph
{
public:
	vector<int> degree;
	vector<int> Ecore;
	vector<vector<bool>> A;
	int n;
	long long nodes;
	long long timeLimit;
	long long cpuTime;
	int FMax; // Size of First Maximum Clique
	int SMax; // Size of Second Maximum Clique
	int SMAX_BOUND;
	vector<int> H1; // First Maximum Clique
	unordered_map<int, bool> H_dict;
	vector<int> H2; // Second Maximum Clique
	vector<int> cor; // core number
	vector<int> ColOrd; 
	vector<int> solution;
	vector<vector<int>> adjacencyList;

	UGraph(int n, vector<vector<bool>> A, vector<int> degree, vector<vector<int>> adjacencyList)
	{
		this->n = n;
		this->A = A;
		this->degree = degree;
		this->adjacencyList = adjacencyList;
		nodes = FMax = SMax = SMAX_BOUND = 0;
		cpuTime = timeLimit = -1;
		solution.resize(n);
		cor.resize(n);
		ColOrd.reserve(n);
		Ecore.resize(n);
	}

	void seed();
	void search(vector<vector<bool>> A, vector<int> degree, vector<int> cor);
	bool conflict(int v, const vector<int> &colorClass);
	void colorSort(vector<int> C, vector<int> ColOrd, vector<int> &P,
		vector<int> &color, vector<vector<int>> &colorClass);
	void expand(vector<int> C, vector<int> P, vector<int> ColOrd, const vector<int> &cor);

	void updateSolution(const vector<int> &C)
	{
		if (C.size() > FMax)
		{
			SMax = FMax; H2 = H1;
			FMax = C.size(); H1 = C;
			H_dict.clear(); for (int u : H1) H_dict.insert({ u, 1 });
		}
		else if (C.size() > SMax)
		{
			bool ok = false;
			for (int u : C) if (H_dict.find(u) == H_dict.end()) { ok = true; break; }
			if (ok) { SMax = C.size(); H2 = C; }
		}
		SMAX_BOUND = max(SMAX_BOUND, SMax);
	}

	void orderVertices(vector<Vertex> V, vector<int> &ColOrd, vector<int> &cor)
	{//最终的ColOrd按核数从大到小排序，cor[i]表示i的核数
		vector<Vertex> L(V);
		int core_number = 0;
		while (!L.empty())
		{
			Vertex v = L[0];  //cout << v.index << ' ';
			for (Vertex u : L) if (u.degree < v.degree) v = u; //cout << v.index << endl;
			if (v.degree > core_number) core_number = v.degree;
			cor[v.index] = core_number;
			ColOrd.push_back(v.index); 
			remove(L.begin(), L.end(), v);
			L.pop_back();
			for (Vertex &u : L) if (A[u.index][v.index] == 1) u.degree--;
		} 
		reverse(ColOrd.begin(), ColOrd.end());
	}

	void insertEdge(int u, int v);
	int delInit(int w, const unordered_map<int, bool> &dict, const vector<int> &H);
	void delWork(int u, int v, unordered_map<int, bool> &dict, vector<int> &H, int &_size);
	bool Find(vector<int> &C, vector<int> P);
	bool maxFind();
	void removeEdge(int u, int v);

	void updateEcore(int u, int v, bool sig)
	{
		if (sig)
		{
			if (Ecore[u] == Ecore[v]) Ecore[u]++, Ecore[v]++;
			else if(Ecore[u] < Ecore[v]) Ecore[u]++;
			else Ecore[v]++;
		}
		Ecore[u] = min(Ecore[u], degree[u]);
		Ecore[v] = min(Ecore[v], degree[v]);
	}
};
