//motor control value
int motor_left = D5;
int IN3 = D2;
int IN4 = D3; 

int motor_right = D4;
int IN1 = D0;
int IN2 = D1;

//motor function
void motor(int left,int right){
  //left
  if(left >= 0){
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);    
  }
  else{
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    left = -left;    
  }
  analogWrite(motor_left,left);

  //right
  if(right >= 0){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);    
  }
  else{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    right = -right;    
  }
  analogWrite(motor_right,right);
}

//setup
void setup() {
  //motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(motor_left,OUTPUT);
  pinMode(motor_right,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  motor(500,-500);delay(500);
  motor(-500,500);delay(500);
  motor(0,0);delay(500);
}
