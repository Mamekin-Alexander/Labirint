#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <algorithm>
#include <vector>
typedef std::pair<int, int> Point2D;
int main()
{
	std::ifstream input("Maze.dat");
	if (!input.is_open())
		return -1;
	int height=0, width=0;
	input >> height>> width;
	
	int** a = new int* [height+2];
	int** dist_map = new int* [height+2];
	for (int i = 0; i < height+2; i++)
	{
		a[i] = new int[width+2];
		dist_map[i] = new int[width+2];
	}

	for (int i = 1; i <= height; i++)
		for (int j = 1; j <= width; j++)
			input >> a[i][j];
	
	//walls on perimetr
	for (int i = 0; i < height + 2; i++)
	{
		a[i][0] = 1;						
		a[i][width + 1] = 1;			
	}
	for (int i = 0; i < width + 2; i++)					
	{
		a[0][i] = 1;
		a[width + 1][i] = 1;
	}

	for (int i = 0; i < height+2; i++)
		for (int j = 0; j < width+2; j++)
			dist_map[i][j] = -1;


	std::cout << "Enter initial and distination coords. Counting starts form 1\n";
	int x1=0, y1=0, x2=0, y2=0;
	std::cin >> x1>> y1>> x2>> y2;

	std::queue<Point2D> q;

	dist_map[x1][y1] = 0;
	q.push(Point2D(x1, y1));

	while (!q.empty())
	{
		Point2D p = q.front();
		q.pop();
		int x = p.first;
		int y = p.second;

		if (a[x - 1][y] == 0 && (dist_map[x - 1][y] == -1 || dist_map[x][y] + 1 < dist_map[x - 1][y]))
		{
			q.push(Point2D(x - 1, y));
			dist_map[x - 1][y] = dist_map[x][y] + 1;
		}
		if (a[x + 1][y] == 0 && (dist_map[x + 1][y] == -1 || dist_map[x][y] + 1 < dist_map[x + 1][y]))
		{
			q.push(Point2D(x + 1, y));
			dist_map[x + 1][y] = dist_map[x][y] + 1;
		}
		if (a[x][y - 1] == 0 && (dist_map[x][y - 1] == -1 || dist_map[x][y] + 1 < dist_map[x][y - 1]))
		{
			q.push(Point2D(x, y - 1));
			dist_map[x][y - 1] = dist_map[x][y] + 1;
		}
		if (a[x][y + 1] == 0 && (dist_map[x][y + 1] == -1 || dist_map[x][y] + 1 < dist_map[x][y + 1]))
		{
			q.push(Point2D(x, y + 1));
			dist_map[x][y + 1] = dist_map[x][y] + 1;
		}
	}

	int x = x2, y = y2;
	std::vector<Point2D> Way;

	if (dist_map[x2][y2] == -1)
		std::cout << "There is no way!\n";
	else
	{
		Way.push_back(Point2D(x2, y2));
		while ((x != x1) || (y != y1))
		{
			if (dist_map[x - 1][y] == dist_map[x][y] - 1)
			{
				Way.push_back(Point2D(x - 1, y));
				x = x - 1;
				continue;
			}
			if (dist_map[x + 1][y] == dist_map[x][y] - 1)
			{
				Way.push_back(Point2D(x + 1, y));
				x = x + 1;
				continue;
			}
			if (dist_map[x][y - 1] == dist_map[x][y] - 1)
			{
				Way.push_back(Point2D(x, y - 1));
				y = y - 1;
				continue;
			}
			if (dist_map[x][y + 1] == dist_map[x][y] - 1)
			{
				Way.push_back(Point2D(x, y + 1));
				y = y + 1;
				continue;
			}
		}
		if (!Way.empty())
			for (int i = Way.size() - 1; i >= 0; i--)
				std::cout << Way.at(i).first << " " << Way.at(i).second << '\n';
	}
	input.close();
}


