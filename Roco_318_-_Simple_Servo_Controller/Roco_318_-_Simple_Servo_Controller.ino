/*-----------------------------------------------------------------------------------------------------
  ----------------------------------------------------------------------------------------------------
  ---------------------------------------------------------------------------------------------------

            _____   ____   _____ ____ ____  __  ___
           |  __ \ / __ \ / ____/ __ \___ \/_ |/ _ \
           | |__) | |  | | |   | |  | |__) || | (_) |
           |  _  /| |  | | |   | |  | |__ < | |> _ <
           | | \ \| |__| | |___| |__| |__) || | (_) |
           |_|  \_\\____/ \_____\____/____/ |_|\___/
                    SIMPLE SERVO CONTROLLER

  This is some super simple code for controlling servos via id and angle values.
  This has been made for the Arduino Nano with a PCA9685 16 channel i2c PWM breakout board.

                         -:Wiring:-
                ARDUINO NANO --->    PCA9685
                     A5      --->      SCL
                     A4      --->      SDA
                    GND      --->      GND
                     5V      --->      VCC

  THIS CODE UTILISES THE ADAFRUIT PWM SERVO DRIVER LIBRARY, TO ADD IT TO YOUR ARDUINO IDE:
  - Click on; Sketch
  - Click on; Include Library
  - Click on; Manage Libraries...
  - In the search bar that appears, type in "Adafruit PWM Servo Driver" and click install on the one that appears with the same name.
  Now you have the neccessary libraries to run the following code.

                     -:USING THE CODE:-
                      ----------------
  When uploaded you can then send simple commands to the board to control your servos.
  It must be in the following format:
    ServoNumber,ServoAngle

    So for example:

    UpdateServo(6, 90);

    This will move servo number 6 to an angle of 90 degrees.

  That is everything you need to know to use the board

  Debugging:

  If you send your servo an angle value and it does not line up, then you may need to calibrate the servo minimum and maximum pulse lengths
  Currently they have been calibrated for a range of 0 to 180 degrees for the Towerpro MG996R
  #define SERVOMIN  135 // This is the 'minimum' pulse length count (out of 4096) For the MG996R this wants to be 135
  #define SERVOMAX  482 // this is the 'maximum' pulse length count (out of 4096) For the MG996R this wants to be 482

  ------------------------------------------------------------------------------------------------
  -------------------------------------------------------------------------------------------------
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN  135 // This is the 'minimum' pulse length count (out of 4096) For the MG996R this wants to be 135
#define SERVOMAX  482 // this is the 'maximum' pulse length count (out of 4096) For the MG996R this wants to be 482

Adafruit_PWMServoDriver PCA9685 = Adafruit_PWMServoDriver();

int ServoPositions[16][5]; //you can use this to make a 2D array of values for your 16 servos positions for each point of your walking gait

#define waistL 1
#define waistR 2
#define hipL 3
#define hipR 4
#define kneeL 5
#define kneeR 6
#define ankleL 7
#define ankleR 8
#define footL 9
#define footR 10


//----------------------------------------------------------------------------//
void setup() {
  Serial.begin(115200); //Nice faster speed
  PCA9685.begin();
  PCA9685.setPWMFreq(50); //Maximum speed this can be set to is 1600
  Wire.setClock(400000); // Fast 400khz I2C Mode
  Serial.println("PCA9685 Servo Controller Connected & Ready");
}


/*----------------------------------------------------------------------------
   __  __          _____ _   _
  |  \/  |   /\   |_   _| \ | |
  | \  / |  /  \    | | |  \| |
  | |\/| | / /\ \   | | | . ` |
  | |  | |/ ____ \ _| |_| |\  |
  |_|  |_/_/    \_\_____|_| \_|
  ----------------------------------------------------------------------------*/
void loop() {

  /*for (int ServoNumber = 0; ServoNumber <= 15; ServoNumber++) // set all servos to 90 degrees
  {
    UpdateServo(ServoNumber, 90);
  }
  delay(1000);*/
  reset();
  //walk_forward();
  //balance();
  //sidewalk(); 
 

}
//End of Main
//----------------------------------------------------------------------------//
//SERVO ZERO DEGREE           clockwise
//  1     105    Waist Left
//  2     105    Waist Right  +
//  3     90     Hip Left
//  4     90     Hip Right    +
//  5     125    Knee Left 
//  6     115    Knee Right   -
//  7     120    Ankle Left 
//  8     120    Ankle Right
//  9     110    Foot Left 
//  10    30     Foot Right
/*----------------------------------------------------------------------------
   ______ _    _ _   _  _____ _______ _____ ____  _   _  _____
  |  ____| |  | | \ | |/ ____|__   __|_   _/ __ \| \ | |/ ____|
  | |__  | |  | |  \| | |       | |    | || |  | |  \| | (___
  |  __| | |  | | . ` | |       | |    | || |  | | . ` |\___ \
  | |    | |__| | |\  | |____   | |   _| || |__| | |\  |____) |
  |_|     \____/|_| \_|\_____|  |_|  |_____\____/|_| \_|_____/
  ----------------------------------------------------------------------------*/
void UpdateServo (int Id, int Angle) {

  double pulselength = map(Angle, 0, 180, SERVOMIN, SERVOMAX); //map the degree value to pulselength value
  PCA9685.setPWM(Id, 0, pulselength); //Send the angle to the appropiate servo

}

