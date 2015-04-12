/****************************************************
** File:    Vertex.h
** Project: CMSC 202 Project 3, Spring 2015
** Author:  Austin DeLauney
** Date:    4/03/15
** Section: 0006
** E-mail:  adelau1@gl.umbc.edu 
**
** This file is the header file for the Vertex Class.
** This has the class declaration, method prototypes
** for the class to function properly. 
******************************************************/
#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>

using namespace std;

class Vertex {
  public:
    /* 
     * Vertex() - default constructor 
     * Preconditions: none 
     * Postconditions: creates a Vertex object with 
     * unique integer ID. 
     */ 
     Vertex(); 
    
    /* 
     * GetID() - returns the ID of the Vertex object. 
     * Preconditions: none 
     * Postconditions: returns the integer ID of the 
     * Vertex object. 
     */ 
    int GetID() const;

  private:
    friend ostream& operator<< (ostream &sout, const Vertex &v);
    int m_vertex_ID;

};
#endif