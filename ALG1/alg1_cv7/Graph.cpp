#include "Graph.h"

Graph::Vertex* Graph::findVertex(int id)
{
	for (auto vertex : this->vertices) {
		if (vertex->id == id) {
			return vertex;
		}
	}

	return nullptr;
}

void Graph::insert(int id)
{
	this->vertices.push_back(new Vertex(id));
}

void Graph::insert(int id, std::vector<int> neighborIds)
{
	Vertex* newVertex = new Vertex(id);
	this->vertices.push_back(newVertex);

	for (auto neighborId : neighborIds) {
		Vertex* neighbor = findVertex(neighborId);

		if (neighbor) {
			newVertex->neighbors.push_back(neighbor);
			if (newVertex != neighbor) {
				neighbor->neighbors.push_back(newVertex);
			}
		}
	}
}

void Graph::bfs(int id)
{
	Vertex* startingVertex = findVertex(id);

	std::queue<Vertex*> que;

	que.push(startingVertex);
	startingVertex->color = 1;

	while (!que.empty()) {
		Vertex* currentVertex = que.front();
		que.pop();

		std::cout << currentVertex->id << std::endl;
		currentVertex->color = 2;

		for (auto neighbor : currentVertex->neighbors) {
			if (neighbor->color == 0) {
				que.push(neighbor);
				neighbor->color = 1;
			}
		}
	}
}