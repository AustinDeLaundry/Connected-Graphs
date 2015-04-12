/********************************************
** File:    Edge.cpp
** Project: CMSC 202 Project 3, Spring 2015
** Author:  Austin DeLauney
** Date:    4/03/15
** Section: 0006
** E-mail:  adelau1@gl.umbc.edu 
**
** This file is the implementation for Edge.h
** It stores two vertices that are connected
** and lets you set and get them. Also 
** includes a cout overridden method
*********************************************/
#include <iostream>
#include <cstdlib>
#include "Vertex.h"
#include "Edge.h"

using namespace std;

Edge::Edge(Vertex *v1, Vertex *v2)
{
	//If one of the vertices is invalid
	if(v1 == NULL || v2 == NULL)
	{
		cerr << "Error in createing an edge. Is it possible that one of the vertices is null? I think so :^)" << endl;
		exit(1);
	}

	//Both vertices are valid go ahead and set them
	else
	{
		m_v1 = v1;
		m_v2 = v2;
	}
}

Vertex* Edge::GetV1() const
{
	return m_v1;
}

Vertex* Edge::GetV2() const
{
	return m_v2;
}

void Edge::SetV1(Vertex *v)
{
	if(v != NULL)
	{
		//Delete the current one to return memory
		delete m_v1;
		m_v1 = v;
	}

	else
		cerr << "Stop trying to set things to NULL! It makes me mad >:(." << endl;
}

void Edge::SetV2(Vertex *v)
{
	if(v != NULL)
	{
		//Delete the current one to return memory
		delete m_v2;
		m_v2 = v;
	}

	else
		cerr << "Stop trying to set things to NULL! It makes me mad >:(." << endl;
}

ostream& operator<<(ostream &sout, const Edge &e)
{
	//Print format: 
	//  ID: x <-->  ID: y
	sout << *e.GetV1() << " <--> " << *e.GetV2();
	return sout;
}
