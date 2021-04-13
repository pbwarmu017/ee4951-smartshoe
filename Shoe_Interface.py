import PySimpleGUI as sg
import pandas as pd

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
            df_list = df_list + [df,] #Add to list of data frames

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

            uploaded_files = uploaded_files + " \n " + str(Date) + " \t " + str(Description)
            win1['P'].update(uploaded_files)


        

win1.close()
if win2_active:
    win2.close()

if win3_active:
    win3.close()

