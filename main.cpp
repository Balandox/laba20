#include <iostream>
#include <fstream>
#include <vector>
#include "Graph.h"


int main() {
	Graph g;
	int v_dot = 0;
	std::string fname = "adjacency_list1";
	try {
		g.load(fname);
	}
	catch (std::exception& e) {
		std::cout << e.what() << fname;
	}
	for (int i = 0; i < g.amount_vertex(); i++)
		g.bfs(i);
	g.save_bfs();
	/*try {
		std::cout << "Input vertex: ";
		std::cin >> v_dot;
		g.save_dot(v_dot);
	}
	catch (std::exception& e) {
		std::cout << e.what() << fname;
	}*/
	return 0;
}