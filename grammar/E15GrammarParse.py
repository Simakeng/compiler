
file_name = "SYSY.md"

with open(file_name,encoding='UTF-8') as f:
    lines = [line[:-1] if line[-1] == '\n' else line for line in f]

lines = list(filter(lambda x : x != '',lines))

pass