import pygame
import serial
import socket
from time import sleep

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

    maxCounter = 120000#1000000
    counter = [0] * 10

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
                    self.original[i][j] = self.value[i][j]
                    if(j == 2):
                        temp = self.print_command('B',"w",9, self.restrictPWM(self.value[i][j]) ) 
                        myString.append(temp)
                    elif(j == 5):
                        temp = self.print_command('B',"w",10, self.restrictPWM(self.value[i][j]) )
                        myString.append(temp)
                    elif(j == 14):
                        #temp = self.print_command('B',"?",00, 0 )
                        myString.append('?')
                
                if(self.value[0][8] == 1):
                    if(self.counter[0] < self.maxCounter):
                        self.counter[0] = self.counter[0]+1
                    elif(self.counter[0] >= self.maxCounter):
                        temp = self.print_command('B',"T",00, 10 )
                        myString.append(temp)
                        self.counter[0] = 0
                if(self.value[0][7] == 1):
                    if(self.counter[1] < self.maxCounter):
                        self.counter[1] = self.counter[1]+1
                    elif(self.counter[1] >= self.maxCounter):
                        temp = self.print_command('B',"t",00, 10 )
                        myString.append(temp)
                        self.counter[1] = 0
                        

                    #print(j)
                    #print(self.value[i][j] )
        return myString

SOCKET = True

if SOCKET:
    s = setupServer()
    conn = setupConnection()

xboxController = controller("A")
xboxController.getValues()

while True:
    try:
        myCommand = xboxController.getValues()
        for i in range(len(myCommand)):
            if SOCKET:
                send_data(conn,myCommand[i])
                sleep(0.01)
            print(myCommand[i] )
    except KeyboardInterrupt:
        if SOCKET:
            conn.close()
        quit()
