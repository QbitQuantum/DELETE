import pyautogui

# Получить размер экрана
screen_size = pyautogui.size()
print(f'Размер экрана: {screen_size}')


from pynput import mouse

# Функция, которая будет вызвана при клике мыши
def on_click(x, y, button, pressed):
    if pressed:
        print(f'Курсор был кликнут в позиции: ({x}, {y})')

# Создание слушателя мыши
with mouse.Listener(on_click=on_click) as listener:
    try:
        listener.join()
    except KeyboardInterrupt:
        print('Программа остановлена пользователем.')