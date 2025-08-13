# ♿ Cadeira de Rodas Controlada por Giroscópio e Arduino

Este projeto implementa um sistema de controle para cadeira de rodas utilizando um **giroscópio fixado na cabeça do usuário** como interface de comando.  
O objetivo é oferecer maior independência para pessoas com mobilidade reduzida, permitindo controlar a direção da cadeira apenas com movimentos da cabeça.

## 🚀 Funcionalidades
- Controle de movimento **frente, trás, esquerda e direita** com inclinação da cabeça.
- Baseado em Arduino uno para fácil manutenção e baixo custo.
- Giroscópio MPU-6050 para detecção de ângulos de inclinação.
- Comunicação com sistema de motores da cadeira de rodas.
- Possibilidade de ajuste de **sensibilidade** dos comandos.

## 🛠️ Componentes Utilizados
- **Arduino Uno** (ou compatível)
- **Módulo Giroscópio/Acelerômetro MPU-6050**
- **Driver de Motor** (ex.: L298N)
- **Motores da cadeira de rodas**
- Fonte de alimentação adequada
- Fios, conectores e suporte para fixação do sensor na cabeça

## 📦 Instalação e Uso

### 1️⃣ Montagem do Hardware
1. Fixe o módulo giroscópio na cabeça do usuário (ex.: faixa ou capacete).
2. Conecte o giroscópio ao Arduino (I2C: pinos **SDA** e **SCL**).
3. Conecte o Arduino ao driver de motor e aos motores da cadeira.
4. Alimente todo o sistema com a tensão adequada.

### 2️⃣ Upload do Código
1. Abra o código no **Arduino IDE**.
2. Instale as bibliotecas necessárias:
   - `MPU6050.h` 
3. Carregue o programa no Arduino.

### 3️⃣ Uso
- Incline a cabeça para frente para **andar**.
- Incline para trás para **recuar**.
- Incline para esquerda/direita para virar.
- O sistema interpreta movimentos suaves e evita falsos comandos com um filtro de leitura.

## ⚙️ Ajustes
- Sensibilidade do giroscópio: pode ser calibrada no código para responder a movimentos menores ou maiores.
- Velocidade da cadeira: ajustável alterando o PWM enviado aos motores.

## 📜 Licença 
Sinta-se livre para modificar e compartilhar.

---

💡 *Este sistema foi projetado com foco em acessibilidade e inovação, podendo ser expandido para outros tipos de controle assistivo.*
