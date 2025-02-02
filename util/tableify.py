###
# Tableify: Input grid of numbers in text file, output numbers organized in a C table structure
###

import sys

if __name__ == '__main__':
    with open(sys.argv[1], 'r') as file:
        print(
            '{\n' + ',\n'.join(['\t{' + ', '.join(x.strip('\n').split()) + '}' for x in  file.readlines()]) + '\n}'
        )