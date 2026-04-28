#ifndef LABIRINTO_H
#define LABIRINTO_H

//Include do arduino para a pinagem dos botões
#include <Arduino.h>

//Include do timer para informar erros e acerto
#include "timer.h"

//linhas e colunas
#define LINHAS 7
#define COLUNAS 7

//Pinos botões
#define pinEsq 16  
#define pinCim 17
#define pinDir 5
#define pinBai 15

//Numeros em bit

class Labirinto {
    private:
        int dir = 1;
        int cim = 2;
        int esq = 4;
        int bai = 8;

        int mapa[9][7][7] = {
            { 
                {dir|bai,esq|dir,esq|bai,dir|bai,esq|dir,esq,0},
                {cim|bai,dir|bai,esq|cim,dir|cim,esq|dir,esq|bai,0},
                {cim|bai,dir|cim,esq|bai,dir|bai,esq|dir,esq|bai|cim,0},
                {cim|bai,dir,esq|cim|dir,esq|cim,dir,esq|cim|bai,0},
                {cim|dir|bai,esq|dir,esq|bai,dir|bai,esq,cim|bai,0},
                {cim|dir,esq,cim|dir,esq|cim,dir,esq|cim,0},
                {0,0,0,0,0,0,0}
            },
            {
                {dir,dir|esq|bai,esq,bai|dir,esq|bai|dir,esq,0},
                {dir|bai,esq|cim,dir|bai,esq|cim,dir|cim,esq|bai,0},
                {cim|bai,bai|dir,esq|cim,dir|bai,esq|dir,esq|cim|bai,0},
                {dir|cim|bai,esq|cim,dir|bai,esq|cim,bai,bai|cim,0},
                {cim|bai,bai,cim|bai,bai|dir,esq|cim,cim|bai,0},
                {cim,dir|cim,cim|esq,cim|dir,esq|dir,esq|cim,0},
                {0,0,0,0,0,0,0}
            },
            {
                {dir|bai,esq|dir,esq|bai,bai,bai|dir,esq|bai,0},
                {cim,bai,cim|bai,cim|dir,esq|cim,cim|bai,0},
                {dir|bai,esq|cim|bai,cim|bai,dir|bai,esq|bai,cim|bai,0},
                {cim|bai,cim|bai,cim|bai,cim|bai,cim|bai,cim|bai,0},
                {cim|bai,cim|dir,cim|esq,cim|bai,cim|bai,cim|bai,0},
                {cim|dir,esq|dir,esq|dir,esq|cim,dir|cim,esq|cim,0},
                {0,0,0,0,0,0,0}
            },
            {
                {dir|bai,esq|bai,dir,esq|dir,esq|dir,esq|bai,0},
                {cim|bai,cim|bai,dir|bai,esq|dir,esq|dir,esq|cim|bai,0},
                {cim|bai,dir|cim,esq|cim,dir|bai,esq,cim|bai,0},
                {cim|bai,dir,dir|esq,esq|dir|cim,esq|dir,esq|cim|bai,0},
                {cim|dir|bai,esq|dir,esq|dir,esq|dir,esq|bai,cim|bai,0},
                {cim|dir,esq|dir,esq,dir,esq|cim,cim,0},
                {0,0,0,0,0,0,0}
            },
            {
                {dir,esq|dir,esq|dir,esq|dir,esq|dir|bai,esq|bai,0},
                {dir|bai,esq|dir,esq|dir,esq|dir|bai,esq|cim,cim,0},
                {dir|cim|bai,esq|bai,dir,esq|cim,dir|bai,esq|bai,0},
                {cim|bai,dir|cim,esq|dir,esq|bai,cim,cim|bai,0},
                {cim|bai,dir|bai,esq|dir,esq|cim|dir,esq,cim|bai,0},
                {cim,cim|dir,esq|dir,esq|dir,esq|dir,esq|cim,0},
                {0,0,0,0,0,0,0}
            },
            {
                {bai,bai|dir,esq|bai,dir,esq|dir|bai,esq|bai,0},
                {cim|bai,cim|bai,cim|bai,dir|bai,esq|cim,cim|bai,0},
                {dir|cim|bai,esq|cim,cim,cim|bai,dir|bai,esq|cim,0},
                {dir|cim,esq|bai,dir|bai,esq|cim|bai,cim|bai,bai,0},
                {dir|bai,esq|cim,cim,cim|bai,cim|dir,esq|cim|bai,0},
                {dir|cim,esq|dir,esq|dir,esq|cim,dir,esq|cim,0},
                {0,0,0,0,0,0,0}
            },
            {
                {dir|bai,esq|dir,esq|dir,esq|bai,dir|bai,esq|bai,0},
                {cim|bai,bai|dir,esq,cim|dir,esq|cim,cim|bai,0},
                {cim|dir,esq|cim,dir|bai,esq,bai|dir,esq|cim,0},
                {dir|bai,esq|bai,cim|dir|bai,esq|dir,esq|cim,bai,0},
                {cim|bai,cim,cim|dir,esq|dir,esq|bai,cim|bai,0},
                {cim|dir,esq|dir,esq|dir,esq|dir,cim|esq|dir,esq|cim,0},
                {0,0,0,0,0,0,0}
            },
            {
                {bai,bai|dir,esq|dir,esq|bai,dir|bai,esq|bai,0},
                {cim|dir|bai,esq|cim|dir,esq,dir|cim,esq|cim,cim|bai,0},
                {cim|bai,dir|bai,esq|dir,esq|dir,esq|bai,cim|bai,0},
                {cim|bai,cim|dir,esq|bai,dir,esq|cim|dir,esq|cim,0},
                {cim|bai,bai,cim|dir,esq|dir,esq|dir,esq,0},
                {cim|dir,cim|dir|esq,esq|dir,esq|dir,esq|dir,esq,0},
                {0,0,0,0,0,0,0}
            },
            {
                {bai,dir|bai,esq|dir,esq|dir,esq|bai|dir,esq|bai,0},
                {cim|bai,cim|bai,dir|bai,esq,cim|bai,cim|bai,0},
                {cim|dir|bai,esq|cim|dir,esq|cim,dir|bai,esq|cim,cim|bai,0},
                {cim|bai,bai,dir|bai,esq|bai,dir,esq|cim|bai,0},
                {cim|bai,cim|bai,cim|bai,dir|bai,esq|bai,cim,0},
                {cim|dir,esq|cim,cim|dir,cim|esq,dir|cim,esq,0},
                {0,0,0,0,0,0,0}
            }
        };

        int pinLed[LINHAS][COLUNAS] = {
            { 6,  7, 20, 21, 34, 35, 48},
            { 5,  8, 19, 22, 33, 36, 47},
            { 4,  9, 18, 23, 32, 37, 46},
            { 3, 10, 17, 24, 31, 38, 45},
            { 2, 11, 16, 25, 30, 39, 44},
            { 1, 12, 15, 26, 29, 40, 43},
            { 0, 13, 14, 27, 28, 41, 42}
        };

        int posBrancoX;
        int posBrancoY;

        int posVermelhoX;
        int posVermelhoY;

        int posVerde1[9][2] = {{2,5},{1,4},{3,3},{0,0},{2,4},{0,4},{0,1},{0,3},{1,2}};
        int posVerde2[9][2] = {{1,0},{3,1},{3,5},{3,0},{5,3},{4,2},{5,1},{3,2},{4,0}};

        int mapaAtual = 0;

        bool estadoAnterior[4] = {false};
        bool estadoAtual[4] = {false};
        bool acertou = false;
        int pinos[4] = {pinEsq, pinCim, pinDir, pinBai};
        
        void desenharBarreira();

    public:
        void renderizar();
        void atualizar(Timer *timer);
        void inicializar();

};

#endif // LABIRINTO_H