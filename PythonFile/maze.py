from block import *
import numpy as np
import pandas
from enum import IntEnum

BLOCK_LENGTH_MIN = 45
BLOCK_LENGTH_MAX = 60


class Maze:
    def __init__(self, filepath, carOriDir=Direction.NORTH):
        df = pandas.read_csv(filepath)
        self.cmd = "P"
        self.blocks = []
        self.bk_array = []
        # print(df.columns.tolist())
        self.vertexNum, column_count = df.shape
        self.length = 0
        self.width = 0
        tmplength, tmpwidth = 0, 0
        self.blockLength = 0
        self.blockWidth = 0
        self.rowNum, self.colNum = 0, 0
        xback = False
        yback = False
        for i in range(self.vertexNum-1):
            # print(i)
            # HorVer = i % 2
            Ydisplacement = df["Yindex"][i+1] - df["Yindex"][i]
            Xdisplacement = df["Xindex"][i+1] - df["Xindex"][i]
            if tmplength > self.length:
                self.length = tmplength
            if tmpwidth > self.width:
                self.width = tmpwidth
            tmplength += Xdisplacement
            tmpwidth += Ydisplacement
        print(self.length, self.width)
        for i in range(BLOCK_LENGTH_MIN, BLOCK_LENGTH_MAX+1):
            if self.length % i == 0:
                self.blockLength = i
                break
        for i in range(BLOCK_LENGTH_MIN, BLOCK_LENGTH_MAX+1):
            if self.width % i == 0:
                self.blockWidth = i
                break
        if self.blockLength == 0:
            for i in range(BLOCK_LENGTH_MIN, BLOCK_LENGTH_MAX+1):
                if self.length % i <= 4:
                    self.blockLength = i
                    break
        if self.blockWidth == 0:
            for i in range(BLOCK_LENGTH_MIN, BLOCK_LENGTH_MAX+1):
                if self.width % i <= 4:
                    self.blockWidth = i
                    break
        print(self.blockLength, self.blockWidth)
        self.colNum = int(self.length/self.blockLength)
        self.rowNum = int(self.width/self.blockWidth)

        print("colNum = ", self.colNum)
        print("rowNum = ", self.rowNum)

        for i in range(self.rowNum):
            new = []
            for j in range(self.colNum):
                new.append(Block(i, j))
            self.bk_array.append(new)

        self.cmd += "{PiPiN:"
        self.cmd += str(self.colNum)
        self.cmd += ",M:"
        self.cmd += str(self.rowNum)
        self.cmd += ",xlen:"
        self.cmd += str(self.blockLength)
        self.cmd += ",ylen:"
        self.cmd += str(self.blockWidth)
        self.cmd += ",action:"
        i, j = 0, 0

        for k in range(self.colNum*self.rowNum):
            # self.bk_array[i][j] = self.bk_array[i][j]
            # print("i = ", i, "j = ", j)

            if k == self.colNum*self.rowNum-1:
                self.bk_array[i][j].forward = 'c'
                if j%2==0:
                    self.bk_array[i][j].backward = 'n'
                else:
                    self.bk_array[i][j].backward = 's'
                
                break
            elif i == 0:
                # if j%2==1:
                if k == 0:
                    self.bk_array[0][0].forward = 's'
                    self.bk_array[0][0].backward = 'm'
                else:
                    if j%2==0:
                        self.bk_array[i][j].forward = 's'
                        self.bk_array[i][j].backward = 'w'
                    else:
                        self.bk_array[i][j].forward = 'e'
                        self.bk_array[i][j].backward = 's'
                if j % 2 == 0:
                    i += 1
                else:
                    j += 1
            elif i == self.rowNum-1:
                if j%2==0:
                    self.bk_array[i][j].forward = 'e'
                    self.bk_array[i][j].backward = 'n'
                else:
                    self.bk_array[i][j].forward = 'n'
                    self.bk_array[i][j].backward = 'w'
                
                if j % 2 == 0:
                    j += 1
                else:
                    i -= 1
            else:
                if j%2==0:
                    self.bk_array[i][j].forward = 's'
                    self.bk_array[i][j].backward = 'n'
                else:
                    self.bk_array[i][j].forward = 'n'
                    self.bk_array[i][j].backward = 's'
                if j % 2 == 0:
                    i += 1
                else:
                    i -= 1

        for i in range(self.rowNum):
            for j in range(self.colNum):
                self.cmd += str(self.bk_array[i][j].forward)
        for i in range(self.rowNum):
            for j in range(self.colNum):
                self.cmd += str(self.bk_array[i][j].backward)      

        self.cmd += "}"
        print("cmd: ", self.cmd)

    def getCmds(self):
        return self.cmd


if __name__ == '__main__':
    testMaze = Maze('./data/testmaze.csv')
