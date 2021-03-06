#define BRAKEVCC 0
#define CW 1
#define CCW 2
#define BRAKEGND 3
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

 

int inApin[2] = {7, 4}; // INA: Clockwise Direction Motor0 and Motor1 (Check:"1.2 Hardware Monster Motor Shield").
int inBpin[2] = {8, 9}; // INB: Counterlockwise Direction Motor0 and Motor1 (Check: "1.2 Hardware Monster Motor Shield").
int pwmpin[2] = {5, 6};            // PWM's input
int cspin[2] = {2, 3};              // Current's sensor input

int statpin = 13;
int i=0;;
void setup()                         
{
Serial.begin(9600);              // Initiates the serial to do the monitoring 
pinMode(statpin, OUTPUT);
for (int i=0; i<2; i++)
    {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
    }
for (int i=0; i<2; i++)
    {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
    }
}

void loop()                          
{

// Routine to increase the speedo of the motor

while(i<255)
    {
    motorGo(0, CW, i);   // Increase the speed of the motor, according to the value of i is increasing       
    delay(50);                          
    i++;                             
    if (analogRead(cspin[0]) > CS_THRESHOLD) // If the motor locks, it will shutdown and...  

{                                                                     // ...Resets the process of increasing the PWM
    motorOff(0);  

}
    Serial.println(i);
    digitalWrite(statpin, LOW);
    }
i=1;

//=========

//Keep the acceleration while the motor not locks

while(i!=0)
    {                                      
    motorGo(0, CW, 255);       // Keep the PWM in 255 (Max Speed) 
    if (analogRead(cspin[0]) > CS_THRESHOLD)     // If the motor locks, it will shutdown and....         

        {                                                                      // ...Resets the process of increasing the PWM
         motorOff(0); 

        }
    }

//========


}
void motorOff(int motor)     //Function to shut the motor down case it locks
{

for (int i=0; i<2; i++)
    {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
    }
analogWrite(pwmpin[motor], 0);
i=0;
digitalWrite(13, HIGH);
Serial.println("Motor Locked");
delay(1000);
}
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
if (motor <= 1)
    {
    if (direct <=4)
        {
        if (direct <=1)
            digitalWrite(inApin[motor], HIGH);
        else
            digitalWrite(inApin[motor], LOW);

        if ((direct==0)||(direct==2))
            digitalWrite(inBpin[motor], HIGH);
        else
            digitalWrite(inBpin[motor], LOW);

        analogWrite(pwmpin[motor], pwm);
        }
    }
}
