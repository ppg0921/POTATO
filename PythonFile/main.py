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
        
        
        interf.send_action(maze.getCmds())
        
        print("maze.getCmds(): ", maze.getCmds())
        # interf.send_action(maze.getCmds()[0])
        # print("maze.nowCmd: ", maze.nowCmd)
        # interf.send_action(maze.getCmds()[maze.nowCmd])
        # maze.nowCmd+=1
        


        # while(True):
        #     state = interf.get_request()
        #     if state == 2:
        #         uidGet = False
        #         while uidGet is False:
        #             UIDstring = interf.get_UID()
        #             if UIDstring!=0:
        #                 uidGet = True
        #                 UIDstring = UIDstring[2:]
        #                 print("UIDstring.len:" , len(UIDstring))
        #                 if len(UIDstring)==7:
        #                     tmp = UIDstring
        #                     UIDstring = "0"
        #                     UIDstring += tmp
        #                     print("UIDstring.len after processed:" , len(UIDstring))
        #                 print("UIDstring:", UIDstring.upper())
                        
        #                 UIDstring = 0
            
        #     elif state == 1:
        #         maze.nowCmd += 1
        #         if(maze.nowCmd<maze.CmdLen):
        #             print("maze.getCmds()[maze.nowCmd]: ", maze.getCmds()[maze.nowCmd])
        #             interf.send_action(maze.getCmds()[maze.nowCmd])
                
                
            
            
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
        
        
        
        # # TODO: You can write your code to test specific function.
        

if __name__ == '__main__':
    main()
