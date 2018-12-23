import socket
import serial

host = '192.168.1.121'
port = 5560
mySerial = serial.Serial(
    port='/dev/ttyAMA0',
    baudrate=9600
    )
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port) )

while True:
    #command = input("Enter your command: ")
    #if command == 'EXIT':
        #send EXIT reques to other end
    #    s.send(str.encode(command) )
    #    break
    #elif command == 'KILL':
        #send KILL commnad
    #    s.send(str.encode(command) )
    #s.send(str.encode(command) )
    try:
        reply = s.recv(1024)
        reply = reply.decode('utf-8')
        mySerial.write(str.encode(reply) )
        print(reply)
    except KeyboardInterrupt:
        s.close()

s.close()
