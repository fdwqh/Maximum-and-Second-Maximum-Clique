#include"Maxclique.h"

void UGraph::seed()
{
	for (int v : ColOrd)
	{
		if (cor[v] >= SMax)
		{
			vector<Vertex> S;
			S.push_back(Vertex(v, degree[v], cor[v]));
			for (int u = 0; u < n; u++) 
				if (A[u][v] == 1 && cor[u] >= SMax) S.push_back(Vertex(u, degree[u], cor[u])); 
			sort(S.begin(), S.end(), [](const Vertex &x, const Vertex &y) {return x.core > y.core; });
			vector<int> C;
			for (Vertex u : S)
			{
				bool ok = true;
				for(int w : C) 
					if (A[u.index][w] == 0) { ok = false; break; }
				if (ok) C.push_back(u.index);
			}
			updateSolution(C);
		}
	}
}
