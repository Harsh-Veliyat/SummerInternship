#include<iostream>
#include<vector>
#include<map>
#include<queue>
using namespace std;

template<class T>
class Graph
{
private:
	map < T, vector<T> > edge;

	void DFS_Recursive(T start, map<T, bool>& visited)
	{
		cout << start << " ";
		visited[start] = true;
		for (auto i : edge[start])
		{
			if (!visited[i])
			{
				DFS_Recursive(i, visited);
			}
		}
	}

	void printAdjacencyList()
	{
		for (auto i : edge) // auto = map<T, vector<T>>::iterator, cannot use T during typedef.
		{
			cout << i.first << " : ";
			for (auto j : i.second)
			{
				cout << j << " -> ";
			}

			cout << endl;
		}
	}

	void BFS(T start)
	{
		queue<T> q;
		map<T, bool> visited;
		q.push(start);
		cout << "BFS from " << start << ": ";
		while (!q.empty())
		{
			T node = q.front();
			q.pop();
			visited[node] = true;
			cout << node << " ";
			for (auto i : edge[node])
			{
				if (visited[i] == false)
				{
					q.push(i);
					visited[i] = true;
				}
			}
		}
		cout << endl;
	}

	void DFS(T start)
	{
		map<T, bool> visited;
		for (auto i : edge)
		{
			visited[i.first] = false;
		}
		cout << "DFS from " << start << ": ";
		DFS_Recursive(start, visited);
		cout << endl;
	}
public:
	void addEdge(T v1, T v2)
	{
		edge[v1].push_back(v2);
	}

	void printGraph()
	{
		return printAdjacencyList();
	}

	void doBFS(T startFrom)
	{
		return BFS(startFrom);
	}

	void doDFS(T startFrom)
	{
		return DFS(startFrom);
	}
	
};

int main()
{
	cout << "------------------\n" << endl;
	Graph<int> Gint;
	Gint.addEdge(0, 2);
	Gint.addEdge(1, 3);
	Gint.addEdge(2, 4);
	Gint.addEdge(2, 0);
	Gint.addEdge(3, 5);
	Gint.addEdge(2, 5);
	Gint.addEdge(1, 0);
	Gint.printGraph();
	
	cout << "\n------------------\n" << endl;
	
	Graph<string> Gstr;
	Gstr.addEdge("A", "C");
	Gstr.addEdge("B", "D");
	Gstr.addEdge("A", "E");
	Gstr.addEdge("G", "F");
	Gstr.addEdge("D", "G");
	Gstr.addEdge("G", "A");
	Gstr.addEdge("C", "D");
	Gstr.addEdge("H", "G");
	Gstr.printGraph();

	cout << "\n------------------\n" << endl;

	Gstr.doDFS("A");
	Gstr.doBFS("A");
	Gstr.doBFS("C");
	Gstr.doDFS("C");
	return 0;
}