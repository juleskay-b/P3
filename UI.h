//
// Created by Ana Petrela on 4/17/25.
//

#ifndef UI_H
#define UI_H
#include "Graph.h"
#include <string>
class UI {
    Graph& graph;
    public:
    UI(Graph& graph);
    void run();
    void showMenu();
    void findShortestPath();
    void showActorFilms();
    void showCoStars();
};

#endif //UI_H
