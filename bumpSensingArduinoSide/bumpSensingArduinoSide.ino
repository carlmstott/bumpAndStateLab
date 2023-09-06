#include <AStar32U4Motors.h>

AStar32U4Motors m;

int leftMotor;
int rightMotor;

const byte numChars = 32;
char receivedChars[numChars];
char tempChar[numChars]; // temporary array used for parsing

boolean newData = false;

int x=0;
int y=0;
int z=0;

int a=0;
int b=0;
int c=0;


//=====================================================

void setup() {
  Serial.begin(115200);
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP); //might have to reassign these to pins that the astar knows
  pinMode(4, INPUT_PULLUP);

  pinMode(5, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP); //pick these pins for yourself,
  pinMode(8, INPUT_PULLUP);

Serial.println("<arduino is ready>");

}

//=====================================================

void loop() {
  recvWithStartEndMarkers();

  if (newData == true){
    
    strcpy(tempChar, receivedChars);
    parseData();
    SendBumpData();
    
    
  }
CommandMotors();

}

//============================================

void recvWithStartEndMarkers() {
//this function is the most important one of the whole lab, read the blog post made my Robin2
//some questions:
      //whats the purpose of the start and end markers?
      //Why bother making this code unblocking?
      //
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
                                         
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();
                                       

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminates the string, frankly unsure why I need 
                                           //this but it breaks if I remove it. Bonus points if you find out why
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============================================

void parseData(){

  //once the data has been recieved, this function turns those charichters into ints that are then sent to the motors. 



  char *strtokIndexer; //doing char * allows strtok to increment across my string properly frankly im not sure why... my kingdom for a proper c++ class

  
  strtokIndexer = strtok(tempChar,","); //sets strtokIndexer = to everything up to the first comma in tempChar /0 //this line is broken
  leftMotor = atoi(strtokIndexer); //converts strtokIndexer into a int
  

  strtokIndexer= strtok(NULL, ","); //setting the first input to null causes strtok to continue looking for commas in tempChar starting from where it left off, im not really sure why 
  rightMotor = atoi(strtokIndexer);

  


  //now that we have extracted the data from the Rpi as floats, we can use them to command actuators somewhere else in the code
}

//============================================
void SendBumpData(){
  
  x=digitalRead(0);
  y=digitalRead(1);
  z=digitalRead(4);

  a=digitalRead(5);
  b=digitalRead(7); //gonna have to set these also
  c=digitalRead(8);
  

  //Serial.print(receivedChars);
  Serial.print(x);
  Serial.print(',');
  Serial.print(y);
  Serial.print(',');
  Serial.print(z);
  Serial.print(',');
  Serial.print(a);
  Serial.print(',');
  Serial.print(b);
  Serial.print(',');
  Serial.println(c);
  newData = false; 
}

//============================================

void CommandMotors(){  

  //m.setM1Speed(rightMotor);
  //m.setM2Speed(leftMotor);
  //uncomment to drive motors
}
