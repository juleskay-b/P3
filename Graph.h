//
// Created by julia on 4/10/2025.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <map>
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
    vector<pair<int, int>> edges; //Edges between films stored as a pair of IDs
public:
    Graph();
    void addFilm(int id, Film* film);
    void addActor(string name, Actor* actor);
    Film* findByID(int id);
    Actor* findByActorName(string name);
};



#endif //GRAPH_H
