import PySimpleGUI as sg
import pandas as pd
import serial
import xlsxwriter
import time

def CreateGreen(data):
    G=[]
    i = 0
    length = len(data)
    while i<length:
        temp = ((data[1+i]%128)*8) + int(data[i+0]/32) #Front 10
        G = G + [temp,]
        temp = ((data[4+i]%32)*32) + ((int(data[7+i]/4))%32) #5-5 split
        G = G + [temp,]
        temp = ((data[11+i]%4)*256) + data[10+i] #Back 10
        G = G + [temp,]
        i = i+16

    return G

def CreateWhite(data):
    W = []
    i = 0
    length = len(data)
    while i<length:
        temp = ((data[0+i]%32)*32) + ((int(data[3+i]/4))%32) #5-5 split
        W = W + [temp,]
        temp = ((data[7+i]%4)*256) + data[6+i] #Back 10
        W = W + [temp,]
        temp = ((data[13+i]%128)*8) + int(data[i+12]/32) #Front 10
        W = W + [temp,]
        i = i+16

    return W

def CreateYellow(data):
    Y = []
    i = 0
    length = len(data)
    while i<length:
        temp = ((data[3+i]%4)*256) + data[2+i] #Back 10
        Y = Y + [temp,]
        temp = ((data[9+i]%128)*8) + int(data[i+8]/32) #Front 10
        Y = Y + [temp,]
        temp = ((data[0+i]%32)*32) + ((int(data[3+i]/4))%32) #5-5 split
        Y = Y + [temp,]
        i = i+16

    return Y

def CreateRed(data):
    R = []
    i = 0
    length = len(data)
    while i<length:
        temp = ((data[5+i]%128)*8) + int(data[i+4]/32) #Front 10
        R = R + [temp,]
        temp = ((data[8+i]%32)*32) + ((int(data[11+i]/4))%32) #5-5 split
        R = R + [temp,]
        temp = ((data[15+i]%4)*256) + data[14+i] #Back 10
        R = R + [temp,]
        i = i+16

    return R

def Import_Data():
    ser.write(b'k')
    s= ser.read(32) #First read may have errors so throw it away
    time.sleep(0.002)
    ser.write(b'k')

    data = b''

    while(1):
        time.sleep(0.002)
        s = ser.read(32)

        if (s == b'Stop!\x00' or s == b''):
            ser.close()
            break

        data = data + s

        ser.write(b'c')

    Green = CreateGreen(data)
    White = CreateWhite(data)
    Yellow = CreateYellow(data)
    Red = CreateRed(data)

    Total = [Green, White, Yellow, Red]

    return Total

def Save_Data(Date, Description):
    text = sg.popup_get_file('Enter File Save Location', save_as=True, file_types=(('Excel File (.xslx)','.xlsx'),))
    workbook = xlsxwriter.Workbook(text)
    worksheet = workbook.add_worksheet('Data')

    worksheet.write(0,0,'Green')
    worksheet.write(0,1,'White')
    worksheet.write(0,2,'Yellow')
    worksheet.write(0,3,'Red')
    worksheet.write(0,4,'Description')

    i = 0
    length = len(read_data[0])
    while i<length:
        worksheet.write(i+1,0,read_data[0][i])
        i=i+1

    i = 0
    length = len(read_data[1])
    while i<length:
        worksheet.write(i+1,1,read_data[1][i])
        i=i+1

    i = 0
    length = len(read_data[2])
    while i<length:
        worksheet.write(i+1,2,read_data[2][i])
        i=i+1

    i = 0
    length = len(read_data[3])
    while i<length:
        worksheet.write(i+1,3,read_data[3][i])
        i=i+1
    
    worksheet.write(1,4,Date)
    worksheet.write(2,4,Description)

    workbook.close()

global ser
global read_data

sg.theme('DarkAmber')

frame_layout = [
    [sg.T('Upload all run data desired, then hit run analysis to analyze the run data analysis', font=("Helvetica", 12), text_color = 'white')]
]

