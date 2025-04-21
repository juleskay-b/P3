//
// Created by julia on 4/10/2025.
//

#include "Graph.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>

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

void Graph::setWeightType(bool b) {
  if (b) {
    moreMovies = true;
  } else {
    moreMovies = false;
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
    for (auto& pair : a->getAdjacent()) {  //tweaked to display actor name
      Actor* coStar = pair.first;
      int numMovies = pair.second;
      cout << "+ " << coStar->getName() << " (" << numMovies << " movie(s))" << endl;
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
      double wt;
      if (moreMovies) {
        wt = 1.0/numFilmsTogether; //Prioritize actors with more films together
      } else {
        wt = numFilmsTogether;
      }
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

vector<Actor*> Graph::BFSPath(const string& firstActor, const string& secondActor) {
  Actor* actor_one = findByActorName(firstActor);
  Actor* actor_two = findByActorName(secondActor);

  set<Actor*> visited;
  queue<Actor*> toVisit;
  unordered_map<Actor*, Actor*> parent;

  if (!actor_one || !actor_two) {
    return {};
  }

  visited.insert(actor_one);
  toVisit.push(actor_one);
  parent[actor_one] = nullptr;

  while (!toVisit.empty()) {
    Actor* current = toVisit.front();
    toVisit.pop();

    //Reconstructing the path
    if (current == actor_two) {
      vector<Actor*> path;
      for (Actor* at = actor_two; at != nullptr; at = parent[at]) {
        path.push_back(at);
      }
      reverse(path.begin(), path.end());
      return path;
    }

    for (auto& movieStar : current->getAdjacent()) {
      Actor* star = movieStar.first;
      if (visited.find(star) == visited.end()) {
        visited.insert(star);
        toVisit.push(star);
        parent[star] = current;
      }
    }
  }
  return {};
}