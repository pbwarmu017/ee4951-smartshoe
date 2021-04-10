import serial
import xlsxwriter

Green=[]
White=[]
Yellow=[]
Red=[]

def AddGreen(data, G):
    i = 0
    while i<17:
        temp = ((data[1+i]%128)*8) + int(data[i+0]/32) #Front 10
        G = G + [temp,]
        temp = ((data[4+i]%32)*32) + ((int(data[7+i]/4))%32) #5-5 split
        G = G + [temp,]
        temp = ((data[11+i]%4)*256) + data[10+i] #Back 10
        G = G + [temp,]
        i = i+16
    
    return G

def AddWhite(data, W):
    i = 0
    while i<17:
        temp = ((data[0+i]%32)*32) + ((int(data[3+i]/4))%32) #5-5 split
        W = W + [temp,]
        temp = ((data[7+i]%4)*256) + data[6+i] #Back 10
        W = W + [temp,]
        temp = ((data[13+i]%128)*8) + int(data[i+12]/32) #Front 10
        W = W + [temp,]
        i = i+16
    
    return W

def AddYellow(data, Y):
    i = 0
    while i<17:
        temp = ((data[3+i]%4)*256) + data[2+i] #Back 10
        Y = Y + [temp,]
        temp = ((data[9+i]%128)*8) + int(data[i+8]/32) #Front 10
        Y = Y + [temp,]
        temp = ((data[0+i]%32)*32) + ((int(data[3+i]/4))%32) #5-5 split
        Y = Y + [temp,]
        i = i+16

    return Y

def AddRed(data, R):
    i = 0
    while i<17:
        temp = ((data[5+i]%128)*8) + int(data[i+4]/32) #Front 10
        R = R + [temp,]
        temp = ((data[8+i]%32)*32) + ((int(data[11+i]/4))%32) #5-5 split
        R = R + [temp,]
        temp = ((data[15+i]%4)*256) + data[14+i] #Back 10
        R = R + [temp,]
        i = i+16
    
    return R

ser = serial.Serial('COM3', 19200, timeout=1, bytesize=8) #Update with the COM spot it's connected in for you

ser.write(b'k')

while(1):
    
    s = ser.read(32)

    if (s == b'Stop!\x00'):
        ser.close()
        break

    Green = Green + AddGreen(s, Green)
    White = White + AddWhite(s, White)
    Yellow = Yellow + AddYellow(s, Yellow)
    Red = Red + AddRed(s, Red)

print(Green)
print(White)
print(Yellow)
print(Red)

workbook = xlsxwriter.Workbook('Wire_Data.xlsx')
worksheet = workbook.add_worksheet('Data')

worksheet.write(0,0,'Green')
worksheet.write(0,1,'White')
worksheet.write(0,2,'Yellow')
worksheet.write(0,3,'Red')

i = 0
length = len(Green)
while i<length:
    worksheet.write(i+1,0,Green[i])
    i=i+1

i = 0
length = len(White)
while i<length:
    worksheet.write(i+1,1,White[i])
    i=i+1

i = 0
length = len(Yellow)
while i<length:
    worksheet.write(i+1,2,Yellow[i])
    i=i+1

i = 0
length = len(Red)
while i<length:
    worksheet.write(i+1,3,Red[i])
    i=i+1

workbook.close()