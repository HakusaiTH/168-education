from mtranslate import translate
import openai
import requests
from playsound import playsound
import wave, struct
from pydub import AudioSegment
from pydub.playback import play
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import cv2
import numpy as np
from datetime import datetime
from multiprocessing import Process
import speech_recognition as sr

from tkinter import *
from tkinter.scrolledtext import ScrolledText
import speech_recognition as sr
import threading

import os
from dotenv import load_dotenv

load_dotenv()

#Open ai
#openai.api_key = "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"
openai.api_key = os.getenv("OPENAI_API_KEY")
model_engine = "text-davinci-003"

#tem
'''
tem_api_key = "0bddcc3609d450dc7d5264d45b10ab09"
city = "ubon ratchathani"
url = f'https://api.openweathermap.org/data/2.5/weather?q={city}&appid={tem_api_key}'
respon = requests.get(url).json()
des = respon['weather'][0]['description']
tem = respon['main']['temp'] - 273.15
dt_string = datetime.now().strftime("%d/%m/%Y %H:%M:%S")
tem_result = f'%.2f°C / {des} | {dt_string}' %(tem)
'''

#gui
root = Tk()

root.title("พี่หมอ")
image = PhotoImage(file="D:/168/img/n.png")

label = Label(root, image=image)

text1 = ScrolledText(root, width=40, height=10, font=("Helvetica", 12),
                     bg="white", insertbackground="black", wrap="word")

vsb1 = Scrollbar(root, orient="vertical", command=text1.yview)
text1.configure(yscrollcommand=vsb1.set)

label.pack(side="left", padx=5, pady=5)
text1.pack(side="top", fill="both", expand=True, padx=5, pady=5)
vsb1.pack(side="right", fill="y")

'''
# Create an Entry widget for the prompt input
entry = Entry(root, width=40, font=("Helvetica", 12))
entry.pack(side="bottom", padx=5, pady=5)
'''

def update_image(img):
    image.configure(file=img)

def play_sound(sound_file): 
    threading.Thread(target=play, args=(sound_file,)).start()

def start_recording():
    r = sr.Recognizer()
    with sr.Microphone() as source:
        audio = r.listen(source)
    try:
        text = r.recognize_google(audio, language="th-TH")
        update_text(text)
    except:
        print("not recognize")

button = Button(root, text="Submit", command=start_recording)
button.pack(side="bottom", padx=5, pady=5)

def update_text(user_input):
        
        prompt = translate(user_input, 'en')

        completion = openai.Completion.create(
            engine=model_engine,
            prompt=prompt,
            max_tokens=1024,
            n=1,
            stop=None,
            temperature=0.5,
        )

        response = completion.choices[0].text
        response_output = translate(response , 'th')

        #vaja 
        url_vaja = 'https://api.aiforthai.in.th/vaja'
        
        headers_vaja = {'Apikey':'If66yNxYjCF1T5XtBgQ3k9VczUbHJn51','Content-Type' : 'application/x-www-form-urlencoded'}

        params_vaja = {'text':response_output,'mode':'st'}
        
        response_vaja = requests.get(url_vaja, params=params_vaja, headers=headers_vaja).json()

        result = response_vaja["output"]["audio"]["result"]
        numChanels = response_vaja["output"]["audio"]["numChannels"]
        validBits = response_vaja["output"]["audio"]["validBits"]
        sizeSample = response_vaja["output"]["audio"]["sizeSample"]
        sampleRate = response_vaja["output"]["audio"]["sampleRate"]
        
        obj = wave.open('sound.wav','wb') 
        obj.setparams((1, int(validBits/8), sampleRate, 0, 'NONE', 'not compressed'))
        for i in range(sizeSample):
            value = int(result[i])
            data = struct.pack('<h', value)  
            obj.writeframesraw(data)
        obj.close()

        sound = AudioSegment.from_wav('sound.wav')

        #sen
        url_sen = "https://api.aiforthai.in.th/ssense" 
        params_sen = {'text':response_output}
        
        headers_sen = {
            'Apikey': "If66yNxYjCF1T5XtBgQ3k9VczUbHJn51"
        }
        response_sen = requests.get(url_sen, headers=headers_sen, params=params_sen).json()
        polarity_score = response_sen['sentiment']['polarity']

        if polarity_score == 'nagative' :
            update_image("D:/168/img/s.png")
        elif polarity_score == 'positive' :
            update_image("D:/168/img/h.png")
        else :
            polarity_score = 'neutral'
            update_image("D:/168/img/n.png")

        text1.insert(END,f'user: {user_input} \n'
                     f'bot: {response_output} \n'
                     )
        text1.see(END)   
        play_sound(sound) 

t = threading.Thread(target=update_text)
t.start()

root.mainloop()