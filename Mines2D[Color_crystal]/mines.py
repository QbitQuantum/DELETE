import pygame
import random

# Константы
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
CELL_SIZE = 50
COLL_X = SCREEN_WIDTH // CELL_SIZE
COLL_Y = SCREEN_HEIGHT // CELL_SIZE
PLAYER_SIZE = CELL_SIZE
CRYSTAL_SIZE = CELL_SIZE // 2
PLAYER_COLOR = (0, 255, 0)
DEEP_START = 3
CRYSTAL_COLORS_SMALL = [(255, 0, 0), (0, 255, 0), (0, 0, 255), (255, 255, 0)]
CRYSTAL_COLORS_BIG = [(50, 50, 0), (0, 50, 50), (50, 0, 50), (50, 50, 50)]
CRYSTAL_COLORS_REDSCALL = [(0, 0, 0)]
BACKGROUND_COLOR = (255, 255, 255)
GRID_COLOR = (128, 128, 128)
CRYSTAL_MULTIPLIERS_BIG = [1, 2, 3, 4]

class Player:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def move(self, dx, dy):
        self.x += dx
        self.y += dy

    def draw(self, screen):
        rect = pygame.Rect(self.x * CELL_SIZE, self.y * CELL_SIZE, PLAYER_SIZE, PLAYER_SIZE)
        pygame.draw.rect(screen, PLAYER_COLOR, rect)

class Crystal:
    def __init__(self, x, y, color):
        self.x = x
        self.y = y
        self.color = color

    def draw(self, screen):
        rect = pygame.Rect(self.x * CELL_SIZE + CELL_SIZE // 2 - CRYSTAL_SIZE // 2,
                           self.y * CELL_SIZE + CELL_SIZE // 2 - CRYSTAL_SIZE // 2,
                           CRYSTAL_SIZE, CRYSTAL_SIZE)
        pygame.draw.rect(screen, self.color, rect)


class CrystalCollector:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption("Crystal Collector")
        self.font = pygame.font.SysFont(None, 24)
        self.player = Player(0, 0)
        self.score = 0
        self.collected_crystals = {color: 0 for color in CRYSTAL_COLORS_SMALL + CRYSTAL_COLORS_BIG + CRYSTAL_COLORS_REDSCALL}
        self.crystals = []
        self.clock = pygame.time.Clock()
        self.occupied_cells = [[False] * COLL_X for _ in range(COLL_Y)]

    def draw_grid(self):
        for x in range(0, SCREEN_WIDTH, CELL_SIZE):
            pygame.draw.line(self.screen, GRID_COLOR, (x, 0), (x, SCREEN_HEIGHT))
        for y in range(0, SCREEN_HEIGHT, CELL_SIZE):
            pygame.draw.line(self.screen, GRID_COLOR, (0, y), (SCREEN_WIDTH, y))

    def draw_crystals(self):
        for crystal in self.crystals:
            crystal.draw(self.screen)

    def draw_player_coordinates(self):
        player_coords_text = self.font.render(f"Player Coordinates: ({self.player.x}, {self.player.y})", True, (0, 0, 0))
        self.screen.blit(player_coords_text, (10, SCREEN_HEIGHT - 30))

    def check_collisions(self):
        for crystal in self.crystals[:]:
            player_rect = pygame.Rect(self.player.x * CELL_SIZE, self.player.y * CELL_SIZE, PLAYER_SIZE, PLAYER_SIZE)
            if player_rect.colliderect(crystal.rect):
                if crystal.color in CRYSTAL_COLORS_BIG:
                    self.collected_crystals[CRYSTAL_COLORS_SMALL[CRYSTAL_COLORS_BIG.index(crystal.color)]] += CRYSTAL_MULTIPLIERS_BIG[CRYSTAL_COLORS_BIG.index(crystal.color)]
                else:
                    self.collected_crystals[crystal.color] += 1
                self.crystals.remove(crystal)

    def draw_score(self):
        score_text = self.font.render(f"Score: {self.score}", True, (0, 0, 0))
        self.screen.blit(score_text, (10, 10))

    def draw_collected_crystals(self):
        y = 40
        for color in CRYSTAL_COLORS_SMALL + CRYSTAL_COLORS_REDSCALL:
            pygame.draw.rect(self.screen, color, pygame.Rect(10, y, 20, 20))
            color_text = self.font.render(f"{self.collected_crystals[color]}", True, (0, 0, 0))
            self.screen.blit(color_text, (40, y))
            y += 30
    
    def generate_perlin_noise(self, scale, octaves, persistence, lacunarity):
        return noise.pnoise2(COLL_X / scale, COLL_Y / scale, octaves=octaves, persistence=persistence, lacunarity=lacunarity)

    def world(self):
        SCALE = 10.0
        OCTAVES = 1
        PERSISTENCE = 0.1
        LACUNARITY = 1.8

        all_noise_values = []

        for cell_y in range(DEEP_START, COLL_Y):
            for cell_x in range(COLL_X):
                noise_value = self.generate_perlin_noise(cell_x, cell_y, SCALE, OCTAVES, PERSISTENCE, LACUNARITY)
                all_noise_values.append(noise_value)
                crystal_x = int(cell_x + noise_value)
                crystal_y = int(cell_y + noise_value)
                if noise_value < 0.5: 
                    color = random.choice(CRYSTAL_COLORS_BIG)
                    crystal = self.create_crystal_in_cell(crystal_x, crystal_y, color)
                    self.crystals.append(crystal)
                    self.occupied_cells[cell_y][cell_x] = True
                else:
                    color = random.choice(CRYSTAL_COLORS_SMALL)
                    crystal = self.create_crystal_in_cell(crystal_x, crystal_y, color)
                    self.crystals.append(crystal)
                    self.occupied_cells[cell_y][cell_x] = True
                    
        for y in range(DEEP_START, cell_y):
            for x in range(cell_x):
                if not self.occupied_cells[y][x]:
                    color = random.choice(CRYSTAL_COLORS_REDSCALL)
                    crystal = self.create_crystal_in_cell(cell_x, cell_y, color)
                    self.crystals.append(crystal)
                    self.occupied_cells[y][x] = True

    def game_loop(self):
        running = True
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

            keys = pygame.key.get_pressed()
            if keys[pygame.K_a] and self.player.x > 0:
                self.player.move(-1, 0)
            if keys[pygame.K_d] and self.player.x < COLL_X - 1:
                self.player.move(1, 0)
            if keys[pygame.K_w] and self.player.y > 0:
                self.player.move(0, -1)
            if keys[pygame.K_s] and self.player.y < COLL_Y - 1:
                self.player.move(0, 1)

            self.check_collisions()

            self.world()


            self.screen.fill(BACKGROUND_COLOR)
            self.draw_grid()
            self.draw_crystals()
            self.player.draw(self.screen)
            self.draw_score()
            self.draw_collected_crystals()
            self.draw_player_coordinates()

            pygame.display.flip()

            self.clock.tick(15)

        pygame.quit()

game = CrystalCollector()
game.game_loop()