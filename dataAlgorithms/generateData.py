import random

def gerar_arquivo(nome_arquivo, quantidade, limite_superior):
    # Garante que os números não se repitam usando um conjunto
    numeros = random.sample(range(1, limite_superior), quantidade)
    with open(nome_arquivo, 'w') as arquivo:
        for numero in numeros:
            arquivo.write(f"{numero}\n")

# Arquivo com 1000 números únicos
gerar_arquivo("subset_1000.txt", 1000, 10_000)

# Arquivo com 10000 números únicos
gerar_arquivo("subset_10000.txt", 10000, 100_000)

# Arquivo com 100000 números únicos
gerar_arquivo("subset_100000.txt", 100000, 1_000_000)
