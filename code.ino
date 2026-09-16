
#include <ESP32Servo.h>
#include<NewPing.h>
#include<math.h>
// #include<Millis.h>
constexpr uint8_t fut =14;
constexpr uint8_t fue=34;
constexpr uint8_t fservo=13;
uint8_t curr_angle;

Servo fs;

NewPing front(fut, fue, 200);

void setup(){
  fs.attach(fservo);
  Serial.begin(115200);
  delay(2000);
curr_angle=fs.read();
  for( uint8_t i=curr_angle;i<100;i++){
    fs.write(i);
    delay(0);
  }
  delay(100);
}

uint8_t getDistance(){
  uint8_t d=front.ping_cm();
  
    return (d==0)? 200:d;
  
}
double calculateDistance(){
  uint8_t tempd1=0, tempd2=0, d1=0, d2=0;
  uint8_t s1=160, s2=20;
  int s=0;
  if(curr_angle>90){
    fs.write(160);}
  else{
    fs.write(90); delay(50);
    fs.write(120); delay(50);
    fs.write(160);

  }
  
  for (curr_angle=160;curr_angle>20;curr_angle-=10){
      fs.write(curr_angle);
      delay(50);      
      tempd1=getDistance()/*sin(radians(curr_angle))*/;
      if(tempd2==0){
        tempd2=tempd1;
      }
      else if((tempd2<tempd1)){
        if((tempd1*sin(radians(curr_angle))>=20)){
        d1=tempd1;
        tempd1=0;
        s1=curr_angle;
        break;
        }
      }
      else{
      tempd2=tempd1;  
      }
      
      // s1=curr_angle;      
      Serial.print("angle: ") ;Serial.println(curr_angle);}
    if(tempd1!==){tempd1=0}
    for (curr_angle=20;curr_angle<s1;curr_angle+=10){
        fs.write(curr_angle);
        delay(50);
        tempd2=getDistance()/*sin(radians(curr_angle))*/;
        if(tempd1==0){
          tempd1=tempd2;
        }
        else if(tempd1<tempd2){
              if((tempd2*sin(radians(curr_angle)))>=20){
              d2=tempd2;
              s2=curr_angle
              break;
            }}
            else{
              tempd1=tempd2;
              // s2=curr_angle;
            }      }
      if(d1==0 || d2==0){
        return -1; //Fail khayooo :(
      }
      s=abs(s1-s2);
      // if(s<0){
      //   s*=-1;
      // }
      double c_squared=d1*d1+d2*d2-2*d1*d2*cos(radians(s));
      c_squared=(c_squared<0)? c_squared*-1:c_squared;
    return sqrt(c_squared);
      }

// double sqrt(double square){
//   if(square<0){
//     square*=-1;
//   }
//     double i=square, highest=square, lowest=0;
//   while(1){
//     if((i*i<=square+0.001) && (i*i>=square-0.001)){
//       return i;
//     }
//     if(i*i<square){
//       lowest=i;
//     }
//     else {
//       highest=i;
//     }
//     i=(highest+lowest)*0.5;
//   }


// }

void loop(){

Serial.println(calculateDistance());
// fs.write(60);
delay(200);

}
// ```