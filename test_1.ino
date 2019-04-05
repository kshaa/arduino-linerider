/***************************05.04.2019*/
#define SPEED_LEFT       12
#define SPEED_RIGHT      13
//#define DIR_LEFT         7
//#define DIR_RIGHT        4 
#define LEFT_pResistor_PIN  14 // Photoresistor at Arduino analog pin A0
#define RIGHT_pResistor_PIN 15
#define CENTRE_pResistor_PIN 16
//#define LED_PIN
 
// The speed with which we move forward (0-255)
#define SPEED            35
 
// Coefficient setting how many times you need to brake
// one of the wheels to turn
#define BRAKE_K          4
 
#define STATE_FORWARD    0
#define STATE_RIGHT      1
#define STATE_LEFT       2
 
int state = STATE_FORWARD;

bool lineORnot(int PinNumber)
{
    int value;
    value = analogRead(PinNumber);    // Store value from photoresistor (0-1023)
    Serial.println(value);
    if (value<500) return true; //it is line
    else return false; //it is not line
    
}

void runForward() 
{
    state = STATE_FORWARD;
 
    // To adjust the speed, the `SPEED` can take values from 0 to 255,
    // the bigger, the faster.
    analogWrite(SPEED_LEFT, SPEED);
    analogWrite(SPEED_RIGHT, SPEED);
 
    // If we write HIGH in DIR_LEFT or DIR_RIGHT, the motor will move the corresponding wheel forward if LOW - back.
    //digitalWrite(DIR_LEFT, HIGH);
    //digitalWrite(DIR_RIGHT, HIGH);
}
 
void steerRight() 
{
    state = STATE_RIGHT;
 
    // Slow down the right wheel relative to the left to start the turn
    analogWrite(SPEED_RIGHT, SPEED / BRAKE_K);
    analogWrite(SPEED_LEFT, SPEED);
 
    //digitalWrite(DIR_LEFT, HIGH);
    //digitalWrite(DIR_RIGHT, HIGH);
}
 
void steerLeft() 
{
    state = STATE_LEFT;
 
    analogWrite(SPEED_LEFT, SPEED / BRAKE_K);
    analogWrite(SPEED_RIGHT, SPEED);
 
    //digitalWrite(DIR_LEFT, HIGH);
    //digitalWrite(DIR_RIGHT, HIGH);
}
 
void setup() 
{
    //pinMode(ledPin, OUTPUT);  // Set lepPin - 9 pin as an output
    Serial.begin(9600); //Initiate Serial communication.
    pinMode(LEFT_pResistor_PIN, INPUT);// Set LEFT_pResistor_PIN - A0 pin as an input (optional
    pinMode(RIGHT_pResistor_PIN, INPUT);
    pinMode(CENTRE_pResistor_PIN, INPUT);
    pinMode(SPEED_LEFT, OUTPUT); //12
    pinMode(SPEED_RIGHT, OUTPUT); //13
    runForward();// Immediately we go forward
} 

void loop() 
{   

    bool left = lineORnot(LEFT_pResistor_PIN);
    bool centre = lineORnot(CENTRE_pResistor_PIN);
    bool right = lineORnot(RIGHT_pResistor_PIN);
    
    // What state should it go to?
    int targetState;

    if((left==0)&&(centre==1)&&(right==0)){
        targetState = STATE_FORWARD;
    } else if (left) {
        // left sensor rests on the track
        // turn left
        targetState = STATE_LEFT;
    } else {
        targetState = STATE_RIGHT;
    }
 
    if (state != targetState) {
        // we are already doing everything we need
        // re-measure
        switch (targetState) {
            case STATE_FORWARD:
                runForward();
                break;
     
            case STATE_RIGHT:
                steerRight();
                break;
     
            case STATE_LEFT:
                steerLeft();
                break;
        }
    }
    
    // do not allow much wag on the line
    delay(50);
}
