//
// Created by Ana Petrela on 4/17/25.
//

#include "UI.h"
#include <iostream>
#include <chrono>
#include <QGraphicsView>
#include <QComboBox>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <cstdlib>
#include <ctime>


using namespace std;

UI::UI(Graph& g) : graph(g) {}

void UI::run() {
    window.setWindowTitle("Star Fishing");
    window.resize(800, 500);
    window.setStyleSheet("background-color: #D2CD95;");


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

    //dropdown for weighting preference
    QComboBox* weightSelector = new QComboBox();
    weightSelector->addItem("Favor more shared films");   // moreMovies = true
    weightSelector->addItem("Favor fewer shared films");  // moreMovies = false
    leftPanel->addWidget(weightSelector);

    //stats label (placeholder for now)
    QLabel* statsLabel = new QLabel("Time to complete:\nTotal connections:\n");
    statsLabel->setWordWrap(true);
    statsLabel->setStyleSheet("margin-top: 15px;");
    leftPanel->addWidget(statsLabel);

    //rotating star setup
    QGraphicsScene* starScene = new QGraphicsScene();
    QGraphicsView* starView = new QGraphicsView(starScene);
    starView->setStyleSheet("background: transparent; border: none;");
    starView->setFixedSize(220, 220); // size of the whole star area alloted

    //disable scroll bars thank goodness
    starView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    starView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap starPixmap("Images/Starfy.webp");
    QGraphicsPixmapItem* starItem = starScene->addPixmap(
        starPixmap.scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation) //actual size of star
    );

    //star positioning
    starItem->setTransformOriginPoint(starItem->boundingRect().center());
    starItem->setPos(
        (starView->width() - starItem->boundingRect().width()) / 2,
        (starView->height() - starItem->boundingRect().height()) / 2
    );

    //put it at the bottom
    leftPanel->addStretch(); //pushes everything to top
    leftPanel->addWidget(starView);

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
    resultLabel->setStyleSheet("color: #336; background-color: #F5DEB3; padding: 10px; border: 1px solid #aaa;");
    rightPanel->addWidget(resultLabel);


    // === VISUAL PATH VIEW === //
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    view->setMinimumHeight(200);
    view->setStyleSheet("background-color: #F5DEB3; color: #000; border: 1px solid #aaa;");
    rightPanel->addWidget(view);


    // ==== FINALIZE LAYOUT ==== //
    mainLayout->addLayout(leftPanel, 1);
    mainLayout->addLayout(rightPanel, 3);
    window.setLayout(mainLayout);
    window.show();

    // === ROTATION FOR THE STAR (using QTimer) === //
    QTimer* spinTimer = new QTimer();
    QObject::connect(spinTimer, &QTimer::timeout, [starItem]() {
        qreal angle = starItem->rotation();
        starItem->setRotation(angle + 2);  //rotate by 2 degrees
    });
    spinTimer->start(50);  // 50ms interval

    // ==== RANDOMNESS SETUP ==== //
    srand(time(nullptr)); //generates random nums for positioning of actor nodes (kinda like a constellation....)

    // ==== BUTTON(S) LOGIC ==== //
    //search button
    QObject::connect(searchButton, &QPushButton::clicked,[=]() {

        string actor1 = actor1Input->text().toStdString();
        string actor2 = actor2Input->text().toStdString();

        //for initial drop-down weight selection
        graph.setWeightType(weightSelector->currentIndex() == 0);


        //validate input
        if (!graph.isActor(actor1) || !graph.isActor(actor2)) {
            resultLabel->setText("One or both actors not found.");
            return;
        }

        //start pathfinding time
        auto start = chrono::high_resolution_clock::now();

        vector<Actor*> path;
        QString algoUsed;

        QColor nodeColor;
        QColor edgeColor;

        if (bfsRadio->isChecked()) {
            path = graph.BFSPath(actor1, actor2);
            nodeColor = QColor("#4C9BE8");
            edgeColor = QColor("#2E86C1");
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
            nodeColor = QColor("#A3B18A");
            edgeColor = QColor("#5B7553");
            algoUsed = "Dijkstra";
        }

        //stop pathfinding
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;


        //display path text in result label
        if (path.empty()) {
            resultLabel->setText("No path found!");
        }
        else {
            QString result = algoUsed + " Path:\n";
            QString moviesList;
            for (int i = 0; i < path.size(); ++i) {
                    result += QString::fromStdString(path[i]->getName());

                        if (i < path.size() - 1) {
                            moviesList += "\nFilms Shared by " + QString::fromStdString(path[i]->getName()) + " and " + QString::fromStdString(path[i + 1]->getName()) + ": ";

                        for (Film* f : path[i]->getFilms()) {
                            for (Film* f2 : path[i + 1]->getFilms()) {
                                if (f == f2) {
                                    moviesList += QString::fromStdString(f2->name) + " (" + QString::fromStdString(f2->year) + "), ";
                                }
                            }
                        }
                    }

                    if (i < path.size() - 1) result += " → ";
            }

            result += "\n\n" + moviesList;
            resultLabel->setText(result);

            //update the stats
            QString statsText;
            statsText += "Time to complete: " + QString::number(elapsed.count(), 'f', 6) + " seconds\n";
            statsText += "Total connections: " + QString::number(path.size() - 1) + "\n";
            statsText += "Algorithm type: " + algoUsed;
            statsLabel->setText(statsText);
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
             scene->addEllipse(x, y, nodeSize, nodeSize, QPen(Qt::black), QBrush(nodeColor));

             //actor name above the nodes
             QGraphicsTextItem* label = scene->addText(QString::fromStdString(path[i]->getName()));
             label->setPos(x, y - 20);
             label->setDefaultTextColor(Qt::black);

             if (i > 0) {
                int x1 = lastCenter.x() + nodeSize / 2;
                int y1 = lastCenter.y() + nodeSize / 2;
                int x2 = x + nodeSize / 2;
                int y2 = y + nodeSize / 2;

                //draw the line
                scene->addLine(x1, y1, x2, y2, QPen(edgeColor));

                //find shared film count
                Actor* a1 = path[i - 1];
                Actor* a2 = path[i];

                int sharedCount = 0;
                auto adjMap = a1->getAdjacent();
                if (adjMap.find(a2) != adjMap.end()) {
                    sharedCount = adjMap[a2];
                }

                //add label halfway on the line
                int midX = (x1 + x2) / 2;
                int midY = (y1 + y2) / 2;

                QGraphicsTextItem* edgeLabel = scene->addText(QString::number(sharedCount) + " films");
                edgeLabel->setPos(midX, midY - 10);
                edgeLabel->setDefaultTextColor(Qt::darkGray);
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
    actor1Input->setStyleSheet("background-color: #F5DEB3; color: #000; border: 1px solid #aaa;");
    actor2Input->setStyleSheet("background-color: #F5DEB3; color: #000; border: 1px solid #aaa;");
    searchButton->setStyleSheet("background-color: #DEB887; color: #000; padding: 5px;");
    clearButton->setStyleSheet("background-color: #DEB887; color: #000; padding: 5px;");
    bfsRadio->setStyleSheet("color: #000;");
    dijkstraRadio->setStyleSheet("color: #000;");
    weightSelector->setStyleSheet("background-color: #F5DEB3; color: #000;");
}