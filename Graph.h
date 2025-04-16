//
// Created by julia on 4/10/2025.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <set>
#include <string>
#include <map>
#include <vector>
#include "Film.h"
using namespace std;

//The Graph Structure::
//A film will be share an edge with another film if the two share at least one actor
//Sharing multiple actors will have no impact on the edge
//Film objects will store a vector of pointers to different actors
//Likewise, actor objects will store a list of pointers to different films

class Graph {
    map<int, Film*> films; //Map with an ID and an accompanying Film Object
    map<string, Actor*> actors; //Map with a name (Last, First) and accompanying Actor Object
    //Each actor has a list of edges (actors they have starred in a film with)
public:
    Graph();
    void addFilm(int id, Film* film);
    void addActor(string name, Actor* actor);
    Film* findByID(int id);
    Actor* findByActorName(string name);

    //Shortest Path Algo and Helper Functions (if necessary) - Dijkstra's
    vector<Actor*> dPath();

    //Shortest Path Algo and Helper Functions (if necessary) - BFS
    vector<Actor*> BFSPath();
};



#endif //GRAPH_H
