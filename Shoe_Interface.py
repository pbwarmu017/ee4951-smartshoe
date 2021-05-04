import PySimpleGUI as sg
import pandas as pd
import serial
import xlsxwriter
import time
import matplotlib.pyplot as plt
import numpy as np
from datetime import datetime

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

def sort_df_list():
    length = len(df_list)
    i=0
    while(i<length-1):
        if(df_list[i][4][0]>df_list[i+1][4][0]):
            temp = df_list[i]
            df_list[i] = df_list[i+1]
            df_list[i+1] = temp
            i=0
        
        else:
            i=i+1

def Get_Averages():
    amount = len(df_list)
    Average_List = []
    i = 0
    while (i<amount):
        j = 0
        Entry_Average=[]
        while(j<4):
            k=0
            length = len(df_list[i][j])
            count = 0
            average = 0
            while(k<length):
                if(df_list[i][j][k] == 1023 or df_list[i][j][k]<512):
                    k = k+1
                
                else:
                    count = count+1
                    temp = df_list[i][j][k] - average
                    temp = temp/count
                    average = average + temp
                    k = k+1
            Entry_Average.append(average)
            j = j+1
        All_Wire_Average = (Entry_Average[0] + Entry_Average[1] + Entry_Average[2] + Entry_Average[3])/4
        Entry_Average.append(All_Wire_Average)
        Average_List = Average_List + [Entry_Average]
        i = i+1
    return Average_List

def Regression(Averages):
    length = len(Averages)
    X_Avg = (length+1)/2
    Y_Avg = [0, 0, 0, 0, 0]
    i = 0
    while(i<5):
        j = 0
        while(j<length):
            temp = (Averages[j][i] - Y_Avg[i])/(j+1)
            Y_Avg[i] = Y_Avg[i] + temp
            j = j + 1
        i = i+1
    
    X_Var = 0
    Cov = [0,0,0,0,0]
    i = 0
    while(i<length):
        temp = i+1-X_Avg
        temp = temp*temp
        X_Var = X_Var + temp
        i = i+1
    
    i = 0
    while(i<5):
        j = 0
        while(j<length):
            temp = Averages[j][i] - Y_Avg[i]
            temp = temp*(j+1-X_Avg)
            Cov[i] = Cov[i] + temp
            j = j+1
        i = i+1
    
    Beta = [0,0,0,0,0]
    i=0

    while(i<5):
        Beta[i] = Cov[i]/X_Var
        i=i+1
    
    Alpha = [0,0,0,0,0]
    i = 0

    while(i<5):
        Alpha[i] = Y_Avg[i] - (Beta[i]*X_Avg)
        i = i+1
    
    R2 = [0,0,0,0,0]
    i=0

    while(i<5):
        j=0
        SRES=0
        STOT=0
        while(j<length):
            temp = Alpha[i] + (Beta[i]*(j+1))
            SRES = SRES + ((Averages[j][i]-temp)**2)
            STOT = STOT + ((Averages[j][i]-Y_Avg[i])**2)
            j= j+1
        R2[i] = 1 - (SRES/STOT)
        i=i+1

    return[X_Avg, Y_Avg, X_Var, Cov, Beta, Alpha, R2]

def Graph():
    Averages = Get_Averages()
    Reg = Regression(Averages)

    Average_Vals = []
    Green_Vals = []
    White_Vals = []
    Yellow_Vals = []
    Red_Vals = []
    t_array = []
    length = len(Averages)
    i = 0

    while(i<length):
        Green_Vals.append(Averages[i][0])
        White_Vals.append(Averages[i][1])
        Yellow_Vals.append(Averages[i][2])
        Red_Vals.append(Averages[i][3])
        Average_Vals.append(Averages[i][4])
        t_array.append(i+1)
        i = i + 1
    
    Green_Arr = np.array(Green_Vals)
    White_Arr = np.array(White_Vals)
    Yellow_Arr = np.array(Yellow_Vals)
    Red_Arr = np.array(Red_Vals)
    Average_Arr = np.array(Average_Vals)
    t_real = np.array(t_array)

    t = np.arange(0., length+1, .1)

    plt.figure()
    plt.subplot(211)
    plt.plot(t_real, Average_Arr, 'bo', t, f(Reg, 4, t), 'b--')
    plt.title('Average of All Sensors')
    plt.grid(True)
    
    plt.subplot(212)
    plt.plot(t_real, Green_Arr, 'go', t, f(Reg, 0, t), 'g--', t_real, White_Arr, 'bo', t, f(Reg, 1, t), 'b--', t_real, Yellow_Arr, 'yo', t, f(Reg, 2, t), 'y--', t_real, Red_Arr, 'ro', t, f(Reg, 3, t), 'r--')
    plt.grid(True)
    plt.title('Average of Each Sensor')
    plt.subplots_adjust(top=0.92, bottom=0.08, left=0.10, right=0.95, hspace=0.25,wspace=0.35)
    plt.show()

def f(Reg, i, t):
    return (Reg[5][i] + (Reg[4][i]*t))

global ser
global read_data

sg.theme('DarkAmber')

