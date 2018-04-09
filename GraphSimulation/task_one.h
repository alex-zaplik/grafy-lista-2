#pragma once

#include <vector>
#include <iostream>
#include <cstdio>

namespace one
{
	typedef struct EdgeInfo
	{
		int from, to;
		double h;

		EdgeInfo(int from, int to, double h) : from{ from }, to{ to }, h{ h } {}
	} EdgeInfo;

	typedef struct Edge
	{
		double h;

		Edge(double h) : h{ h } {}
	} Edge;

	void print_graph(int max, Edge*** graph);
	void print_paths(int max, int** path_matrix);
	bool has_edge(std::vector<EdgeInfo> edges, int a, int b);
	Edge*** generate_martix(int max, std::vector<EdgeInfo> edges);
	std::vector<int> get_shortest_path_rec(int from, int to, int max, Edge*** graph, std::vector<int> path, unsigned int dist);
	void get_shortest_path(int from, int to, int max, Edge*** graph, int** path_matrix);
	int** generate_paths(int max, Edge*** graph, std::vector<EdgeInfo> edges);
	int simulate_iter(std::vector<EdgeInfo> edges, int max);
	double simulate(std::vector<EdgeInfo> &edges, int n, int max);
	void task_a();
	void task_b();
	void task_c();
	void task_d();
}
