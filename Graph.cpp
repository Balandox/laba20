#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <queue>
#include <fstream>
#include "Graph.h"

void Graph::load(const std::string fname) {
	std::ifstream fin(fname);
	std::vector<int> tmp_vec;
	char num;
	int tmp_num;
	if (!fin)
		throw std::exception("Can not fill graph from ");
	while (fin.get(num)) {
		if (num >= '0' && num <= '9') {
			tmp_num = (int)num - 48;
			tmp_vec.push_back(tmp_num);
		}
		else if (num == '\n') {
			this->list.push_back(tmp_vec);
			tmp_vec.clear(); tmp_vec.resize(0);
		}
	}
	if (tmp_vec.size() > 0)
		this->list.push_back(tmp_vec);
}

size_t Graph::amount_vertex() {
	return this->list.size();
}

void Graph::bfs(int v) {
	std::queue<int> graph_queue;
	this->visited.clear();  this->visited.resize(0);
	this->finding.clear(); this->finding.resize(0);
	int node = 0;
	if (v == 0)
		this->track.resize(this->list.size());
	graph_queue.push(v);
	while (!graph_queue.empty()) {
		node = graph_queue.front();
		graph_queue.pop();				// удаляем эту же вершину из очереди
		this->visited.push_back(node); // отмечаем ее как посещенную
		for (int i = 0; i < this->list[node].size(); i++)
			if (!is_visited(this->list[node][i]) && !is_finding(this->list[node][i])) {
				this->finding.push_back(this->list[node][i]);
				graph_queue.push(this->list[node][i]);
				this->track[v].push_back(this->list[node][i]);
			}
	}
}

bool Graph::is_visited(int node) {
	for (int i = 0; i < this->visited.size(); i++)
		if(this->visited[i] == node)
			return true;
	return false;
}

bool Graph::is_finding(int node) {
	for (int i = 0; i < this->finding.size(); i++)
		if (this->finding[i] == node)
			return true;
	return false;
}

void Graph::save_bfs() {
	std::ofstream fout("Distination.txt");
	fout << "List of reachable nodes:\n\n";
	for (int i = 0; i < this->track.size(); i++) {
		fout << "vertex " << i << ":  ";
		std::copy(this->track[i].begin(), this->track[i].end(), std::ostream_iterator<int>(fout, "  "));
		fout << std::endl;
	}
	
}

std::ostream& operator << (std::ostream& out, const Graph& gr) {
	std::cout << "List of reachable nodes:\n\n";
	for (int i = 0; i < gr.track.size(); i++) {
		std::cout << "vertex " << i << ":  ";
		std::copy(gr.track[i].begin(), gr.track[i].end(), std::ostream_iterator<int>(std::cout, "  "));
		std::cout << std::endl;
	}
	return out;
}

void Graph::save_dot(int v_dot) {
	std::ofstream fout("graph.dot");

	if (v_dot < 0 || v_dot >= this->track.size())
		throw std::exception("This vertex no find!");

	fout << "digraph{\n";
	fout << v_dot << " [color = red];\n";
	for (int i = 0; i < this->track[v_dot].size(); i++) {
		fout << this->track[v_dot][i] << " [color = green];\n";
	}
	for (int i = 0; i < list.size(); i++) {
		for (int j = 0; j < list[i].size(); j++) {
			fout << i << "->" << list[i][j] << ";\n";
		}
		//fout << std::endl;
	}
	fout << "\n}";
}



//dot -Tpng graph.dot -ogr.png