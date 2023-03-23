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
	vector<vector<bool>> A;
	int n;
	long long nodes;
	long long timeLimit;
	long long cpuTime;
	int FMax; // Size of First Maximum Clique
	int SMax; // Size of Second Maximum Clique
	vector<int> H1; // First Maximum Clique
	unordered_map<int, bool> H_dict;
	vector<int> H2; // Second Maximum Clique
	vector<int> cor; // core number
	vector<int> ColOrd; 
	vector<int> solution;

	UGraph(int n, vector<vector<bool>> A, vector<int> degree)
	{
		this->n = n;
		this->A = A;
		this->degree = degree;
		nodes = FMax = SMax = 0;
		cpuTime = timeLimit = -1;
		solution.resize(n);
		cor.resize(n);
		ColOrd.reserve(n);
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
	}

	void orderVertices(vector<Vertex> V, vector<int> &ColOrd, vector<int> &cor)
	{
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
	void removeEdge(int u, int v);
};
