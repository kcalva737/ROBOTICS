#Robotics
import pygame
import serial
import socket
from time import sleep
import sys  
import math
import time
reload(sys)  
sys.setdefaultencoding('utf8')

host = ''
port = 5560

def setupServer():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM )
    print("Socket create")
    try:
        s.bind((host, port))
    except socket.error as msg:
        print(msg)
    print("Socket bind complete!")
        
    return s

def setupConnection():
    s.listen(1)
    conn, address = s.accept()
    print("Connected to: "+address[0]+":"+str(address[1] ))
    
    return conn

def send_data(conn,myString):
    conn.sendall(str.encode(myString) )

#0xff ff ff
# 0000 0000-0000 0000-0000 0000
def encode(pin,value):
    #value = value + 1
    myString = ord('#')<<16
    myString |= pin<<10
    myString |= value
   
    val1 = chr( (myString & 0xff0000) >> 16)
    val2 = chr( (myString & 0x00ff00) >> 8)
    val3 = chr(myString & 0x0000ff)
    #print(bin(bytes(val3)))
    #print ord(val1)#,end=' ')  + val2 + val3))
    #print ord(val2)# ,end=' ')
    
    return val1  + val2 + val3




class controller:
    original = []
    value = []
    total_control = 0
    controller = []
    
    numaxes = []
    numbuttons = []
    numhats = []
    total =[]
    channel = "Hello"

    maxCounter = 10000#1000000
    counter = [0] * 10
    degreeValue = [0] * 10

    maxRange = 180

    Socket = False

    def __init__(self, channel ):
        pygame.init()
        pygame.joystick.init()
        self.total_control = pygame.joystick.get_count()

        
        self.channel = channel
        for j in range(self.total_control):
            controller = pygame.joystick.Joystick(j)
            self.controller.append(controller)
            self.controller[j].init()

            self.numaxes.append(controller.get_numaxes() )
            self.numbuttons.append(controller.get_numbuttons() )
            self.numhats.append(controller.get_numhats() )
            self.total.append(self.numaxes[j] + self.numbuttons[j] + 4*self.numhats[j] )#controller.get_numaxes() + controller.get_numbuttons() + 4*controller.get_numhats()
            
            self.original.append([0]*self.total[j])
            self.value.append([0]*self.total[j])
            
    def print_command(self,chan, command, pin, value):
        # "#D12-1234"
        value = int(value)
        #print(value)
        if value > 999:
            value = str(value)
        elif value > 99:
            value = "0" + str(value)
        elif value > 9:
            value = "00"+ str(value)
        else:
            value = "000"+str(value)

        if pin > 9:
            pin = str(pin)
        else:
            pin = "0" + str(pin)

        string = "#"+chan+command+pin+"-"+value
        #print(string)
        return string

    def restrictPWM(self,value):
        value = int(value/4.01 )
        return value

    def restrictDegree(self,value):
        value = int(value/5.69)
        return value
    def initValue(self):
    
        for i in range (self.total_control):
            for j  in range(self.numaxes[i] ):
                self.original[i][j] = int ((self.controller[i].get_axis(j)  + 1) * 511.6 )
            for j in range(self.numbuttons[i]):
                self.original[i][j+ self.numaxes[i] ] = self.controller[i].get_button(j)
            for j in range(self.numhats[i]):
                hat = self.controller[i].get_hat(j) 
                if(hat[0]) > 0:
                    self.original[i][j+self.numaxes[i]+self.numbuttons[i] ] =1
                elif(hat[0]) < 0:
                    self.original[i][j+self.numaxes[i]+self.numbuttons[i] + 1 ] =1
                else:
                    self.original[i][j+self.numaxes[i]+self.numbuttons[i]] = self.value[i][j+self.numaxes[i]+self.numbuttons[i] +1 ] = 0

                if(hat[1]) > 0:
                    self.original[i][j+self.numaxes[i]+self.numbuttons[i] + 2] =1
                elif(hat[1]) < 0:
                    self.origianl[i][j+self.numaxes[i]+self.numbuttons[i] + 3 ] =1
                else:
                    self.original[i][j+self.numaxes[i]+self.numbuttons[i] + 2] = self.value[i][j+self.numaxes[i]+self.numbuttons[i] +3 ] = 0

    def getValues(self):
        myString = []
        pygame.event.pump()
        for i in range (self.total_control):
            for j  in range(self.numaxes[i] ):
                self.value[i][j] = int ((self.controller[i].get_axis(j)  + 1) * 511.6 )
            for j in range(self.numbuttons[i]):
                self.value[i][j+ self.numaxes[i] ] = self.controller[i].get_button(j)
            for j in range(self.numhats[i]):
                hat = self.controller[i].get_hat(j) 
                if(hat[0]) > 0:
                    self.value[i][j+self.numaxes[i]+self.numbuttons[i] ] =1
                elif(hat[0]) < 0:
                    self.value[i][j+self.numaxes[i]+self.numbuttons[i] + 1 ] =1
                else:
                    self.value[i][j+self.numaxes[i]+self.numbuttons[i]] = self.value[i][j+self.numaxes[i]+self.numbuttons[i] +1 ] = 0

                if(hat[1]) > 0:
                    self.value[i][j+self.numaxes[i]+self.numbuttons[i] + 2] =1
                elif(hat[1]) < 0:
                    self.value[i][j+self.numaxes[i]+self.numbuttons[i] + 3 ] =1
                else:
                    self.value[i][j+self.numaxes[i]+self.numbuttons[i] + 2] = self.value[i][j+self.numaxes[i]+self.numbuttons[i] +3 ] = 0

        for i in range(self.total_control):
            for j in range(int( self.total[i] ) ):
                if(self.original[i][j] != self.value[i][j] ):
                    #control mapping:
                    #analog:
                        #left-analog:
                            #x-axis:0
                            #y-axis:1
                        #right-analog:
                            #x-axis:3
                            #y-axis:4
                        #left-trigger:
                            #vertical-axis:2
                        #right-trigger:
                            #vertical-axis:5
                    #digital:
                        #left-bumper:10
                        #right-bumper:11

                        #U-D-L-R:
                            #UP:19
                            #Down:20
                            #Left:18
                            #Right:17
                        
                        #Y-A-X-B
                            #Y:9
                            #A:6
                            #X:8
                            #B:7
                        
                        #Back-Home-Start
                            #Back:12
                            #Home:14
                            #Start:13

                        #AnalogButton
                            #Left-Axis-Button:15
                            #Right-Axis-Button:16

                    #self.original[i][j] = self.value[i][j]
                    # print "change in val: ",i," and  ",j #index of the values changing
                    #self.original[i][j] = self.value[i][j]
                    #print "change in val: ",i," and  ",j #index of the values changing
                    # if(abs(self.value[i][j] - self.original[i][j] ) < 1000 ):
                    
                    if(self.value[i][j] > self.original[i][j] ):
                        self.original[i][j] += 1 + abs(self.value[i][j] - self.original[i][j] )/10#math.sqrt(abs(self.original[i][j]-self.value[i][j])+1)
                    elif(self.value[i][j] < self.original[i][j] ):
                        self.original[i][j]-= 1+abs(self.value[i][j] - self.original[i][j] )/10 #math.sqrt(abs(self.original[i][j]-self.value[i][j])+1)
                    
                    time.sleep(0.02)
                    #print  "abs change in val: ", abs(self.value[i][j] - self.original[i][j] ),"value: ",self.original[i][j]
                    
                    # print(self.value[i][j] )#prints value of input
                    
                    # if(j == 2):#left trigger
                    #     if self.Socket:
                    #         temp = self.print_command('B',"w",9, self.restrictPWM(self.original[i][j]) ) 
                    #     else:
                    #         temp = encode(9,self.restrictPWM(self.original[i][j]) )


                        
                    #     myString.append(temp)
                    # elif(j == 5):#right trigger
                    #     if self.Socket:
                    #         temp = self.print_command('B',"w",10, self.restrictPWM(self.original[i][j]) )
                    #     else:
                    #         temp = encode(0,self.restrictPWM(self.original[i][j]) )``````````````````````````````````````````````````````````````````````````````````````````````````````````````
                    #     #print(encode(10, self.restrictPWM(self.value[i][j]) ) )
                    #     myString.append(temp)
                    # print self.original[0][5]

                    if(j==1):#left analog- xaxis
                        temp = encode(12,self.restrictDegree(self.original[i][j]) )
                        myString.append(temp)

                    elif(j==0):#left analog- yaxis
                        temp = encode(11,self.restrictDegree(self.original[i][j]) )
                        myString.append(temp)




                    elif(j == 11):
                        self.degreeValue[0] += 1
                        if(self.degreeValue[0] > self.maxRange):
                            self.degreeValue[0] = self.maxRange-1
                        # print self.degreeValue[0]
                        temp = encode(9,self.degreeValue[0] )
                        myString.append(temp)
                    elif(j == 10):
                        self.degreeValue[0] -= 1
                        if(self.degreeValue[0] < 0):
                            self.degreeValue[0] = 0
                        # print self.degreeValue[0]
                        temp = encode(9,self.degreeValue[0] )
                        myString.append(temp)
                        
                    elif(j == 5):
                        self.degreeValue[1] += 1
                        if(self.degreeValue[1] > self.maxRange):
                            self.degreeValue[1] = self.maxRange-1
                        # print self.degreeValue[1]
                        temp = encode(8,self.degreeValue[1] )
                        myString.append(temp)
                    elif(j == 2):
                        self.degreeValue[1] -= 1
                        if(self.degreeValue[1] < 0):
                            self.degreeValue[1] = 0
                        # print self.degreeValue[1]
                        temp = encode(8,self.degreeValue[1] )
                        myString.append(temp)
                    
                    elif(j == 7):
                        self.degreeValue[2] += 1
                        if(self.degreeValue[2] > self.maxRange):
                            self.degreeValue[2] = self.maxRange-1
                        # print self.degreeValue[2]
                        temp = encode(7,self.degreeValue[2] )
                        myString.append(temp)
                    elif(j == 6):
                        self.degreeValue[2] -= 1
                        if(self.degreeValue[2] < 0):
                            self.degreeValue[2] = 0
                        # print self.degreeValue[2]
                        temp = encode(7,self.degreeValue[2] )
                        myString.append(temp)

                    elif(j == 4):
                        #print self.original[0][4]
                        if(self.original[0][4] > 530):
                            self.degreeValue[3] += 1
                            if(self.degreeValue[3] > self.maxRange):
                                self.degreeValue[3] = self.maxRange -1
                            print self.degreeValue[3]
                            temp = encode(6,self.degreeValue[2] )
                            myString.append(temp)
                        if(self.original[0][4] < 490):
                            self.degreeValue[3] -= 1
                            if(self.degreeValue[3] < 0):
                                self.degreeValue[3] = 0
                            print self.degreeValue[3]
                            temp = encode(6,self.degreeValue[3] )
                            myString.append(temp)

                    elif(j == 16):
                        self.degreeValue[4] += 1
                        if(self.degreeValue[4] > self.maxRange):
                            self.degreeValue[4] = self.maxRange-1
                        print self.degreeValue[4]
                        temp = encode(5,self.degreeValue[4] )
                        myString.append(temp)
                    elif(j == 15):
                        self.degreeValue[4] -= 1
                        if(self.degreeValue[4] < 0):
                            self.degreeValue[4] = 0
                        # print self.degreeValue[4]
                        temp = encode(5,self.degreeValue[4] )
                        myString.append(temp)
                            





                    elif(j == 18):#relay switch Y
                        print self.original[i][j]
                        temp = encode(22,self.original[0][18])
                        myString.append(temp)
                    elif(j == 17):#A
                        # print self.original[0][8]
                        temp = encode(23,self.original[0][17])
                        myString.append(temp)

                    elif(j == 20):#dn
                        temp = encode(24,self.original[0][20])
                        myString.append(temp)
                    elif(j == 19):#relay switch up
                        temp = encode(25,self.original[0][19])
                        myString.append(temp)
                    elif(j == 8):#relay switch left
                        temp = encode(26,self.original[0][8])
                        myString.append(temp)
                    elif(j == 9):#right
                        temp = encode(27,self.original[0][9])
                        myString.append(temp)
                    # print(j)#prints out value of input being pressed
                    # print(self.original[i][j] )#prints value of input

                # self.counter[0] +=1
                # if(self.counter[0] > self.maxCounter):
                #     # print "counter: ", self.counter[0]
                #     self.counter[0] = 0
                #     if(self.original[0][11]):
                #         self.degreeValue[0] += 1
                #         if(self.degreeValue[0] > self.maxRange):
                #             self.degreeValue[0] = self.maxRange-1
                #         print self.degreeValue[0]
                #         temp = encode(9,self.degreeValue[0] )
                #         myString.append(temp)
                #     # elif(j == 10):
                #     elif(self.original[0][10]):
                #         self.degreeValue[0] -= 1
                #         if(self.degreeValue[0] < 0):
                #             self.degreeValue[0] = 0
                #         print self.degreeValue[0]
                #         temp = encode(9,self.degreeValue[0] )
                #         myString.append(temp)

                #     elif(self.original[0][7]):#j == 7):
                #         self.degreeValue[2] += 1
                #         if(self.degreeValue[2] > self.maxRange):
                #             self.degreeValue[2] = self.maxRange-1
                #         # print self.degreeValue[2]
                #         temp = encode(7,self.degreeValue[2] )
                #         myString.append(temp)
                #     elif(self.original[0][6]): #j == 6):
                #         self.degreeValue[2] -= 1
                #         if(self.degreeValue[2] < 0):
                #             self.degreeValue[2] = 0
                #         # print self.degreeValue[2]
                #         temp = encode(7,self.degreeValue[2] )
                #         myString.append(temp)
                    
                #     elif( self.value[0][5] > 0):#j == 5):
                #         self.degreeValue[1] += 1
                #         if(self.degreeValue[1] > self.maxRange):
                #             self.degreeValue[1] = self.maxRange-1
                #         print self.degreeValue[1]
                #         temp = encode(8,self.degreeValue[1] )
                #         myString.append(temp)
                #     elif(self.value[0][2] > 0):#j == 2):
                #         self.degreeValue[1] -= 1
                #         if(self.degreeValue[1] < 0):
                #             self.degreeValue[1] = 0
                #         print self.degreeValue[1]
                #         temp = encode(8,self.degreeValue[1] )
                #         myString.append(temp)
                
        return myString

SOCKET = False

if SOCKET:
    s = setupServer()
    conn = setupConnection()
else:
    serialPort = serial.Serial('/dev/ttyUSB0',9600)
    serialPort.close()
    serialPort.open() 
    #serialPort.write(string.encode())
    #print("test: ")

xboxController = controller("A")
# xboxController.getValues()
# for x in range(100):
xboxController.initValue()

while True:
    try:
        if SOCKET:
            myCommand = xboxController.getValues()
            for i in range(len(myCommand)):
                #if SOCKET:
                send_data(conn,myCommand[i])
                sleep(0.01)
                #print(myCommand[i] )
        else:
            myCommand = xboxController.getValues()
            for i in range(len(myCommand)):
                serialPort.write(myCommand[i])
                #print(myCommand[i])
                #print  ""
    except KeyboardInterrupt:
        if SOCKET:
            conn.close()
        quit()

