# 🧩 LAB-4 — Temporal Execution and Interaction Between Tasks and LEDs (FreeRTOS)

## 📘 Visão geral

Sistema baseado em **FreeRTOS** executando em uma **FRDM-KL25Z (MKL25Z128VLK4)** com duas tarefas concorrentes que controlam um LED RGB via `ledrgb_hal`:

| Task | Prioridade | Função | LED Controlado |
|------|-------------|---------|----------------|
| **Task1** | 1 (menor) | Liga/desliga o LED **vermelho** a cada 500 ms | 🔴 Red |
| **Task2** | 2 (maior) | Liga/desliga o LED **verde** (300 ms ON / 300 ms OFF) quando liberada | 🟢 Green |

O sistema pode operar em **dois modos**:
- **Semáforo binário** (`ledSema`): sincronização entre tarefas.  
- **Mutex OSA** (`ledMutex`): exclusão mútua do driver de LED.

Para alternar entre modos:
- Defina `#define USE_MUTEX` no topo de `main.c`, ou  
- Adicione `USE_MUTEX` às **Defined symbols (-D)** nas propriedades do projeto.

---

## 🔁 Modo Semáforo (Sinalização entre Tasks)

## ⚙️ SYSML Diagram

![alt text](sysml_semaphore.png)

### ⚙️ Funcionamento
- `Task1` liga o LED vermelho e aguarda 500 ms.  
- Após o delay, **dá** o semáforo (`led_signal()`), acordando **Task2**.  
- `Task2`, ao receber o semáforo, liga o LED verde por 300 ms.  
- Como o vermelho ainda está ligado, há sobreposição (vermelho + verde → **laranja**).  
- Depois Task1 desliga o vermelho e o ciclo se repete.

### 🕒 Tabela Temporal — **Semáforo (com sobreposição / laranja)**

| Tempo (ms) | Tarefa em execução | Ação / Estado | LEDs |
|-------------|--------------------|----------------|------|
| **0 – 500** | 🟥 Task1 | Liga RED e aguarda (`vTaskDelay(500)`) | 🔴⚫⚫ → **Vermelho ON** |
| **≈ 500** | 🟥→🟢 (preempção) | `xSemaphoreGive()` → Task2 acorda | 🔴🟢🟠 → **Laranja (overlap)** |
| **500 – 800** | 🟢 Task2 | GREEN ON (`vTaskDelay(300)`) | 🔴🟢🟠 → **Laranja** |
| **≈ 800** | 🟢 Task2 | Desliga GREEN (`vTaskDelay(300)`) | 🔴⚫⚫ → **Somente vermelho** |
| **≈ 1000** | 🟥 Task1 | Desliga RED (`vTaskDelay(500)`) | ⚫⚫⚫ → **Todos OFF** |
| **1000 – 1500** | 🟥 Task1 | Novo ciclo: RED ON | 🔴⚫⚫ → **Reinicia padrão** |

### 🧩 Resumo rápido (Semáforo)
- **Sincroniza** as tarefas (Task1 → Task2).  
- **Permite sobreposição física** entre LEDs → cor **laranja** visível.  
- Excelente para **coordenação temporal** entre tarefas.

---

## 🔒 Modo Mutex (Exclusão Mútua via OSA)

## ⚙️ SYSML Diagram

![alt text](sysml_mutex.png)

### ⚙️ Funcionamento
- O mutex (`ledMutex`) protege as operações de escrita no driver `ledrgb_hal`.  
- **Task1** adquire o mutex, acende o vermelho e **mantém o lock durante todo o delay de 500 ms**.  
- Enquanto isso, **Task2** bloqueia ao tentar adquirir o mutex — impedindo qualquer acesso concorrente.  
- Quando Task1 libera o mutex, Task2 executa seu ciclo verde.  
- O resultado é **execução serializada**, sem sobreposição (sem cor laranja).

### 🕒 Tabela Temporal — **Mutex (sem sobreposição / sem laranja)**

| Tempo (ms) | Tarefa em execução | Ação / Estado | LEDs |
|-------------|--------------------|----------------|------|
| **0 – 500** | 🟥 Task1 | `lock → setRed → delay(500)` (mantém lock) | 🔴⚫⚫ → **Somente vermelho** |
| **≈ 500** | 🟥 Task1 | `unlock` (libera mutex) | 🔴⚫⚫ → **Vermelho ainda ON fisicamente** |
| **≈ 500 – 800** | 🟢 Task2 | Tenta `lock`, adquire após unlock → `setGreen` + `delay(300)` | 🟢⚫⚫ → **Somente verde (sem laranja)** |
| **≈ 800 – 1000** | 🟢 Task2 | `clearGreen` + unlock | ⚫⚫⚫ → **OFF** |
| **1000 – 1500** | 🟥 Task1 | Reinicia ciclo: `lock → setRed → delay` | 🔴⚫⚫ → **Reinicia padrão** |

### 🧩 Resumo rápido (Mutex)
- **Garante exclusão mútua**, impedindo acesso simultâneo ao hardware.  
- **Não sincroniza** tarefas; apenas evita concorrência.  
- Com o lock mantido durante o ON, **não ocorre sobreposição** (sem cor laranja).  
- Ideal para proteger **regiões críticas curtas** no HAL ou GPIOs compartilhados.

---

## ⚖️ Comparativo rápido

| Característica | **Semáforo** | **Mutex** |
|----------------|---------------|------------|
| Objetivo | Sinalizar eventos entre tarefas | Proteger recurso compartilhado |
| Ordem entre tarefas | ✅ Sim | ❌ Não (execução independente) |
| Exclusão mútua | ⚠️ Parcial (depende da ordem) | ✅ Completa |
| Priority inheritance | ❌ Não | ✅ Sim |
| Pode ser usado em ISR | ✅ Sim | ❌ Não |
| Overlap (laranja) | ✅ Sim (se give antes de clear) | ❌ Não (modo atual) |
| Ideal para | Coordenação temporal | Proteção do driver HAL |

---

## 🔧 Notas práticas

- Defina `USE_MUTEX` **globalmente** nas opções do compilador, ou com `#define USE_MUTEX` no topo de `main.c`.  
- Se `USE_MUTEX` não estiver definido → **modo semáforo**.  
- Ajuste delays conforme o comportamento desejado (ex.: tempos diferentes de ON/OFF para visualização).  
- Combine ambos (Semáforo + Mutex) se quiser **ordem controlada** + **proteção de hardware**.

---

## ✅ Conclusão

> - No modo **Semáforo**, o sistema sincroniza as tarefas — permitindo **overlap físico (laranja)**.  
> - No modo **Mutex**, as tarefas se **excluem mutuamente** — sem overlap, operação mais determinística.  
> - Ambos os modos são úteis para compreender as diferenças entre **sincronização de tarefas** e **exclusão mútua** em sistemas embarcados baseados em FreeRTOS.

---
