# name = "Alice"
# age = 30
# print(f"My name is {name} and I am {age} years old.")

import pygame
pygame.init()

#window
screen_width = 600
screen_height = 600
screen = pygame.display.set_mode((screen_width,screen_height))
pygame.display.set_caption('O - X game')

#setting color
BLACK = (0,0,0)
WHITE = (255,255,255)
RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0,0,255)

#board (0: none, 1: O -1:X) row:行 column:列
board = [
    [0,0,0],
    [0,0,0],
    [0,0,0]]

number = 1
game_over = False

#function-------------------------------------------------------------------------------------------

#drawing grid lines
def draw_grid():
    line_width = 5
    for i in range(1,3):
        pygame.draw.line(screen,BLACK,(0,200 * i),(screen_width,200 * i),line_width)
        pygame.draw.line(screen,BLACK,(200 * i,0),(200 * i,screen_height),line_width)

#draw O and X
def draw_board():
    for row_index,row in enumerate(board):
        for col_index,col in enumerate(row):
            if col == 1:
                #draw circle
                pygame.draw.circle(screen,RED,(col_index * 200 + 100, row_index * 200 + 100), 80, 5)
            elif col == -1:
                #draw cross mark
                pygame.draw.line(screen,BLUE,(col_index * 200 + 20, row_index * 200 + 20),(col_index * 200 + 180, row_index * 200 + 180),5)
                pygame.draw.line(screen,BLUE,(col_index * 200 + 180, row_index * 200 + 20),(col_index * 200 + 20, row_index * 200 + 180),5)

#get player's action
def get_player_action(number, run):
    global board, game_over
    check = check_winner()

    # Getting event
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                run = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            mx, my = pygame.mouse.get_pos()  # Update mouse position here
            x = mx // 200
            y = my // 200

            if game_over:
                reset_game()
                game_over = False

            if board[y][x] == 0 and not game_over:  # Adjusted condition
                board[y][x] = number
                number *= -1
                # print(board)
                check = check_winner()
                if check != 0:
                    show_winner(check)

    return number, run

def reset_game():
    global board, number
    board = [
        [0, 0, 0],
        [0, 0, 0],
        [0, 0, 0]]
    number = 1

def show_winner(check):
    font = pygame.font.SysFont(None, 100)
    if check == 1:
        side = font.render("O win!", True, BLACK, GREEN)
    elif check == -1:
        side = font.render("X win!", True, BLACK, GREEN)

    info = font.render("click to reset", True, BLACK, GREEN)

    while True:
        screen.fill(WHITE)
        draw_grid()
        draw_board()
        screen.blit(side, (screen_width/2 - 160, screen_height/2 - 60))
        screen.blit(info, (screen_width/2 - 180, screen_height/2 + 50))
        pygame.display.update()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.quit()
                    quit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                reset_game()
                return

def check_winner():
    for row_index, row in enumerate(board):
        # Check vertical axis
        if sum(row) == 3:
            return 1
        if sum(row) == -3:
            return -1
        # Check horizontal axis
        if board[0][row_index] + board[1][row_index] + board[2][row_index] == 3:
            return 1
        if board[0][row_index] + board[1][row_index] + board[2][row_index] == -3:
            return -1
        # Check diagonal
        if board[0][0] + board[1][1] + board[2][2] == 3 or board[0][2] + board[1][1] + board[2][0] == 3:
            return 1
        if board[0][0] + board[1][1] + board[2][2] == -3 or board[0][2] + board[1][1] + board[2][0] == -3:
            return -1
    return 0  # Return 0 if no one has won yet

#---------------------------------------------------------------------------------------------------



#main loop--------------------------------------------------------------------------------------------
run = True
while run:

    #full screen in color
    screen.fill(WHITE)

    draw_grid()

    draw_board()

    number, run = get_player_action(number, run)

    #display update
    pygame.display.update()
#-----------------------------------------------------------------------------------------------------
