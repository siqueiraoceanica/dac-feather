#include <Arduino.h>

#define DAC_PIN A0 // Pino conectado ao DAC
#define ADC_PIN A1 // Pino conectado ao ADC

#define DAC_RESOLUTION 1023.0 // Resolução do DAC (10 bits)
#define DAC_MAX_VOLTAGE 3.3   // Tensão máxima de saída do DAC em volts

#define SIGNAL_FREQUENCY 2000.0 // Frequência do SINAL GERADO

// float phase = 0;                     // Fase inicial da onda
// float deltaTime = 1.0 / SAMPLE_RATE; // Tempo entre as amostras

int t1;
#define N_PONTOS (round(1000000.0 / SIGNAL_FREQUENCY))

uint32_t pt[N_PONTOS];

uint32_t pts[N_PONTOS];
uint32_t dts[N_PONTOS];

int dt = 0;
int dtRel = 0;

void setup()
{

  Serial.begin(9600);
  while (!Serial)
  {
    // Aguarda até que o Serial esteja pronto
  }

  // definindo curva do sinal em um período com pontos variando a cada 1 us (atende amostragem do DAC até 1 Msps)
  for (int i = 0; i < N_PONTOS; i++)
  {
    pt[i] = round((sin(2 * PI * SIGNAL_FREQUENCY * i * 0.000001) + 1.0) * DAC_RESOLUTION / 2);
  }

  t1 = micros();

  for (int i = 0; i < N_PONTOS; i++)
  {
    dtRel = dt % N_PONTOS;
    analogWrite(DAC_PIN, pt[dtRel]);
    dts[i] = dt;
    pts[i] = pt[dtRel];
    dt = (dt + micros() - t1);
    t1 = micros();
    delayMicroseconds(20);
  }

  for (int i = 0; i < N_PONTOS; i++)
  {
    Serial.print(dts[i]);
    Serial.print('t');
    Serial.println(pts[i]);
  }

  Serial.println("ok");

  // analogWriteResolution(10);
  dt = 0;
  t1 = micros();
}

int cont = 0;

int dt2;

int adcRead;

void loop()
{
  // Escreve o valor no DAC
  dtRel = dt % N_PONTOS;
  analogWrite(DAC_PIN, pt[dtRel]);
  dt = (dt + micros() - t1) % N_PONTOS;
  t1 = micros();
  delayMicroseconds(20);

  // adcRead = analogRead(ADC_PIN);

  // Atualiza a fase para a próxima amostra
  // phase += deltaTime;
  // if (phase >= 1.0)
  //{
  //  phase -= 1.0; // Mantém a fase entre 0 e 1
  //}
  // cont++;
  // dt2 = dt;

  // Serial.print('t');
  // Serial.print(adcRead);
  // Serial.print('t');
  // Serial.println(dt);
  // delay(200);

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
