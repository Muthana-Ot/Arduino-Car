int enA=6;
int motorLF = 4; 
int motorLB = 2;
int enB = 3;
int motorRF = 5;
int motorRB = 7;

// Front Left Right
int echoPinF = 13;
int trigPinF = 12;  
int echoPinL = 8;
int trigPinL = 9;
int echoPinR = 10;
int trigPinR = 11;

unsigned long previousMillis = 0;
int CHECK_INTERVAL = 200;
int moveState = 0; // State machine for movement
bool moving = false;
const int delayTime = 100; 
const int delayOfCaseR = 420; // Delay of LeftCase RightCase, it depends on the softness of the floor
const int delayOfCaseL = 420; 

void setup() {

  pinMode(motorRF, OUTPUT);
  pinMode(motorRB, OUTPUT);
  pinMode(motorLF, OUTPUT);
  pinMode(motorLB, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(echoPinF, INPUT);
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(trigPinR, OUTPUT);
  analogWrite(enA,100);
  analogWrite(enB,100);

  
  
}

float UltraSonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int travelTime = pulseIn(echoPin, HIGH, 25000);
  float distance = 0.034 * travelTime / 2;
  return distance;
}


void  moveForward(){
   digitalWrite(motorRF , HIGH);
   digitalWrite(motorLF , HIGH);  
   digitalWrite(motorRB , LOW);
   digitalWrite(motorLB , LOW); 
   analogWrite(enA,100);
   analogWrite(enB,100);

}

void stopp() {
  digitalWrite(motorRF, LOW);
  digitalWrite(motorLF, LOW);
  digitalWrite(motorRB, LOW);
  digitalWrite(motorLB, LOW);
}

void turnLeft() {
  digitalWrite(motorRF, HIGH);
  digitalWrite(motorRB, LOW);
  digitalWrite(motorLF, LOW);
  digitalWrite(motorLB, HIGH);
  analogWrite(enA,255);
  analogWrite(enB,255);
}

void turnRight() {
  digitalWrite(motorRF, LOW);
  digitalWrite(motorRB, HIGH);
  digitalWrite(motorLF, HIGH);
  digitalWrite(motorLB, LOW);
  analogWrite(enA,255);
  analogWrite(enB,255);
}

void LeftCase(){ //This method is used to let the car turn left in the case that's needed to based on the maze
  turnLeft();
  delay(delayOfCaseL); 
  stopp();
  moveState++;
}

void RightCase(){ //This method is used to let the car turn right in the case that's needed to based on the maze
  turnRight();
  delay(delayOfCaseR); 
  stopp();
  moveState++;
}

void CheckCase(){
  stopp();
  moving = false;
  moveState++;
  delay(delayTime);
}


