#include"Maxclique.h"

void UGraph::insertEdge(int u, int v)
{
	degree[u]++;
	degree[v]++;
	A[u][v] = A[v][u] = 1;

	int n_e = 2;
	vector<int> C;
	vector<int> P;
	vector<int> degree_e(n);
	P.push_back(u);
	P.push_back(v);
	degree_e[u] = degree_e[v] = 1;
	for (int w = 0; w < n; w++) 
		if (A[u][w] && A[v][w] && degree[w] >= SMax) //pruning
		{
			P.push_back(w);
			n_e++;
			for (int x : P) if (A[w][x]) { degree_e[w]++; degree_e[x]++; }
		}
	vector<int> ColOrd_e;
	vector<int> cor_e(n);
	vector<vector<int>> colorClass(n_e);
	vector<Vertex> Vertex_P(n_e);
	for (int i = 0; i < n_e; i++) Vertex_P[i] = Vertex(P[i], degree_e[P[i]]);
	orderVertices(Vertex_P, ColOrd_e, cor_e);
	expand(C, P, ColOrd_e, cor_e);

	for (int i : H1) cout << i << ' '; cout << endl;
	for (int i : H2) cout << i << ' '; cout << endl;
}