frame_layout = [
    [sg.T('Upload all run data desired, then hit run data analysis to analyze the run data', font=("Helvetica", 12), text_color = 'white')]
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
win4_active = False #Window 4 is not open

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
            if isinstance(df.at[0, 'Description'], str):
                df_list = df_list + [[df['Green'].values.tolist(), df['White'].values.tolist(), df['Yellow'].values.tolist(), df['Red'].values.tolist(), [datetime.strptime(df.at[0, 'Description'], '%Y-%m-%d %H:%M:%S'), df.at[1, 'Description']]],]#Add to list of data frames

            else:
                df_list = df_list + [[df['Green'].values.tolist(), df['White'].values.tolist(), df['Yellow'].values.tolist(), df['Red'].values.tolist(), [df.at[0, 'Description'], df.at[1, 'Description']]],]#Add to list of data frames
            
            uploaded_files = uploaded_files + " \n " + str(df.at[0, 'Description']) + " \t " + df.at[1, 'Description']
            win1['P'].update(uploaded_files) #Update main window
    
    if not win2_active and ev1 == 'R': #Open up data analysis window
        Headings = ['Run Number', 'Green', 'White', 'Yellow', 'Red', 'Total']
        header =  [[sg.Text(h, size=(14,1), text_color = "black", background_color = "white") for h in Headings]]

        sort_df_list()
        Average_List = Get_Averages()

        results = []
        length = len(Average_List)
        i = 0

        while(i<length):
            name = 'Run ' + str(i+1) + '\n' + str(df_list[i][4][0])
            temp = [sg.Text(name, size = (14,2), text_color = "black", background_color = "white")]
            j = 0
            while(j<5):
                temp.append(sg.Text(str(round(Average_List[i][j],3)), size = (14,2), text_color = "black", background_color = "grey"))
                j = j+1
            
            i = i+1
            results = results + [temp,]
        
        Reg = Regression(Average_List)
        temp = [sg.Text('Average Run', size = (14,1), text_color = "black", background_color = "white")]
        j=0
        while(j<5):
            temp.append(sg.Text(str(round(Reg[1][j],3)), size = (14,1), text_color = "black", background_color = "grey"))
            j = j+1
        
        results = results + [temp,]

        Title = [[sg.Text('The table below shows the average data reads from each wire from each run')],]

        frame1_layout2 = Title + header + results

        Headings = ['Run Number', 'Green', 'White', 'Yellow', 'Red', 'Total']
        header =  [[sg.Text(h, size=(14,1), text_color = "black", background_color = "white") for h in Headings]]

        reg_res = []

        temp = [sg.Text('Slope', size = (14,1), text_color = "black", background_color = "white")] 
        j=0
        while(j<5):
            temp.append(sg.Text(str(round(Reg[4][j],3)), size = (14,1), text_color = "black", background_color = "grey"))
            j = j+1
        
        reg_res = reg_res + [temp,]

        temp = [sg.Text('Y-Intercept', size = (14,1), text_color = "black", background_color = "white")] 
        j=0
        while(j<5):
            temp.append(sg.Text(str(round(Reg[5][j],3)), size = (14,1), text_color = "black", background_color = "grey"))
            j = j+1
        
        reg_res = reg_res + [temp,]

        temp = [sg.Text('Correlation \n Coef.', size = (14,2), text_color = "black", background_color = "white")] 
        j=0
        while(j<5):
            temp.append(sg.Text(str(round(Reg[6][j],3)), size = (14,2), text_color = "black", background_color = "grey"))
            j = j+1
        
        reg_res = reg_res + [temp,]

        Title = [[sg.Text('The table below shows results from linear regression.')],]

        frame2_layout2 = Title + header + reg_res

        Interpretation = 'The data above reflects the amount of flex each sensor experienced. '\
        'The Data Averages section shows the average amount of flex on each sensor on each run '\
        'along with averages from every sensor. The Regression Results section shows the values '\
        'obtained from running linear regression the sensor average with respect to the run '\
        'number. Below is the option to graph the sensor averages from each run to see the change. ' \
        'There is also an option to view a diagram to see where each sensor is on the shoe. For '\
        'reference, a higher flex value means there was more flex in the shoe, which implies more '\
        'wear on the shoe.'
        
        layout2 =[
            [sg.Frame('Data Averages', frame1_layout2)],
            [sg.Frame('Regression Results', frame2_layout2)],
            [sg.T(Interpretation, size = (90,5), text_color = 'white')],
            [sg.Button('Graph Sensor Averages', size = (45, 3), key = 'Graph'), sg.Button('Shoe Sensor Diagram', size = (45, 3), key = 'SSD')]
            ]
        
        win2 = sg.Window('Data Analysis', layout2)
        win2_active = True

    if win2_active: #Data Analysis here
        ev2, vals2 = win2.read(timeout=10)
        if ev2 == 'Graph':
            Graph()
        
        if ev2 == 'SSD' and not win4_active:
            layout4 = [
                [sg.Image(r'C:\Users\enter\Desktop\Python\Shoe_Diagram.png')],
            ]

            win4 = sg.Window('Shoe Sensor Diagram', layout4)
            win4_active = True


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
            date_time_obj = datetime.strptime(Date, '%Y-%m-%d %H:%M:%S')
            Description = vals3['Description']
            win3_active = False
            win3.close()

            read_data = read_data + [[date_time_obj, Description],]
            df_list = df_list + [read_data,]
            Save_Data(Date, Description)

            uploaded_files = uploaded_files + " \n " + str(Date) + " \t " + str(Description)
            win1['P'].update(uploaded_files)

    if win4_active:
        ev4, vals4 = win4.read(timeout=10)
        if ev4 == sg.WIN_CLOSED:
            win4_active = False
            win4.close()      

win1.close()
if win2_active:
    win2.close()

if win3_active:
    win3.close()

if win4_active:
    win4.close()