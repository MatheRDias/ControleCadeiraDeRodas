#include "KalmanMPU6050.h"
#include <WiFi.h>
#include <esp_now.h>

// MAC do receptor
uint8_t macDestino[] = {0x00, 0x4B, 0x12, 0x95, 0x47, 0xE0};

#define DEADZONE 30

// pacote de dados
typedef struct {
  float roll;
  float pitch;
  char comando; // 'f','t','d','e','p'
} DadosIMU;

DadosIMU dados;

// callback envio (API nova)
void onSend(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  Serial.print("Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "OK" : "FALHA");
}

// ----------- Setup -----------
void setup() {
  Serial.begin(115200);

  IMU::init();
  delay(100);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ESP-NOW");
    return;
  }

  esp_now_register_send_cb(onSend);

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, macDestino, 6);
  peer.channel = 0;
  peer.encrypt = false;

  if (esp_now_add_peer(&peer) != ESP_OK) {
    Serial.println("Erro ao adicionar peer");
    return;
  }
}

// ----------- Loop -----------
void loop() {

  IMU::read();

  dados.roll  = IMU::getRoll();
  dados.pitch = IMU::getPitch();

  // -------- Lógica de movimento --------
  if (dados.pitch > DEADZONE) {
    dados.comando = 'd'; // direita
  }
  else if (dados.pitch < -DEADZONE) {
    dados.comando = 'e'; // esquerda
  }
  else if (dados.roll > DEADZONE) {
    dados.comando = 't'; // trás
  }
  else if (dados.roll < -DEADZONE) {
    dados.comando = 'f'; // frente
  }
  else {
    dados.comando = 'p'; // parar
  }

  // -------- Envio --------
  esp_now_send(macDestino, (uint8_t *)&dados, sizeof(dados));

  // -------- Debug --------
  Serial.print("Roll: ");
  Serial.print(dados.roll);
  Serial.print(" | Pitch: ");
  Serial.print(dados.pitch);
  Serial.print(" | Cmd: ");
  Serial.println(dados.comando);

  delay(50);
}
