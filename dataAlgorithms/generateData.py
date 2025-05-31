import random
import os

def gerar_arquivo(nome_arquivo, quantidade, limite_superior):
    os.makedirs(os.path.dirname(nome_arquivo), exist_ok=True)

    numeros = random.sample(range(1, limite_superior + 1), quantidade)

    with open(nome_arquivo, 'w') as arquivo:
        for numero in numeros:
            arquivo.write(f"{numero}\n")

# Arquivo com 5 números únicos
gerar_arquivo("data/subset_pequeno.txt", 5, 100)

# Arquivo com 15 números únicos
gerar_arquivo("data/subset_medio.txt", 15, 100)

# Arquivo com 25 números únicos
gerar_arquivo("data/subset_grande.txt", 25, 100)
