//
// Created by Ana Petrela on 4/17/25.
//

#ifndef UI_H
#define UI_H
#include "Graph.h"

#include <string>
//qt stuff let's gooooo and see what happens
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QApplication>
#include <QGroupBox>
#include <QRadioButton>

class UI {
    Graph& graph;
    QWidget window;
public:
    UI(Graph& graph);
    void run();
    void showActorFilms();
    void showCoStars();
};

#endif //UI_H
