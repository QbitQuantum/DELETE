import ctypes
import psutil
import pyautogui
import time 

process_name = 'Mines3.exe'

def get_game_process_id(process_name):
    for proc in psutil.process_iter(['pid', 'name']):
        if proc.info['name'] == process_name:
            return proc.info['pid']
    return None

process_id = get_game_process_id(process_name)

if process_id:
    print(f'ID процесса игры: {process_id}')

# дескриптор процесса с правами PROCESS_VM_READ
process_handle = ctypes.windll.kernel32.OpenProcess(0x0010, False, process_id)

def cord_bot_x(x_cor):
    # Читаем значение из памяти
        buffer_x = ctypes.c_int()
        bytes_read = ctypes.c_int()
        ctypes.windll.kernel32.ReadProcessMemory(process_handle, 
                                                 x_cor, 
                                                 ctypes.byref(buffer_x), 
                                                 ctypes.sizeof(buffer_x), 
                                                 ctypes.byref(bytes_read))
        return buffer_x.value

def cord_bot_y(y_cor):
    # Читаем значение из памяти
        buffer_y = ctypes.c_int()
        bytes_read = ctypes.c_int()
        ctypes.windll.kernel32.ReadProcessMemory(process_handle, 
                                                 y_cor, 
                                                 ctypes.byref(buffer_y), 
                                                 ctypes.sizeof(buffer_y), 
                                                 ctypes.byref(bytes_read))
        return buffer_y.value 

adress_x = 0x0E121994
adress_y = 0x124F7EF8

cor1x = cord_bot_x(adress_x)
cor1y = cord_bot_y(adress_y)
print(cor1x)
print(cor1y)

def move_pravo(step):
        while (cord_bot_x(adress_x) < cor1x + step):
            pyautogui.press('d')  # Нажимаем клавишу 'd' для перемещения вправо
            time.sleep(0.3)  # Небольшая пауза для имитации реального пользовател

def move_levo(step):
        while (cord_bot_x(adress_x) > cor1x - step):
            pyautogui.press('a')  # Нажимаем клавишу 'd' для перемещения вправо
            time.sleep(0.3)  # Небольшая пауза для имитации реального пользовател

def move_vniz(deep):
        while (cord_bot_y(adress_y) < cor1y + deep):
            pyautogui.press('s')  # Нажимаем клавишу 's' для перемещения вниз
            time.sleep(0.3)  # Небольшая пауза для имитации реального пользовател

step = 4
deep = 1

time.sleep(3)
try:
    while True:
        move_pravo(step)
        #pyautogui.keyUp('d')   
        move_vniz(deep)
        cor1y +=deep
        #pyautogui.keyUp('s')  
        move_levo(step)
        #pyautogui.keyUp('a')  
        move_vniz(deep)
        cor1y +=deep
        #pyautogui.keyUp('s')  

except KeyboardInterrupt:
    # Закрытие дескриптора процесса при прерывании с клавиатуры
    ctypes.windll.kernel32.CloseHandle(process_handle)
    print("Закрытие дескриптора процесса.")