#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "game.h"

class Ranking {
private:
    string fileName = "ranking.txt";
    string entireText = "";
public:

    //Almacena en un string las puntuaciones que ya estuviesen registradas
    void leeFichero() {
        entireText = "";
        string line;
        ifstream fIn;
        try {
            fIn.open(fileName);
            if (fIn.is_open()) {
                while (getline(fIn, line))
                    entireText += line + ",";
            }
            fIn.close();
        }
        catch (exception e) {
            cout << e.what() << endl;
        }
    };

    //Introduce la nueva puntuacion en su posicion exacta
    void escribeFichero(int puntosJugadorTotal) {
        ofstream fOut;
        try {
            fOut.open(fileName);
            istringstream ss(entireText);
            string word;
            int c = 0;
            if (fOut.is_open()) {
                while (getline(ss, word, ',')) {
                    int a = atoi(word.c_str());
                    if (a > (puntosJugadorTotal)) {
                        fOut << word << endl;
                    }
                    else {
                        if (c == 0) {
                            fOut << puntosJugadorTotal << endl; //Añade el valor nuevo puntuacion
                            cout << puntosJugadorTotal << endl;
                            c++;
                            fOut << word << endl;
                        }
                        else {
                            fOut << word << endl;
                        }
                    }
                }
                fOut.close();
            }
        }
        catch (exception e) {
            cout << e.what() << endl;
        }
    };
};