from time import sleep
import serial
# these codes are for bluetooth
# hint: please check the function "sleep". how does it work?

class bluetooth:
    def __init__(self):
        self.ser = serial.Serial()

    def do_connect(self,port):
        self.ser.close()
        print("Connecting...")
        try:
            self.ser = serial.Serial(port,9600,timeout=2)
            print("connect success")
            print("")
        except serial.serialutil.SerialException:
            print("fail to connect")
            print("")
            return False
        return True

    def disconnect(self):
        self.ser.close()

    def SerialWriteString(self, data: str):
        send = data.encode("utf-8")
        print(send)
        self.ser.write(send)

    def SerialWriteBytes(self, data: bytes):
        print(data)
        self.ser.write(data)

    def SerialReadString(self):
        waiting = self.ser.in_waiting
        if waiting >= 0:
            rv = self.ser.readline().decode("utf-8")[:]
            # rv = self.ser.readline()
            return rv
        return ""
    
    def SerialReadOneByte(self):
        sleep(0.1)
        # waiting = self.ser.in_waiting

        waiting = self.ser.in_waiting
        if waiting >= 0:
            rv = self.ser.readline().decode("ascii")[:-1]
            # rv = self.ser.read(1)
            # print("rv: ", rv)
            return rv
        return ""
        # rv = self.ser.readline(1)
        # if(rv):
        #     rvtrans = rv.decode("utf-8")
        #     print("rvtrans: ", rvtrans)
        #     return rvtrans
        # else:
        #     return 0

    def SerialReadByte(self):
        sleep(0.05)
        waiting = self.ser.in_waiting
        rv = self.ser.read(waiting)
        if(rv):
            UID = hex(int.from_bytes(rv, byteorder='big', signed=False))
            self.ser.flushInput()
            return UID
        else:
            return 0
