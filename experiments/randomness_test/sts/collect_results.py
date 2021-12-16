import os
import numpy as np
import pandas as pd
from termcolor import colored
from constants import * #


def is_valid(line):
    return line != '__INVALID__\n' and line != 'nan\n' and line != '-nan\n'


def append_results(data: dict, input_type: str, hash_size: int, rounds_count: int):
    passed = 0
    failed = 0
    splitters = 0

    with open('results/result.txt', 'r') as f:
        for line in f:
            if line.endswith('tests passed successfully both the analyses.\n'):
                passed = int(line.split('/')[0])
                continue
            if line.endswith('tests did not pass successfully both the analyses.\n'):
                failed = int(line.split('/')[0])
                continue
            if line.startswith('- - - - - -'):
                splitters += 1
                if splitters == 2:
                    break
                continue

    data['Input type'].append(input_type)
    data['Hash size'].append(hash_size)
    data['Rounds count'].append(rounds_count)
    data['Tests passed'].append(passed)
    data['Tests failed'].append(failed)

    for test in test_names:
        with open('results/' + folder_names[test] + '/results.txt', 'r') as f:
            p_values = [float(line) for line in f if is_valid(line)]
            if len(p_values) == 0:
                p = 0.
            else:
                p = np.mean(p_values)
            data[test].append(p)




data = {i: [] for i in column_names}

for input_type in input_types:
    for hash_size in hash_sizes:
        for rounds in rounds_counts:
            file_name = f'{input_types_short[input_type]}_output_{hash_size}_{rounds}.txt'
            os.system(execution_command(hash_size, file_name))
            append_results(data, input_type, hash_size, rounds)

            print(colored('#####', 'yellow', attrs=['bold']))
            print(colored(f'file {file_name} processed', 'yellow', attrs=['bold']))
            print(colored('#####', 'yellow', attrs=['bold']))
        print(colored('##########', 'cyan', attrs=['bold']))
        print(colored(f'input_type {input_type} with hash_size {hash_size} processed', 'cyan', attrs=['bold']))
        print(colored('##########', 'cyan', attrs=['bold']))
            

df = pd.DataFrame(data)
df.to_csv('result_statistics.csv')








