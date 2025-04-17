//
// Created by julia on 4/10/2025.
//

#include "Graph.h"
#include <iostream>
#include <queue>

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

bool Graph::isActor(const string& name) {
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
  auto it = films.find(id);
  if (it != films.end()) {
    return it->second;
  }
  return nullptr;
}

Actor* Graph::findByActorName(const string& name) {
  auto it = actors.find(name);
  if (it != actors.end()) {
    return it->second;
  }
  return nullptr;
}

unsigned int Graph::getFilmNum() const {
  return films.size();
}

unsigned int Graph::getActorNum() const {
  return actors.size();
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

void Graph::printAdjacent(const string& name) {
  if (actors.find(name) != actors.end()) {
    auto a = actors[name];
    for (auto it = a->getAdjacent().begin(); it != a->getAdjacent().end(); it++) {
      cout << it->first << ", " << it->second << " movie(s)." << endl;
    }
  }
}

void Graph::printFilms(const string& name) {
  if (actors.find(name) != actors.end()) {
    for (Film* f : actors[name]->getFilms()) {
      cout << f->id << endl;
    }
  }
}

vector<Actor*> Graph::BFSPath(const string& firstActor, const string& secondActor) {
  //Getting Actor names by input and then putting it into the two actor objects
  Actor* actor_one = findByActorName(firstActor);
  Actor* actor_two = findByActorName(secondActor);

  //visited are the actor objects we found
  //toVisit are the actor objects we still need to go through
  unordered_set<Actor*> visited;
  queue<Actor*> toVisit;

  //Making sure the user puts in input for both names, if not function returns empty vector
  if (!actor_one || !actor_two) {
    return {};
  }

  //Inserting first actor in what's been visited
  //Inserting first actor in what we currently need to visit
  visited.insert(actor_one);
  toVisit.push(actor_one);

  //Going to update the queue and visit other stars until the queue is empty
  while(!toVisit.empty()) {
    Actor* current = toVisit.front();
    toVisit.pop();


    //Going to visit other co-stars
    for (auto movieStar : current->getAdjacent()) {
      Actor* star = findByActorName(movieStar.first->getName());
      if (visited.find(star) == visited.end()) {
        visited.insert(star);
        toVisit.push(star);
      }
    }
  }

  return {};
}