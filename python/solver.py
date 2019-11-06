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
    return

# returns all numbers in the given row
def inRow(board, row):
    return [i for i in board[row] if i != 0]

# returns all numbers in the given column
def inCol(board, col):
    return [board[i][col] for i in range(9) if board[i][col] != 0]

# returns all numbers in the square around x, y
def inSquare(board, row, col):
    # starting indexes of the square (top left corner)
    rowStart = (row // 3) * 3
    colStart = (col // 3) * 3
    ret = []
    for r in range(rowStart, rowStart + 3):
        for c in  range(colStart, colStart + 3):
            if board[r][c] != 0:
                ret.append(board[r][c])
    return ret
    
def squareOpts(board, row, col):
    # square already filled; no work to do
    if (board[row][col] != 0):
        return [board[row][col]]

    # generate all options by process of elimination
    opts = list(range(1, 10))
    for num in inRow(board, row):
        if num in opts:
            opts.remove(num)
    for num in inCol(board, col):
        if num in opts:
            opts.remove(num)
    for num in inSquare(board, row, col):
        if num in opts:
            opts.remove(num)
    return opts

# generates a 3d array. opts[i][j] represents all possible numbers for square
# [i][j] in the board.
def genOpts(board):
    opts = []
    for r in range(9):
        row = []
        for c in range(9):
            row.append(squareOpts(board, r, c))
        opts.append(row)
    return opts

# returns minimum length option list
def minOpts(options):
    minR = -1
    minC = -1
    min = 10
    for r in range(9):
        for c in range(9):
            nOpts = len(options[r][c])
            if (nOpts > 1 and nOpts < min):
                min = nOpts
                minR = r
                minC = c
    return minR, minC

def checkRow(board, row):
    for i in range(1, 10):
        if (board[row].count(i) > 1):
            # print("duplicate of " + str(i))
            return False
    return True

def checkCol(board, col):
    colList = [board[i][col] for i in range(9)]
    for i in range(1, 10):
        if (colList.count(i) > 1):
            # print("duplicate of " + str(i))
            return False
    return True

def checkSquare(board, row, col):
    squareList = []
    for i in range(row, row + 3):
        for j in range(col, col + 3):
            squareList.append(board[i][j])
    for i in range(1, 10):
        if (squareList.count(i) > 1):
            # print("duplicate of " + str(i))
            return False
    return True

# returns true if the board is valid, false otherwise
def validate(board):
    for i in range(9):
        if not (checkCol(board, i) or checkRow(board, i)):
            return False
    for i in [0, 3, 6]:
        for j in [0, 3, 6]:
            if not (checkSquare(board, i, j)):
                return False
    return True

# solves the board by filling in all squares with one logically possible
# answer. if none of those squares exist, tries every option for the square
# with the fewest options. returns False if the board is self-contradictory,
# returns the solved board otherwise.
def solve(board):
    options = genOpts(board)
    newBoard = []
    solved = True
    # create new board
    for r in range(9):
        newRow = []
        for c in range(9):
            # no option exists; the board is impossible
            if (options[r][c] == []):
                return False
            # build new board from options
            if (len(options[r][c]) == 1):
                newRow.append(options[r][c][0])
            else:
                solved = False
                newRow.append(0)
        newBoard.append(newRow)
    # check if the board is valid
    if (not validate(board)):
        return False
    # no unsolved squares left; we're done, so return the board
    if solved:
        return newBoard
    # no change has happened, so time for fancy recursion
    elif (newBoard == board):
        tryRow, tryCol = minOpts(options)
        # try every option; all except the right one will cause an
        # impossible board and return false
        # print("Recursing on " + str(tryRow) + ", " + str(tryCol) +
        #       " with options " + str(options[tryRow][tryCol]))
        for opt in options[tryRow][tryCol]:
            # print("  trying " + str(opt))
            newBoard[tryRow][tryCol] = opt
            #printBoard(newBoard)
            test = solve(newBoard)
            if (test):
                return test
            # print("failed")
            
    # simple recursion--we have made progress, so we can keep doing
    # process of elimination style solving
    else:
        #printBoard(newBoard)
        return solve(newBoard)

curBoard = parse("board3.txt")
printBoard(curBoard)
printBoard(solve(curBoard))
#printBoard(solve(curBoard))
