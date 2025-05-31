import time
import csv

LCG_SEED = 12345

lcg_state = LCG_SEED

def lcg_rand():
    global lcg_state
    lcg_state = (1103515245 * lcg_state + 12345) & 0x7fffffff
    return lcg_state

def brute_force_check_sum(arr, n, target):
    total_masks = 1 << n
    for mask in range(total_masks):
        soma = 0
        for i in range(n):
            if mask & (1 << i):
                soma += arr[i]
        if soma == target:
            return True
    return False

def ler_arquivo(caminho):
    with open(caminho, "r") as f:
        return [int(linha.strip()) for linha in f]

def testar_subset(caminho):
    arr = ler_arquivo(caminho)
    n = len(arr)

    soma_total = sum(arr)
    target = lcg_rand() % (soma_total + 1)

    start = time.time()
    found = brute_force_check_sum(arr, n, target)
    end = time.time()
    duracao = end - start

    return n, target, found, duracao

def main():
    subsets = {
        "data/subset_pequeno.txt": None,
        "data/subset_medio.txt": None,
        "data/subset_grande.txt": None
    }

    with open("data/dataBasePython.csv", mode="w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["iteracao", "arquivo", "n", "target", "found", "duracao"])

        for iteracao in range(1, 51):

            for caminho in subsets.keys():
                n, target, found, duracao = testar_subset(caminho)

                writer.writerow([
                    iteracao,
                    caminho,
                    n,
                    target,
                    int(found),       
                    f"{duracao:.6f}"
                ])
                print(f"{iteracao}, {caminho}, {n}, {target}, {int(found)}, {duracao:.6f}")

if __name__ == "__main__":
    main()
