//
// Created by julia on 4/10/2025.
//

#include "Graph.h"
#include <iostream>

Graph::Graph() {
  films = {};
  actors = {};
}

void Graph::addFilm(Film* film) {
  if (films.find(film->id) == films.end()) {
    films[film->id] = film;
  }
}

void Graph::addActor(Actor* actor) {;
  if (actors.find(actor->getName()) == actors.end()) {
    actors[actor->getName()] = actor;
  }
}

bool Graph::isActor(string name) {
  if (actors.find(name) != actors.end()) {
    return true;
  }
  return false;
}

bool Graph::isFilm(int id) {
  if (films.find(id) != films.end()) {
    return true;
  }
  return false;
}


Film* Graph::findByID(int id) {
  if (films.find(id) != films.end()) {
    return films[id];
  }
  return nullptr;
}

Actor* Graph::findByActorName(string name) {
  if (actors.find(name) != actors.end()) {
    return actors[name];
  }
  return nullptr;
}

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

