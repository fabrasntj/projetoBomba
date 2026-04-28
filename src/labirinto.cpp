#include <labirinto.h>
#include <FastLED.h>

// Definições
#define NUM_LEDS 50        // Número de LEDs na fita
#define DATA_PIN 2         // Pino de dados
#define LED_TYPE WS2812B   // Tipo de LED
#define COLOR_ORDER RGB    // Ordem de cores

CRGB leds[NUM_LEDS];

void Labirinto::desenharBarreira(){
    //barreira
    for(int i = 0; i < COLUNAS; i++){
        leds[pinLed[COLUNAS - 1][i]] = CRGB::MediumVioletRed;
        leds[pinLed[i][COLUNAS - 1]] = CRGB::MediumVioletRed;
    }
}

void Labirinto::inicializar() {
    // Inicializar a fita LED
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(255);  // Define brilho (0-255)
    FastLED.clear();             // Limpa todos os LEDs

    //Pinagem dos botões
    pinMode(pinBai, INPUT_PULLDOWN);
    pinMode(pinCim, INPUT_PULLDOWN);
    pinMode(pinDir, INPUT_PULLDOWN);
    pinMode(pinEsq, INPUT_PULLDOWN);
    
    // mapaAtual = 0; //nao vai ser usado por enquanto
    
    randomSeed(analogRead(0));  //Função rand para definir os leds em posições aleatórias
    mapaAtual = rand() % 9;

    do {
        posBrancoY = rand() % 6; //gerar ou na primeira ou segunda coluna podendo variar qualquer linha
        posBrancoX = rand() % 2;
    } while((posBrancoY == posVerde1[mapaAtual][0] && posBrancoX == posVerde1[mapaAtual][1]) || (posBrancoY == posVerde2[mapaAtual][0] && posBrancoX == posVerde2[mapaAtual][1]));

    do {
        posVermelhoY = rand() % 6; //gerar ou na ultima ou penultima coluna podendo variar qualquer linha
        posVermelhoX = (rand() % 2) + 4;
    } while((posVermelhoY == posVerde1[mapaAtual][0] && posVermelhoX == posVerde1[mapaAtual][1]) || (posVermelhoY == posVerde2[mapaAtual][0] && posVermelhoX == posVerde2[mapaAtual][1]));

    //Colorir os elementos na tela
    desenharBarreira();
    leds[pinLed[posBrancoY][posBrancoX]] = CRGB::White;
    leds[pinLed[posVermelhoY][posVermelhoX]] = CRGB::Red;
    leds[pinLed[posVerde1[mapaAtual][0]][posVerde1[mapaAtual][1]]] = CRGB::Green;
    leds[pinLed[posVerde2[mapaAtual][0]][posVerde2[mapaAtual][1]]] = CRGB::Green;
    
    FastLED.show();
}

void Labirinto::renderizar() {
    FastLED.clear();
    leds[pinLed[posVerde1[mapaAtual][0]][posVerde1[mapaAtual][1]]] = CRGB::Green;
    leds[pinLed[posVerde2[mapaAtual][0]][posVerde2[mapaAtual][1]]] = CRGB::Green;
    leds[pinLed[posVermelhoY][posVermelhoX]] = CRGB::Red;
    leds[pinLed[posBrancoY][posBrancoX]] = CRGB::White;
    desenharBarreira();
    FastLED.show();
}

void Labirinto::atualizar(Timer* timer) {
    if(posBrancoX == posVermelhoX && posBrancoY == posVermelhoY && !acertou){
        timer->acerto();
        acertou = true;
    } else if(!acertou) {
        for(int i = 0; i < 4; i++){
            estadoAtual[i] = digitalRead(pinos[i]);
            if(estadoAtual[i] && !estadoAnterior[i]){
                switch(pinos[i]){
                    case pinEsq: //esquerda
                        if (esq & mapa[mapaAtual][posBrancoY][posBrancoX]) {
                            posBrancoX--;
                        } else {
                            timer->erro();
                        }
                        break;
                        case pinDir: //cima
                        if (dir & mapa[mapaAtual][posBrancoY][posBrancoX]) {
                            posBrancoX++;
                        } else {
                            timer->erro();
                        }
                        break;
                        case pinCim: //direita
                        if (cim & mapa[mapaAtual][posBrancoY][posBrancoX]) {
                            posBrancoY--;
                        } else {
                            timer->erro();
                        }
                        break;
                        case pinBai: //baixo
                        if (bai & mapa[mapaAtual][posBrancoY][posBrancoX]) {
                            posBrancoY++;
                        } else {
                            timer->erro();
                        }
                    break;
                }
                delay(20); //pausa para debounce
                renderizar();
            }
            estadoAnterior[i] = estadoAtual[i];
        }

        
        //botao de incremento so para ver se os mapas estão funcionando:
        // if(digitalRead(pinDebug)){
            //     if(mapaAtual >= 8){
                //         mapaAtual = 0;
                //     } else {
                    //         mapaAtual++;
                    //     }
                    //     while(digitalRead(pinDebug));
                    //     inicializar();
                    //     delay(1000);
                    // }
        }
        if(acertou) FastLED.clear();
    }