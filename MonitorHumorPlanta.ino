/*
  Projeto: Monitor de Humor da Planta
  Hardware: ESP32-2432S028R + Sensor de Umidade
  Autor: Jefferson Carlos Lima (Revisado por IA Gemini)
  Descrição: Exibe uma emoção em pixel art (apenas olhos e boca, sem contorno)
*/

// ===================== BIBLIOTECAS =====================
#include <SPI.h>
#include <TFT_eSPI.h>              // Biblioteca de display
#include <XPT2046_Touchscreen.h>   // Biblioteca de touchscreen

// ===================== CONFIGURAÇÃO DO DISPLAY =====================
TFT_eSPI tft = TFT_eSPI();
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Pinos do Touchscreen (ajuste se necessário)
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

// ===================== CONFIGURAÇÃO DO SENSOR =====================
#define SOIL_SENSOR_PIN 35

// !! IMPORTANTE: CALIBRE SEU SENSOR AQUI !!
#define SENSOR_DRY_VALUE 4095 // Valor lido com o sensor no ar (seco)
#define SENSOR_WET_VALUE 1200 // Valor lido em terra bem úmida

// ===================== VARIÁVEIS GLOBAIS =====================
int soilPercent = 0;
unsigned long lastReadTime = 0;
int lastPercent = -1;

// ===================== FUNÇÃO PRINCIPAL DE DESENHO =====================

void drawEmotionFace(int percent) {
  enum Emotion { HAPPY, SERIOUS, SAD };
  Emotion currentEmotion;
  if (percent >= 50) currentEmotion = HAPPY;
  else if (percent >= 20) currentEmotion = SERIOUS;
  else currentEmotion = SAD;

  tft.fillScreen(TFT_BLACK);

  uint16_t featureColor = TFT_WHITE;
  int cx = SCREEN_WIDTH / 2;
  int cy = SCREEN_HEIGHT / 2;
  int p = 10;

  int startX = cx - (14 * p / 2);
  int startY = cy - (8 * p / 2);

  auto drawBlock = [&](int bx, int by) {
    tft.fillRect(startX + bx * p, startY + by * p, p, p, featureColor);
  };

  switch (currentEmotion) {
    case HAPPY: {
      drawBlock(0, 0); drawBlock(1, 0); drawBlock(2, 0);
      drawBlock(0, 1);                 drawBlock(2, 1);
      drawBlock(11, 0); drawBlock(12, 0); drawBlock(13, 0);
      drawBlock(11, 1);                  drawBlock(13, 1);
      drawBlock(3, 4);
      drawBlock(4, 5);
      drawBlock(5, 6); drawBlock(6, 6); drawBlock(7, 6); drawBlock(8, 6);
      drawBlock(9, 5);
      drawBlock(10, 4);
      break;
    }
    case SERIOUS: {
      drawBlock(0, 1); drawBlock(1, 1); drawBlock(2, 1);
      drawBlock(11, 1); drawBlock(12, 1); drawBlock(13, 1);
      for (int i = 3; i <= 10; i++) {
        drawBlock(i, 6);
      }
      break;
    }
    case SAD: {
      drawBlock(0, 0); drawBlock(1, 0); drawBlock(2, 0);
      drawBlock(0, 1);                 drawBlock(2, 1);
      drawBlock(11, 0); drawBlock(12, 0); drawBlock(13, 0);
      drawBlock(11, 1);                  drawBlock(13, 1);
      drawBlock(3, 6);
      drawBlock(4, 5);
      drawBlock(5, 4); drawBlock(6, 4); drawBlock(7, 4); drawBlock(8, 4);
      drawBlock(9, 5);
      drawBlock(10, 6);
      break;
    }
  }
}

// ===================== FUNÇÃO DE LEITURA DO SENSOR =====================
int readSoilPercent() {
  int value = analogRead(SOIL_SENSOR_PIN);
  int percent = map(value, SENSOR_DRY_VALUE, SENSOR_WET_VALUE, 0, 100);
  return constrain(percent, 0, 100);
}

// ===================== SETUP =====================
void setup() {
  Serial.begin(115200);
  tft.init(); // Inicializa o display
  
  // ADICIONE ESTA LINHA PARA CORRIGIR AS CORES INVERTIDAS
  tft.invertDisplay(true); 
  
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK); // Agora isso deve funcionar e deixar a tela preta

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawCentreString("Monitor de Umidade", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 4);
  delay(2500);

  pinMode(SOIL_SENSOR_PIN, INPUT);
}

// ===================== LOOP =====================
void loop() {
  if (millis() - lastReadTime > 1000) {
    soilPercent = readSoilPercent();
    Serial.print("Umidade: "); Serial.print(soilPercent); Serial.println("%");

    int currentEmotionalState = (soilPercent >= 50) ? 2 : (soilPercent >= 20) ? 1 : 0;
    int lastEmotionalState = (lastPercent >= 50) ? 2 : (lastPercent >= 20) ? 1 : 0;

    if (currentEmotionalState != lastEmotionalState || lastPercent == -1) {
      drawEmotionFace(soilPercent);
      lastPercent = soilPercent;
    }
    
    lastReadTime = millis();
  }
}