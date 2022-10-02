import serial

try:
    with serial.Serial('COM6',9600, timeout=1) as ser:
        while(1):
            try:
                line = ser.readline()   # read a '\n' terminated line
                print(line)
            except KeyboardInterrupt:
                print("Keyboard Interrupt")
                break
            except:
                print("HARDWARE NOT DETECTED")
except:
    print("Device not connected Or wrong port number")
  