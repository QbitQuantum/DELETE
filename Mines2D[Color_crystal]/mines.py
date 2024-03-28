import pygame
import random
import noise
# Константы игры
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
CELL_SIZE = 3
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

    def generate_perlin_noise(self, x, y, scale, octaves, persistence, lacunarity):
        return noise.pnoise2(x / scale, y / scale, octaves=octaves, persistence=persistence, lacunarity=lacunarity)

    def generate_crystals(self):
        SCALE = 29.0
        OCTAVES = 1
        PERSISTENCE = 0.5
        LACUNARITY = 5
        all_noise_values = []
        crystal_map = [[None for _ in range(COLL_X)] for _ in range(COLL_Y)]
        for y in range(DEEP_START, COLL_Y):
            for x in range(COLL_X):
                noise_value = self.generate_perlin_noise(x, y, SCALE, OCTAVES, PERSISTENCE, LACUNARITY)
                all_noise_values.append(noise_value)
                crystal_x = int(x + noise_value)
                crystal_y = int(y + noise_value)
                if noise_value > 0.5:
                    color = random.choice(CRYSTAL_COLORS_BIG)
                else:
                    color = random.choice(CRYSTAL_COLORS_SMALL)
                crystal = Crystal(crystal_x, crystal_y, color)
                self.crystals.append(crystal)
                crystal_map[crystal_y][crystal_x] = crystal

        # Fill in empty cells with a specific color
        for y in range(DEEP_START-1, COLL_Y):
            for x in range(COLL_X):
                if crystal_map[y][x] is None:
                    color = CRYSTAL_COLORS_SKALL[0]  # Replace with the desired color
                    crystal = Crystal(x, y, color)
                    self.crystals.append(crystal)


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