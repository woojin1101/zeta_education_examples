# Write or read, erase memo.txt file.

import sys

option = sys.argv[1]

if option == '-w':
    memo = sys.argv[2]
    f = open('memo.txt', 'a')
    f.write(memo)
    f.write('\n')
    f.close()

elif option == '-r':
    f = open('memo.txt')
    memo = f.read()
    f.close()
    print(memo)

elif option == '-e':
    with open('memo.txt', 'w') as f:
        f.truncate(0)
    print("All text has been erased!")

else:
    print("There is no correct argument!")