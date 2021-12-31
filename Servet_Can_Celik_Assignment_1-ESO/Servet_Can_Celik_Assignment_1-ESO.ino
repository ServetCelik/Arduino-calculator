/* Servet Can Celik
 * 26 sep. 2021
 * This assignment Which combines knowledge of a button, LEDs, potentiometer, display and programming. 
 * It is a simple calculator with these components using the Arduino and the Rich Shield. * 
 */

#include "Display.h"
/*Firstly I declared some variables at this point*/
const int KNOB=14; /*potentiometer*/
const int LEDRED=4; /*red lamp*/
const int LEDYELLOW=7; /*yellow lamp*/
const int BUTTON=8; 

const int lastbuttonstate= HIGH;   
float firstNumber;
float secondNumber;
int symbol;
float result;
int vol;
int state=0;  /*I use this variable to change my stages*/



void setup() {     
pinMode(BUTTON,INPUT_PULLUP);
pinMode(LEDRED,OUTPUT);
pinMode(LEDYELLOW,OUTPUT);
pinMode(KNOB,INPUT);
Display.clear();


}

void loop() {
delay(200);  /*This delay prevent repetitions(bouncing) after return command*/

  int buttonstate;
  buttonstate=digitalRead(BUTTON);

  if(lastbuttonstate!=buttonstate && state==0){  /*this stage will be operated only once. Our code will not be return to state==0 again.*/
    Display.show("____");
    delay(3000);
    state=1;
    return;
  }

  if(state==1){    /*This is the stage for our first value*/
  vol=analogRead(KNOB);
  firstNumber=map(vol,0,1023,-20,20);
  Display.show(firstNumber);
    if(lastbuttonstate!=buttonstate){
    state=2;
    return;
    }
  }
 
  if(state==2){   /*this is the stage to determine which operator should we use*/
    vol=analogRead(KNOB);
    if(vol<256)
      {
      symbol = 1;
      Display.show("a"); 
    }
    else if(vol>256 && vol<512)
    {
      symbol = 2;
      Display.show("s");
    }
    else if(vol>512 && vol<738)
     {symbol = 3;
      Display.show("t");
     }
     
    else if(vol>738)
    {symbol = 4;
     Display.show("d");
    }

    if(lastbuttonstate!=buttonstate){
      state=3;
      return;
      }
    
   }

   if(state==3)    /*This is the stage for our second value*/
   {  
    vol=analogRead(KNOB);
    secondNumber=map(vol,0,1023,-20,20);
    Display.show(secondNumber);

     if(lastbuttonstate!=buttonstate){
        state=4;
        return;
      }
   }

  if(state==4)   /*at this stage we add,subtract,divide or multiply our numbers depend on the stage 2*/
  {

  if(symbol==1)
  {result = firstNumber + secondNumber;
  }

   else if(symbol==2)
   {result = firstNumber - secondNumber;
   }
   
   else if(symbol==3)
   {result = firstNumber * secondNumber;
   }
   
   else if(symbol==4)
   {result = firstNumber / secondNumber;
   }
   
   
   if(secondNumber==0 && symbol==4)   /*if our second number 0 and we will try to divide first number with it, we will get an error message*/
    {Display.show('Err');
    digitalWrite(LEDRED,HIGH);
      }
   else{Display.show(result);     /*or the result will be shown on the screen*/
    digitalWrite(LEDYELLOW,HIGH);
      }
    
   if(lastbuttonstate!=buttonstate){   /*at the and our lamps will be turned off and we will go back to state 1*/
    digitalWrite(LEDRED,LOW);
    digitalWrite(LEDYELLOW,LOW);
    state=1;
    return;
   }
  }

}
  
  
