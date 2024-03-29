import time
# Время до выполнения кода
start_time = time.time()

import numpy as np
import matplotlib.pyplot as plt
import noise

size_x = 32000
size_y = 32000

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

# Создание шума Перлина
noise_map = generate_perlin_noise(size_x, size_y)
modified_noise_map = np.copy(noise_map)
height = np.concatenate((np.full(size_y // 2, 0.05), np.logspace(np.log10(0.05), np.log10(0.5), size_y // 2)))

for i in range(size_x):
    for j in range(len(modified_noise_map[i])):
        if height[i] <= modified_noise_map[i][j] <= 0.5:
            modified_noise_map[i][j] = 1  # Белый
        elif modified_noise_map[i][j] < height[i]:
            modified_noise_map[i][j] = 0  # Чёрный
            

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
# Вычисление времени выполнения

end_time = time.time()
execution_time = end_time - start_time
print(f"Время выполнения программы: {execution_time} секунд")

plt.show()

