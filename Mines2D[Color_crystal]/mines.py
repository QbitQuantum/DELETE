import pygame
import random
import noise
import numpy as np

# Константы игры
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 800
CELL_SIZE = 4
COLL_X = SCREEN_WIDTH // CELL_SIZE
COLL_Y = SCREEN_HEIGHT // CELL_SIZE
DEEP_START = 3
CRYSTAL_SIZE = CELL_SIZE
PLAYER_SIZE = CELL_SIZE
PLAYER_COLOR = (0, 255, 0)
CRYSTAL_COLORS_SMALL = [(0, 255, 0), (0, 0, 255), (255, 0, 0), (255, 0, 254), (0, 255,254)]
CRYSTAL_COLORS_BIG = [(0, 54, 0), (0, 0, 54), (54, 0, 0), (54, 0, 53), (0, 54,53)]
CRYSTAL_MULTIPLIERS_BIG = [4, 2, 2, 1, 1]
CRYSTAL_COLORS_SKALL = [(0, 0, 0)]
BACKGROUND_COLOR = (255, 255, 255)
GRID_COLOR = (128, 128, 128)

# Инициализация Pygame
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Crystal Collector")
font = pygame.font.SysFont(None, 24)

# Классы
class Player:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def move(self, dx, dy, game_map):
        new_x = self.x + dx
        new_y = self.y + dy
        # Проверяем, что новая позиция находится в пределах игрового поля
        if 0 <= new_x < COLL_X and 0 <= new_y < COLL_Y:
            # Проверяем, что в новой позиции нет кристаллов, которые нельзя проходить
            if not any(crystal.x == new_x and crystal.y == new_y and crystal.color in CRYSTAL_COLORS_SKALL for crystal in game_map.crystals):
                self.x = new_x
                self.y = new_y

    def draw(self, surface):
        rect = pygame.Rect(self.x * CELL_SIZE, self.y * CELL_SIZE, PLAYER_SIZE, PLAYER_SIZE)
        pygame.draw.rect(surface, PLAYER_COLOR, rect)

class Crystal:
    def __init__(self, x, y, color):
        self.x = x
        self.y = y
        self.color = color

    def draw(self, surface):
        rect = pygame.Rect(self.x * CELL_SIZE, self.y * CELL_SIZE, CRYSTAL_SIZE, CRYSTAL_SIZE)
        pygame.draw.rect(surface, self.color, rect)

class GameMap:
    def __init__(self):
        self.crystals = []
        self.generate_crystals()

    def generate(self, width, height, scale=300, octaves=7, persistence=0.5, lacunarity=2.0, seed=None):
        """
        #Шум перлинга
        if seed is not None:
            np.random.seed(seed)
        shape = (width, height)
        world = np.zeros(shape)
        for i in range(width):
            for j in range(height):
                world[i][j] = noise.pnoise2(i/scale,
                                            j/scale,
                                            octaves=octaves,
                                            persistence=persistence,
                                            lacunarity=lacunarity,
                                            repeatx=width,
                                            repeaty=height,
                                            base=0)
                                            """
        #Шум Диамонда
        if seed is not None:
            np.random.seed(seed)
        shape = (width, height)
        world = np.zeros(shape)
        half_width = width // 2
        half_height = height // 2
        world[half_width][half_height] = 1.0

        for i in range(octaves - 1, 0, -1):
            size = 2 ** i
            for x in range(0, width - size, size // 2):
                for y in range(0, height - size, size // 2):
                    square_average = (world[x][y] + world[x + size // 2][y] +
                                    world[x][y + size // 2] + world[x + size // 2][y + size // 2]) * 0.25
                    world[x + size // 2][y + size // 2] = square_average + np.random.uniform(-1, 1) * persistence
        
            for x in range(0, width, size):
                for y in range(0, height, size):
                    diamond_average = (world[x - size // 2][y] + world[x - size // 2][y] +
                                    world[x][y - size // 2] + world[x][y - size // 2]) * 0.25
                    world[x][y] = diamond_average + np.random.uniform(-1, 1) * persistence

        return world

    def generate_crystals(self):
        world = self.generate(COLL_X, COLL_Y)
        height = np.concatenate((np.full(COLL_Y // 2, 0.05), np.logspace(np.log10(0.05), np.log10(0.4), COLL_Y // 2)))
        crystal_map = [[None for _ in range(COLL_X)] for _ in range(COLL_Y)]
        for j in range(3, COLL_Y):
            for i in range(len(world[j])):
                if height[i] <= world[i][j] <= 0.5:
                    color = random.choice(CRYSTAL_COLORS_BIG)
                elif world[i][j] < height[i]:
                    color = random.choice(CRYSTAL_COLORS_SMALL)
                crystal = Crystal(i, j, color)
                self.crystals.append(crystal)
                crystal_map[j][i] = crystal


    def draw(self, surface):
        self.draw_grid(surface)
        for crystal in self.crystals:
            crystal.draw(surface)

    def draw_grid(self, surface):
        for x in range(0, SCREEN_WIDTH, CELL_SIZE):
            pygame.draw.line(surface, GRID_COLOR, (x, 0), (x, SCREEN_HEIGHT))
        for y in range(0, SCREEN_HEIGHT, CELL_SIZE):
            pygame.draw.line(surface, GRID_COLOR, (0, y), (SCREEN_WIDTH, y))

    def draw_score(self, score, surface):
        score_text = font.render(f"Score: {score}", True, (0, 0, 0))
        surface.blit(score_text, (10, 10))

    def draw_collected_crystals(self, collected_crystals, surface):
        y = 40
        for color in CRYSTAL_COLORS_SMALL:
            pygame.draw.rect(surface, color, pygame.Rect(10, y, 20, 20))
            color_text = font.render(f"{collected_crystals[color]}", True, (0, 0, 0))
            surface.blit(color_text, (40, y))
            y += 30

# Главная функция игры
def game_loop():
    player = Player(0, 0)
    game_map = GameMap()
    score = 0
    collected_crystals = {color: 0 for color in CRYSTAL_COLORS_SMALL + CRYSTAL_COLORS_BIG + CRYSTAL_COLORS_SKALL}
    clock = pygame.time.Clock()

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        keys = pygame.key.get_pressed()
        if keys[pygame.K_a]:
            player.move(-1, 0, game_map)
        if keys[pygame.K_d]:
            player.move(1, 0, game_map)
        if keys[pygame.K_w]:
            player.move(0, -1, game_map)
        if keys[pygame.K_s]:
            player.move(0, 1, game_map)

        # Проверка столкновений игрока с кристаллами
        for crystal in game_map.crystals[:]:
            if player.x == crystal.x and player.y == crystal.y:
                if crystal.color in CRYSTAL_COLORS_BIG or crystal.color in CRYSTAL_COLORS_SMALL:
                    if crystal.color in CRYSTAL_COLORS_BIG:
                        index = CRYSTAL_COLORS_BIG.index(crystal.color)
                        collected_crystals[CRYSTAL_COLORS_SMALL[index]] += CRYSTAL_MULTIPLIERS_BIG[index]
                    else:
                        collected_crystals[crystal.color] += 1
                    score += 1
                    game_map.crystals.remove(crystal)

        # Отрисовка
        screen.fill(BACKGROUND_COLOR)
        game_map.draw(screen)
        player.draw(screen)
        game_map.draw_score(score, screen)
        game_map.draw_collected_crystals(collected_crystals, screen)

        pygame.display.flip()

        # Ограничение частоты кадров
        clock.tick(15)

    pygame.quit()

# Запуск игрового цикла
game_loop()