from random import randint

def main():
    table = [ [" " , " " , " "] , 
              [" " , " " , " "] , 
              [" " , " " , " "] ]
    #printTable(table)
    print()

    turn = 0
    for turn in range(4):
        enemyMove(turn, table)
        myMove(turn, table)
        turn = turn + 1


#Functions

def printTable(table):
    print()

    for i in range(3):
        for j in range(3):
            print(" " * 2, end="")
            print(table[i][j], end="")
            if j == 2:
                break
            else:
                print("|", end="")
        
        print("")
        if i == 2:
            break
        else:
            print("---" * 4)


def enemyMove(count, table):
    player = "O"

    if (count == 0):
        xMove = randint(0,2)
        yMove = randint(0,2)
    else: 
        print()
    
    table[xMove][yMove] = "O"
    printTable(table)

def myMove(count, table):
    print()

main()
