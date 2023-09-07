#!/usr/bin/env python3
import serial
import time
import numpy as np

from sendStringScript import sendString

String2Send='<150,10>'

if __name__ == '__main__':
    ser=serial.Serial("/dev/ttyACM0",115200)
    #every time the serial port is opened, the arduino program will restart, very convient!
    ser.reset_input_buffer()
    ser.reset_output_buffer() #we clear the input and output buffer at the beginning of running any program to make sure
                             #that any bits left over in the buffer dont show up

    while True: 
            #sendString('/dev/ttyACM0',115200,String2Send,0.0005)
            ser.write(String2Send.encode('utf-8'))

            #theses are 2 seprate methods to send a string from the rpi to the arduino, you can use the serial moniter on the arduino
            #side to examine what the string looks like when it arrives to the arduino. What do you notice?
            #is one of these 2 methods better than the other? which one? use the internet to try to figure out why one of these 
            #methods works better than the other (I'm not totally sure myself even thought I wrote the sendString() function to solve 
            #this problem)

            #why so I append '<' and '>' to the beginning and end of my message that I send to the arduino?


            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8')
                print(line)
                #ive just called 2 methods from the ser object, what do they do?