# Subset Sum Benchmark

## 🎯 Objetivo

Analisar a **complexidade de tempo** de um algoritmo de força-bruta para o problema **Subset Sum**, comparando o desempenho entre as linguagens **C** e **Python**.

---

## 📁 Estrutura de Pastas

```
checkSumAlgorithms/
├── bruteForceCheckSum.c           # Código em C
├── PythonBruteForceCheckSum.py    # Código em Python
├── data/
│   ├── subset_pequeno.txt         # Arquivos de entrada
│   ├── subset_medio.txt
│   ├── subset_grande.txt
│   ├── dataBaseC.csv              # Resultados da execução em C
│   └── dataBasePython.csv         # Resultados da execução em Python
└── output/
    └── bruteForceCheckSum.exe     # Executável compilado em C (opcional)
```

---

## ▶️ Como Rodar

### ✅ Em C

```bash
cd checkSumAlgorithms
gcc -o bruteForceCheckSum.exe bruteForceCheckSum.c
./bruteForceCheckSum.exe
```

> Os resultados serão salvos automaticamente em:  
> `data/dataBaseC.csv`

---

### ✅ Em Python

```bash
cd checkSumAlgorithms
python PythonBruteForceCheckSum.py
```

> Os resultados serão salvos automaticamente em:  
> `data/dataBasePython.csv`

---

## 🔁 Como Mudar a Seed do LCG

- No código **C**, edite:
  ```c
  #define LCG_SEED 12345
  ```

- No código **Python**, edite:
  ```python
  LCG_SEED = 12345
  ```

> Isso permite gerar diferentes sequências de targets pseudo-aleatórios para os testes.

---

Pronto! Execute, compare os resultados e analise o desempenho entre as linguagens.
