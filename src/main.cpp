/**************************************************************************/
/*!
    @file     trianglewave.pde
    @author   Adafruit Industries
    @license  BSD (see license.txt)

    This example will generate a triangle wave with the MCP4725 DAC.

    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/
/**************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;
#define GREEN_PIN 8 // Define o pino do LED VERDE

const int numPontos = 20;       // Número de pontos da onda senoidal
float senoTable[numPontos];     // Tabela para armazenar os valores da onda senoidal
const float frequencia = 500.0; // Frequência da onda senoidal em Hz

void setup(void)
{
  // Pré-calcular os valores da onda senoidal
  for (int i = 0; i < numPontos; i++)
  {
    float t = i * (1.0 / frequencia) / numPontos;
    senoTable[i] = sin(2 * M_PI * frequencia * t);
  }
  pinMode(GREEN_PIN, OUTPUT);
  Serial.begin(9600);
  // Aguarda até que o Serial esteja pronto
  // while (!Serial)
  //{
  //}
  Serial.println("Hello!");

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x60);

  Serial.println("Generating a triangle wave");

  analogReadResolution(12);
  digitalWrite(GREEN_PIN, HIGH);
}

uint16_t amp = 1;
uint16_t contCiclos;
bool aumentaAmp = true;
void loop(void)
{
  // a cada 5 é amplitude de 8 mV
  for (int i = 5; i <= 1000; i += 5)
  {
    for (int j = 0; j < numPontos; j++)
    {
      int valorDAC = i * senoTable[j] + 2048; // Conversão para o valor do DAC
      dac.setVoltage(valorDAC, false);
      delayMicroseconds(100);
    }
  }

  // a cada 5 é amplitude de 8 mV
  for (int i = 995; i >= 5; i -= 5)
  {
    for (int j = 0; j < numPontos; j++)
    {
      int valorDAC = i * senoTable[j] + 2048; // Conversão para o valor do DAC
      dac.setVoltage(valorDAC, false);
      delayMicroseconds(100);
    }
  }
}

//