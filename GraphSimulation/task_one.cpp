#include "task_one.h"

using namespace one;

void one::print_graph(int max, Edge*** graph)
{
	for (int y = 0; y <= max; y++)
	{
		for (int x = 0; x <= max; x++)
		{
			if (x == 0 && y == 0)
			{
				std::cout << "    ";
			}
			else if (y == 0 && x > 0)
			{
				if (x < 10) std::cout << "  " << x << " ";
				else if (x < 100) std::cout << " " << x << " ";
				else std::cout << x << " ";
			}
			else if (x == 0)
			{
				if (y < 10) std::cout << "  " << y << " ";
				else if (y < 100) std::cout << " " << y << " ";
				else std::cout << y << " ";
			}
			else
			{
				if (graph[x][y]) printf("%.2f", graph[x][y]->h);
				else std::cout << "    ";
			}
		}

		std::cout << std::endl;
	}
}

void one::print_paths(int max, int** path_matrix)
{
	for (int y = 0; y <= max; y++)
	{
		for (int x = 0; x <= max; x++)
		{
			if (x == 0 && y == 0)
			{
				std::cout << "    ";
			}
			else if (y == 0 && x > 0)
			{
				if (x < 10) std::cout << "  " << x << " ";
				else if (x < 100) std::cout << " " << x << " ";
				else std::cout << x << " ";
			}
			else if (x == 0)
			{
				if (y < 10) std::cout << "  " << y << " ";
				else if (y < 100) std::cout << " " << y << " ";
				else std::cout << y << " ";
			}
			else
			{
				printf("%4d", path_matrix[x][y]);
			}
		}

		std::cout << std::endl;
	}
}

bool one::has_edge(std::vector<EdgeInfo> edges, int a, int b)
{
	for (auto it = edges.begin(); it != edges.end(); it++)
	{
		if ((*it).from == a && (*it).to == b) return true;
		if ((*it).from == b && (*it).to == a) return true;
	}

	return false;
}

Edge*** one::generate_martix(int max, std::vector<EdgeInfo> edges)
{
	Edge*** matrix = new Edge**[max + 1];
	for (int x = 0; x < max + 1; x++)
	{
		matrix[x] = new Edge*[max + 1];

		for (int y = 0; y < max + 1; y++)
		{
			matrix[x][y] = nullptr;
		}
	}

	for (auto it = edges.begin(); it != edges.end(); it++)
	{
		matrix[(*it).from][(*it).to] = new Edge((*it).h);
		matrix[(*it).to][(*it).from] = new Edge((*it).h);
	}

	return matrix;
}

std::vector<int> one::get_shortest_path_rec(int from, int to, int max, Edge*** graph, std::vector<int> path, unsigned int dist)
{
	path.push_back(from);

	if (dist < path.size() && dist > 0)
	{
		return path;
	}

	if (from == to)
	{
		return path;
	}

	std::vector<int> shortest;

	for (int t = 1; t <= max; t++)
	{
		if (graph[from][t] && std::find(path.begin(), path.end(), t) == path.end())
		{
			std::vector<int> p = get_shortest_path_rec(t, to, max, graph, path, shortest.size());

			if (shortest.size() == 0 || (shortest.size() > p.size() && p.size() > 0))
			{
				shortest.swap(p);
			}
		}
	}

	return shortest;
}

void one::get_shortest_path(int from, int to, int max, Edge*** graph, int** path_matrix)
{
	if (path_matrix[from][to] != -1)
	{
		return;
	}

	std::vector<int> dummy;
	std::vector<int> path = get_shortest_path_rec(from, to, max, graph, dummy, 0);

	if (path.size() == 0)
	{
		return;
	}

	size_t path_size_minus_one = (path.size() < 1) ? 0 : (path.size() - 1);
	for (size_t i = 0; i < path_size_minus_one; i++)
	{
		path_matrix[path[i]][to] = path[i + 1];
	}
}

