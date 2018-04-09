#include "task_two.h"

using namespace two;

void two::print_graph(int max, Edge*** graph)
{
	for (int y = 0; y <= max; y++)
	{
		for (int x = 0; x <= max; x++)
		{
			if (x == 0 && y == 0)
			{
				std::cout << "     ";
			}
			else if (y == 0 && x > 0)
			{
				printf("%7d     ", x);
			}
			else if (x == 0)
			{
				if (y < 10) std::cout << "  " << y << " |";
				else if (y < 100) std::cout << " " << y << " |";
				else std::cout << y << " |";
			}
			else
			{
				if (graph[x][y]) printf(" a=%8d ", graph[x][y]->a);
				else printf("            ");
			}
		}

		std::cout << std::endl;

		for (int x = 0; x <= max; x++)
		{
			if (x == 0)
			{
				std::cout << "    |";
			}
			else
			{
				if (graph[x][y]) printf(" c=%8.2f ", (graph[x][y]->c));
				else printf("            ");
			}
		}

		std::cout << std::endl;

		for (int x = 0; x <= max; x++)
		{
			if (x == 0)
			{
				std::cout << "    |";
			}
			else
			{
				if (graph[x][y]) printf(" u=%8.2f ", (graph[x][y]->c - graph[x][y]->c_used));
				else printf("            ");
			}
		}

		std::cout << std::endl;

		for (int x = 0; x <= max; x++)
		{
			if (x == 0)
			{
				std::cout << "    |";
			}
		}

		std::cout << std::endl;
	}
}

void two::print_paths(int max, int** path_matrix)
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

bool two::has_edge(std::vector<EdgeInfo> edges, int a, int b)
{
	for (auto it = edges.begin(); it != edges.end(); it++)
	{
		if ((*it).from == a && (*it).to == b) return true;
		if ((*it).from == b && (*it).to == a) return true;
	}

	return false;
}

Edge*** two::generate_martix(int max, std::vector<EdgeInfo> edges)
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
		matrix[(*it).from][(*it).to] = new Edge;
		matrix[(*it).to][(*it).from] = new Edge;
	}

	return matrix;
}

std::vector<int> two::get_path_rec(int from, int to, int max, int m, Edge*** graph, std::vector<int> path, unsigned int dist)
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
		if (graph[from][t] && graph[from][t]->c_used - m >= 0 && std::find(path.begin(), path.end(), t) == path.end())
		{
			std::vector<int> p = get_path_rec(t, to, max, m, graph, path, shortest.size());

			if (shortest.size() == 0 || (shortest.size() > p.size() && p.size() > 0))
			{
				shortest.swap(p);
			}			
		}
	}

	return shortest;
}

bool two::get_path(int from, int to, int max, int m, Edge*** graph, int** path_matrix)
{
	std::vector<int> dummy;
	std::vector<int> path = get_path_rec(from, to, max, m, graph, dummy, 0);

	if (path.size() == 0)
	{
		return false;
	}

	size_t path_size_minus_one = (path.size() < 1) ? 0 : (path.size() - 1);
	for (size_t i = 0; i < path_size_minus_one; i++)
	{
		path_matrix[path[i]][to] = path[i + 1];
		graph[path[i]][path[i + 1]]->c_used -= m;
		graph[path[i]][path[i + 1]]->a += 1;
	}

	return true;
}

int** two::generate_paths(int max, int m, int** N, Edge*** graph, std::vector<EdgeInfo> edges)
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
				for (int k = 0; k < N[i - 1][j - 1]; k++)
				{
					if (!get_path(i, j, max, m, graph, path_matrix))
					{
						// print_graph(max, graph);

						for (int x = 0; x <= max; x++)
						{
							delete[] path_matrix[x];
						}

						delete[] path_matrix;

						return nullptr;
					}
				}
			}
		}
	}

	return path_matrix;
}

void clear(Edge*** graph, int** path_matrix, int max)
{
	if (graph)
	{
		for (int x = 0; x <= max; x++)
		{
			for (int y = 0; y <= max; y++)
			{
				delete[] graph[x][y];
			}

			delete[] graph[x];
		}

		delete[] graph;
	}

	if (path_matrix)
	{
		for (int x = 0; x <= max; x++)
		{
			delete[] path_matrix[x];
		}

		delete[] path_matrix;
	}
}

