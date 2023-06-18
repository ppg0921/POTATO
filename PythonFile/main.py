import maze as mz
from BTinterface import BTinterface

import numpy as np
import pandas
import time
import sys
import os
# import keyboard as kb

def main():
    maze = mz.Maze("data/testmaze.csv")
    interf = BTinterface()
    interf.start()

    
    # interf.start()
    # TODO : Initialize necessary variables
    StartIndex = 48
    FinishIndex = 47
    UIDstring = ""
    uidGet = False
    if (sys.argv[1] == '0'):
        print("Mode 0: for treasure-hunting")
        # TODO : for treasure-hunting, which encourages you to hunt as many scores as possible
        
    elif (sys.argv[1] == '1'):

        print("Mode 1: Self-testing mode.")
        
        
        print(maze.getCmds())
        # CommandString = maze.getCmds()
        # for i in range(maze.getCmdLen()):
        #     interf.send_action(CommandString[i])
        
        
        # send first action
        
        
        # interf.send_action(maze.getCmds())
        print("maze.getCmds(): ", maze.getCmds())
        # interf.send_action(maze.getCmds()[0])
        # print("maze.nowCmd: ", maze.nowCmd)
        # interf.send_action(maze.getCmds()[maze.nowCmd])
        # maze.nowCmd+=1            
        
        
        while(True):
            String_read = interf.get_string()
            if String_read != "":
                print("String_read = ", String_read);
            
        #     # if kb.is_pressed("w"):
        #     #     interf.send_action("f")
        #     # elif kb.is_pressed("a"):
        #     #     interf.send_action("l")
        #     # elif kb.is_pressed("s"):
        #     #     interf.send_action("b")
        #     # elif kb.is_pressed("d"):
        #     #     interf.send_action("r")
        #     # elif kb.is_pressed("h"):
        #     #     interf.send_action("h")
        #     # else:
        #     #     interf.send_action("h")
        
        
        
        # TODO: You can write your code to test specific function.
        

if __name__ == '__main__':
    main()
