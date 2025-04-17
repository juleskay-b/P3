//
// Created by julia on 4/10/2025.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <map>
#include <vector>
#include "Film.h"
using namespace std;

//The Graph Structure::
//An actor will be share an edge with another actor if the two have been in at least one film
//The edge will be weighted by the multiplicative inverse of the total number of films the two share (1/numFilms)
//Film objects will store a set of pointers to different actors
//Likewise, actor objects will store a set of pointers to different films

class Graph {
    map<int, Film*> films; //Map with an ID and an accompanying Film Object
    map<string, Actor*> actors; //Map with a name ("First Last") and accompanying Actor Object
    //Each actor has a list of edges (actors they have starred in a film with)
public:
    Graph();
    void addFilm(Film* film);
    void addActor(Actor* actor);
    Film* findByID(int id);
    Actor* findByActorName(const string& name);

    bool isActor(const string& name); //Returns if an actor is already in the list
    bool isFilm(int id); //Returns if a film is already in the list

    void printFilms(); //Testing insertion
    void printActors(); //Testing insertion
    void printAdjacent(const string& name); //Testing edges
    void printFilms(const string& name); //Testing insertion

    //Stuff for data - how many actors and films are there total?
    unsigned int getFilmNum() const;
    unsigned int getActorNum() const;

    //Shortest Path Algo and Helper Functions (if necessary) - Dijkstra's
    vector<Actor*> DijkstrasPath();

    //Shortest Path Algo and Helper Functions (if necessary) - BFS
    vector<Actor*> BFSPath(const string& firstActor, const string& secondActor);
};



#endif //GRAPH_H
