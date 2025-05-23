import time
import os
import csv

def get_elapsed_us(start, end):
    return (end - start) * 1_000_000

def subset_sum_dp(arr, target, filename):
    dp = [False] * (target + 1)
    prev = [0] * (target + 1)
    
    dp[0] = True
    
    start_total = time.perf_counter()
    
    for i in range(len(arr)):
        for j in range(target, arr[i] - 1, -1):
            if dp[j - arr[i]] and not dp[j]:
                dp[j] = True
                prev[j] = i + 1
    
    end_total = time.perf_counter()
    total_time_ms = (end_total - start_total) * 1000
    
    if not dp[target]:
        print(f"Nenhum subconjunto encontrado com soma {target}.")
        # Salva no CSV mesmo quando não encontra
        save_to_csv(filename, target, total_time_ms, False)
        return False
    
    print(f"Subconjunto encontrado com soma {target}: {{ ", end="")
    curr = target
    
    while curr > 0:
        start_element = time.perf_counter()
        
        idx = prev[curr] - 1
        print(f"\n\t{arr[idx]} ", end="")
        curr -= arr[idx]
        
        end_element = time.perf_counter()
        elapsed_us = get_elapsed_us(start_element, end_element)
        print(f"(tempo para este elemento: {elapsed_us:.3f} microsegundos)", end="")
    
    print("\n}")
    
    print(f"Tempo total da busca: {total_time_ms:.2f} milissegundos")
    print(f"ou {total_time_ms / 1000:.4f} segundos")
    
    # Salva os resultados no CSV
    save_to_csv(filename, target, total_time_ms, True)
    
    return True

def save_to_csv(filename, target, total_time_ms, found):
    csv_filename = os.path.join("..", "data", "subset_results.csv")
    
    # Verifica se o arquivo já existe para decidir se escreve o cabeçalho
    file_exists = os.path.isfile(csv_filename)
    
    with open(csv_filename, mode='a', newline='') as file:
        writer = csv.writer(file)
        
        if not file_exists:
            writer.writerow(["Arquivo", "Target", "Tempo (ms)", "Encontrado"])
        
        writer.writerow([filename, target, f"{total_time_ms:.2f}", "Sim" if found else "Não"])

def main():
    filename = input("Digite o nome do arquivo (ex: subset_1000.txt): ")
    target = int(input("Digite o valor da soma alvo: "))
    
    fullpath = os.path.join("..", "data", filename)
    
    try:
        with open(fullpath, "r") as file:
            arr = [int(line.strip()) for line in file if line.strip()]
    except FileNotFoundError:
        print("Erro ao abrir o arquivo.")
        return
    
    subset_sum_dp(arr, target, filename)

if __name__ == "__main__":
    main()