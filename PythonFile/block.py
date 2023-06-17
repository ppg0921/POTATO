from enum import IntEnum

class Direction(IntEnum):
    NORTH = 1
    SOUTH = 2
    WEST  = 3
    EAST  = 4


class Block:
    def __init__(self, Xindex = 0, Yindex = 0):
        self.Xindex = Xindex
        self.Yindex = Yindex
        self.forward = 'h'
        self.backward = 'h'
    
    