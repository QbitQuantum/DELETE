import pygame
import random
import math
#import numpy as np

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

CELL_SIZE = 7

# Вычисление количества клеток по горизонтали и вертикали
COLL_X = SCREEN_WIDTH // CELL_SIZE
COLL_Y = SCREEN_HEIGHT // CELL_SIZE
# Вычисление количества клеток по горизонтали и вертикали

CELL_SIZE = min(SCREEN_WIDTH // COLL_X, SCREEN_HEIGHT // COLL_Y)
#ELL_SIZE = 7
PLAYER_SIZE = CELL_SIZE
CRYSTAL_SIZE = CELL_SIZE 
PLAYER_COLOR = (0, 255, 0)
DEEP_START = 3

# Цвета
CRYSTAL_COLORS_SMALL = [(255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 255, 0)]
CRYSTAL_COLORS_BIG = [(50, 50, 0), (0, 50, 50), (50, 0, 50), (50, 50, 50)]

BACKGROUND_COLOR = (255, 255, 255)  # Белый
GRID_COLOR = (128, 128, 128)  # Серый
PLAYER_COLOR = (0, 255, 0)
PLAYER_CELL_X = 0
PLAYER_CELL_Y = 0

CRYSTAL_MULTIPLIERS_BIG = [1, 2, 3, 4]
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Crystal Collector")
font = pygame.font.SysFont(None, 24)

crystals = []
occupied_cells = [[False] * COLL_X for _ in range(COLL_Y)]

# Функции для рисования
def draw_grid():
    for x in range(0, SCREEN_WIDTH, CELL_SIZE):
        pygame.draw.line(screen, GRID_COLOR, (x, 0), (x, SCREEN_HEIGHT))
    for y in range(0, SCREEN_HEIGHT, CELL_SIZE):
        pygame.draw.line(screen, GRID_COLOR, (0, y), (SCREEN_WIDTH, y))

def draw_player(player): 
    pygame.draw.rect(screen, PLAYER_COLOR, player)

def create_crystal_in_cell(cell_x, cell_y, color):
    x = cell_x * CELL_SIZE + CELL_SIZE // 2 - CRYSTAL_SIZE // 2
    y = cell_y * CELL_SIZE + CELL_SIZE // 2 - CRYSTAL_SIZE // 2
    return {'rect': pygame.Rect(x, y, CRYSTAL_SIZE, CRYSTAL_SIZE), 'color': color}

def draw_crystals(crystals):
    for crystal in crystals:
        pygame.draw.rect(screen, crystal['color'], crystal['rect'])

def draw_player_coordinates(player_cell_x, player_cell_y):
    player_coords_text = font.render(f"Player Coordinates: ({player_cell_x}, {player_cell_y})", True, (0, 0, 0))
    screen.blit(player_coords_text, (10, SCREEN_HEIGHT - 30))

def check_collisions(player, crystals, collected_crystals):
    for crystal in crystals[:]:
        if player.colliderect(crystal['rect']):
            if crystal['color'] in CRYSTAL_COLORS_BIG:
                collected_crystals[CRYSTAL_COLORS_SMALL[CRYSTAL_COLORS_BIG.index(crystal['color'])]] += CRYSTAL_MULTIPLIERS_BIG[CRYSTAL_COLORS_BIG.index(crystal['color'])]
            else:
                collected_crystals[crystal['color']] += 1
            crystals.remove(crystal)
    return collected_crystals

def draw_score(score):
    score_text = font.render(f"Score: {score}", True, (0, 0, 0))
    screen.blit(score_text, (10, 10))

def draw_collected_crystals(collected_crystals):
    y = 40
    for color in CRYSTAL_COLORS_SMALL:
        pygame.draw.rect(screen, color, pygame.Rect(10, y, 20, 20))
        color_text = font.render(f"{collected_crystals[color]}", True, (0, 0, 0))
        screen.blit(color_text, (40, y))
        y += 30

def game_loop():
    player_cell_x = PLAYER_CELL_X
    player_cell_y = PLAYER_CELL_Y
    score = 0
    collected_crystals = {color: 0 for color in CRYSTAL_COLORS_SMALL + CRYSTAL_COLORS_BIG}
    clock = pygame.time.Clock()

    running = True
    while running:  
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        keys = pygame.key.get_pressed()
        if keys[pygame.K_a] and player_cell_x > 0:
            player_cell_x -= 1
        if keys[pygame.K_d] and player_cell_x < COLL_X - 1:
            player_cell_x += 1  
        if keys[pygame.K_w] and player_cell_y > 0:
            player_cell_y -= 1
        if keys[pygame.K_s] and player_cell_y < COLL_Y - 1:
            player_cell_y += 1

        player = pygame.Rect(player_cell_x * CELL_SIZE, player_cell_y * CELL_SIZE, PLAYER_SIZE, PLAYER_SIZE)

        collected_crystals = check_collisions(player, crystals, collected_crystals)
        
        # Генерация кристаллов

        # Отрисовка
        screen.fill(BACKGROUND_COLOR)
        draw_grid() 
        draw_crystals(crystals)
        draw_player(player)
        draw_score(score)
        draw_collected_crystals(collected_crystals)
        draw_player_coordinates(player_cell_x, player_cell_y)

        pygame.display.flip()

        # Ограничиваем частоту кадров
        clock.tick(15)

    pygame.quit()

# Генерируем кристаллы в каждой ячейке
for cell_y in range(DEEP_START, COLL_Y):
    for cell_x in range(COLL_X):
        if cell_y > int(COLL_Y / 2):  # Генерация больших кристаллов на глубине DEEP_START
            color = random.choice(CRYSTAL_COLORS_BIG)
        else:
            color = random.choice(CRYSTAL_COLORS_SMALL)
        crystal = create_crystal_in_cell(cell_x, cell_y, color)
        crystals.append(crystal)
        occupied_cells[cell_y][cell_x] = True

# Запуск игрового цикла
game_loop()