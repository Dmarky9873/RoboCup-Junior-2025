import serial


def readserial(comport, baudrate):

    # 1/timeout is the frequency at which the port is read
    # pylint: disable=no-member
    try:
        ser = serial.Serial(comport, baudrate, timeout=0.1)
    except serial.serialutil.SerialException as _:
        print("Lost connection to port... restart needed")
        return "[ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ]"

    while True:
        data = ser.readline().decode().strip()
        if data:
            return data
        else:
            return "[ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ]"


if __name__ == '__main__':

    readserial('/dev/tty.usbmodem139169701', 9600)
