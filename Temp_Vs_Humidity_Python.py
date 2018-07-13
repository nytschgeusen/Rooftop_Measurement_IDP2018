import serial # import Serial Library
import numpy as np  # Import numpy
import matplotlib.pyplot as plt #import matplotlib library
from drawnow import *


t = []
h = []

arduinoData = serial.Serial('COM5',9600) #Creating our serial object named arduinoData 
plt.ion() #Tell matplotlib you want interactive mode to plot live data
cnt=0

def makeFig(): #Create a function that makes our desired plot
    plt.ylim(15,50)                                 #Set y min and max values
    plt.title('Temperature and Humidity')      #Plot the title
    plt.grid(True)                                  #Turn the grid on
    plt.ylabel('Temperature C')                            #Set ylabels
    plt.plot(t, 'ro-', label='Degrees C')       #plot the temperature
    plt.legend(loc='upper left')                    #plot the legend
    plt2=plt.twinx()                                #Create a second y axis
    plt.ylim(10,70)                           #Set limits of second y axis- adjust to readings you are getting
    plt2.plot(h, 'b^-', label='Humidity (h)') #plot Humidity data
    plt2.set_ylabel('Relative Humidity (h)')                    #label second y axis
    plt2.ticklabel_format(useOffset=False)           #Force matplotlib to NOT autoscale y axis
    plt2.legend(loc='upper right')                  #plot the legend
    

while True: # While loop that loops forever
    while (arduinoData.inWaiting()==0): #Wait here until there is data
        pass #do nothing
    arduinoString = arduinoData.readline() #read the line of text from the serial port
    dataArray = arduinoString.split(',')   #Split it into an array called dataArray
    temp = int( dataArray[0])            #Convert first element to floating number and put in temp
    hum = int( dataArray[1])            #Convert second element to floating number and put in H
    t.append(temp)                     #Build our temperature array by appending temp readings
    h.append(hum)                     #Building our Humidity array by appending P readings
    drawnow(makeFig)                       #Call drawnow to update our live graph
    plt.pause(.000001)                     #Pause Briefly. Important to keep drawnow from crashing
    cnt=cnt+1
    if(cnt>50):                            #If you have 50 or more points, delete the first one from the array
        t.pop(0)                       #This allows us to just see the last 50 data points
        h.pop(0)
        
        
       

