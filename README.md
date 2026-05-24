# ♿ CONTROLE DE CADEIRA DE RODAS POR MOVIMENTO DA CABEÇA

## 📖 SOBRE O PROJETO

Este projeto foi desenvolvido com foco em **tecnologia assistiva** para pessoas com deficiência motora e mobilidade reduzida que possuem movimentos da cabeça, mas não conseguem utilizar as mãos para controlar uma cadeira de rodas convencional.

A proposta consiste em utilizar um capacete equipado com sensores para identificar os movimentos da cabeça e transformá-los em comandos de direção.

O sistema realiza comunicação sem fio entre dois módulos ESP32 utilizando o protocolo **ESP-NOW**, permitindo transmissão rápida e eficiente dos dados.

---

## ⚙️ FUNCIONAMENTO DO SISTEMA

O projeto é dividido em duas partes principais:

# 🎩 MÓDULO TRANSMISSOR — CAPACETE

O capacete possui:

- ESP32
- Sensor MPU6050
- Sistema de alimentação

O sensor MPU6050 é responsável por detectar:

- Inclinação da cabeça
- Movimento angular
- Aceleração

As informações capturadas são processadas pelo ESP32 e enviadas sem fio para outro ESP32 utilizando ESP-NOW.

---

# 🚗 MÓDULO RECEPTOR

O segundo ESP32 recebe os dados enviados pelo capacete e interpreta os movimentos da cabeça como comandos de controle.

Atualmente, o sistema controla um carrinho robótico utilizado para testes e validação do projeto.

A proposta futura é adaptar o sistema para controlar uma cadeira de rodas motorizada real, realizando ajustes no software e no sistema eletrônico de potência.

---

## 🎮 CONTROLE POR MOVIMENTO DA CABEÇA

| Movimento da Cabeça | Ação |
|---|---|
| ⬆️ Inclinar para frente | Avançar |
| ⬇️ Inclinar para trás | Recuar |
| ⬅️ Inclinar para esquerda | Virar à esquerda |
| ➡️ Inclinar para direita | Virar à direita |

---

## 🛠️ TECNOLOGIAS UTILIZADAS

### 🔌 HARDWARE

- ESP32
- MPU6050
- Motores DC
- Ponte H
- Bateria
- Carrinho robótico
- Capacete adaptado

---

### 💻 SOFTWARE

- Arduino IDE
- ESP-NOW
- Filtro de Kalman
- Comunicação Wi-Fi

---

## 📡 COMUNICAÇÃO ESP-NOW

A comunicação entre os módulos ESP32 é realizada utilizando o protocolo **ESP-NOW**, permitindo:

- Baixa latência
- Comunicação direta entre dispositivos
- Maior velocidade de resposta
- Menor consumo de energia

---

## 🧠 FILTRO DE KALMAN

O projeto utiliza o **Filtro de Kalman** para melhorar a precisão do sensor MPU6050.

O filtro ajuda a:

- Corrigir drift do giroscópio
- Reduzir ruídos
- Melhorar estabilidade
- Aumentar a precisão dos movimentos

Isso proporciona um controle mais suave e confiável.

---

## 🎯 OBJETIVO

O principal objetivo deste projeto é desenvolver uma solução acessível de tecnologia assistiva capaz de proporcionar maior autonomia e independência para pessoas com deficiência motora severa.

---

## 🚀 POSSÍVEIS MELHORIAS FUTURAS

- Controle de velocidade proporcional
- Frenagem automática
- Detecção de obstáculos
- Integração com cadeira de rodas real
- Aplicativo mobile para monitoramento
- Sistema de calibração automática
- Sistema de segurança contra falhas

---

## ⚠️ OBSERVAÇÃO

Atualmente o projeto encontra-se em fase de prototipagem utilizando um carrinho robótico para testes.

A adaptação para uma cadeira de rodas motorizada real exige modificações adicionais de hardware, potência e segurança.

---

## 👨‍💻 AUTOR

**Matheus Renan Dias da Silva**

🎓 Análise e Desenvolvimento de Sistemas  
🔧 Técnico em Eletrônica