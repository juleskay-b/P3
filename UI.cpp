//
// Created by Ana Petrela on 4/17/25.
//

#include "UI.h"
#include <iostream>
#include <chrono>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <cstdlib>
#include <ctime>


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
    QLabel* statsLabel = new QLabel("Time to complete:\nTotal connections:\n");
    statsLabel->setWordWrap(true);
    statsLabel->setStyleSheet("margin-top: 15px;");
    leftPanel->addWidget(statsLabel);
    leftPanel->addStretch(); //pushing content to top

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

    //reset button
    QPushButton* clearButton = new QPushButton("Clear");
    rightPanel->addWidget(clearButton);

    //result label text (might remove later we'll see)
    QLabel* resultLabel = new QLabel("Result will appear here...");
    resultLabel->setWordWrap(true);
    resultLabel->setAlignment(Qt::AlignTop);
    resultLabel->setMinimumHeight(200);
    resultLabel->setStyleSheet("color: #336; background-color: #eee; padding: 10px; border: 1px solid #ccc;");
    rightPanel->addWidget(resultLabel);
    rightPanel->addStretch();

    // === VISUAL PATH VIEW === //
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    view->setMinimumHeight(200);
    view->setStyleSheet("background-color: white; border: 1px solid #ccc;");
    rightPanel->addWidget(view);
    rightPanel->addStretch();

    // ==== FINALIZE LAYOUT ==== //
    mainLayout->addLayout(leftPanel, 1);
    mainLayout->addLayout(rightPanel, 3);
    window.setLayout(mainLayout);
    window.show();

    // ==== RANDOMNESS SETUP ==== //
    srand(time(nullptr)); //generates random nums for positioning of actor nodes (kinda like a constellation....)

    // ==== BUTTON(S) LOGIC ==== //
    //search button
    QObject::connect(searchButton, &QPushButton::clicked,[=]() {

        string actor1 = actor1Input->text().toStdString();
        string actor2 = actor2Input->text().toStdString();

        //validate input
        if (!graph.isActor(actor1) || !graph.isActor(actor2)) {
            resultLabel->setText("One or both actors not found.");
            return;
        }

        vector<Actor*> path;
        QString algoUsed;

        if (bfsRadio->isChecked()) {
            path = graph.BFSPath(actor1, actor2);
            algoUsed = "BFS";
        }
        else if (dijkstraRadio->isChecked()) {
            Actor* a1 = graph.findByActorName(actor1);
            Actor* a2 = graph.findByActorName(actor2);
            if (!a1 || !a2) {
                resultLabel->setText("One or both actors not found.");
                return;
            }
            path = graph.DijkstrasPath(a1, a2);
            algoUsed = "Dijkstra";
        }

        //display path text in result label
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

        //to clear previous visual
        scene->clear();

        //draw new one
         int width = 600;
         int height = 200;
         int nodeSize = 30;
         QPoint lastCenter;

         for (int i = 0; i < path.size(); ++i) {
             int x = rand() % width;
             int y = rand() % height;

             //draw node
             scene->addEllipse(x, y, nodeSize, nodeSize, QPen(Qt::black), QBrush(QColor("#A3B18A")));

             //actor name above the nodes
             QGraphicsTextItem* label = scene->addText(QString::fromStdString(path[i]->getName()));
             label->setPos(x, y - 20);
             label->setDefaultTextColor(Qt::black);

             //draw line from previous node
             if (i > 0) {
                 scene->addLine(lastCenter.x() + nodeSize / 2, lastCenter.y() + nodeSize / 2,
                                x + nodeSize / 2, y + nodeSize / 2,
                                QPen(Qt::black));
             }

             lastCenter = QPoint(x, y);
         }
    });

    //reset button functionality
    QObject::connect(clearButton, &QPushButton::clicked, [=]() {
        actor1Input->clear();
        actor2Input->clear();
        resultLabel->setText("Result will appear here...");
        scene->clear();
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