#include <WiFi.h>
#include <esp_now.h>

// ---------- Timeout de segurança ----------
unsigned long ultimaMensagem = 0;
unsigned long tempoLimite = 5000; // 5s sem comando = parar

// ---------- Pinos ----------
#define IN1 4
#define IN2 5
#define ENA 18
#define IN3 17
#define IN4 16
#define ENB 15
#define ESQ 13
#define DIR 12

// ---------- Estrutura recebida ----------
typedef struct {
  float roll;
  float pitch;
  char comando;
} DadosIMU;

DadosIMU dados;

// ---------- Funções de movimento ----------
void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Parado");
}

void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  Serial.println("Frente");
}

void tras() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  Serial.println("Trás");
}

void direita() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  Serial.println("Direita");
}

void esquerda() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  Serial.println("Esquerda");
}

// ---------- Callback ESP-NOW ----------
void onReceive(const esp_now_recv_info *info, const uint8_t *data, int len) {
  memcpy(&dados, data, sizeof(dados));

  ultimaMensagem = millis(); // atualiza tempo

  Serial.print("Cmd: ");
  Serial.print(dados.comando);
  Serial.print(" | Roll: ");
  Serial.print(dados.roll);
  Serial.print(" | Pitch: ");
  Serial.println(dados.pitch);

  // -------- Executa comando --------
  switch (dados.comando) {
    case 'f': frente(); break;
    case 't': tras(); break;
    case 'd': direita(); break;
    case 'e': esquerda(); break;
    case 'p': parar(); break;
  }
}

// ---------- Setup ----------
void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ESQ, INPUT_PULLUP);
  pinMode(DIR, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(onReceive);
}

// ---------- Loop ----------
void loop() {

  // Segurança: se perder comunicação, para tudo
  if (millis() - ultimaMensagem > tempoLimite) {
    parar();
  }

}
