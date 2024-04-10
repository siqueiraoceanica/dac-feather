#include <Arduino.h>

#define DAC_PIN A0 // Pino conectado ao DAC
#define ADC_PIN A1 // Pino conectado ao ADC

#define GREEN_PIN 8 // Define o pino do LED VERDE

#define DEPURAR false // Se o sistema estiver sendo depurado com

#define DAC_RESOLUTION 1023.0  // Resolução do DAC (10 bits)
#define DAC_MAX_VOLTAGE 3300.0 // Tensão máxima de saída do DAC em mV

#define SIGNAL_FREQUENCY 200.0 // Frequência do SINAL GERADO
#define SIGNAL_AMP 100.0       // Amplitude do SINAL GERADO (mV)

// float phase = 0;                     // Fase inicial da onda
// float deltaTime = 1.0 / SAMPLE_RATE; // Tempo entre as amostras

int t1;
#define N_PONTOS 5000

uint16_t pt[N_PONTOS];

// teste

// uint32_t pts[N_PONTOS];
// uint32_t dts[N_PONTOS];

uint32_t dt = 0;
// uint32_t dtRel = 0;

void setup()
{

#if DEPURAR
  Serial.begin(9600);
  // Aguarda até que o Serial esteja pronto
  while (!Serial)
  {
  }
#endif

  // Inicializa o pino do LED VERDE como saída
  pinMode(GREEN_PIN, OUTPUT);

  // Desliga o LED VERDE
  digitalWrite(GREEN_PIN, LOW);

  // definindo curva do sinal em um período com pontos variando a cada 1 us (atende amostragem do DAC até 1 Msps)
  // float factor = SIGNAL_AMP * DAC_RESOLUTION / (2.0 * DAC_MAX_VOLTAGE);
  for (int i = 0; i < N_PONTOS; i++)
  {
    pt[i] = round((sin(2 * PI * SIGNAL_FREQUENCY * i * 0.000001 + PI) + 1.0) * 15);
    Serial.println(pt[i]);
  }

  t1 = micros();

  /*for (int i = 0; i < N_PONTOS; i++)
  {
    dtRel = dt % N_PONTOS;
    analogWrite(DAC_PIN, pt[dtRel]);
    dts[i] = dt;
    pts[i] = pt[dtRel];
    dt = (dt + micros() - t1);
    t1 = micros();
    delayMicroseconds(100);
  }

  for (int i = 0; i < N_PONTOS; i++)
  {
    Serial.print(dts[i]);
    Serial.print('t');
    Serial.println(pts[i]);
  }*/

  Serial.println("ok");

  // Liga o LED VERDE para ostrar que o dispositivo está em operação
  digitalWrite(GREEN_PIN, HIGH);

  dt = 0;
  t1 = micros();
}

int dt2;

int adcRead;
int cont = 0;
const int sizeDt = 1000;
uint32_t dts[sizeDt];

void loop()
{
  cont++;
  if (cont < sizeDt)
  {
    dts[cont - 1] = analogRead(A5);
  }
  if (cont == sizeDt)
  {
    for (int i = 0; i < sizeDt; i++)
    {
      Serial.println(dts[i]);
    }
  }
  // Escreve o valor no DAC
  // dtRel = dt % N_PONTOS;
  // dtRel = dt;

  // dt = (dt + micros() - t1);
  dt = (dt + micros() - t1) % N_PONTOS;

  analogWrite(DAC_PIN, pt[dt]);
  t1 = micros();
  delayMicroseconds(200);
}
