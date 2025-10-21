# MonitorHumorPlanta
🪴 Monitor de umidade do solo para ESP32 que mostra o "humor" da sua planta com um rosto emotivo em pixel art num display TFT. Feito com as bibliotecas TFT_eSPI e XPT2046_Touchscreen em C++/Arduino.

Com certeza\! Aqui está a documentação formatada como um arquivo `README.md`, ideal para plataformas como o GitHub.

-----

# 🪴 Monitor de Humor da Planta

Um monitor de umidade do solo com uma interface de pixel art que exibe o "humor" da sua planta em um display TFT, utilizando um ESP32.

-----

## 📜 Sumário

  * [Descrição](#descrição)
  * [Características](#características)
  * [Hardware Necessário](#hardware-necessário)
  * [Software e Bibliotecas](#software-e-bibliotecas)
  * [Configuração e Calibração](#️-configuração-e-calibração)
  * [Estrutura do Código](#-estrutura-do-código)
  * [Melhorias Futuras](#-melhorias-futuras)
  * [Autor](#autor)

-----

## Descrição

Este projeto transforma um simples sensor de umidade do solo em um display interativo. Ele mede a umidade da terra de um vaso e traduz essa informação em uma das três emoções faciais, desenhadas em um estilo minimalista de pixel art:

  * 😄 **Feliz:** A umidade está ótima (\>= 50%).
  * 😐 **Sério:** A umidade está média (\>= 20% e \< 50%), é bom ficar de olho.
  * 😢 **Triste:** A umidade está baixa (\< 20%), a planta precisa de água\!

O código é otimizado para atualizar a tela apenas quando o "humor" da planta muda, economizando processamento.

## Características

  * **Monitoramento em Tempo Real:** Verifica a umidade do solo a cada segundo.
  * **Feedback Visual Imediato:** A interface gráfica mostra o estado da planta de forma clara.
  * **Estilo Minimalista:** Fundo preto com traços brancos para um visual limpo e de alto contraste.
  * **Código Eficiente:** A tela só é redesenhada quando o estado emocional da planta muda.
  * **Fácil de Calibrar:** Parâmetros de calibração bem definidos no início do código.

## Hardware Necessário

  * **Placa de Desenvolvimento:** `ESP32-2432S028R` (ou similar com display TFT integrado).
  * **Sensor:** Sensor de umidade do solo (preferencialmente capacitivo para maior durabilidade).
  * **Fios/Jumpers:** Para conectar o sensor à placa.

## Software e Bibliotecas

  * **IDE:** Arduino IDE ou PlatformIO.
  * **Bibliotecas (Arduino):**
      * `TFT_eSPI`: Instale através do Gerenciador de Bibliotecas da Arduino IDE.
      * `XPT2046_Touchscreen`: Instale através do Gerenciador de Bibliotecas.

## ⚙️ Configuração e Calibração

Siga estes passos para montar e configurar o projeto corretamente.

### 1\. Montagem do Hardware

Conecte o sensor de umidade do solo à placa ESP32:

  * **Pino VCC** do sensor -\> **Pino 3.3V ou 5V** do ESP32.
  * **Pino GND** do sensor -\> **Pino GND** do ESP32.
  * **Pino Analógico (AOUT)** do sensor -\> **Pino 35** do ESP32 (conforme definido em `SOIL_SENSOR_PIN`).

### 2\. Calibração do Sensor (O PASSO MAIS IMPORTANTE)

Para que as leituras sejam precisas, você **precisa** calibrar o seu sensor específico, pois cada sensor e tipo de solo se comporta de maneira diferente.

1.  **Carregue o código** no ESP32 com os valores de calibração padrão.
2.  **Abra o Monitor Serial** na Arduino IDE (velocidade `115200`).
3.  **Medir o valor SECO:** Deixe o sensor totalmente no ar, sem tocar em nada. Anote o valor de "Umidade" que aparece no monitor. Este será o seu `SENSOR_DRY_VALUE`.
    ```cpp
    // Exemplo:
    #define SENSOR_DRY_VALUE 4095 // Valor lido com o sensor no ar (seco)
    ```
4.  **Medir o valor ÚMIDO:** Mergulhe a ponta do sensor em um copo com água ou coloque-o em terra bem encharcada. Anote o novo valor que aparece no monitor. Este será o seu `SENSOR_WET_VALUE`.
    ```cpp
    // Exemplo:
    #define SENSOR_WET_VALUE 1200 // Valor lido em terra bem úmida
    ```
5.  **Atualize o Código:** Altere os valores no topo do arquivo `.ino` com os números que você anotou e carregue o código novamente.

### 3\. Upload Final

Após a calibração, o seu monitor de humor da planta estará pronto para uso\!

## 💻 Estrutura do Código

O código fonte está dividido nas seguintes seções:

  * **Bibliotecas:** Inclusão das dependências para o display e touch.
  * **Configuração do Display e Sensor:** Definição de pinos, dimensões da tela e, mais importante, os valores de calibração do sensor.
  * **Variáveis Globais:** Variáveis que controlam o estado atual do sistema.
  * **Função `drawEmotionFace()`:** Responsável por desenhar o rosto na tela de acordo com a porcentagem de umidade.
  * **Função `readSoilPercent()`:** Lê o valor analógico do sensor e o converte para uma porcentagem (0-100).
  * **Função `setup()`:** Inicializa o hardware (display, serial) e exibe uma tela de boas-vindas.
  * **Função `loop()`:** O ciclo principal que lê o sensor periodicamente e decide se deve ou não atualizar a tela.

## 🚀 Melhorias Futuras

  * **Interação com Touchscreen:** Usar a tela de toque para exibir gráficos históricos de umidade ou para configurar alertas.
  * **Mais Emoções e Animações:** Adicionar mais estados (ex: "com sede", "muito molhado") ou pequenas animações de piscar de olhos.
  * **Conectividade Wi-Fi:** Enviar dados de umidade para uma plataforma de IoT (Blynk, Home Assistant) ou receber notificações no celular.
  * **Modo de Economia de Energia:** Colocar o ESP32 em modo *deep sleep* para economizar bateria, acordando apenas de tempos em tempos para fazer a medição.

## Autor

  * **Jefferson Carlos Lima**
  * *Código revisado e documentação gerada pela IA Gemini.*
