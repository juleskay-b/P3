//
// Created by julia on 4/10/2025.
//

#include "Graph.h"
#include <iostream>

//Constructor - initializes an empty graph
Graph::Graph() {
  films = {};
  actors = {};
}

//Adds a film - not a vertex, but indicates an edge between actors
void Graph::addFilm(Film* film) { //Adds a film - not a vertex, but indicates an edge between actors
  if (films.find(film->id) == films.end()) {
    films[film->id] = film;
  }
}

//Adds an actor - a vertex in the graph
void Graph::addActor(Actor* actor) {
  if (actors.find(actor->getName()) == actors.end()) {
    actors[actor->getName()] = actor;
  }
}

//Checks if an actor is already in the graph by name
bool Graph::isActor(string name) {
  if (actors.find(name) != actors.end()) {
    return true;
  }
  return false;
}

//Checks if a film is already in the list by unique ID
bool Graph::isFilm(int id) {
  if (films.find(id) != films.end()) {
    return true;
  }
  return false;
}

//Getter of sorts - returns a film using its id, or nullptr if it doesn't exist
Film* Graph::findByID(int id) {
  if (films.find(id) != films.end()) {
    return films[id];
  }
  return nullptr;
}

//Getter of sorts - returns an actor given a name, or nullptr if it doesn't exist
Actor* Graph::findByActorName(string name) {
  if (actors.find(name) != actors.end()) {
    return actors[name];
  }
  return nullptr;
}

//Debug stuff - printing functions
void Graph::printFilms() {
  for (auto it = films.begin(); it != films.end(); it++) {
    cout << it->second->name << endl;
  }
}

void Graph::printActors() {
  for (auto it = actors.begin(); it != actors.end(); it++) {
    cout << it->second->getName() << endl;
  }
}

void Graph::printAdjacent(string name) {
  if (actors.find(name) != actors.end()) {
    auto a = actors[name];
    for (auto it = a->getAdjacent().begin(); it != a->getAdjacent().end(); it++) {
      cout << it->first << ", " << it->second << " movie(s)." << endl;
    }
  }
}

void Graph::printFilms(string name) {
  if (actors.find(name) != actors.end()) {
    for (Film* f : actors[name]->getFilms()) {
      cout << f->id << endl;
    }
  }
}

