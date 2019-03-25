int ledPin = 13;


void setup(){ 
	//Create a Serial Object
	Serial.begin(9600); 

	pinMode (ledPin, OUTPUT);
} 

void loop() 
{ 
//Have the arduino wait to receive input 
while (Serial.available() == 0); 

//Read input 
int val = Serial.read() - '0'; 
if (val == 1){ 
Serial.println("Led is on"); 
digitalWrite (ledPin, HIGH);
}   
else if (val == 0){ 
Serial.println("Led is off"); 
digitalWrite (ledPin, LOW);
} 
else { 
Serial.println ("Invalid");
} 
Serial.flush();

//Echo the input 
Serial.println(val); 


}