import os.path as path
import os
from genericpath import isfile
l = ["cpp", 'h', 'py', 'md']


def search(dir='.'):
    res = 0
    for file in os.listdir(dir):
        full_dir = path.join(dir, file)
        if(path.isfile(file)):
            file_ext = file.split('.')[-1]
            if(file_ext in l):
                file_line = len([line for line in open(
                    full_dir, 'r', encoding='utf-8')])
                print(file_line, ":"+full_dir)
                res += file_line
        elif (path.isdir(file)):
            res += search(full_dir)
    return res

total = search()

print(total,"lines in total")