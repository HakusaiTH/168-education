//read sensor form ic 4051b value
int a = D6;
int b = D7;
int c = D8;
int sw = A0;

//read sensor
int vblack = 500; 
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

//setup
void setup() {
  //sensor 
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(c,OUTPUT);
  pinMode(sw,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int left = r_com(1,1,0);   
  int center = r_com(0,1,0); 
  int right = r_com(1,0,0); 
  Serial.printf("%d %d %d\n",left,center,right);
}

//get value form sensor
int r_com(int aa,int bb,int cc){
    digitalWrite(a,aa);
    digitalWrite(b,bb);
    digitalWrite(c,cc);
    int val = analogRead(sw);
    return val;
}
