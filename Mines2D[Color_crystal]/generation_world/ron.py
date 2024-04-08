

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def lerp(a, b, t):
    return a + t * (b - a)

def fade(t):
    return t * t * t * (t * (t * 6 - 15) + 10)

def grad(hash, x, y, z):
    h = hash & 15
    u = h < 8
    v = h < 4
    u = np.where(u, x, y)
    v = np.where(v, y, np.where(h == 12, x, z))
    return np.where(h & 1 == 0, u, -u) + np.where(h & 2 == 0, v, -v)

def perlin(x, y, z):
    p = np.arange(256, dtype=int)
    np.random.shuffle(p)
    p = np.stack([p, p]).flatten()

    xi = x.astype(int)
    yi = y.astype(int)
    zi = z.astype(int)

    xf = x - xi
    yf = y - yi
    zf = z - zi

    u = fade(xf)
    v = fade(yf)
    w = fade(zf)

    aaa = p[p[p[xi] + yi] + zi]
    aba = p[p[p[xi] + yi + 1] + zi]
    aab = p[p[p[xi] + yi] + zi + 1]
    abb = p[p[p[xi] + yi + 1] + zi + 1]
    baa = p[p[p[xi + 1] + yi] + zi]
    bba = p[p[p[xi + 1] + yi + 1] + zi]
    bab = p[p[p[xi + 1] + yi] + zi + 1]
    bbb = p[p[p[xi + 1] + yi + 1] + zi + 1]

    x1 = xf
    x2 = xf - 1
    y1 = yf
    y2 = yf - 1
    z1 = zf
    z2 = zf - 1

    a = grad(aaa, x1, y1, z1)
    b = grad(baa, x2, y1, z1)
    c = grad(aba, x1, y2, z1)
    d = grad(bba, x2, y2, z1)
    e = grad(aab, x1, y1, z2)
    f = grad(bab, x2, y1, z2)
    g = grad(abb, x1, y2, z2)
    h = grad(bbb, x2, y2, z2)

    k0 = a
    k1 = b - a
    k2 = c - a
    k3 = e - a
    k4 = a - b - c + d
    k5 = a - c - e + g
    k6 = a - b - e + f
    k7 = -a + b + c - d + e - f - g + h

    return k0 + k1*u + k2*v + k3*w + k4*u*v + k5*v*w + k6*w*u + k7*u*v*w

"""
"""
# Пример использования
x, y, z = np.meshgrid(np.linspace(0, 5, 10), np.linspace(0, 5, 10), np.linspace(0, 5, 10))
noise = perlin(x, y, z)
print(noise)
"""

"""

def visualize_perlin_noise_and_derivatives(x, y, z, noise):
    integrated_noise = np.cumsum(noise)

    # Взятие производной
    dx, dy, dz = np.gradient(noise)

    # Создание графиков
    fig = plt.figure(figsize=(15, 5))

    # График исходного шума
    ax1 = fig.add_subplot(131, projection='3d')
    sc1 = ax1.scatter(x, y, z, c=noise.flatten(), cmap='viridis', linewidth=0.5)
    ax1.set_title('Original Noise')

    # График интеграла шума
    ax2 = fig.add_subplot(132, projection='3d')
    sc2 = ax2.scatter(x, y, z, c=integrated_noise.flatten(), cmap='viridis', linewidth=0.5)
    ax2.set_title('Integrated Noise')

    # График производной шума
    ax3 = fig.add_subplot(133, projection='3d')
    sc3 = ax3.scatter(x, y, z, c=dx.flatten(), cmap='viridis', linewidth=0.5)
    ax3.set_title('Derivative of Noise')

    # Общая цветовая шкала
    fig.subplots_adjust(right=0.8)
    cbar_ax = fig.add_axes([0.85, 0.15, 0.05, 0.7])
    fig.colorbar(sc1, cax=cbar_ax)
    cbar_ax.set_title('Шкала значений')

    plt.show()

x, y, z = np.meshgrid(np.linspace(1, 5, 10), np.linspace(1, 5, 10), np.linspace(1, 5, 10))
noise = perlin(x, y, z)
visualize_perlin_noise_and_derivatives(x, y, z, noise)