from PIL import Image
import random
import math
import numpy as np
import noise
import matplotlib.pyplot as plt
wid = 100
hei = 100
image = Image.new("RGB",(wid,hei))
world_test_x = np.zeros(image.size)
world_test_y = np.zeros(image.size)
scale       = 0.1 
octaves     = 6
persistence = 0.6
lacunarity  = 2.0
seed = 19829813476
mult = 50
for x in range(wid):
    for y in range(hei):
        world_test_x[x][y] = ((noise.pnoise2(x/100, 
                                    y/100, 
                                    octaves     = octaves, 
                                    persistence = persistence, 
                                    lacunarity  = lacunarity, 
                                    repeatx     = wid, 
                                    repeaty     = hei, 
                                    base        = 0)))*mult
for x in range(wid):
    for y in range(hei):
        world_test_y[x][y] = ((noise.pnoise2((x+seed)/100, 
                                    (y+seed)/100, 
                                    octaves     = octaves, 
                                    persistence = persistence, 
                                    lacunarity  = lacunarity, 
                                    repeatx     = wid, 
                                    repeaty     = hei, 
                                    base        = 0)))*mult

def generate_voronoi_diagram(width, height, num_cells):
    image = Image.new("RGB", (width, height))
    putpixel = image.putpixel
    imgx, imgy = image.size
    nx = []
    ny = []
    nr = []
    ng = []
    nb = []
    nsize = []
    for i in range(num_cells):
        nx.append(random.randrange(imgx))
        ny.append(random.randrange(imgy))
        nr.append(random.randrange(256))
        ng.append(random.randrange(256))
        nb.append(random.randrange(256))
        nsize.append(0)
    for y in range(int(imgy)):
        for x in range(int(imgx)):
            dmin = math.hypot(imgx-1, imgy-1)
            j = -1
            for i in range(num_cells):
                d = math.hypot((nx[i]-x+world_test_x[x][y]), (ny[i]-y+world_test_y[x][y]))
                if d < dmin:
                    dmin = d
                    j = i
                nsize[j] += 1
            putpixel((x, y), (nr[j], ng[j], nb[j]))

    # Преобразуем изображение в массив numpy для визуализации
    img_array = np.array(image)

    # Визуализация с использованием matplotlib
    plt.imshow(img_array)
    plt.show()

generate_voronoi_diagram(wid, hei, 8)