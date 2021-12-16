# P-value is shown
test_names = [
    'Frequency',
    'Block Frequency',
    'Cumulative Sums',
    'Runs',
    'Longest Run of Ones',
    'Binary Matrix Rank',
    'Discrete Fourier Transform',
    'Non-overlapping Template Matching',
    'Overlapping Template Matching',
    'Maurer\'s Universal Statistical',
    'Approximate Entropy',
    'Random Excursions',
    'Random Excursions Variant',
    'Serial',
    'Linear Complexity',
]

column_names = [
    'Input type',
    'Hash size',
    'Rounds count',
    'Tests passed',
    'Tests failed',
]
column_names += test_names

input_types = ['Low hamming weight', 'High hamming weight', 'Random strings']
input_types_short = {input_types[0]: 'low', input_types[1]: 'high', input_types[2]: 'rand'}

hash_sizes = [224, 256, 384, 512]
rounds_counts = [1, 2, 3, 4, 5, 6, 12, 24]

folder_names = {name: name.replace(' ', '') for name in test_names}
folder_names['Longest Run of Ones'] = 'LongestRun'
folder_names['Binary Matrix Rank'] = 'Rank'
folder_names['Discrete Fourier Transform'] = 'DFT'
folder_names['Non-overlapping Template Matching'] = 'NonOverlappingTemplate'
folder_names['Overlapping Template Matching'] = 'OverlappingTemplate'
folder_names['Maurer\'s Universal Statistical'] = 'Universal'


# sts execution command
time_measure = 'time '
command = './sts '
log_settings = '-v 1 -I 1 '
def size_settings(hash_size):
    return '-S 5663792 -P 1=65536 -i {} '.format(hash_size // 8)
output_setting = '-w ./results -s '
def input_settings(file_name):
    return '-F r ../data/' + file_name

def execution_command(hash_size, file_name):
    return (time_measure + command + log_settings +
        size_settings(hash_size) + output_setting + input_settings(file_name))


input_types = ['Low hamming weight', 'High hamming weight', 'Random strings']
input_types_short = {input_types[0]: 'low', input_types[1]: 'high', input_types[2]: 'rand'}

hash_sizes = [224, 256, 384, 512]
rounds_counts = [1, 2, 3, 4, 5, 6, 12, 24]
