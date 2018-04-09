#include <algorithm>

#include <ctime>

#include "task_one.h"
#include "task_two.h"

void print_matrix(int max, int** path_matrix)
{
	for (int y = -1; y < max; y++)
	{
		for (int x = -1; x < max; x++)
		{
			if (x == -1 && y == -1)
			{
				std::cout << "    ";
			}
			else if (y == -1 && x > -1)
			{
				if (x < 10) std::cout << "  " << x << " ";
				else if (x < 100) std::cout << " " << x << " ";
				else std::cout << x << " ";
			}
			else if (x == -1)
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

void task_one()
{
	one::task_a();
	one::task_b();
	one::task_c();
	one::task_d();
}

void task_two_sim(double T_max, int iterations, int** N)
{
	std::cout << "Progress for T_max = " << T_max << ": ----------" << std::endl;
	std::cout << "                           " << std::flush;

	int success_count = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (i % (iterations / 10) == 0) std::cout << "#" << std::flush;

		if (two::task_c(N, 0.85, T_max))
		{
			success_count++;
		}
	}

	std::cout << "\nThe probability of success is " << (double)success_count / iterations * 100.0 << "% (" << success_count << "/" << iterations << ")" << std::endl;
}

void task_two()
{
	int** N = new int*[10];
	for (int i = 0; i < 10; i++) N[i] = new int[10];

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			N[x][y] = (x != y) ? std::max(0, rand() % 20 - 10) : 0;
		}
	}

	print_matrix(10, N);
	std::cout << std::endl;

	int iterations = 10000;

	double T_sum = 0;
	int T_times = 0;

	for (int i = 0; i < iterations; i++)
	{
		if (i % (iterations / 10) == 0)
		{
			std::cout << "#" << std::flush;
		}

		double T;
		two::task_b(N, T);
		if (T != -1)
		{
			T_sum += T;
			T_times++;
		}
	}
	std::cout << std::endl;

	T_sum /= T_times;
	std::cout << "Average T = " << T_sum << std::endl;
	std::cout << std::endl;

	iterations = 10000;
	for (int T_max = 90; T_max >= 0; T_max -= 10)
	{
		task_two_sim((double)T_max / 1000, iterations, N);
	}
}

int main()
{
	std::srand((unsigned int)time(NULL));

	// task_one();
	task_two();

	std::cin.get();
}