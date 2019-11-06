# reads the given filename and returns a sudoku board, represented as
# a 2d list. assumes the board is given as 9 lines of plain text.
def parse(inputFile):
    ret = []
    with open(inputFile) as f:
        strLines = f.readlines()
        for line in strLines:
            ret.append([int(ch) for ch in line if ch != "\n"])
    return ret

# prints out the board all nice and formatted
def printBoard(board):
    print()
    for i in range(9):
        if (i % 3 == 0 and i != 0):
            print("-" * 21)
        for j in range(9):
            if (j % 3 == 0 and j != 0):
                print("| ", end = "")
            print(str(board[i][j]) + " ", end = "")
        print()
    print()

printBoard(parse("board0.txt"))
