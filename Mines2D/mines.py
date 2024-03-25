import pygame
import random
import time

# Константы для настройки игры
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
NUM_CELLS_X = 12  # Количество клеток по горизонтали
NUM_CELLS_Y = 20  # Количество клеток по вертикали
CELL_SIZE = min(SCREEN_WIDTH // NUM_CELLS_X, SCREEN_HEIGHT // NUM_CELLS_Y)
PLAYER_SIZE = CELL_SIZE
CRYSTAL_SIZE = CELL_SIZE  # Размер кристаллов вдвое меньше клеток
PLAYER_COLOR = (0, 255, 0)  # Зеленый

CRYSTAL_COLORS_SMALL = ["images/crystal_small_1.png", 
                        "images/crystal_small_2.png", 
                        "images/crystal_small_3.png", 
                        "images/crystal_small_4.png"]
CRYSTAL_COLORS_BIG = ["images/crystal_big_1.png", 
                      "images/crystal_big_2.png", 
                      "images/crystal_big_3.png", 
                      "images/crystal_big_4.png"]
BACKGROUND_COLOR = (255, 255, 255)  # Белый
GRID_COLOR = (128, 128, 128)  # Серый

PLAYER_CELL_X = 0
PLAYER_CELL_Y = 0

CRYSTAL_MULTIPLIERS_BIG = [1, 2, 3, 4]

# Инициализация pygame
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Crystal Collector")
font = pygame.font.SysFont(None, 24)

# Функция для отрисовки сетки
def draw_grid():
    for x in range(0, SCREEN_WIDTH, CELL_SIZE):
        pygame.draw.line(screen, GRID_COLOR, (x, 0), (x, SCREEN_HEIGHT))
    for y in range(0, SCREEN_HEIGHT, CELL_SIZE):
        pygame.draw.line(screen, GRID_COLOR, (0, y), (SCREEN_WIDTH, y))

# Функция для отрисовки игрока
def draw_player(player):
    pygame.draw.rect(screen, PLAYER_COLOR, player)

def draw_player_coordinates(player_cell_x, player_cell_y):
    player_coords_text = font.render(f"Player Coordinates: ({player_cell_x}, {player_cell_y})", True, (0, 0, 0))
    screen.blit(player_coords_text, (10, SCREEN_HEIGHT - 30))

# Функция для отрисовки кристаллов
def draw_crystals(crystals):
    for crystal in crystals:
        # Загрузите изображение кристалла
        crystal_image = pygame.image.load(crystal['image'])
        # Измените размер изображения, чтобы он соответствовал размеру сетки
        crystal_image = pygame.transform.scale(crystal_image, (CELL_SIZE, CELL_SIZE))
        # Отрисовка изображения кристалла
        screen.blit(crystal_image, crystal['rect'])

# Функция для проверки столкновений игрока с кристаллами
def check_collisions(player, crystals, collected_crystals):
    for crystal in crystals[:]:
        if player.colliderect(crystal['rect']):
            if crystal['image'] in CRYSTAL_COLORS_BIG:
                collected_crystals[CRYSTAL_COLORS_SMALL[CRYSTAL_COLORS_BIG.index(crystal['image'])]] += CRYSTAL_MULTIPLIERS_BIG[CRYSTAL_COLORS_BIG.index(crystal['image'])]
            else:
                collected_crystals[crystal['image']] += 1
            crystals.remove(crystal)
    return collected_crystals

# Функция для создания новых кристаллов в клетках
def create_crystal_in_cell(cell_x, cell_y, image):
    x = cell_x * CELL_SIZE + CELL_SIZE // 2 - CRYSTAL_SIZE // 2
    y = cell_y * CELL_SIZE + CELL_SIZE // 2 - CRYSTAL_SIZE // 2
    return {'rect': pygame.Rect(x, y, CRYSTAL_SIZE, CRYSTAL_SIZE), 'image': image}

# Функция для отрисовки счета
def draw_score(score):
    score_text = font.render(f"Score: {score}", True, (0, 0, 0))
    screen.blit(score_text, (10, 10))

# Функция для отрисовки статистики съеденных кристаллов
def draw_collected_crystals(collected_crystals):
    y = 40
    for image in CRYSTAL_COLORS_SMALL:
        crystal_image = pygame.image.load(image)
        crystal_image = pygame.transform.scale(crystal_image, (20, 20))
        screen.blit(crystal_image, (10, y))
        color_text = font.render(f"{collected_crystals[image]}", True, (0, 0, 0))
        screen.blit(color_text, (40, y))
        y += 30

# Основной игровой цикл
def game_loop():
    player_cell_x = PLAYER_CELL_X
    player_cell_y = PLAYER_CELL_Y
    crystals = []
    score = 0
    collected_crystals = {image: 0 for image in CRYSTAL_COLORS_SMALL + CRYSTAL_COLORS_BIG}
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
        
        # Проверяем столкновения
        collected_crystals = check_collisions(player, crystals, collected_crystals)
        DEEP_START = 2
        while len(crystals) < 100: #DELETE
            for cell_y in range(DEEP_START, 4):
                for cell_x in range(NUM_CELLS_X):
                    if not occupied_cells[cell_y][cell_x]:
                        crystal_image = CRYSTAL_COLORS_SMALL[0]
                        crystals.append(create_crystal_in_cell(cell_x, cell_y, crystal_image))
                        occupied_cells[cell_y][cell_x] = True

        # Генерируем кристаллы на клетках, начиная с cell_y = 5
            for cell_y in range(5, 9):
                for cell_x in range(NUM_CELLS_X):
                    if not occupied_cells[cell_y][cell_x]:
                        crystal_images_to_add = [CRYSTAL_COLORS_SMALL[0], CRYSTAL_COLORS_BIG[0]]
                        crystal_image = random.choice(crystal_images_to_add)
                        crystals.append(create_crystal_in_cell(cell_x, cell_y, crystal_image))
                        occupied_cells[cell_y][cell_x] = True

        # Генерируем кристаллы на клетках, начиная с cell_y = 9
            for cell_y in range(10, 16):
                for cell_x in range(NUM_CELLS_X):
                    if not occupied_cells[cell_y][cell_x]:
                        crystal_image = CRYSTAL_COLORS_BIG[0]
                        crystals.append(create_crystal_in_cell(cell_x, cell_y, crystal_image))
                        occupied_cells[cell_y][cell_x] = True

        # Отрисовываем все объекты
        screen.fill(BACKGROUND_COLOR)
        draw_grid()  # Отрисовываем сетку
        draw_crystals(crystals)
        draw_player(player)
        draw_score(score)
        draw_collected_crystals(collected_crystals)
        # Отрисовываем координаты игрока
        draw_player_coordinates(player_cell_x, player_cell_y)

        pygame.display.flip()

        # Ограничиваем частоту кадров
        clock.tick(15)

    pygame.quit()

# Запуск игрового цикла
game_loop()