import BT

# hint: You may design additional functions to execute the input command, which will be helpful when debugging :)

class BTinterface:
    def __init__(self):
        print("")
        print("Arduino Bluetooth Connect Program.")
        print("")
        self.ser = BT.bluetooth()
        port = input("PC bluetooth port name: ")
        while(not self.ser.do_connect(port)):
            if(port == "quit"):
                self.ser.disconnect()
                quit()
            port = input("PC bluetooth port name: ")

    def start(self):
        input("Press enter to start.")
        # self.ser.SerialWriteString('s')

    def get_UID(self):
        return self.ser.SerialReadByte()
    
    def get_request(self):
        request = str(self.ser.SerialReadOneByte())[:-1]
        # print("request: ", request)
        if request == "N":
            print("get_request N, give next action")
            return 1
        elif request == "R":
            print("get_request R, receive uid")
            return 2
        elif request == "69":
            print("ALL WHITE!!!!!!!!")
            return 0
        else:
            return 0

    def send_action(self,dirc):
        # dircstring = str(dirc)
        self.ser.SerialWriteString(dirc)
        
        # TODO : send the action to car
        return

    def end_process(self):
        self.ser.SerialWriteString('e')
        self.ser.disconnect()
    
    

if __name__ == '__main__':
    test = BTinterface()
    test.start()
    test.ser.SerialWriteString("testString")
    test.end_process()