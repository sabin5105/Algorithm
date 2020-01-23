// 그래프에서 정점끼리의 최단 경로를 구하는 방법

#include<iostream>
#include<vector>
#include<utility>	// pair
#include<stack>

#define MAX 987654321
#define NIL -1
using namespace std;

int n, m;

vector<vector<pair<int, int>>> fw;
stack<int> path;

int main()
{
	cin >> n >> m;
	fw.resize(n + 1);	// 테이블 초기화
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fw[i].push_back(make_pair(MAX, NIL));
			if (i == j) fw[i][j].first = 0;
		}
	}
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		fw[u - 1][v - 1].first = w;
		fw[u - 1][v - 1].second = u - 1;
	}
	//--------------------------------------------------------
	printf("--------초기 테이블---------\n");
	printf("--거리\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf(fw[i][j].first == MAX ? "INF\t" : "%d\t", fw[i][j].first);
		}
		printf("\n");
	}
	//---------------------------------------------------------
	printf("--직전 프로시저\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf(fw[i][j].second == MAX ? "INF\t" : "%d\t", fw[i][j].second + 1);
		}
		printf("\n");
	}
	for (int i = 0; i < n; i++)
		for(int j=0;j<n;j++)
			for (int k = 0; k < n; k++)
			{
				if (fw[k][j].first > fw[k][i].first + fw[i][j].first)
				{
					fw[k][j].first = fw[k][i].first + fw[i][j].first;
					fw[k][j].second = fw[i][j].second;
				}
			}
	//----------------------------------------------------------
	printf("\n///////////완료 후 테이블/////////\n");
	printf("--거리\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf(fw[i][j].first == MAX ? "INF\t" : "%d\t", fw[i][j].first);
		}
		printf("\n");
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf(fw[i][j].second == MAX ? "INF\t" : "%d\t", fw[i][j].second + 1);
		}
		printf("\n");
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (fw[i][j].second == NIL) continue;
			printf("%d부터 %d까지의 경로 : ", i + 1, j + 1);
			int pre = j;
			path.push(j + 1);

			while (i != fw[i][pre].second)
			{
				pre = fw[i][pre].second;
				path.push(pre + 1);
			}
			printf("%d", i + 1);
			while (!path.empty())
			{
				printf("-%d", path.top());
				path.pop();
			}
			printf("\n");
		}
	}
}