#pragma once
#include <vector>
#include <queue>
#include <iostream>

class Graph {
private:
	class Vertex {
	public:
		int id;
		std::vector<Vertex*> neighbors;
		int color = 0; // 0 - white, 1 - gray, 2 - black

		Vertex(int id) { this->id = id; }
	};

	std::vector<Vertex*> vertices;

	Vertex* findVertex(int id);

public:
	void insert(int id);
	void insert(int id, std::vector<int> neighborsId);
	void bfs(int id);
};