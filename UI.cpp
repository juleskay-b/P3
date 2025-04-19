//
// Created by Ana Petrela on 4/17/25.
//

#include "UI.h"
#include <iostream>
#include <chrono>

using namespace std;

UI::UI(Graph& g) : graph(g) {}

void UI::run() {
    window.setWindowTitle("Star Fishing");
    window.resize(800, 500);

    // ==== MAIN LAYOUT ==== (horizontal)
    QHBoxLayout* mainLayout = new QHBoxLayout();

    // ==== LEFT PANEL ==== (vertical)
    QVBoxLayout* leftPanel = new QVBoxLayout();

    //title
    QLabel* title = new QLabel("Find Shortest Path");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 18px; font-weight: bold;");
    leftPanel->addWidget(title);

    //radio (small,circular) buttons for algorithm selection
    QGroupBox* algoGroup = new QGroupBox("Choose Algorithm");
    QVBoxLayout* algoLayout = new QVBoxLayout();
    QRadioButton* bfsRadio = new QRadioButton("BFS");
    QRadioButton* dijkstraRadio = new QRadioButton("Dijkstra");
    bfsRadio->setChecked(true);
    algoLayout->addWidget(bfsRadio);
    algoLayout->addWidget(dijkstraRadio);
    algoGroup->setLayout(algoLayout);
    leftPanel->addWidget(algoGroup);

    //stats label (placeholder for now)
    QLabel* statsLabel = new QLabel("Time to complete:\nTotal connections:\nAlgorithm type:");
    statsLabel->setWordWrap(true);
    statsLabel->setStyleSheet("margin-top: 15px;");
    leftPanel->addWidget(statsLabel);
    leftPanel->addStretch();

    // ==== RIGHT PANEL ==== (vertical)
    QVBoxLayout* rightPanel = new QVBoxLayout();

    //input row
    QHBoxLayout* inputRow = new QHBoxLayout();
    QLineEdit* actor1Input = new QLineEdit();
    actor1Input->setPlaceholderText("Actor One");
    QLineEdit* actor2Input = new QLineEdit();
    actor2Input->setPlaceholderText("Actor Two");
    inputRow->addWidget(actor1Input);
    inputRow->addWidget(actor2Input);
    rightPanel->addLayout(inputRow);

    //search button
    QPushButton* searchButton = new QPushButton("Find Shortest Path");
    rightPanel->addWidget(searchButton);

    //result label
    QLabel* resultLabel = new QLabel("Result will appear here...");
    resultLabel->setWordWrap(true);
    resultLabel->setAlignment(Qt::AlignTop);
    resultLabel->setMinimumHeight(200);
    resultLabel->setStyleSheet("color: #336; background-color: #eee; padding: 10px; border: 1px solid #ccc;");
    rightPanel->addWidget(resultLabel);
    rightPanel->addStretch();

    //add panels to main layout
    mainLayout->addLayout(leftPanel, 1);
    mainLayout->addLayout(rightPanel, 3);
    window.setLayout(mainLayout);
    window.show();

    // ==== BUTTON LOGIC ==== //subject to change
    QObject::connect(searchButton, &QPushButton::clicked,[this, actor1Input, actor2Input, resultLabel, bfsRadio, dijkstraRadio]() {
        string actor1 = actor1Input->text().toStdString();
        string actor2 = actor2Input->text().toStdString();

        if (!graph.isActor(actor1) || !graph.isActor(actor2)) {
            resultLabel->setText("One or both actors not found.");
            return;
        }

        vector<Actor*> path;
        QString algoUsed;

        if (bfsRadio->isChecked()) {
            path = graph.BFSPath(actor1, actor2);
            algoUsed = "BFS";
        } else if (dijkstraRadio->isChecked()) {
            Actor* a1 = graph.findByActorName(actor1);
            Actor* a2 = graph.findByActorName(actor2);
            if (!a1 || !a2) {
                resultLabel->setText("One or both actors not found.");
                return;
            }
            path = graph.DijkstrasPath(a1, a2);
            algoUsed = "Dijkstra";
        }

        if (path.empty()) {
            resultLabel->setText("No path found!");
        } else {
            QString result = algoUsed + " Path:\n";
            for (int i = 0; i < path.size(); ++i) {
                result += QString::fromStdString(path[i]->getName());
                if (i < path.size() - 1) result += " → ";
            }
            resultLabel->setText(result);
        }
    });
}




//maybe useful later
void UI::showActorFilms() {
    string name;
    cout << "Enter the actor's name: ";
    getline(cin, name);

    if (!graph.isActor(name)) {
        cout << "Actor not found." << endl;
    } else {
        cout << "Films for " << name << ":" << endl;
        graph.printFilms(name);
    }
}

void UI::showCoStars() {
    string name;
    cout << "Enter the actor's name: ";
    getline(cin, name);

    if (!graph.isActor(name)) {
        cout << "Actor not found." << endl;
    }
    else {
        cout << "Co-Stars for " << name << ":" << endl;
        graph.printAdjacent(name);
    }
}