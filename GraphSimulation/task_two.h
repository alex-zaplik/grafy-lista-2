#pragma once

#include <vector>
#include <iostream>
#include <cstdio>
#include <queue>

namespace two
{
	typedef struct EdgeInfo
	{
		int from, to;
		int a;
		double c;

		EdgeInfo(int from, int to) : from{ from }, to{ to }, a{ 0 }, c{ 0.0 } {}
	} EdgeInfo;

	typedef struct Edge
	{
		int a;
		double c, c_used;

		Edge() : a{ 0 }, c{ 0.0 }, c_used{ 0.0 } {}
	} Edge;

	void print_graph(int max, Edge*** graph);
	void print_paths(int max, int** path_matrix);
	bool has_edge(std::vector<EdgeInfo> edges, int a, int b);
	Edge*** generate_martix(int max, std::vector<EdgeInfo> edges);
	std::vector<int> get_path_rec(int from, int to, int max, int m, Edge*** graph, std::vector<int> path, unsigned int dist);
	bool get_path(int from, int to, int max, int m, Edge*** graph, int** path_matrix);
	int** generate_paths(int max, int m, int** N, Edge*** graph, std::vector<EdgeInfo> edges);
	void task_b(int** N, double &out_T);
	bool task_c(int** N, double p, double T_max);
}