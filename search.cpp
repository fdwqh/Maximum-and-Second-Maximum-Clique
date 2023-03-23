#include"Maxclique.h"

void UGraph::search(vector<vector<bool>> A, vector<int> degree, vector<int> cor)
{
	vector<Vertex> U;
	for (int i = 0; i < n; i++)  U.push_back(Vertex(i, degree[i]));
	orderVertices(U, ColOrd, cor);
	for (int i = 0; i < n; i++) cout << cor[i] << ' '; cout << endl;
	seed();
	for (int i : H1) cout << i << ' '; cout << endl;
	for (int i : H2) cout << i << ' '; cout << endl;
	vector<int> V;
	for (int i = 0; i < n; i++)
		if (cor[i] >= SMax)
			V.push_back(i);
		else
			for (int j = 0; j < n; j++) 
				if (A[i][j]) { A[i][j] = 0; degree[j]--; }
	while (!V.empty())
	{
		// Let u be the vertex with smallest degree 
		int u = V[0];
		int min_Deg = 1e9;
		for(int v: V)
			if (degree[v] < degree[u]) { min_Deg = degree[v]; u = v; }

		// InitialBranch 
		int n_u = degree[u] + 1;
		if (n_u > SMax)
		{
			vector<int> C;
			vector<int> P;
			vector<int> degree_u(n);
			P.push_back(u);
			n_u = 1;
			for (int v : V) 
				if (A[u][v] && degree[u] >= SMax) // pruning
				{
					P.push_back(v);
					n_u++;
					for (int w : P) if (A[v][w]) { degree_u[v]++; degree_u[w]++; }
				}
			vector<int> ColOrd_u;
			vector<int> cor_u(n);
			vector<vector<int>> colorClass(n_u);
			vector<Vertex> Vertex_P(n_u);
			for (int i = 0; i < n_u; i++) Vertex_P[i] = Vertex(P[i], degree_u[P[i]]);
			orderVertices(Vertex_P, ColOrd_u, cor_u);
			expand(C, P, ColOrd_u, cor_u);
		}

		// Remove u from G and explicitly remove vertices from G 
		for (int v : V) 
			if (A[u][v]) { A[u][v] = A[v][u] = 0; degree[v]--; cor[v] = max(cor[v], degree[v]); }
		vector<int> T;
		for (int v : V) if (cor[v] >= SMax && v != u) T.push_back(v);
		V = T;
	}
	puts("");
	for (int i : H1) cout << i << ' '; cout << endl;
	for (int i : H2) cout << i << ' '; cout << endl;
}
