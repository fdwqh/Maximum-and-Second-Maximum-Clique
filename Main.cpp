#include "Maxclique.h"

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<bool>> A(n);
	vector<int> degree(n);
	for (int i = 0; i < n; i++)
		A[i].resize(n);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		A[u][v] = A[v][u] = 1;
		degree[u]++;
		degree[v]++; 
	}
	UGraph MC(n, A, degree); 

	MC.search();
	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << MC.A[i][j] << ' ';
		cout << endl;
	}*/

	system("pause");
	return 0;
}