void reset(){
  {
    UpdateServo(1, 105); //WaistL
    UpdateServo(2, 105); //WaistR
    UpdateServo(3, 90); //HipL
    UpdateServo(4, 90); //HipR 
    UpdateServo(5, 125); //KneeL
    UpdateServo(6, 115); //KneeR
    UpdateServo(7, 120); //AnkleL
    UpdateServo(8, 120); //AnkleR
    UpdateServo(9, 110); //FootL +
    UpdateServo(10, 30); //FootR +
  }
}

void walk_forward(){
  reset();
  delay(500); //WaistR tilt & WaistL lift
  UpdateServo(ankleR,130);
  UpdateServo(waistR,92);
  UpdateServo(waistL,92);
  UpdateServo(hipL,80);
  delay(500);
  UpdateServo(ankleR,135);
  UpdateServo(waistR,95);
  UpdateServo(waistL,85);
  UpdateServo(hipL,65);
  delay(500);
  UpdateServo(ankleR,145);
  UpdateServo(waistR,90);
  UpdateServo(hipL, 50);
  delay(500);
  UpdateServo(kneeL, 135); //Lifting Left Leg 
  UpdateServo(footL, 120);
  delay(500); 
  UpdateServo(kneeL, 155);
  ///UpdateServo(hipL, 75);
  delay(500); 
  UpdateServo(kneeL, 160);
  delay(500); 
  UpdateServo(ankleL,130); 
  UpdateServo(footL, 110);
  delay(500); 
  UpdateServo(ankleR,120);
  UpdateServo(waistR,105);
  //UpdateServo(hipL, 90);
  delay(500);
  UpdateServo(kneeL,125); //Straighten Both Legs
  UpdateServo(waistL,105);
  delay(500);
  UpdateServo(hipL,90);
///////////////////////////////////////////////////////////////////////////////////////////////////// 
  delay(500); //WaistR tilt & WaistL lift
  UpdateServo(ankleL,110);
  UpdateServo(waistR,110);
  UpdateServo(waistL,125);
  UpdateServo(hipR,100);
  delay(500);
  UpdateServo(ankleL,107);
  UpdateServo(waistL,115);
  UpdateServo(waistR,130);
  UpdateServo(hipR,110);
  delay(500);
  UpdateServo(ankleL,105);
  UpdateServo(waistL,120);
  UpdateServo(hipR, 120);
  delay(500);
  UpdateServo(kneeR, 100); //Lifting Left Leg 
  UpdateServo(footR, 40);
  delay(500); 
  UpdateServo(hipR, 150);
  UpdateServo(kneeR, 50);
  delay(500);
  UpdateServo(hipR, 180);
  UpdateServo(kneeR, 20);
  UpdateServo(footR, 50);
  delay(500); 
  UpdateServo(kneeR, 60);
  UpdateServo(hipR, 115);
  UpdateServo(hipL, 110); 
  delay(500); 
  UpdateServo(hipR, 90);
  UpdateServo(ankleR,130); 
  UpdateServo(footR, 40);
  delay(500);
  UpdateServo(kneeR,85); 
  UpdateServo(hipL, 90);
  delay(500);
  UpdateServo(kneeR,125); //Straighten Both Legs
  UpdateServo(ankleL,120);
  UpdateServo(waistL,105);
  UpdateServo(waistR,105);
  delay(500);
}


void balance(){
  delay(100);
  UpdateServo(waistR, 110);
  UpdateServo(ankleR,125);
  UpdateServo(ankleL,110);
  delay(100);
  UpdateServo(ankleR,130);
  UpdateServo(waistR, 115);
  UpdateServo(ankleL,100);
  delay(100);
  UpdateServo(ankleR,132);
  UpdateServo(waistR, 120);
  UpdateServo(ankleL,90);
  delay(100);
  UpdateServo(ankleR,135);
  UpdateServo(waistR, 125);
  UpdateServo(ankleL,80);
  delay(100);
  UpdateServo(ankleR,137);
  UpdateServo(waistR, 130);
  delay(100);
  UpdateServo(ankleR,140);
  UpdateServo(waistR, 135);
  delay(100);
  UpdateServo(ankleR,142);
  UpdateServo(waistR, 140);
  delay(100);
  UpdateServo(ankleR,145);
  UpdateServo(waistR, 145);
  delay(100);
  UpdateServo(ankleR,142);
  UpdateServo(waistR, 140);
  delay(100);
  UpdateServo(ankleR,140);
  UpdateServo(waistR, 135);
  delay(100);
  UpdateServo(ankleR,137);
  UpdateServo(waistR, 130);
  delay(100);
  UpdateServo(ankleR,135);
  UpdateServo(waistR, 125);
  delay(100);
  UpdateServo(ankleR,132);
  UpdateServo(waistR, 120);
  delay(100);
  UpdateServo(ankleR,130);
  UpdateServo(waistR, 115);
  delay(100);
  UpdateServo(ankleR,127);
  UpdateServo(waistR, 110);
  delay(100);
  UpdateServo(ankleR,125);
  UpdateServo(waistR, 105);
  delay(100);
}

void sidewalk(){
delay(500);
UpdateServo(ankleR,145);
UpdateServo(waistL, 85);
delay(500);  
}
