import serial
import time

while True:
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout = .2)
    for i in range(64):
        print(i)
        ser.write(bytes(str(i), 'utf-8'))
        time.sleep(2)
    ser.close()
    time.sleep(1)
