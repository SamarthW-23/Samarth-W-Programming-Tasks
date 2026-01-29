# Samarth-W-Programming-Tasks
#LED-blink

## Connection Setup
1) Arduino UNO
2) Red LED
3) Button 1 (Orange) for ON/OFF
4) Button 2 (Purple) for Changing blinking speed.

-> The anode of LED connected to -> Pin 3 of board which is PWM capable.
-> The cathode of LED connected to -> ground pin of board

->Button 1 (ON/OFF button) connected between Pin 7 and ground.
->Button 2 (Blinking speed change) connected between Pin 6 and ground.

## In setup()
-> The LED Pin (IN1) is set as an OUTPUT.
-> Both the button pins are set as INPUT_PULLUP (meaning HIGH by default, LOW when pressed).

## Approach:-

### Checking for button press:- 
Both the buttons are set as INPUT_PULLUP in setup(), meaning they are set as HIGH by default and switch to LOW (as the other end is grounded) when pressed.
But during even a single button press, the button does not simply fo from HIGH -> LOW -> HIGH again, instead it continuously toggles between HIGH and LOW multiple times. This is called bouncing.

To account for bouncing of the ON/OFF button, I have implemented the 'minimum debounce time' approach, and for the changing blinking speed button, the 'delay()' approach is used.

#### Minimum debounce time approach:-

In this approach we continuously record the state of the button and then check if it has remained in that same state for more than a threshold minimum time (ie DebounceTime). If yes, then only the state of the button is considered to be changed.

#### Execution:-
For this, we define some variables.
1) raw -> to store the state of the button at every instance.
2) prevButtonState -> stores the state of the button previous to the raw reading.
3) prevChangeTime -> to record the time at which raw reading != prevButtonState.
4) StableButtonState -> the final 'stable' button state after debouncing.

--> prevButtonState and StableButtonState are initially set to HIGH.

--> The variable 'raw' continuosly reads and stores the current state of the button using    digitalRead()

--> if raw != previousButtonState:- 
(i) prevChangeTime reads and stores the time (using millis()) at which the change occured.
(ii) the prevButtonState is set equal to raw;

--> If [ current time - prevChangeTime > DebounceTime ] && [raw != StableButtonState]:-
(i) StateButtonState = raw (meaning it was a genuine button press and not bounce)
(ii) if [ StableButtonState == LOW ]:-
        reverse the boolean value of 'isOn';


#### delay() approach for Debouncing:-

this approach has been used for changing blinking speed button which is less significant than ON/OFF button. Here, we once check the state of the button if it's == LOW, then pause the code for 30ms (DebounceTime) and again check if the state is still == LOW. If yes, then only we consider it as a genuine press, and change the value of delayTime.

Also we have to add an empty while() loop with the condition of Button == LOW, which is for the time period when the button is pressed but not yet released. Because of this empty while loop, the programs keeps re-cheacking the button.
So the process become:- 

    >   Check the state of delayButton and store it in variable 'read'

    >   If 'read' == LOW --> delay(30) --> check again if 'read' == LOW

    >   If yes, then change the delayTime. 

    >   But if the button is still pressed, read is still LOW, keep re-cheacking again and  do not proceed to further steps until the user lets go of the button.


### Changing Blinking Speed:-

The blinking speed is changed using delay() function. Using PWM for the LED Pin (IN1) at Pin 3 of the board, we start a loop wherein the value of PWM is changed from 80 (LED on) to 0 (LED Off) using analogWrite() for Pin 3, with a delay time in between.

The initial delay time is set to 200ms. with every button press incrementing/decrementing the value by 200ms (delayIncrement). 

Once the value of delay time reaches 1000ms, we change the sign of delayIncrement from +200 to -200 and similarly when the value of delay time reaches 200ms, we again change it back to 200ms.

So with every press the delay time changes its values as:-

200ms --> 400ms --> 600ms --> 800ms --> 1000ms (1sec) --> 800ms --> 600ms --> 400ms --> and 200ms again. 



....



