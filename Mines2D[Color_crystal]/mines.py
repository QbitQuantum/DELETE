import pygame
import random
import math
#import numpy as np

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

SHIRINA = 74
DEEP = 300

CELL_SIZE = min(SCREEN_WIDTH // SHIRINA, SCREEN_HEIGHT // DEEP)
PLAYER_SIZE = CELL_SIZE
CRYSTAL_SIZE = CELL_SIZE 
PLAYER_COLOR = (0, 255, 0)
DEEP_START = 3

# Цвета
CRYSTAL_COLORS_SMALL = [(0, 0, 1), (0, 0, 2), (0, 0, 3), (0, 0, 4)]
CRYSTAL_COLORS_BIG = [(255, 0, 0), (255, 0, 0), (255, 0, 0), (255, 0, 0)]

BACKGROUND_COLOR = (255, 255, 255)  # Белый
GRID_COLOR = (128, 128, 128)  # Серый
PLAYER_COLOR = (0, 255, 0)
PLAYER_CELL_X = 0
PLAYER_CELL_Y = 0

# Функция для вычисления количества клеток
def calculate_num_cells(screen_size, cell_size):
    return screen_size // cell_size

# Вычисление количества клеток по горизонтали и вертикали
NUM_CELLS_X = calculate_num_cells(SCREEN_WIDTH, min(SCREEN_WIDTH // SHIRINA, SCREEN_HEIGHT // DEEP)) # SCREEN_WIDTH/2
NUM_CELLS_Y = calculate_num_cells(SCREEN_HEIGHT, min(SCREEN_WIDTH // SHIRINA, SCREEN_HEIGHT // DEEP)) # SCREEN_HEIGHT/2

#NUM_CELLS_X = int(SCREEN_WIDTH/2)
#NUM_CELLS_Y = int(SCREEN_HEIGHT/2)



print(f"SCREEN_WIDTH = {SCREEN_WIDTH}")
print(f"SCREEN_HEIGHT = {SCREEN_HEIGHT}")

print(f"NUM_CELLS_X = {NUM_CELLS_X}")
print(f"NUM_CELLS_Y = {NUM_CELLS_Y}")

CRYSTAL_MULTIPLIERS_BIG = [1, 2, 3, 4]
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Crystal Collector")
font = pygame.font.SysFont(None, 24)

# Функции для рисования
def draw_grid():
    for x in range(0, SCREEN_WIDTH, CELL_SIZE):
        pygame.draw.line(screen, GRID_COLOR, (x, 0), (x, SCREEN_HEIGHT))
    for y in range(0, SCREEN_HEIGHT, CELL_SIZE):
        pygame.draw.line(screen, GRID_COLOR, (0, y), (SCREEN_WIDTH, y))

def draw_player(player): 
    pygame.draw.rect(screen, PLAYER_COLOR, player)

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

def create_crystal_in_cell(cell_x, cell_y, color, depth):
    x = cell_x * CELL_SIZE + CELL_SIZE // 2 - CRYSTAL_SIZE // 2
    y = cell_y * CELL_SIZE + CELL_SIZE // 2 - CRYSTAL_SIZE // 2
    y += depth * CELL_SIZE  # Сдвиг по вертикали в зависимости от глубины
    return {'rect': pygame.Rect(x, y, CRYSTAL_SIZE, CRYSTAL_SIZE), 'color': color}

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
crystals = []
occupied_cells = [[False] * NUM_CELLS_X for _ in range(NUM_CELLS_Y)]

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
        if keys[pygame.K_d] and player_cell_x < NUM_CELLS_X - 1:
            player_cell_x += 1  
        if keys[pygame.K_w] and player_cell_y > 0:
            player_cell_y -= 1
        if keys[pygame.K_s] and player_cell_y < NUM_CELLS_Y - 1:
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
i=0
#for cell_y in range(DEEP_START, DEEP):
#            for cell_x in range(SHIRINA):

#test 70


for cell_y in range(DEEP_START, NUM_CELLS_Y):
    for cell_x in range(NUM_CELLS_X):
        while (not occupied_cells[cell_y][cell_x]):
            if cell_y > 75 :  # Генерация больших кристаллов на глубине DEEP_START
                i += 1
                color = random.choice(CRYSTAL_COLORS_BIG)
                crystal = create_crystal_in_cell(cell_x, cell_y, color, cell_y - DEEP_START)
                crystals.append(crystal)
                occupied_cells[cell_y][cell_x] = True
                i += 1
            else:  # Генерация больших кристаллов на глубине DEEP_START + 1
                color = random.choice(CRYSTAL_COLORS_SMALL)
                crystal = create_crystal_in_cell(cell_x, cell_y, color, cell_y - DEEP_START)
                crystals.append(crystal)
                occupied_cells[cell_y][cell_x] = True


print(f"Больших {i}")
"""
for cell_y in range(DEEP_START, NUM_CELLS_Y):
    for cell_x in range(NUM_CELLS_X):
        if not occupied_cells[cell_y][cell_x]:  # Проверка, что ячейка не занята
            if cell_y > 75 :  # Генерация маленьких кристаллов на глубине DEEP_START
                color = random.choice(CRYSTAL_COLORS_BIG)
            else:  # Генерация больших кристаллов на глубине DEEP_START + 1
                color = random.choice(CRYSTAL_COLORS_SMALL)
            crystal = create_crystal_in_cell(cell_x, cell_y, color, cell_y - DEEP_START)
            crystals.append(crystal)
            occupied_cells[cell_y][cell_x] = True

"""

"""
for depth in range(DEEP_START, NUM_CELLS_Y):  # Глубина, в которой будут спавниться кристаллы
    cell_x = random.randint(0, NUM_CELLS_X - 1)
    cell_y = random.randint(0, NUM_CELLS_Y - 1)
    if not occupied_cells[cell_y][cell_x]:  # Проверка, что ячейка не занята
        if depth < math.ceil(NUM_CELLS_Y/2) :  # Генерация маленьких кристаллов на глубине DEEP_START
            color = random.choice(CRYSTAL_COLORS_SMALL)
        else:  # Генерация больших кристаллов на глубине DEEP_START + 1
            color = random.choice(CRYSTAL_COLORS_BIG)
        crystal = create_crystal_in_cell(cell_x, cell_y, color, depth - DEEP_START)
        crystals.append(crystal)
        occupied_cells[cell_y][cell_x] = True
"""

"""
for depth in range(DEEP_START, NUM_CELLS_Y):  # Глубина, в которой будут спавниться кристаллы
    for _ in range(150):  # Количество кристаллов, которые будут спавниться на каждой глубине
        cell_x = random.randint(0, NUM_CELLS_X - 1)
        cell_y = random.randint(0, NUM_CELLS_Y - 1)
        if not occupied_cells[cell_y][cell_x]:  # Проверка, что ячейка не занята
            if depth < math.ceil(NUM_CELLS_Y/2) :  # Генерация маленьких кристаллов на глубине DEEP_START
                color = random.choice(CRYSTAL_COLORS_SMALL)
            else:  # Генерация больших кристаллов на глубине DEEP_START + 1
                color = random.choice(CRYSTAL_COLORS_BIG)
            crystal = create_crystal_in_cell(cell_x, cell_y, color, depth - DEEP_START)
            crystals.append(crystal)
            occupied_cells[cell_y][cell_x] = True
"""


"""
for _ in range(NUM_CELLS_X * NUM_CELLS_Y):  # Количество кристаллов, которые будут спавниться на каждой глубине
    cell_x = random.randint(0, NUM_CELLS_X - 1)
    cell_y = random.randint(0, NUM_CELLS_Y - 1)
    if not occupied_cells[cell_y][cell_x]:  # Проверка, что ячейка не занята
        depth = np.random.normal(mean, std_dev)  # Генерация глубины с помощью нормального распределения
        depth = max(0, min(int(depth), NUM_CELLS_Y - 1))  # Ограничение глубины в рамках NUM_CELLS_Y
        if depth < math.ceil(NUM_CELLS_Y/2) :  # Генерация маленьких кристаллов на глубине DEEP_START
            color = random.choice(CRYSTAL_COLORS_SMALL)
        else:  # Генерация больших кристаллов на глубине DEEP_START + 1
            color = random.choice(CRYSTAL_COLORS_BIG)
        crystal = create_crystal_in_cell(cell_x, cell_y, color, depth - DEEP_START)
        crystals.append(crystal)
        occupied_cells[cell_y][cell_x] = True

"""
# Запуск игрового цикла
game_loop()
