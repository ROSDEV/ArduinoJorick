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

Servo myservo;

const int step_360= 200;
int waarde = 0; //stepper

const int knopPin = 48;  // knop aan pin 1
int knopstatus = 0;  // knop1 variabele

int  TeMakenStappen;    // variabele voor aantal stappen
int active = 0;           // variabele voor activiteit motor
// 4 regels hiervoor stonden eerst onder de Stepper small stepper.
int angle = 0; //servo 

#define STAPPEN_PER_MOTOR_OMWENTELING 32 // is nodig omdat hij anders niet aangeeft hoeveel stappen die zet, je zou het kunnen voor een variable zoals alleen het getal 32, het is ter aanduiding van
#define STAPPEN_PER_TOTAAL_OMWENTELING1 2048 // 64 x 32 = 2048 = 1 omwenteling rechtsom 
#define SERVO_1_INIT 9


Stepper small_stepper1(STAPPEN_PER_MOTOR_OMWENTELING, 8, 10, 9, 11);                  
Stepper small_stepper2(STAPPEN_PER_MOTOR_OMWENTELING, 22, 24, 26, 28); 
 
/*
  Het programmablok void setup wordt eenmaal beschreven
*/
void setup(){
//attach servo to a pin 
  myservo.attach(SERVO_1_INIT);

  myservo.write(0);
  delay(5000);
  myservo.write(90); //90 graden draaien

  delay(3000); // delay voor de start stepper 

  // stepper gaat draaien
  pinMode(knopPin, INPUT);  //knopPin is input
  small_stepper1.setSpeed(500);               // zet de snelheid
  small_stepper2.setSpeed(500);
  Serial.begin(9600);
 // while(digitalRead(knopPin)== HIGH);

  pinMode (7, INPUT);  //mircoswitch 
  pinMode (13, OUTPUT); //"lampje" 
  
  digitalWrite(13, LOW); //hier wordt de mircoswitch niet ingedrukt en gebeuert dus niks

}


void loop(){
  knopstatus = digitalRead(knopPin);  // lees toestand knop1
//if (knopstatus != lastknopstatus){
 // if (knopstatus == HIGH){
    
  
if (knopstatus == 0){

   waarde = 1;
     
      while (waarde == 1) //|| waarde micro == 1){ // while is zolang waarde 1 is voor dit.. uit. hier moet de mirco switch in worden gezet die ook waarde 1 moet hebben als de attractie moet stoppen.
      for(int s=0; s<step_360; s++) // waarde wordt veranderd van 0 naar 1, hij voert dus waarde 1 uit totdat hij naar waarde 0 wordt gebracht. Hier gaan we zeggen dat hij gestopt moet worden met de microswitch.
        {
           small_stepper1.step(1);
           small_stepper2.step(1);
        }

       
      }
    //  waarde = 0; volgens mij kan deze waarde weg want er word niks verteld


  if(digitalRead (7)== LOW) // als switch niet is ingedrukt dan lampje 13 aan anders(else) is lampje 13 uit , low == aan
  {
    digitalWrite(13, HIGH);
  }
  else 
  {
    digitalWrite(13, LOW);
  }
  }
    

//}
