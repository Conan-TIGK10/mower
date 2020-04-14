#include <math.h>

struct Point{
    float x;
    float y;
  };

struct TwoMatrix{
    Point row1;
    Point row2;
  };

TwoMatrix rotationMatrix;
Point enhetVector;
uint16_t angle;
uint8_t distance;
Point currentPosition;


void setupVisual(void){
    enhetVector.x = 1;
    enhetVector.y = 0;
    currentPosition.x = 0;
    currentPosition.y = 0;
    angle = 0;
  
  }

void updateVisual(double rotation){
    calcAngle(rotation);
    calcEnhetVector();

    if(distance != 0){
        calcCurrentPosition();
      }
}

void setDistance(uint8_t dist){
      distance = dist;
  }

void calcCurrentPosition(void){
  
    distance = 0;
  }

void calcAngle(double rotation){
    if(rotation < 0)
        angle = rotation+360;
    else
        angle = rotation;
  }

void calcEnhetVector(){
    setRotationMatrix();
    calcMatrixOnVector(); 
  }

void setRotationMatrix(){
    Serial.print("Angle: ");
    Serial.println(angle);
    rotationMatrix.row1.x = cos(angle);
    rotationMatrix.row1.y = -sin(angle);
    rotationMatrix.row2.x = sin(angle);
    rotationMatrix.row2.y = cos(angle);
  }
  
void calcMatrixOnVector(){
    enhetVector.x = 1;
    enhetVector.y = 0;
    enhetVector.x = ((enhetVector.x * rotationMatrix.row1.x) + (enhetVector.y * rotationMatrix.row2.x));
    enhetVector.y = ((enhetVector.x * rotationMatrix.row2.y) + (enhetVector.y * rotationMatrix.row2.y));

  /*  Serial.print("X: ");
    Serial.println(enhetVector.x);
    Serial.print("Y: ");
    Serial.println(enhetVector.y);
        Serial.print("X: ");
    Serial.println(rotationMatrix.row1.x);
    Serial.print("Y: ");
    Serial.println(rotationMatrix.row1.y);
        Serial.print("X: ");
    Serial.println(rotationMatrix.row2.x);
    Serial.print("Y: ");
    Serial.println(rotationMatrix.row2.y);*/

    
  
  }

  
