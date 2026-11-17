// Pinos
const uint8_t PINO_PWM = 9;
const uint8_t PINO_PV  = A0;
const uint8_t PINO_POT = A1;
const uint8_t PINO_V1  = A2;
const uint8_t PINO_V2  = A3;

// PID
const float KP = 12.0;
const float TI = 2.0;
const float TD = 0.5;
const float N_FILTRO = 5.0;
const float B_PESO = 0.0;   // pesos da referencia: 0 = I-PD, 1 = PID classico
const float C_PESO = 0.0;

// Modo de operacao
const bool  USAR_POTENCIOMETRO = true;  // true: SP lido do potenciometro em A1
const bool  ENSAIO_KCR = false;         // true: controle P puro com Kp = KCR
const float KCR = 29.0;                 // ganho critico

// Graficos no Monitor serial
const uint8_t GRAFICO = 1;              // 1 = malha, 2 = planta, 3 = parcelas do PID
const bool  USAR_ANTI_WINDUP = true;    // false: mostra o efeito do windup

// Amostragem e limites
const unsigned long TS_US = 10000UL;    // 10 ms
const float TS = TS_US * 1.0e-6;
const float U_MIN = 0.0;
const float U_MAX = 5.0;
const uint8_t DECIMACAO = 5;            // imprime a cada 50 ms

// Estado
float kp, ti, td, bPeso, cPeso;
float aD, bD;
float I = 0.0;
float D = 0.0;
float vAnterior = 0.0;
bool  primeiraAmostra = true;
unsigned long t0, tAmostra;
uint8_t contador = 0;

float referencia(float t) {
  if (USAR_POTENCIOMETRO) return analogRead(PINO_POT) * (5.0 / 1023.0);
  if (ENSAIO_KCR)         return (t < 1.0) ? 0.0 : 2.5;
  if (t < 1.0)  return 0.0;
  if (t < 11.0) return 1.0;
  return 3.0;
}

void imprimeLinha(const float *valores, uint8_t n, uint8_t casas) {
  for (uint8_t i = 0; i < n; i++) {
    if (i > 0) Serial.print(',');
    Serial.print(valores[i], casas);
  }
  Serial.println();
}

void setup() {
  pinMode(PINO_PWM, OUTPUT);
  analogWrite(PINO_PWM, 0);
  TCCR1B = (TCCR1B & 0b11111000) | 0x05;  // PWM ~30,6 Hz
  Serial.begin(115200);

  if (ENSAIO_KCR) {
    kp = KCR; ti = 0.0; td = 0.0; bPeso = 1.0; cPeso = 1.0;
  } else {
    kp = KP;  ti = TI;  td = TD;  bPeso = B_PESO; cPeso = C_PESO;
  }
  float tf = td / N_FILTRO;
  aD = (td > 0.0) ? tf / (tf + TS) : 0.0;
  bD = (td > 0.0) ? kp * td / (tf + TS) : 0.0;

  t0 = micros();
  tAmostra = t0;
}

void loop() {
  if ((long)(micros() - tAmostra) < 0) return;
  float t = (tAmostra - t0) * 1.0e-6;
  tAmostra += TS_US;

  // 1) Leitura
  float y  = analogRead(PINO_PV) * (5.0 / 1023.0);
  float sp = referencia(t);
  float e  = sp - y;

  // 2) Acoes P e D
  float P = kp * (bPeso * sp - y);
  float v = cPeso * sp - y;
  if (primeiraAmostra) { vAnterior = v; primeiraAmostra = false; }
  D = aD * D + bD * (v - vAnterior);
  vAnterior = v;

  // 3) Saturacao e anti-windup
  float uPID = P + I + D;
  float u = constrain(uPID, U_MIN, U_MAX);
  float Iusado = I;
  bool integra = (uPID < U_MAX || e < 0.0) && (uPID > U_MIN || e > 0.0);
  if (ti > 0.0 && (integra || !USAR_ANTI_WINDUP))
    I += kp * TS / ti * e;

  // 4) PWM: 0..5 V -> 1..254
  int duty = (int)(u * 255.0 / 5.0 + 0.5);
  analogWrite(PINO_PWM, constrain(duty, 1, 254));

  // 5) Monitor serial
  if (++contador >= DECIMACAO) {
    contador = 0;
    if (GRAFICO == 2) {
      float v1 = analogRead(PINO_V1) * (5.0 / 1023.0);
      float v2 = analogRead(PINO_V2) * (5.0 / 1023.0);
      float linha[] = {sp, v1, v2, y};
      imprimeLinha(linha, 4, 3);
    } else if (GRAFICO == 3) {
      float linha[] = {P, Iusado, D, u};
      imprimeLinha(linha, 4, 2);
    } else {
      float linha[] = {sp, y, u};
      imprimeLinha(linha, 3, 3);
    }
  }
}
