# Controle PID de tensão em uma planta RC com Arduino

Trabalho prático de **Controle e Servomecanismos II**. Um Arduino Uno controla, com um PID, a tensão no último capacitor de uma rede RC de três estágios. O circuito foi montado e simulado no Tinkercad.

**Circuito no Tinkercad:** [https://www.tinkercad.com/things/hY5ynRgVgmF-surprising-borwo-blad](https://www.tinkercad.com/things/hY5ynRgVgmF-surprising-borwo-blad/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fthings%2FhY5ynRgVgmF-surprising-borwo-blad&sharecode=VNuOX_KoyNxMAWbYHH-vn_nFf1nRlfRQxKFoia4_SnY)

[![Abrir no Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/Kjotas/PID-ControlesII-Project/blob/main/graficos/PID_Graf.ipynb)

## Resultados

| Item | Valor |
|---|---|
| Função de transferência da planta | G(s) = 1 / (s³ + 5s² + 6s + 1) |
| Parâmetros do PID | Kp = 12, Ti = 2 s, Td = 0,5 s |
| Sobressinal no degrau | 0,9 % |
| Tempo de acomodação (±2 %) | 4,3 s (malha aberta: 20,8 s) |

## Componentes e ligações

- 1 Arduino Uno R3
- 3 resistores de 10 kΩ (R1, R2, R3)
- 3 capacitores eletrolíticos de 100 µF (C1, C2, C3)
- 1 potenciômetro de 10 kΩ
- Protoboard e fios

O pino D9 alimenta a escada R1 → R2 → R3, e cada nó tem um capacitor para o GND. A tensão em C3 é lida em A0, e o cursor do potenciômetro vai em A1. O [esquemático](https://github.com/Kjotas/PID-ControlesII-Project/blob/main/esquematico/fig02_esquematico.png) e a [montagem na protoboard](https://github.com/Kjotas/PID-ControlesII-Project/blob/main/esquematico/fig03_protoboard.png) estão na pasta [`esquematico/`](https://github.com/Kjotas/PID-ControlesII-Project/tree/main/esquematico).

## Estrutura

| Caminho | Conteúdo |
|---|---|
| [`codigo/controle_pid_rc2.ino`](https://github.com/Kjotas/PID-ControlesII-Project/blob/main/codigo/controle_pid_rc2.ino) | Código do Arduino |
| [`esquematico/fig02_esquematico.png`](https://github.com/Kjotas/PID-ControlesII-Project/tree/main/esquematico/fig02_esquematico.png) | Esquemático e montagem na protoboard |
| [`graficos/PID_Graf.ipynb`](https://github.com/Kjotas/PID-ControlesII-Project/blob/main/graficos/PID_Graf.ipynb) | Notebook do Google Colab que gera os gráficos |
| [`graficos/`](https://github.com/Kjotas/PID-ControlesII-Project/tree/main/graficos) | Resposta ao degrau e curva com o Arduino |
| [`relatorio/PID___Controles_II.pdf`](https://github.com/Kjotas/PID-ControlesII-Project/blob/main/relatorio/PID___Controles_II.pdf) | Relatório |

## Como reproduzir

1. **Simulação:** abra o link do Tinkercad, clique em *Iniciar simulação*, abra o *Monitor serial* e clique no ícone de gráfico.
2. **Referência:** com `USAR_POTENCIOMETRO = true`, a referência vem do potenciômetro. Com `false`, o código aplica os degraus do relatório: de 0 a 1 V em t = 1 s e de 1 a 3 V em t = 11 s.
3. **Gráficos:** clique no botão *Abrir no Colab* acima e execute a célula do notebook.

## Autores

Matheus da Silva da Mota.

## Licença

Distribuído sob a licença GNU GPL v3. Veja [`LICENSE`](https://github.com/Kjotas/PID-ControlesII-Project/blob/main/LICENSE).
