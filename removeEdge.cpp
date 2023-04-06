#include"Maxclique.h"

int UGraph::delInit(int w, const unordered_map<int, bool> &dict, const vector<int> &H)
{
	bool ok = false;
	for(int p = 0; p < n; p++)
		if (dict.find(p) == dict.end())
		{ 
			ok = true;
			for (int u : H) if (u != w && !A[p][u]) { ok = false; break; }
			if (ok) return p;
		}
	return -1;
}

void UGraph::delWork(int u, int v, unordered_map<int, bool> &dict, vector<int> &H, int &_size)
{
	int w = delInit(u, dict, H);
	if (w != -1) 
	{ 
		remove(H.begin(), H.end(), u); H.pop_back(); H.push_back(w); 
		dict.erase(u); dict.insert({ w, 1 });
	}
	else
	{
		w = delInit(v, dict, H);
		remove(H.begin(), H.end(), v); H.pop_back(); 
		dict.erase(v);
		if (w != -1) { H.push_back(w); dict.insert({ w, 1 }); }
		else _size--;
	}
}

bool UGraph::Find(vector<int> &C, vector<int> P)
{
	if (P.empty() && C.size() > FMax)
	{
		H1 = C; FMax = C.size();
		return true;
	}
	while (!P.empty())
	{
		if (C.size() + P.size() <= FMax) return false;
		int u = P.back(); P.pop_back();
		vector<int> T;
		for (int i : P) if (A[i][u]) T.push_back(i);
		C.push_back(u); bool ok = Find(C, T); C.pop_back();
		if (ok) return true;
	}
	return false;
}

bool UGraph::maxFind()
{
	for(int i = 0; i < n; i++)
		if (degree[i] >= FMax)
		{
			vector<int> C;
			vector<int> P;
			for (int j = i + 1; j < n; j++)
				if (A[i][j] && degree[j] >= FMax) P.push_back(j);
			C.push_back(i);
			if (Find(C, P)) return true;
		}
	return false;
}

void UGraph::removeEdge(int u, int v)
{
	if (A[u][v]) 
	{
		A[u][v] = A[v][u] = 0;
		degree[u]--; 
		degree[v]--;
	}

	unordered_map<int, bool> I_dict;
	for (int i : H2) I_dict.insert({ i, 1 });
	if (H_dict.find(u) != H_dict.end() && H_dict.find(v) != H_dict.end())
		delWork(u, v, H_dict, H1, FMax);
	if (I_dict.find(u) != I_dict.end() && I_dict.find(v) != I_dict.end()) 
		delWork(u, v, I_dict, H2, SMax);
	if (FMax < SMAX_BOUND && SMax == SMAX_BOUND)
	{
		H1.swap(H2);
		swap(FMax, SMax);
		H_dict.swap(I_dict);
	}
	else if (FMax < SMAX_BOUND && SMax < SMAX_BOUND)
	{
		vector<int> T(H1);
		if (maxFind()) { SMax = T.size(); H2 = T; }
		else { SMAX_BOUND = FMax; }
	}

	for (int i : H1) cout << i << ' '; cout << endl;
	for (int i : H2) cout << i << ' '; cout << endl;
}