df_locations = [] #list of files that have already been used, so no files are uploaded twice
df_list = [] #list of data frames

uploaded_files = "" #Used to display files that have been uploaded

layout = [
    [sg.Frame('Instructions', frame_layout, size = (80, 3))],
    [sg.T('Uploaded Runs', font=("Helvetica", 25), size =(25, 1))],
    [sg.T(uploaded_files, key = 'P', size = (100, 20), text_color = "black", background_color = "grey")],
    [sg.Button('Upload Past Data', size = (33, 5), key = 'U'), sg.Button('Import New Run Data', size = (33, 5), key='N'), sg.Button('Run Data Analysis', size = (33, 5), key = 'R')]
]

win1 = sg.Window('Main', layout) #Create Main Window

win2_active = False #Window 2 is not open
win3_active = False #Window 3 is not open

while (True):
    ev1, vals1 = win1.read(timeout = 10)

    if ev1 == sg.WIN_CLOSED:
        break

    if ev1 == 'U': #Upload new file
        location = sg.popup_get_file('Please enter a file name')

        if location == None:
            continue #Cancel button was hit, leave this area

        new_location = True

        i = 0
        while i<len(df_locations):
            if df_locations[i] == location:
                new_location = False #File has alread been uploaded
                break
            i = i+1
        
        
        if new_location:
            df_locations = df_locations + [location,] #Add to list of locations used
            df = pd.read_excel(location) #Read the dataframe from excel (Subject to Change)
            df_list = df_list + [[df['Green'].values.tolist(), df['White'].values.tolist(), df['Yellow'].values.tolist(), df['Red'].values.tolist(), [df.at[0, 'Description'], df.at[1, 'Description']]],]#Add to list of data frames

            uploaded_files = uploaded_files + " \n " + str(df.at[0, 'Description']) + " \t " + df.at[1, 'Description']
            win1['P'].update(uploaded_files) #Update main window
    
    if not win2_active and ev1 == 'R': #Open up data analysis window
        layout2 = [
            [sg.T('Data Analysis results will go here', size = (70, 30))],
            [sg.Button('Maybe Some Graphing', size = (35, 5)), sg.Button('Maybe Some Other Graphing', size = (35, 5))]
        ]
        win2 = sg.Window('Data Analysis', layout2)
        win2_active = True

    if win2_active: #Data Analysis here
        ev2, vals2 = win2.read(timeout=10)
        if ev2 == sg.WIN_CLOSED:
            win2_active  = False
            win2.close()

    if ev1 == 'N' and not win3_active: #Upload new run
        port = sg.popup_get_text('Enter name of the COM port used', 'COM Port')

        try:
            ser = serial.Serial(port, 19200, timeout=1, bytesize=8)
        except:
            sg.popup('Could not connect to the port specified')
            continue
        
        read_data = Import_Data()
        ser.close()

        layout3 = [
            [sg.T('Enter Run Date and Description')],
            [sg.Input(key='Date', size=(20,1)), sg.CalendarButton('Date', target='Date')],
            [sg.Input('Description', key = 'Description')],
            [sg.Button('Okay', key = 'Okay')]
        ]
        win3 = sg.Window('Date and Description', layout3)
        win3_active = True
    
    if win3_active:
        ev3, vals3 = win3.read(timeout=10)
        if ev3 == sg.WIN_CLOSED:
            win3_active  = False
            win3.close()
            
        
        if ev3 == 'Okay':
            Date = vals3['Date']
            Description = vals3['Description']
            win3_active = False
            win3.close()

            read_data = read_data + [[Date, Description],]
            df_list = df_list + [read_data,]
            Save_Data(Date, Description)

            uploaded_files = uploaded_files + " \n " + str(Date) + " \t " + str(Description)
            win1['P'].update(uploaded_files)      

win1.close()
if win2_active:
    win2.close()

if win3_active:
    win3.close()
