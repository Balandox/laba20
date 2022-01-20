#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <fstream>

class Graph {
private:
	std::vector<std::vector<int>> list;  // список смежности
	std::vector<int> visited;   // вершины в которых я уже был
	std::vector<std::vector<int>> track;    // список всех доступных вершин из вершины v
	std::vector<int> finding;
public:
	void load(const std::string fname);
	void bfs(int v);
	size_t amount_vertex();
	bool is_visited(int node);
	bool is_finding(int node);
	friend std::ostream& operator << (std::ostream& out, const Graph& m);
};

#endif

