<p align="center">
<img src="https://raw.githubusercontent.com/SivertGullbergHansen/GolfMk4RemoteStart/main/Media/logo.png" style="max-width: 100%;" width="25%"><br/><br/>
<img src="https://raw.githubusercontent.com/SivertGullbergHansen/GolfMk4RemoteStart/main/Media/title.png" style="max-width: 100%;" width="60%"><br/>
</p>

<br>
<br>

<p align="center">
<img src="https://img.shields.io/github/issues/SivertGullbergHansen/GolfMk4RemoteStart"> <img src="https://img.shields.io/github/forks/SivertGullbergHansen/GolfMk4RemoteStart"> <img src="https://img.shields.io/github/stars/SivertGullbergHansen/GolfMk4RemoteStart"> <img src="https://img.shields.io/github/license/SivertGullbergHansen/GolfMk4RemoteStart">
</p>

<br>
<br>

<h1 align="center">Introduction</h1>
<p align="center">🚀 This is an arduino sketch that enables the use of a sim-reader in order to remotely start a vehicle</p>

<br>
<br>
<br>

<h1 align="center">Description</h1>
<p>
This Arduino sketch is specifically made and tested for a Volkswagen Golf MK4 GTI, but it will most likely work on older cars as long as the immobilizer is removed/defeated.

You will need to have a neutral switch in your car if it is a manual car, you can easily connect this switch to an arduino pin.

Our Arduino Sketch requires a SIM card-reader that you can send SMS messages to. We wrote the sketch specifically for the **sim800l gsm module**.
We recommend using a prepaid card for your sim, as it is free to receive messages.

</p>

<br>
<br>
<br>

<h1 align="center">Requirements</h1>
<p>These items are required for our sketch to work.</p>
<ol>
  <li>💻 An arduino</li>
  <li>💾 A sim-card module that can read and send messages</li>
  <li>📱 A phone that can send messages</li>
  <li>📲 A sim-card that can receive messages</li>
  <li>⚙️ A neutral-switch in your car</li>
</ol>

<h3>Optional</h3>
<ol>
  <li>🖨️ A 3D-printer to print our case for the arduino and a relay-box</li>
</ol>

<br>
<br>
<br>

<h1 align="center">How To</h1>
<h2>Use our sketch</h2>
<p>To use our sketch, you will need to upload our .ino file to your arduino-board. <i>Make sure you've changed all necessary values before uploading and that you've properly hooked the arduino to your sim-reader and your vehicle before powering on the arduino.</i></p>
