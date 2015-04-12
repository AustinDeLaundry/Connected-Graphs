/******************************************
** File:    proj3.cpp
** Project: CMSC 202 Project 3, Spring 2015
** Author:  Austin DeLauney
** Date:    4/03/15
** Section: 0006
** E-mail:  adelau1@gl.umbc.edu 
**
** This file is the runner for project 3.
** In main it prints out the status of a 
** loaded file. Then waits for user input
** and does the action corresponding to
** the user's selection. 
*******************************************/
#include <iostream>
#include <cstdio>
#include "Graph.h"

using namespace std;

void PrintFileStatus(string fileName);

/*
 * PrintOptions()
 * Prints option that the program can do
 * Pre:  None
 * Post: Options displayed to screen
 */
void PrintOptions();

/*
 * TakeSelection()
 * Gets user input from user regarding which action they want
 * Pre:  Options displayed to screen
 * Post: Returns a valid selection for an acrtion
 */
char TakeSelection();

/*
 * LoadFile(Graph*, string*)
 * Loads a file into the CioherMessage pointer, prints out if there is any file loaded, 
 * Pre:  User must've selected to load file
 * Post: Attempt to load file into message, true if file loads, false if it doesn't
 */
bool LoadFile(Graph* graph, string* fileName);

/*
 * ValidVertex(Graph*, int)
 * Checks if the vertex ID givenis valid for the loaded file
 * Pre:  Graph is a valid graph object, and vertexID is an integer within the range of int
 * Post: Returns wether the vertex is able to be accessed by the graph
 */
bool ValidVertex(Graph* graph, int vertexID);

/*
 * ListVertices(Graph*)
 * Prints the vertices in graph
 * Pre:  Graph has a loaded file
 * Post: Prints out all of the vertices within the graph instance to the CLI
 */
void ListVertices(Graph* graph);

/*
 * ListEdges(Graph*)
 * Prints out the edges between vertices
 * Pre:  Graph has a loaded file
 * Post: Prints out each edge from the connected vertices to the CLI
 */
void ListEdges(Graph* graph);

/*
 * ListConnectedComponent(Graph*)
 * Prints all of the IDs connected to a given ID (Gets ID in method)
 * Pre:  Graph has a loaded file
 * Post: Prints out all of the IDs connected to the given ID
 */
void ListConnectedComponent(Graph* graph);

int main()
{
  string fileName = ""; //Name of the file
  char selection = '\0'; //Current selection is null
  Graph graph; //Create a Graph object

  //While user wants to keep going
  while(selection != 'q') 
  {
    //Print the status of the file
    PrintFileStatus(fileName);

    //Print the options and take user input
    PrintOptions();
    selection = TakeSelection();

    //Switch through the users selection
    switch(selection)
    {
      //Load file
      case('l'): 
      {
        printf("Enter the file name: ");
        string oldFileName = fileName; //Take the old file name, just incase if the inputted one is invalid
        cin >> fileName;

        if(!LoadFile(&graph, &fileName)) //If file is invalid, rewrite fileName so it prints out correct file loaded
        {
          fileName = oldFileName;
        }

            break;
      }

      //List verticies of the loaded graph
      case('v'):
      {
        ListVertices(&graph);
        break;
      }

      //List edges of the loaded graph
      case('e'):
      {
        ListEdges(&graph);
        break;
      }

      //List the connected component of the specific vertex
      case('c'):
      {
        ListConnectedComponent(&graph);
        break;
      }

      //Quit program
      case('q'):
        printf("\nGoodbye!\n");
        break;
    }
  }

  //Return with no errors
  return 0;
}

void PrintFileStatus(string fileName)
{
  printf("\n"); //Add a new line to make it pretty

  if(fileName == "") //There is no file loaded
    printf("There is no data file loaded");

  else //There is a file loaded
    printf("The data file %s is loaded\n", fileName.c_str());

  printf("\n"); //Add a new line to make it pretty
}

void PrintOptions()
{
  //Print all options possible
  printf("Choose an action from the following menu: \n\n");
  printf(" l - load a data file\n");
  printf(" v - list the vertices of the loaded graph\n");
  printf(" e - list the edges of the loaded graph \n");
  printf(" c - list the connected component of a specific vertex\n");
  printf(" q - quit\n");
}

char TakeSelection()
{
  char selection = '\0';        //Selection
  bool properSelection = false;    //Current selection is '\0', so not valid

  //While we don't have a proper selection
  while(!properSelection)
  {
    //Get selection
    printf("Selection: ");
    cin >> selection;

    switch(selection)
    {
      //If proper selection set properSelection true to break loop
      case('l'): case('v'): case('e'):
      case('c'): case('q'):
        properSelection = true;
        break;

      //Not a proper selection, keep it false and print error
      default: 
        printf("ERROR! Please select again!\n");
        break;
    }
  }

  return selection;
}

bool LoadFile(Graph* graph, string* fileName)
{
  //If error in loading file
  if(!graph -> LoadFromFile(*fileName))
  {
    //Print error
    printf("Error loading the data file (%s)\n", fileName -> c_str());
    return false;
  }

  else
  {
    //Delete all of the previous values in the Graph m_vertices and m_edges so there isn't a memory leak
    for(int i = 0; i < graph -> GetNumVertices(); i++)
      delete graph -> GetVertices().at(i);

    for(int i = 0; i < graph -> GetNumEdges(); i++)
      delete graph -> GetEdges().at(i);

    return true;
  }
}

bool ValidVertex(Graph* graph, int vertexID)
{
  //Vertex offset (Used so all valid vertices will be in range from 0 to GetNumVertices - 1)
  int vertexOffset = graph -> GetVertices()[graph -> GetVertices().size() - 1] -> GetID() + 1 - graph -> GetNumVertices();

  //If the vertexID is from 0 to GetNumVertices - 1
  //AKA A valid vertex
  if(0 <= vertexID - vertexOffset && vertexID - vertexOffset < graph -> GetNumVertices())
    return true;

  else
    return false;
}

void ListVertices(Graph* graph)
{
  printf("\nVertices:\n"); //Note: we're printing out vertices

  //Print out each vertex ID in the graph
  for(int i = 0; i < graph -> GetNumVertices(); i++)
    cout << *graph -> GetVertices().at(i) << endl;
}

void ListEdges(Graph* graph)
{
  printf("\nEdges:\n"); //Note: We're print out edges

  //Prints each edge
  for(int i = 0; i < graph -> GetNumEdges(); i++)
    cout << *graph -> GetEdges().at(i) << endl; 
}

void ListConnectedComponent(Graph* graph)
{
  //Get the vertex to test connectedness
  printf("Give me a me a vertex ID: ");
  int vertexToTest = 0;
  cin >> vertexToTest;

  //If the user gives us a valid vertex
  if(ValidVertex(graph, vertexToTest))
  {
      //Get the vertex list
      vector<Vertex *> vertices = graph -> GetVertices();

      //Pointer to the vertex to test
      Vertex* toTest = NULL;

      //Get the vertex
      for(int i = 0; i < vertices.size(); i++)
      {
        if(vertices.at(i) -> GetID() == vertexToTest)
          toTest = vertices.at(i);
      }

      //Get each vertex that is connected to the requested vertex
      vector<Vertex *> connectedIDs = graph -> GetConnectedComponent(toTest);

      //Print out each vertex that's connected
      for(int i = 0; i < connectedIDs.size(); i++)
      {
        //Spaces for formating
        cout << "  " << *connectedIDs.at(i) << endl;
      }
  }

  else
  {
    //Print that the vertex was not found
    printf("Vertex with ID %d not found\n", vertexToTest);
  }
}