void loop() {
    unsigned long currentMillis = millis();
    
    switch (moveState) {
    case 0: // Move forward 100 cm
        if (!moving) {
            moving = true;
            moveForward();
        } else {
            // Adjust the direction based on the right distance sensor
                   if (currentMillis - previousMillis >= CHECK_INTERVAL) {
                    previousMillis = currentMillis;
                    float distanceR = UltraSonic(trigPinR, echoPinR);
                    if(distanceR < 10){
                      turnLeft();
                      delay(50);
                    }
                   } 
            // Check the front distance sensor for obstacles
            float distance = UltraSonic(trigPinF, echoPinF);
            if (distance == 0) {
                moveForward();
            } else if (distance <= 20 && distance > 0) {
                CheckCase();
            } else {
                moveForward();
            }
        }
        break;
    case 1: // Turn left
        LeftCase();
        break;
   case 2: // Move forward 100 cm
        if (!moving) {
            moving = true;
            moveForward();
        } else {
            // Adjust the direction based on the right distance sensor
                   if (currentMillis - previousMillis >= CHECK_INTERVAL) {
                    previousMillis = currentMillis;
                    float distanceR = UltraSonic(trigPinR, echoPinR);
                    if(distanceR < 10){
                      turnLeft();
                      delay(50);
                    }
                   } 
            // Check the front distance sensor for obstacles
            float distance = UltraSonic(trigPinF, echoPinF);
            if (distance == 0) {
                moveForward();
            } else if (distance <= 20 && distance > 0) {
                CheckCase();
            } else {
                moveForward();
            }
        }
        break;
     case 3 : // turn right
        RightCase();
        break;

     case 4: // Move forward 100 cm
        if (!moving) {
            moving = true;
            moveForward();
        } else {
            if (currentMillis - previousMillis >= CHECK_INTERVAL) {
                    previousMillis = currentMillis;
                    float distanceL = UltraSonic(trigPinL, echoPinL);
                   if(distanceL < 10){
                      turnRight();
                      delay(50);
                    }
                   } 
            float distance = UltraSonic(trigPinF, echoPinF);

            if (distance == 0) {
               moveForward();
            } else if (distance <= 20 && distance > 0) {
                CheckCase();
            }
        }
        break; 
       case 5: // turn right
         RightCase();
         break; 

       case 6: // Move forward 100 cm
        if (!moving) {
            moving = true;
            moveForward();
        } else {
            float distance = UltraSonic(trigPinF, echoPinF);
            //Serial.println(distance);
            //Serial.println(moveState);

            if (distance == 0) {
               moveForward();
            } else if (distance <= 20 && distance > 0) {
                CheckCase();
            }
        }
        break; 

      case 7: // Turn left
        LeftCase();
        break;
        
      case 8: // Move forward 100 cm
        if (!moving) {
            moving = true;
            moveForward();
        } else {
          // Adjust the direction based on the right distance sensor
                   if (currentMillis - previousMillis >= CHECK_INTERVAL) {
                    previousMillis = currentMillis;
                    float distanceR = UltraSonic(trigPinR, echoPinR);
                    if(distanceR == 0 ){moveForward();}
                    else if(distanceR < 10){
                      turnLeft();
                      delay(50);
                    }
                   } 
            float distance = UltraSonic(trigPinF, echoPinF);
          
            if (distance == 0) {
               moveForward();
            } else if (distance <= 20 && distance > 0) {
                CheckCase();
            }
        }
        break; 

       case 9: // Turn left
        LeftCase();
        break;

       case 10: // Move forward 100 cm
        if (!moving) {
            moving = true;
            moveForward();
        } else {
          // Adjust the direction based on the right distance sensor
                   if (currentMillis - previousMillis >= CHECK_INTERVAL) {
                      previousMillis = currentMillis;
                      float distanceR = UltraSonic(trigPinR, echoPinR);
                      if(distanceR ==0 ){ moveForward();}
                      else if(distanceR < 10){
                        turnLeft();
                        delay(50);
                      }else if(distanceR >= 40){
                        turnRight();
                        delay(50);
                      }
                   }
            float distance = UltraSonic(trigPinF, echoPinF);

            if (distance == 0) {
               moveForward();
            } else if (distance <= 20 && distance > 0) {
                CheckCase();
            }
        }
        break; 

       case 11: // Turn left
        LeftCase();
        break;

       case 12: // Move forward 100 cm
        if (!moving) {
            moving = true;
            moveForward();
        } else {
            float distance = UltraSonic(trigPinF, echoPinF);
            //Serial.println(distance);
            //Serial.println(moveState);

            if (distance == 0) {
               moveForward();
            } else if (distance <= 20 && distance > 0) {
                CheckCase();
            }
        }
        break;

       case 13: // Turn left
        LeftCase();
        break;

       case 14: // Move forward 100 cm
        if (!moving) {
            moving = true;
            moveForward();
        } else {
             if (currentMillis - previousMillis >= CHECK_INTERVAL) {
                    previousMillis = currentMillis;
                    float distanceR = UltraSonic(trigPinR, echoPinR);
                    if(distanceR == 0 ){moveForward();}
                    else if(distanceR < 10){
                      turnLeft();
                      delay(50);
                    }
                   } 
            float distance = UltraSonic(trigPinF, echoPinF);
            float distanceR = UltraSonic(trigPinR, echoPinR);
          
            if (distanceR == 0) {
               moveForward();
            } else if (distanceR > 50) { // 5aberni
                CheckCase();
            }
        }
        break;

         case 15: // turn right
         RightCase();
         break;

         case 16: // Move forward 100 cm
         if (!moving) {
            moving = true;
            moveForward();
         } else {
            float distance = UltraSonic(trigPinF, echoPinF);

            if (distance == 0) {
               moveForward();
            } else if (distance <= 10 && distance > 0) {
                stopp();
                moveForward();
                delay(250); // on test 
                CheckCase();
            }
        }
        break; 

        case 17: // Turn left
        LeftCase();
        break;

        case 18: // Move forward 100 cm
        if (!moving) {
            moving = true;
            moveForward();
        } else {
            // Adjust the direction based on the right distance sensor
                   if (currentMillis - previousMillis >= CHECK_INTERVAL) {
                    previousMillis = currentMillis;
                    float distanceR = UltraSonic(trigPinR, echoPinR);
                   if(distanceR < 10){
                      turnLeft();
                      delay(50);
                    }
                   } 
            // Check the front distance sensor for obstacles
            float distance = UltraSonic(trigPinF, echoPinF);
            if (distance == 0) {
                moveForward();
            } else if (distance <= 10 && distance > 0) {
                CheckCase();
            } else {
                moveForward();
            }
        }
        break;
         case 19: // turn right
         RightCase();
         break;

        case 20: // Move forward 100 cm
        if (!moving) {
            moving = true;
            moveForward();
        } else {
            // Adjust the direction based on the right distance sensor
                   if (currentMillis - previousMillis >= CHECK_INTERVAL) {
                    previousMillis = currentMillis;
                    float distanceL = UltraSonic(trigPinL, echoPinL);
                   if(distanceL < 10){
                      turnRight();
                      delay(50);
                    }
                   } 
            // Check the front distance sensor for obstacles
            float distance = UltraSonic(trigPinF, echoPinF);
            if (distance == 0) {
                moveForward();
            } else if (distance <= 10 && distance > 0) {
                CheckCase();
            } else {
                moveForward();
            }
        }
         break;
         
        case 21: // turn right
         RightCase();
         break;

        case 22: // Move forward 100 cm
         if (!moving) {
            moving = true;
            moveForward();
         } else {
            // Adjust the direction based on the right distance sensor
                   if (currentMillis - previousMillis >= CHECK_INTERVAL) {
                    previousMillis = currentMillis;
                    float distanceL = UltraSonic(trigPinL, echoPinL);
                   if(distanceL < 10){
                      turnRight();
                      delay(50);
                    }
                   } 
            // Check the front distance sensor for obstacles
            float distance = UltraSonic(trigPinF, echoPinF);
            if (distance == 0) {
                moveForward();
            } else if (distance <= 10 && distance > 0) {
                CheckCase();
            } else {
                moveForward();
            }
        }
         break;

        case 23: // Turn left
        LeftCase();
        break;

        case 24: // Move forward 100 cm
          if (!moving) {
            moving = true;
            moveForward();
          } else {
            // Adjust the direction based on the right distance sensor
                   if (currentMillis - previousMillis >= CHECK_INTERVAL) {
                    previousMillis = currentMillis;
                    float distanceR = UltraSonic(trigPinR, echoPinR);
                   if(distanceR < 10){
                      turnLeft();
                      delay(50);
                    }
                   } 
            // Check the front distance sensor for obstacles
            float distance = UltraSonic(trigPinF, echoPinF);
            if (distance == 0) {
                moveForward();
            } else if (distance <= 10 && distance > 0) {
                CheckCase();
            } else {
                moveForward();
            }
        }
        break;
         

      default: 
       stopp();
       break;    
    }
    delay(50);
}
