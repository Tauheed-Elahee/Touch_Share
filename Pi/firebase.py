# Lab 3 – Pyrebase example code 
import pyrebase 
import random 
import time 
import datetime
import random

# Config will contain the information needed to connect to your firebase 
#   The API KEY and Project ID are found in your project settings 
#   The DB URL can be found under the Realtime Database tab 


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


# get time stamp 
ts = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

sensorData = ""

for i in range(4):
    for j in range(4):
        sensorData = sensorData + "({}, {}, {})".format(i, j, random.randint(0, 255))

key=1
# When writing to your DB each child is a JSON key:value pair 
db.child(dataset).child(ts).set(sensorData) 


# Next, we will retrieve the data we wrote to the DB 
# This code will read all sensor data as a Python dictionary, 
# convert it to a list, extract the final entry, and print its  
# key and value pair 

mySensorData = db.child(username).child(dataset).get() 

#print("Parent Key:{}".format(mySensorData.key())) 
#print("Parent Value: {}".format(mySensorData.val()))   

# Returns the dictionary as a list 
mySensorData_list = mySensorData.each() 

# Takes the last element of the list 
#lastDataPoint = mySensorData_list[-1] 
#print ("three most recent measurements: \n")
#print ("recorded at {}: {}".format(mySensorData_list[-2].key(), mySensorData_list[-2].val()))
#print ("recorded at {}: {}".format(mySensorData_list[-3].key(), mySensorData_list[-3].val()))
#print ("recorded at {}: {}".format(mySensorData_list[-4].key(), mySensorData_list[-4].val()))
 
#print("Child Key: {}".format(lastDataPoint.key())) 
#print("Child Value: {}\n".format(lastDataPoint.val())) 
