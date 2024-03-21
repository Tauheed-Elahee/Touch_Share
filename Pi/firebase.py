# code for communicating position from one touch share to the other 

import pyrebase 
import time 
import datetime
import random
import serial 

mode = "t" # can be receive(r) or transmit ('t')

# Config will contain the information needed to connect to the firebase

config = { 
  "apiKey": "AIzaSyCoJ6WI4UIXVkrs3CrLGj7LE-7daex69kw", 
  "authDomain": "touchshare-5b3f2.firebaseapp.com", 
  "databaseURL": "https://touchshare-5b3f2-default-rtdb.firebaseio.com/", 
  "storageBucket": "touchshare-5b3f2.appspot.com" 
} 

# Connect using your configuration 
firebase = pyrebase.initialize_app(config) 
db = firebase.database() 
dataset = "touchshare1" 
username = "arsalan" 

# recieved data settings
rec_data = [[0,0], [0,0]]
COM_PORT = "/dev/ttyACM0"
BAUD_RATE = 9600

# start the serial port 
arduino = serial.Serial(COM_PORT, BAUD_RATE)


# message to be sent to the arduino
last_msg_to_arduino = ""

# for for indexing firebase
key = 0

while(True):
    
    
    
    if(mode == 'r'):
        # get the data from firebase 
        mySensorData = db.child(dataset).get() 

        # convert data into a dictionary 
        mySensorData_dict = mySensorData.val() 

        # get time that the sensor data was taken 
        time_stamp = list(mySensorData_dict.keys())[-1]

        # get the most recent data for the nodes
        all_data = mySensorData_dict[time_stamp]

        if(last_msg_to_arduino != all_data):
            # send the data out of the serial port 
<<<<<<< HEAD
            arduino.write(all_data.encode())
=======
            ser.write(bytes("500", 'utf-8'))
>>>>>>> 87c56ef (Change encoding python code)

            print("data sent to arduino: {}".format(all_data))

            last_msg_to_arduino = all_data

        else:
            print("nothing new to send")
        



    ## ================== ##
    ## WRITE TO FIREBASE  ## 
    ## ================== ##

    elif(mode == 't'):
        
        # flush the input buffer
        #arduino.reset_input_buffer()

        # Read a line of text from the serial port
        line = arduino.readline()

        try:

            # Check if the line is not empty
            if line:

                line = line.decode().strip()

                print("Received:", line)  # Print the received line

                # get time stamp
                ts = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

                # upload to firebase 
                db.child(dataset).child(key).set(line) 

                key = key + 1

                
        except UnicodeDecodeError:
            print("error decoding input. Skipping")
            
        

