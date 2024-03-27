import pygame
import random
import math

SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
NUM_CELLS_X = 100  
NUM_CELLS_Y = 80 
CELL_SIZE = min(SCREEN_WIDTH // NUM_CELLS_X, SCREEN_HEIGHT // NUM_CELLS_Y)
PLAYER_SIZE = CELL_SIZE
CRYSTAL_SIZE = CELL_SIZE 
PLAYER_COLOR = (0, 255, 0)
DEEP_START = 2
N_SECTION = 10

# Цвета
CRYSTAL_COLORS_SMALL = [(255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 255, 0)]
CRYSTAL_COLORS_BIG = [(255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 255, 0)]
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

def create_crystal_in_cell(cell_x, cell_y, color):
    x = cell_x * CELL_SIZE + CELL_SIZE // 2 - CRYSTAL_SIZE // 2
    y = cell_y * CELL_SIZE + CELL_SIZE // 2 - CRYSTAL_SIZE // 2
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

def calc(N):
    return N * NUM_CELLS_Y / N_SECTION

def game_loop():
    player_cell_x = PLAYER_CELL_X
    player_cell_y = PLAYER_CELL_Y
    crystals = []
    score = 0
    collected_crystals = {color: 0 for color in CRYSTAL_COLORS_SMALL + CRYSTAL_COLORS_BIG}
    clock = pygame.time.Clock()
    
    occupied_cells = [[False] * NUM_CELLS_X for _ in range(NUM_CELLS_Y)]
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
        while len(crystals) < 30:
            for cell_x in range(NUM_CELLS_X):
                for cell_y in range(DEEP_START, math.ceil(calc(1))):
                    if not occupied_cells[cell_y][cell_x]:
                        crystal_color = CRYSTAL_COLORS_SMALL[2]
                        crystals.append(create_crystal_in_cell(cell_x, cell_y, crystal_color))
                        occupied_cells[cell_y][cell_x] = True

            for cell_x in range(NUM_CELLS_X):
                for cell_y in range(math.ceil(calc(1)), math.ceil(calc(2))):
                    if not occupied_cells[cell_y][cell_x]:
                        crystal_colors_to_add = [CRYSTAL_COLORS_SMALL[3], CRYSTAL_COLORS_BIG[0]]
                        crystal_color = random.choice(crystal_colors_to_add)
                        crystals.append(create_crystal_in_cell(cell_x, cell_y, crystal_color))
                        occupied_cells[cell_y][cell_x] = True

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

# Запуск игрового цикла
game_loop()
