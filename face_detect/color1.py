#importing modules

import cv2   
import numpy as np
import os
import time

#capturing video through webcam
cap=cv2.VideoCapture(0)

import serial
data = serial.Serial(
    "COM3",
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesixe=serial.EIGHTBITS,
    )
timeout=1

while True:        

        _, image_frame = cap.read()
##        image_frame = frame.array
            
        #converting frame(img i.e BGR) to HSV (hue-saturation-value)

        hsv=cv2.cvtColor(image_frame,cv2.COLOR_BGR2HSV)
        
        #definig the range of red color
        red_lower=np.array([136,87,111],np.uint8)
        red_upper=np.array([180,255,255],np.uint8)

        #defining the Range of Green color
        green_lower=np.array([45,100,50],np.uint8)
        green_upper=np.array([75,255,255],np.uint8)

        #defining the Range of yellow color
        yellow_lower=np.array([22,60,200],np.uint8)
        yellow_upper=np.array([60,255,255],np.uint8)

        #defining the Range of blue color
        blue_lower=np.array([110,50,50],np.uint8)
        blue_upper=np.array([130,255,255],np.uint8)

        #finding the range of red,blue and yellow color in the image
        red=cv2.inRange(hsv, red_lower, red_upper)
        blue=cv2.inRange(hsv,blue_lower,blue_upper)
        green=cv2.inRange(hsv,green_lower,green_upper)
        yellow=cv2.inRange(hsv,yellow_lower,yellow_upper)

        #Morphological transformation, Dilation  	
        kernal = np.ones((5 ,5), "uint8")

        red=cv2.dilate(red, kernal)
        res=cv2.bitwise_and(image_frame, image_frame, mask = red)

        blue=cv2.dilate(blue,kernal)
        res1=cv2.bitwise_and(image_frame, image_frame, mask = blue)

        green=cv2.dilate(green,kernal)
        res2=cv2.bitwise_and(image_frame, image_frame, mask = green)  

        yellow=cv2.dilate(yellow,kernal)
        res3=cv2.bitwise_and(image_frame, image_frame, mask = yellow)    


        #Tracking the Red Color
        (_,contours,hierarchy)=cv2.findContours(red,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

        for pic, contour in enumerate(contours):
                area = cv2.contourArea(contour)
                if(area>800):
                        
                        x,y,w,h = cv2.boundingRect(contour)	
                        image_frame = cv2.rectangle(image_frame,(x,y),(x+w,y+h),(0,0,255),2)
                        cv2.putText(image_frame,"RED color",(x,y),cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0,0,255))
                        print ('change to red')
                        data.write(str.encode('R'))
                        time.sleep(1)
                        
        #Tracking the Blue Color
        (_,contours,hierarchy)=cv2.findContours(blue,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
        for pic, contour in enumerate(contours):
                area = cv2.contourArea(contour)
                if(area>800):
                        x,y,w,h = cv2.boundingRect(contour)	
                        image_frame = cv2.rectangle(image_frame,(x,y),(x+w,y+h),(255,0,0),2)
                        cv2.putText(image_frame,"BLUE color",(x,y),cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255,0,0))
                        print ('change to BLUE')
                        data.write(str.encode('B'))
                        time.sleep(1)


        #Tracking the green Color
        (_,contours,hierarchy)=cv2.findContours(green,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
        for pic, contour in enumerate(contours):
                area = cv2.contourArea(contour)
                if(area>800):
                        x,y,w,h = cv2.boundingRect(contour)	
                        image_frame = cv2.rectangle(image_frame,(x,y),(x+w,y+h),(0,255,0),2)
                        cv2.putText(image_frame,"green  color",(x,y),cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0,255,0))
                        print ('change to GREEN')
                        data.write(str.encode('G'))
                        time.sleep(1)

        cv2.imshow("Color Tracking",image_frame)
        if cv2.waitKey(10) & 0xFF == ord('q'):
##                cap.release()
                cv2.destroyAllWindows()
                break  
          

    

