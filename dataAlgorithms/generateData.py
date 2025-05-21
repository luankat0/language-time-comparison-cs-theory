import random
import os

def gerar_arquivo(nome_arquivo, quantidade, limite_superior):
    os.makedirs(os.path.dirname(nome_arquivo), exist_ok=True)

    numeros = random.sample(range(1, limite_superior + 1), quantidade)

    with open(nome_arquivo, 'w') as arquivo:
        for numero in numeros:
            arquivo.write(f"{numero}\n")

# Arquivo com 1000 números únicos
gerar_arquivo("data/subset_1000.txt", 1000, 1000)

# Arquivo com 10000 números únicos
gerar_arquivo("data/subset_10000.txt", 10000, 10000)

# Arquivo com 100000 números únicos
gerar_arquivo("data/subset_100000.txt", 100000, 100000)
