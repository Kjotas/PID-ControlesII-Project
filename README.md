# Controle PID de tensão em uma planta RC com Arduino

Trabalho prático de **Controle e Servomecanismos II**. Um Arduino Uno controla, com um PID, a tensão no último capacitor de uma rede RC de três estágios. O circuito foi montado e simulado no Tinkercad.

**Circuito no Tinkercad:** https://www.tinkercad.com/things/hY5ynRgVgmF-surprising-borwo-blad

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

O pino D9 alimenta a escada R1 → R2 → R3, e cada nó tem um capacitor para o GND. A tensão em C3 é lida em A0, e o cursor do potenciômetro vai em A1. O esquemático e a montagem estão em [`figuras/`](figuras/).

## Estrutura

| Caminho | Conteúdo |
|---|---|
| [`codigo/controle_pid_rc.ino`](codigo/controle_pid_rc.ino) | Código do Arduino |
| [`codigo/graficos_relatorio_colab.ipynb`](codigo/graficos_relatorio_colab.ipynb) | Notebook do Google Colab que gera os gráficos |
| [`codigo/graficos_relatorio.py`](codigo/graficos_relatorio.py) | O mesmo código dos gráficos em um único arquivo |
| [`figuras/`](figuras/) | Esquemático, montagem na protoboard e curvas |
| [`Relatorio_PID_Controle_II.pdf`](Relatorio_PID_Controle_II.pdf) | Relatório |
| `main.tex`, `horiz_blu.png` | Fonte do relatório no Overleaf |

## Como reproduzir

1. **Simulação:** abra o link do Tinkercad, clique em *Iniciar simulação*, abra o *Monitor serial* e clique no ícone de gráfico.
2. **Referência:** com `USAR_POTENCIOMETRO = true`, a referência vem do potenciômetro. Com `false`, o código aplica os degraus do relatório: de 0 a 1 V em t = 1 s e de 1 a 3 V em t = 11 s.
3. **Gráficos:** no Google Colab, faça upload de `codigo/graficos_relatorio_colab.ipynb` e execute todas as células.

## Autores

Matheus da Silva da Mota.
