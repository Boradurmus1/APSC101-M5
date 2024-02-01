
#include <NewPing.h>
#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200
#include <Servo.h>
Servo myservo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int greenPin = 7;
int redPin = 6;

void setup()
{
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(10, LOW);
  digitalWrite(13, HIGH);
  pinMode(8,INPUT_PULLUP); 
  myservo.attach(9); 
  myservo.write(60); 
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  
  }

void loop(){
  delay(100);
  digitalWrite(greenPin, HIGH);
  
  int DISTANCE_IN_CM = sonar.ping_cm();
  Serial.println(DISTANCE_IN_CM);
  if(DISTANCE_IN_CM < 8){ //close the claw (change the second arg after testing with the prototype)

    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    Serial.println("Picking up object");
    delay(7000); // SAFETY!!! wait for seconds to align the crane for the object

    int DISTANCE_IN_CM4 = sonar.ping_cm();
    Serial.println(DISTANCE_IN_CM4);
    if(DISTANCE_IN_CM4 < 8){ //back up plan

      Serial.println("Extra time");
      Serial.println(DISTANCE_IN_CM4);
      for(int i = 0; i < 20; i++){

        digitalWrite(redPin, LOW);
        delay(125); //wait for an extra five seconds if we could not pick the object up at the first try
        digitalWrite(redPin, HIGH);
        delay(125);
        
      }
      
      
    }

    Serial.println("Object picked up");
    myservo.write(60); //close the claw
    delay(5000);
    int firstCheckpoint = 0; //counter
    
    while(firstCheckpoint == 0){ //keeps the claw closed until it is up by 150 cm
           
            int DISTANCE_IN_CM2 = sonar.ping_cm();
            Serial.println(DISTANCE_IN_CM2);
            //Serial.println(DISTANCE_IN_CM2);
          
            myservo.write(60); //keep it closed

            if(DISTANCE_IN_CM2 > 150){ //checkpoint - means we have gone up
              
              Serial.println(DISTANCE_IN_CM2);
              digitalWrite(greenPin, HIGH);
              Serial.println("Gone up");
              firstCheckpoint++;
              
            }
    }

    int secondCheckpoint = 0; //counter
    
    while(secondCheckpoint == 0){ //opens the claw when the dıstance ıs less than 8 cm
      
      int DISTANCE_IN_CM3 = sonar.ping_cm();
      Serial.println(DISTANCE_IN_CM3);
      //Serial.println("FUCK");

      if(DISTANCE_IN_CM3 < 8){ //checkpoint - means we have gone down

        Serial.println("Gone down");
        Serial.println(DISTANCE_IN_CM3);
        digitalWrite(greenPin, LOW);
        digitalWrite(redPin, LOW);
        
        for(int a = 0; a < 8; a++){

          digitalWrite(greenPin, HIGH);
          delay(125);
          digitalWrite(greenPin, LOW);
          digitalWrite(redPin, HIGH);
          delay(125);
          digitalWrite(redPin, LOW);


          
        }
        
        myservo.write(150); // open the claw
        
        secondCheckpoint++;
        
        delay(5000); // SAFETY!!! wait for 5 seconds as we are going up, do not read any data from the sensor
        Serial.println("Gone up again");
        
      }
    }
    
  }
  
  else if(DISTANCE_IN_CM >= 8){ //change the second arg after testing with the prototype

    Serial.println("The claw is up");
    myservo.write(150); //open the claw
  }

  //Serial.println(DISTANCE_IN_CM);
  }
