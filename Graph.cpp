//
// Created by julia on 4/10/2025.
//

#include "Graph.h"
#include <cmath>
#include <algorithm>
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

vector<Actor *> Graph::DijkstrasPath(Actor *start, Actor *end) {
  unordered_map<Actor*, double> distance;
  unordered_map<Actor*, Actor*> prev;
  priority_queue<pair<double, Actor*>, vector<pair<double, Actor*>>, greater<>> q;

  for (pair<string, Actor*> pair : actors) {
    distance[pair.second] = INFINITY;
  }

  distance[start] = 0;

  q.push({0, start});

  while (!q.empty()) {
    Actor* curr = q.top().second;
    double d = q.top().first;
    q.pop();

    if (curr == end) {
      break;
    }

    for (pair<Actor*, int> a : curr->getAdjacent()) {
      Actor* neighbor = a.first;
      int numFilmsTogether = a.second;
      double wt = 1.0/numFilmsTogether; //Prioritize actors with more films together
      double d2 = d + wt;

      if (d2 < distance[neighbor]) {
        distance[neighbor] = d2;
        prev[neighbor] = curr;
        q.push({d2, neighbor});
      }
    }
  }

  vector<Actor*> path;
  if (distance[end] == INFINITY) {
    return path;
  }

  for (Actor* a = end; a != nullptr; a = prev[a]) {
    path.push_back(a);
  }

  reverse(path.begin(), path.end());
  return path;

}

vector<Actor *> Graph::BFSPath(const string &firstActor, const string &secondActor) {
  return {};
}
