#include <AccelStepper.h>

AccelStepper stepper1(1, 3, 2);
AccelStepper stepper2CW(1, 5, 4);
AccelStepper stepper2CCW(1, 7, 6);
AccelStepper stepper3(1, 9, 8);
AccelStepper stepper4(1, 11, 10);


String inputstring = "0"; // input from python code
char inputkey = '0';

int stringlength = 0;
int stringpos = 0;

int ax1state = 0;
int ax2state = 128;
int ax3state = 128;
int ax4state = 0;
int ax5state = 0;

int ax1pos = 0; //Step command variable from input
int ax2CWpos = 0;
int ax2CCWpos = 0;
int ax3pos = 0;
int ax4pos = 0;
int ax5pos = 0;

int x = 0;

void setup()  {
  Serial.begin(9600);

  stepper1.setMaxSpeed(1000); 
  stepper1.setAcceleration(6000);
  
  stepper2CW.setMaxSpeed(1000);
  stepper2CW.setAcceleration(6000);

  stepper2CCW.setMaxSpeed(1000);
  stepper2CCW.setAcceleration(6000);
  
  stepper3.setMaxSpeed(3000);
  stepper3.setAcceleration(6000);

  stepper4.setMaxSpeed(1000);
  stepper4.setAcceleration(6000);
}

void loop() {
  
  if (Serial.available() > 0)   {
    inputstring = Serial.readString();
    Serial.print("I received: ");
    Serial.println(inputstring);

      
    for (stringlength = inputstring.length(); stringlength > 0; stringlength--){ 

      inputkey = inputstring.charAt(stringpos);

      Serial.print("I have left: ");
      Serial.println(inputstring);
      stringpos = stringpos + 1;
      
      if ((inputkey == 'w') && (ax2state < 132))  {
      
       ax2state = ax2state + 1;          
     }
      else if ((inputkey == 's') && (ax2state > 126))  {
         
       ax2state = ax2state - 1; 
     }
     else if (inputkey == 'd')  { // Axis 1 right
           
     }
     else if (inputkey == 'a')  { // Axis 1 left
            
     }
     else if ((inputkey == 'i') && (ax3state < 132))  { // Axis 3 up
      
       ax3pos = ax3pos + 400;
       ax3state = ax3state + 1;
      
      }
      else if ((inputkey == 'k') && (ax3state > 124))  { // Axis 3 down

        ax3pos = ax3pos - 400;
        ax3state = ax3state - 1;
        
        digitalWrite(13, HIGH);
      
        delayMicroseconds(300);
        digitalWrite(13, LOW);
        
     }
      else if (inputkey == 'l')  { // Axis 4 right
            
      }
      else if (inputkey == 'j')  { // Axis 4 left
              
      }
      else if (inputkey == 'u')  { // Axis 5 up
           
      }
      else if (inputkey == 'o')  { // Axis 5 down
        
      }
    }
  }
    stringpos = 0;
    
    stepper2CW.moveTo(ax2CWpos); 
    stepper2CCW.moveTo(ax2CCWpos); 
    stepper3.moveTo(ax3pos);
      

    
  while((stepper1.distanceToGo() != 0) || (stepper3.distanceToGo() != 0) || (stepper2CW.distanceToGo() != 0) || (stepper4.distanceToGo()!=0)) {  

    if(stepper1.distanceToGo() != 0) {
      stepper1.run();
    }
    
    if(stepper2CW.distanceToGo() != 0){
      stepper2CW.run();
      stepper2CCW.run();
    }
    
    if(stepper3.distanceToGo() != 0) {
      stepper3.run();
    }
    
    if(stepper4.distanceToGo() != 0) {
      stepper4.run();
    }
    
  } 
   
}
