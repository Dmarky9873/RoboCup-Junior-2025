import serial


def readserial(comport, baudrate):

    # 1/timeout is the frequency at which the port is read
    ser = serial.Serial(comport, baudrate, timeout=0.1)

    while True:
        data = ser.readline().decode().strip()
        if data:
            print(data)


if __name__ == '__main__':

    readserial('COM28', 115200)
