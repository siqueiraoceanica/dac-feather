#include <Arduino.h>

#define DAC_PIN A0 // Pino conectado ao DAC
#define ADC_PIN A1 // Pino conectado ao ADC

#define DAC_RESOLUTION 1023.0 // Resolução do DAC (10 bits)
#define DAC_MAX_VOLTAGE 3.3   // Tensão máxima de saída do DAC em volts

#define SAMPLE_RATE 2000 // Frequência de amostragem em Hz (2 kHz)

float phase = 0;                     // Fase inicial da onda
float deltaTime = 1.0 / SAMPLE_RATE; // Tempo entre as amostras

void setup()
{

  Serial.begin(9600);
  while (!Serial)
  {
    // Aguarda até que o Serial esteja pronto
  }
}
/*
void loop()
{
  // Gera um sinal de onda senoidal no DAC e lê o valor correspondente no ADC
  int t1 = micros();
  for (int i = 0; i < 1000; i++)
  {
    float sinValue = sin(radians(i));      // Calcula o valor do seno para o ângulo atual
    int dacValue = (sinValue * 512) + 512; // Mapeia o valor do seno para a faixa de 0 a 1023
    Serial.println(dacValue);

    // Define a tensão de saída no DAC
    analogWrite(DAC_PIN, dacValue);

    // Lê o valor do ADC no pino A1
    // analogReadResolution(10);
    int adcValue = analogRead(ADC_PIN);
    Serial.println(adcValue);

    // Converte o valor do ADC para a tensão correspondente
    float voltage = (adcValue * DAC_MAX_VOLTAGE) / DAC_RESOLUTION;

    // Imprime o valor da tensão lida
    Serial.print("Tensão lida: ");
    Serial.print(voltage);
    Serial.println(" volts");
  }
  int t2 = micros();
  Serial.print("Tempo (us) para 1000 amostras: ");
  Serial.println(t2 - t1);
  delay(5000);
}*/

int t1 = micros();
int cont = 0;

void loop()
{
  // Escreve o valor no DAC
  analogWrite(DAC_PIN, (sin(2 * PI * 2000 * phase) + 1) * (512));

  // Atualiza a fase para a próxima amostra
  phase += deltaTime;
  if (phase >= 1.0)
  {
    phase -= 1.0; // Mantém a fase entre 0 e 1
  }
  cont++;
  if (cont >= 1000)
  {
    int dt = micros() - t1;
    cont = 0;
    Serial.print("Tempo (us) para 1000 amostras: ");
    Serial.println(dt);
    delay(10000);
    t1 = micros();
  }
}