void two::task_b(int** N, double &out_T)
{
	bool success = true;

	std::vector<EdgeInfo> edges;
	int max = 10;
	unsigned int G = 0;
	int m = 32;

	// Add edges to the vector here
	for (int i = 1; i < max / 2; i++)
	{
		edges.push_back(EdgeInfo(i, i + 1));
		edges.push_back(EdgeInfo(i + 5, i + 6));
		edges.push_back(EdgeInfo(i, i + 5));
	}
	edges.push_back(EdgeInfo(1, 5));
	edges.push_back(EdgeInfo(6, 10));
	edges.push_back(EdgeInfo(5, 10));

	Edge*** graph = generate_martix(max, edges);

	// Calculate c here
	for (int y = 1; y <= max; y++)
	{
		for (int x = 1; x <= max; x++)
		{
			if (graph[x][y] && x > y) {
				graph[x][y]->c = 200 * (rand() % 8 + 8);
				graph[x][y]->c_used = graph[x][y]->c;

				graph[y][x]->c = graph[x][y]->c;
				graph[y][x]->c_used = graph[x][y]->c;
			}
		}
	}

	int** path_matrix = generate_paths(max, m, N, graph, edges);

	if (path_matrix == nullptr)
	{
		// std::cout << "\nThe network failed due to data overflow" << std::endl;
		clear(graph, path_matrix, max);
		out_T = -1;
		return;
	}

	// print_graph(max, graph);

	// Calculate G here
	for (int x = 0; x < max; x++)
	{
		for (int y = 0; y < max; y++)
		{
			if (N[x][y])
			{
				G += N[x][y];
			}
		}
	}

	// print_graph(max, graph);
	// std::cout << std::endl;
	// print_paths(max, path_matrix);

	// Evaluate the sum here
	// T = 1/G * SUM_e( a(e)/(c(e)/m - a(e)) )
	double T = 0;

	for (int x = 1; success && x <= max; x++)
	{
		for (int y = 1; y <= max; y++)
		{
			if (graph[x][y] && graph[x][y]->a != 0 && (double)graph[x][y]->c / m - graph[x][y]->a <= 0.0) {
				success = false;
				break;
			}
			else if (graph[x][y] && graph[x][y]->a != 0)
			{
				T += (double)graph[x][y]->a / ((double)graph[x][y]->c / m - graph[x][y]->a);
			}
		}
	}

	T /= G;

	if (success)
	{
		// std::cout << "\nThe expected wait time is " << T << std::endl;
		out_T = T;
	}
	else
	{
		// std::cout << "\nThe network failed due to data overflow." << std::endl;
		out_T = -1;
	}

	clear(graph, path_matrix, max);
}

bool two::task_c(int** N, double p, double T_max)
{
	bool success = true;

	std::vector<EdgeInfo> edges;
	int max = 10;
	unsigned int G = 0;
	int m = 32;

	// Add edges to the vector here
	for (int i = 1; i < max / 2; i++)
	{
		edges.push_back(EdgeInfo(i, i + 1));
		edges.push_back(EdgeInfo(i + 5, i + 6));
		edges.push_back(EdgeInfo(i, i + 5));
	}
	edges.push_back(EdgeInfo(1, 5));
	edges.push_back(EdgeInfo(6, 10));
	edges.push_back(EdgeInfo(5, 10));

	// Remove edges based on p
	auto it = edges.begin();
	while (it != edges.end())
	{
		if ((rand() % 1000) / 1000.0 > p)
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

	// Calculate c here
	for (int y = 1; y <= max; y++)
	{
		for (int x = 1; x <= max; x++)
		{
			if (graph[x][y] && x > y) {
				graph[x][y]->c = 200 * (rand() % 8 + 8);
				graph[x][y]->c_used = graph[x][y]->c;

				graph[y][x]->c = graph[x][y]->c;
				graph[y][x]->c_used = graph[x][y]->c;
			}
		}
	}

	int** path_matrix = generate_paths(max, m, N, graph, edges);
	if (!path_matrix)
	{
		// std::cout << "\nThe network broke" << std::endl;
		clear(graph, path_matrix, max);
		return false;
	}

	// Calculate G here
	for (int x = 0; x < max; x++)
	{
		for (int y = 0; y < max; y++)
		{
			if (N[x][y])
			{
				G += N[x][y];
			}
		}
	}

	// print_graph(max, graph);
	// std::cout << std::endl;
	// print_paths(max, path_matrix);

	// Evaluate the sum here
	// T = 1/G * SUM_e( a(e)/(c(e)/m - a(e)) )
	double T = 0;

	for (int x = 1; success && x <= max; x++)
	{
		for (int y = 1; y <= max; y++)
		{
			if (graph[x][y] && graph[x][y]->a != 0 && (double)graph[x][y]->c / m - graph[x][y]->a <= 0.0) {
				success = false;
				break;
			}
			else if (graph[x][y] && graph[x][y]->a != 0)
			{
				T += (double)graph[x][y]->a / ((double)graph[x][y]->c / m - graph[x][y]->a);
			}
		}
	}

	T /= G;

	// if (success) std::cout << "\nThe expected wait time is " << T << std::endl;
	// else std::cout << "\nThe network failed due to data overflow." << std::endl;

	clear(graph, path_matrix, max);

	return success && T_max > T;
}
