/************************************************************
** File:    Vertex.cpp
** Project: CMSC 202 Project 3, Spring 2015
** Author:  Austin DeLauney
** Date:    4/03/15
** Section: 0006
** E-mail:  adelau1@gl.umbc.edu 
**
** This file is the implementation file for the Vertex Class.
** This file also has the declaration of the static int 
** VERTEX_COUNT variable, because you can't instatiate it in
** the header (well at least you shouldn't). 
*************************************************************/
#include <cstdio>
#include "Vertex.h"

using namespace std;

static int VERTEX_COUNT = 0; //The count of vertices that is used to be set m_vertex_ID

Vertex::Vertex()
{
  //Set the vertex ID to the current count, and then increment for next assignment
  m_vertex_ID = VERTEX_COUNT++;
}

int Vertex::GetID() const
{
  return m_vertex_ID;
}

ostream& operator<< (ostream &sout, const Vertex &v)
{
  //Two spaces for formating
  sout << "  ID: " << v.GetID();
  return sout;
}
