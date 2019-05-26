# Embeddet Praktikum 06 

#### Valentin Hertel Moritz Wifhöft

## Aufgabe 1

| **Befehl**           | **Benötigte    Taktzyklen** |
| -------------------- | --------------------------- |
| CMP   %[input], #128 | 1                           |
| BEQ   over127        | 1                           |
| LSL   %[result], #1  | 1                           |
| B end                | 1 + P                       |
| mov   %[result]      | 1                           |
| Gesammt              | 5 + P                       |

P∊ {0<=p<=3}

## Aufgabe 2

| **Befehl**         | **Benötigte    Taktzyklen** |
| ------------------ | --------------------------- |
| Mov r4,   %[i]     | 1                           |
| sub r4, #2         | 1                           |
| Mov r5,   %[arr]   | 1                           |
| ldr r6,   [r5, #0] | 2 x 11                      |
| ldr r7,   [r5, #1] | 2 x 11                      |
| ADD r6, r7         | 1 x 11                      |
| STR r6,   [r5,#2]  | 2 x 11                      |
| ADD r5, #1         | 1 x 11                      |
| SUB r4, #1         | 1 x 11                      |
| cmp r4, #0         | 1 x 11                      |
| Bne   fibDataLoop  | 1+P x 12                    |
| Gesammt            | 124+12P                     |

P∊ {0<=p<=3}

##### Überlegen Sie Sich weiterhin, wie Sie sicherstellen können, dass durch Ihren Programmcode veränderte Register nach der Durchführung ihre ursprünglichen Werte bekommen.

Wenn man vor der Benutzung die benötigten Register, mit push, in den Stack legt und nach der Durchführung die Register mit pop zurückholt.