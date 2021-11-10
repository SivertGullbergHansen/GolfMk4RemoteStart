<p align="center">
<img src="https://raw.githubusercontent.com/SivertGullbergHansen/GolfMk4RemoteStart/main/Media/logo.png" style="max-width: 100%;" width="25%"><br/>

<img src="https://raw.githubusercontent.com/SivertGullbergHansen/GolfMk4RemoteStart/main/Media/title.png" style="max-width: 100%;" width="60%"><br/>

![GitHub issues](https://img.shields.io/github/issues/sivertgullberghansen/golfmk4remotestart) [![GitHub forks](https://img.shields.io/github/forks/SivertGullbergHansen/GolfMk4RemoteStart)](https://github.com/SivertGullbergHansen/GolfMk4RemoteStart/network) [![GitHub stars](https://img.shields.io/github/stars/SivertGullbergHansen/GolfMk4RemoteStart)](https://github.com/SivertGullbergHansen/GolfMk4RemoteStart/stargazers) [![GitHub license](https://img.shields.io/github/license/SivertGullbergHansen/GolfMk4RemoteStart)](https://github.com/SivertGullbergHansen/GolfMk4RemoteStart)</p>

## Requirements
- :computer: An arduino
- :floppy_disk: A sim-card module you can read a sim-card with
- :iphone: A phone that can send messages
- :calling: A sim-card that can receive messages
- :gear: A neutral-switch in your car

## Optional
- :printer: A 3D-printer to print our case for the arduino and a relay-box

## Description
This Arduino sketch is specifically made and tested for a Volkswagen Golf MK4 GTI, but it will most likely work on older cars as long as the immobilizer is removed/defeated.

You will need to have a neutral switch in your car if it is a manual car, you can easily connect this switch to a arduino pin. 

Our Arduino Sketch requires a SIM card-reader that you can send SMS messages to. We wrote the sketch specifically for the **sim800l gsm module**. 
We recommend using a prepaid card for your sim, as it is free to receive messages. 
