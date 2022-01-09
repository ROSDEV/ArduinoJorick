/*Autheur:      Fun met Electronica
  Link:         https://training.funmetelectronica.nl/docs/arduino-basis/lessen/les-14-stappenmotor/  
  Beschrijving: Stappenmotor aansturen
  
  Aansluiting stappenmotor:
    1n1 = pin 8
    1n2 = pin 9
    1n3 = pin 10
    1n4 = pin 11
    --  = gnd
    +5v = +5v
*/
 
/*
  Een library en een paar constantes definiëren
 */
#include <Servo.h>
#include <Stepper.h>

Servo servo_1;

bool servos_resetted = false;
const int SERVO_1_CONNECTION_PIN = 9;
const int SERVO_RESET_POS = 0;
const int SERVO_DRAAI_KWART = 90;

const int KNOP_AAN = 1;
const int KNOP_UIT = 0;
const int KNOP_PIN1 = 48;  // knop aan pin 1 => Maar eigenlijk Pin 48 ?

const int ONE_SECOND = 1000;

const int step_360= 200;
int waarde = 0; //stepper

int  TeMakenStappen;    // variabele voor aantal stappen
int active = 0;           // variabele voor activiteit motor
// 4 regels hiervoor stonden eerst onder de Stepper small stepper.
int angle = 0; //servo 

#define STAPPEN_PER_MOTOR_OMWENTELING 32 // is nodig omdat hij anders niet aangeeft hoeveel stappen die zet, je zou het kunnen voor een variable zoals alleen het getal 32, het is ter aanduiding van
#define STAPPEN_PER_TOTAAL_OMWENTELING1 2048 // 64 x 32 = 2048 = 1 omwenteling rechtsom 

Stepper small_stepper1(STAPPEN_PER_MOTOR_OMWENTELING, 8, 10, 9, 11);                  
Stepper small_stepper2(STAPPEN_PER_MOTOR_OMWENTELING, 22, 24, 26, 28); 

void setup()
{

  Serial.begin(9600);
  servo_1.attach(SERVO_1_CONNECTION_PIN);    

  // stepper gaat draaien
  pinMode(KNOP_PIN1, INPUT);        //knopPin is input
  small_stepper1.setSpeed(500);     
  small_stepper2.setSpeed(500);
  
 // while(digitalRead(knopPin)== HIGH);

  pinMode(7, INPUT);  //mircoswitch 
  pinMode(13, OUTPUT); //"lampje" 
  
  digitalWrite(13, LOW); //hier wordt de mircoswitch niet ingedrukt en gebeuert dus niks

}

void ResetServoOnce(Servo servo) 
{
  if(!servo.attached) 
  {
    printLine("Servo is not attached ...");
    //Throw or just returns ?
    return;
  }
  if(!servos_resetted) 
  {
    servo.write(SERVO_RESET_POS);
    servo.write(SERVO_DRAAI_KWART);
    servos_resetted = true;
  }    
}

void WaitUntillAttached(Servo servo) 
{
  int maxtries = 5;
  int tries = 0;
  while (!servo.attached && tries < maxtries)
  {
    tries++;    
    printLine(std::format("Try {0} : NOT Attached waiting 1000 milliseconds..", tries);
    delay(ONE_SECOND);
  }  

  if(!servo.attached) 
  {
    //What to do usually throw an exception you can't so anything right ? 
  }
}

void printLine(string message) 
{
  Serial.print(message);
  Serial.writeln();
}

void loop()
{
  WaitUntillAttached(servo_1);
  ResetServoOnce(servo_1);

  int knopstatus = digitalRead(KNOP_PIN1);  
  if (knopstatus == KNOP_UIT)
  { 
    for(int s = 0; s < step_360; s++) // waarde wordt veranderd van 0 naar 1, hij voert dus waarde 1 uit totdat hij naar waarde 0 wordt gebracht. Hier gaan we zeggen dat hij gestopt moet worden met de microswitch.
    {
      small_stepper1.step(1);
      small_stepper2.step(1);
    }

    if(digitalRead(7) == LOW) // als switch niet is ingedrukt dan lampje 13 aan anders(else) is lampje 13 uit , low == aan
    {
      digitalWrite(13, HIGH);
    }
    else 
    {
      digitalWrite(13, LOW);
    }
  }
}