int** one::generate_paths(int max, Edge*** graph, std::vector<EdgeInfo> edges)
{
	int** path_matrix = new int*[max + 1];
	for (int i = 0; i < max + 1; i++)
	{
		path_matrix[i] = new int[max + 1];

		for (int j = 0; j < max + 1; j++)
		{
			path_matrix[i][j] = -1;
		}
	}

	for (int i = 1; i <= max; i++)
	{
		for (int j = 1; j <= max; j++)
		{
			if (i != j)
			{
				get_shortest_path(i, j, max, graph, path_matrix);
			}
		}
	}

	return path_matrix;
}

int one::simulate_iter(std::vector<EdgeInfo> edges, int max)
{
	auto it = edges.begin();
	while (it != edges.end())
	{
		if ((rand() % 1000) / 1000.0 >(*it).h)
		{
			int index = it - edges.begin();
			edges.erase(it);
			it = edges.begin() + index;
		}
		else
		{
			it++;
		}
	}

	Edge*** graph = generate_martix(max, edges);
	int** path_matrix = generate_paths(max, graph, edges);

	int negative_ones = -max;
	for (int x = 1; x <= max; x++)
	{
		for (int y = 1; y <= max; y++)
		{
			if (path_matrix[x][y] == -1)
			{
				negative_ones++;
			}
		}
	}

	for (int x = 0; x <= max; x++)
	{
		for (int y = 0; y <= max; y++)
		{
			delete[] graph[x][y];
		}

		delete[] graph[x];
	}

	delete[] graph;

	for (int x = 0; x <= max; x++)
	{
		delete[] path_matrix[x];
	}

	delete[] path_matrix;

	if (negative_ones == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

double one::simulate(std::vector<EdgeInfo> &edges, int n, int max)
{
	int success_count = 0;

	for (int i = 0; i < n; i++)
	{
		success_count += simulate_iter(edges, max);
	}

	return (double)success_count / n;
}

void one::task_a()
{
	std::cout << "Starting task A..." << std::endl;

	std::vector<EdgeInfo> edges;
	int max = 20;

	for (int i = 1; i < max; i++)
	{
		edges.push_back(EdgeInfo(i, i + 1, 0.95));
	}

	std::cout << "A: " << simulate(edges, 1000, max) << "\n" << std::endl;
}

void one::task_b()
{
	std::cout << "Starting task B..." << std::endl;

	std::vector<EdgeInfo> edges;
	int max = 20;

	for (int i = 1; i < max; i++)
	{
		edges.push_back(EdgeInfo(i, i + 1, 0.95));
	}
	edges.push_back(EdgeInfo(1, 20, 0.95));

	std::cout << "B: " << simulate(edges, 1000, max) << "\n" << std::endl;
}

void one::task_c()
{
	std::cout << "Starting task C..." << std::endl;

	std::vector<EdgeInfo> edges;
	int max = 20;

	for (int i = 1; i < max; i++)
	{
		edges.push_back(EdgeInfo(i, i + 1, 0.95));
	}
	edges.push_back(EdgeInfo(1, 20, 0.95));
	edges.push_back(EdgeInfo(1, 10, 0.8));
	edges.push_back(EdgeInfo(5, 15, 0.7));

	std::cout << "C: " << simulate(edges, 1000, max) << "\n" << std::endl;
}

void one::task_d()
{
	std::cout << "Starting task D..." << std::endl;

	std::vector<EdgeInfo> edges;
	int max = 20;

	for (int i = 1; i < max; i++)
	{
		edges.push_back(EdgeInfo(i, i + 1, 0.95));
	}
	edges.push_back(EdgeInfo(1, 20, 0.95));
	edges.push_back(EdgeInfo(1, 10, 0.8));
	edges.push_back(EdgeInfo(5, 15, 0.7));

	for (int i = 0; i < 4; i++)
	{
		int from = rand() % 20 + 1;
		int to = rand() % 20 + 1;

		while (from == to || has_edge(edges, from, to))
		{
			from = rand() % 20 + 1;
			to = rand() % 20 + 1;
		}

		edges.push_back(EdgeInfo(from, to, 0.4));
	}

	std::cout << "D: " << simulate(edges, 1000, max) << "\n" << std::endl;
}