/******************************************
** File:    Graph.cpp
** Project: CMSC 202 Project 3, Spring 2015
** Author:  Austin DeLauney
** Date:    4/03/15
** Section: 0006
** E-mail:  adelau1@gl.umbc.edu 
**
** This file is the main gist of Project 3.
** It holds all of the vertices and edges
** that are given through the loaded file.
** Also has the GetAdjacencyMatrix method
** which returns a matrix with all of the 
** edges with respect to the vertex. This
** file also has the method of finding out
** which vertices are connected to each
** other.
*******************************************/
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

using namespace std;

Graph::Graph()
{ /* nothing to do */ }

Graph::Graph(vector<Vertex *> vertices, vector<Edge *> edges) :
	m_vertices(vertices), m_edges(edges)
{
	for (int i = 0; i < vertices.size(); i++)
		if (vertices[i] == NULL) {
			cerr << "Error: Graph constructor expects non-null vertices." << endl;
			exit(1);
		}
  
	for (int i = 0; i < edges.size(); i++)
		if (edges[i]->GetV1() == NULL || edges[i]->GetV2() == NULL) {
			cerr << "Error: Graph constructor expects edges with non-null vertices." << endl;
			exit(1);
		}
}     

bool Graph::LoadFromFile(string fileName) {
	int numVertices;
	int v1, v2;
	vector<Vertex*> vertices;
	vector<Edge*> edges;
	ifstream dataFile;

	/* Set exception flags for file input stream */ 

	dataFile.exceptions(ios::failbit | ios::badbit);

	try {

		dataFile.open(fileName.c_str());
		dataFile >> numVertices;

		for ( int i = 0; i < numVertices; i++ )
			vertices.push_back( new Vertex() );

		dataFile >> v1 >> v2;
  
		while ( v1 > 0 && v2 > 0 ) {
			if (v1 <= numVertices && v2 <= numVertices )
				edges.push_back( new Edge(vertices[v1-1], vertices[v2-1]) );
			dataFile >> v1 >> v2;
		}

		dataFile.close();
	}

	catch (exception e) {
		return false;
	}

	m_vertices = vertices;
	m_edges = edges;

	return true;
}

int Graph::GetNumVertices() const
{
	//Cast m_vertices.size to an int and return it
	return (int)m_vertices.size();
}

int Graph::GetNumEdges() const
{
	//Cast m_edges.size to an int and return it
	return (int)m_edges.size();
}

vector<Vertex *> Graph::GetVertices() const
{
	return m_vertices;
}

vector<Edge *> Graph::GetEdges() const
{
	return m_edges;
}

Matrix Graph::GetAdjacencyMatrix() const
{
	Matrix toRet(GetNumVertices(), GetNumVertices()); //Matrix of edges between vertecies

	//So we don't go out of bounds 
	int vertexOffset = GetVertices()[GetVertices().size() - 1] -> GetID() + 1 - GetNumVertices();

	//Make each vertex connected to itself
	for(int i = 0; i < GetNumVertices(); i++)
		toRet.Set(i, i, 1.0);

	//Set each vertex connected to each other when theres an edge
	for(int i = 0; i < GetNumEdges(); i++)
	{
		toRet.Set(m_edges.at(i) -> GetV1() -> GetID() - vertexOffset, m_edges.at(i) -> GetV2() -> GetID() - vertexOffset, 1.0);
		toRet.Set(m_edges.at(i) -> GetV2() -> GetID() - vertexOffset, m_edges.at(i) -> GetV1() -> GetID() - vertexOffset, 1.0);
	}

	//Print out the adjacencyMatrix (Testing purposes)
	/*
	for(int i = 0; i < GetNumVertices(); i++)
	{
		for(int j = 0; j < GetNumVertices(); j++)
			printf("%1.0f ", toRet.Get(i, j));
		printf("\n");
	}
	*/

	return toRet;
}

vector<Vertex *> Graph::GetConnectedComponent(Vertex *v) const
{
	vector<Vertex* > toReturn;                      //Connected vertexes to *v
	Matrix adjacencyMatrix(GetAdjacencyMatrix());   //Adjacency matix of the graph
	vector<double> x;                               //Double vector that will be multiplyed

	//So we don't go out of bounds
	int vertexOffset = GetVertices()[GetVertices().size() - 1] -> GetID() + 1 - GetNumVertices();

	//For each row in the matrix
	for(int i = 0; i < adjacencyMatrix.GetNumRows(); i++)
	{
		//If the vertex has the ID we're looking for
		if(i == v -> GetID() - vertexOffset)
			x.push_back(1);	//Add a 1 to the double vector because that's the vertex we're looking to multiply with

		else
			x.push_back(0);	//Add 0 because we need to fill the matrix 0 so it doesn't have a blank
	}

	//Answer holds all of the vertices that are connected (reperesented)
	vector<double> answer = adjacencyMatrix.Matvec(x);

	//For each edge
	for(int i = 0; i < adjacencyMatrix.GetNumRows(); i++)
	{
		//For each double in answer
		for(int j = 0; j < answer.size(); j++)
		{
  		//If it does not equal 1 set it to 1, because if we don't the number may be greater than allowed
  		if(answer.at(j) != 0)
			{
				answer[j] = 1;
  		}
		}

		//Keep multiplying because we need to get the vertices connected to the other vertices
		answer = adjacencyMatrix.Matvec(answer);
	}

	//For each answer
	for(int i = 0; i < answer.size(); i++)
	{
		//If it's connected
		if(answer.at(i) != 0)
		{
  			//Add to the vector because it is connected
  			toReturn.push_back(this -> GetVertices().at(i));
		}
	}

	return toReturn;
}