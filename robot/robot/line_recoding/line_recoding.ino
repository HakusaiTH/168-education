//read sensor form ic 4051b value
int a = D6;
int b = D7;
int c = D8;
int sw = A0;

//read sensor
int vblack = 400; 
bool B(int n){
  if(n < vblack){  
    return true;  //is black
  }  
  else {
    return false; 
  }
}
bool W(int n){
  if(n >= vblack){
    return true;  //is white
  }  
  else {
    return false; 
  }
}

//get value form sensor
int r_com(int aa,int bb,int cc){
    digitalWrite(a,aa);
    digitalWrite(b,bb);
    digitalWrite(c,cc);
    int val = analogRead(sw);
    return val;
}

//motor control value
int motor_left = D5;
int IN3 = D2;
int IN4 = D3; 

int motor_right = D4;
int IN1 = D0;
int IN2 = D1;

//motor function
int baseSpeed = 600;
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

int nx = 0;
int sta = 1;
void Tl(){
  int left = r_com(1,1,0);   
  int center = r_com(0,1,0); 
  int right = r_com(1,0,0); 

  if(B(left) && B(center) && B(right)){
    motor(baseSpeed,baseSpeed);delay(300);
    if(sta == 1){
      nx++;  
    }
    else if(sta == 2){
      nx--;  
    }
  }

  if(B(left)){
    motor(-baseSpeed,baseSpeed);  
  }
  else if(B(right)){
    motor(baseSpeed,-baseSpeed);  
  }
  else{
    motor(baseSpeed,baseSpeed);  
  }
  Serial.printf("%d %d %d nx = %d sta = %d\n",left,center,right,nx,sta);
}

void ao(){motor(0,0);}

void backwards(){
  motor(baseSpeed,-baseSpeed);delay(750);
  ao();delay(500);  
}

void line_recoding(int posit){
  if(posit > nx){
    if(sta == 1){
      Tl();  
    }
    else if(sta == 2){
      backwards();
      sta = 1;  
    }  
  } 
  else if(posit < nx){
    if(sta == 2){
      Tl();  
    }
    else if(sta == 1){
      backwards();
      sta = 2;  
    }  
  }
  else {
    ao();delay(5000);  
  }
}

//setup
void setup() {
  //sensor 
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(sw,INPUT_PULLUP);

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
  line_recoding(1);
}
