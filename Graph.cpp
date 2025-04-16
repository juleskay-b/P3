//
// Created by julia on 4/10/2025.
//

#include "Graph.h"

Graph::Graph() {
  films = {};
  actors = {};
}

void Graph::addFilm(Film* film) {
  if (films.find(film->id) == films.end()) {
    films[film->id] = film;
  }
}

void Graph::addActor(Actor* actor) {
  string name = actor->getFirst() + " " + actor->getLast();
  if (actors.find(name) == actors.end()) {
    actors[name] = actor;
  }
}

Film* Graph::findByID(int id) {
  //Implement search
  return nullptr;
}

Actor* Graph::findByActorName(string name) {
  return nullptr;
}