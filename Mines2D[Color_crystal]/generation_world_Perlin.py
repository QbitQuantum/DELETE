import time
# Время до выполнения кода
start_time = time.time()

import numpy as np
import matplotlib.pyplot as plt
import noise

size_x = 16000
size_y = 16000

# Функция для генерации шума Перлина
def generate_perlin_noise(width, height, scale=300, octaves=6, persistence=0.5, lacunarity=2.0, seed=None):
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
                                         repeatx=size_x,
                                         repeaty=size_y,
                                         base=0)
    return world

def generate_height_array(length, max_value=0.5, start_value=0.05):
    half_length = length // 2
    log_values = np.logspace(np.log10(start_value), np.log10(max_value), half_length)  # Инвертированный логарифм
    height = np.concatenate((np.full(half_length, start_value), log_values))
    return height

# Создание шума Перлина
noise_map = generate_perlin_noise(size_x, size_y)

# Создание второго массива, копии исходного
modified_noise_map = np.copy(noise_map)

# Добавление зависимости от y
height = generate_height_array(size_y)

for i in range(size_x):
    modified_noise_map[i][(modified_noise_map[i] >= height[i]) & (modified_noise_map[i] <= 0.5)] = 1  # Белый
    modified_noise_map[i][(modified_noise_map[i] < height[i])] = 0  # Чёрный

# Вывод обоих массивов с использованием matplotlib
plt.figure(figsize=(15, 5))

plt.subplot(1, 2, 1)
plt.imshow(noise_map, cmap='gray')
plt.colorbar()
plt.title('Original Perlin Noise')

plt.subplot(1, 2, 2)
plt.imshow(modified_noise_map, cmap='gray')
plt.colorbar()
plt.title('Modified Perlin Noise')

plt.show()

end_time = time.time()
# Вычисление времени выполнения
execution_time = end_time - start_time
print(f"Время выполнения программы: {execution_time} секунд")
