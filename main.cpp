//
// Created by julia on 4/10/2025.
//

#include "Graph.h"
#include "Film.h"
#include "UI.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <vector>
#include <algorithm>

// ImGui core stuffs
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// OpenGL & GLFW stuffs
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
using namespace std;

//Main function: Make a separate function to read file and create objects?
int main() {
    //Build graph from CSV
    auto start{chrono::steady_clock::now()}; //Timer for building graph - Starts here

    Graph g;

    string filename = "Datasets/actors.csv";
    ifstream data(filename);
    string line;

    int count = 0;

    if (!data.is_open()) {
        cout << "Could not open file" << endl;
        return 0;
    }

    getline(data, line);

    while (getline(data, line) && count <= 100000) {
        string stringID, actorName;
        stringstream ss(line);

        count++;

        if (getline(ss, stringID, ',') && getline(ss, actorName, ',')) {

        try {
            int filmID = stoi(stringID);

            Film* f = nullptr;
            Actor* a = nullptr;

            f = g.findByID(filmID);
            if (!f) {
                f = new Film(filmID);
                g.addFilm(f);
            }

            a = g.findByActorName(actorName);
            if (!a) {
                a = new Actor(actorName);
                g.addActor(a);
            }

            if (f && a) {
                f->addActor(a);
            }

        } catch (const invalid_argument& e) {
            cerr << "Something went wrong with ID " << stringID << endl;
        }
        } else {
            std::cerr << "Error: Invalid CSV format in line: " << line << std::endl;
        }
    }

    auto finish{chrono::steady_clock::now()};

    chrono::duration<double> elapsed_seconds{finish - start};

    cout << "Graph built in ";
    cout << elapsed_seconds.count();
    cout << " seconds." << endl;
    cout << "There are " << g.getActorNum() << " actors and " << g.getFilmNum() << " films." << endl;

    // TEMP TEST: basic GLFW window creation
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // required on macOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // required on macOS

    GLFWwindow* window = glfwCreateWindow(800, 600, "Test Window", NULL, NULL);
    if (!window) {
        std::cerr << "Window creation failed.\n";
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    // //argument mode for backend
    // if (argc == 4) {
    //     string actor1 = argv[1];
    //     string actor2 = argv[2];
    //     string algorithm = argv[3];
    //
    //     vector<Actor*> path;
    //
    //     auto algo_start = chrono::steady_clock::now();
    //
    //     if (algorithm == "bfs") {
    //         path = g.BFSPath(actor1, actor2);
    //     }
    //     else if (algorithm == "dijkstra") {
    //         Actor* start = g.findByActorName(actor1);
    //         Actor* end = g.findByActorName(actor2);
    //         if (start && end) {
    //             path = g.DijkstrasPath(start, end);
    //         }
    //     }
    //
    //     auto algo_end = chrono::steady_clock::now();
    //     chrono::duration<double> algo_time = algo_end - algo_start;
    //     cout << "Search took " << algo_time.count() << " seconds." << endl;
    //
    //     if (path.empty()) {
    //         cout << "No path found." << endl;
    //     }
    //     else {
    //         for (Actor* actor : path) {
    //             cout << actor->getName() << endl;
    //         }
    //     }
    //     return 0;
    // }
    // //CLI mode : if i give up
    //     UI ui(g);
    //     ui.run();
    return 0;
}