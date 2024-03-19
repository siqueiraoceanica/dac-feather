#include <Arduino.h>

#define DAC_PIN A0 // Pino conectado ao DAC
#define ADC_PIN A1 // Pino conectado ao ADC

#define DAC_RESOLUTION 1023.0 // Resolução do DAC (10 bits)
#define DAC_MAX_VOLTAGE 3.3   // Tensão máxima de saída do DAC em volts

#define SIGNAL_FREQUENCY 3000 // Frequência do SINAL GERADO

// float phase = 0;                     // Fase inicial da onda
// float deltaTime = 1.0 / SAMPLE_RATE; // Tempo entre as amostras

int t1;
#define N_PONTOS (1000000 / SIGNAL_FREQUENCY)

int pt[N_PONTOS];

void setup()
{

  Serial.begin(9600);
  while (!Serial)
  {
    // Aguarda até que o Serial esteja pronto
  }

  // definindo curva do sinal em um período com pontos variando a cada 1 us (atende amostragem até 1 Msps)
  for (int i = 0; i < N_PONTOS; i++)
  {
    pt[i] = (sin(2 * PI * SIGNAL_FREQUENCY * i * 0.000001) + 1) * 511;
  }

  t1 = micros();
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

int cont = 0;
int dt = 0;
int dt2;

int adcRead;

void loop()
{
  // Escreve o valor no DAC
  // analogWrite(DAC_PIN, (sin(2 * PI * 2000 * phase) + 1) * 512 - 1);
  analogWrite(DAC_PIN, pt[dt]);

  adcRead = analogRead(ADC_PIN);

  // Atualiza a fase para a próxima amostra
  // phase += deltaTime;
  // if (phase >= 1.0)
  //{
  //  phase -= 1.0; // Mantém a fase entre 0 e 1
  //}
  // cont++;
  dt2 = dt;
  dt = (dt + micros() - t1) % N_PONTOS;

  Serial.print(pt[dt2]);
  Serial.print('t');
  Serial.print(adcRead);
  Serial.print('t');
  Serial.println(dt);
  delay(200);
  t1 = micros();
  /*if (cont >= 1000)
  {
    int dt = micros() - t1;
    cont = 0;
    Serial.print("Tempo (us) para 1000 amostras: ");
    Serial.println(dt);
    delay(10000);
    t1 = micros();
  }*/
}
