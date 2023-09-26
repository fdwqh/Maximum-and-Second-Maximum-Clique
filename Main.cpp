#include "Maxclique.h"

int main()
{
	FILE *fpin = freopen("s3.txt", "r", stdin);
	FILE *fpout = freopen("ans.txt", "w", stdout);

	int n, m;
	cin >> n >> m;
	vector<vector<bool>> A(n);
	vector<int> degree(n);
	vector<vector<int>> adjacencyList(n);
	for (int i = 0; i < n; i++)
		A[i].resize(n);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		A[u][v] = A[v][u] = 1;
		adjacencyList[u].push_back(v);
		adjacencyList[v].push_back(u);
		degree[u]++;
		degree[v]++; 
	}
	UGraph MC(n, A, degree, adjacencyList); 

	MC.search(MC.A, MC.degree, MC.cor);
	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << MC.A[i][j] << ' ';
		cout << endl;
	}*/
	bool sig;
	int u, v;
	while (cin >> sig >> u >> v)
	{
		if (sig) MC.insertEdge(u, v);
		else MC.removeEdge(u, v);
		/*cout << MC.SMAX_BOUND << endl;*/
		cout << MC.H1.size() << endl;
		/*puts("");*/
	}

	fclose(fpin);
	fclose(fpout);
	//system("pause");
	return 0;
}
