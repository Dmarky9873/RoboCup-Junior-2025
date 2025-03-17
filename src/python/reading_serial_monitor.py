import serial


def readserial(comport, baudrate):

    # 1/timeout is the frequency at which the port is read
    # pylint: disable=no-member
    try:
        ser = serial.Serial(comport, baudrate, timeout=0.1)
    except serial.serialutil.SerialException as _:
        print("Cannot connect to port")
        quit()

    while True:
        data = ser.readline().decode().strip()
        if data:
            return data
        else:
            print("Lost connection to port... restarting")
            return "[ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ]"


if __name__ == '__main__':
    readserial('/dev/cu.usbmodem159293001', 9600)
