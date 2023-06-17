// Ultrasonic module: HCSR04
#include <math.h>

#define PI 3.1415926535897932384626433832795

class Ultrasonic
{
private:
  int trig, echo;
  int timeout = 30000;
  double orthoDis;
public:
  Ultrasonic() {}
  Ultrasonic(const int, const int);
  ~Ultrasonic() {}
  int getdist();
  double getOrthoDis();

};

Ultrasonic::Ultrasonic(const int t, const int e)
{
  pinMode(t, OUTPUT);
  pinMode(e, INPUT);
  trig = t;
  echo = e;
}

int Ultrasonic::getdist()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  return 0.017 * pulseIn(echo, HIGH, timeout);
}

double Ultrasonic::getOrthoDis()
{ 
  return orthoDis; 
}

// void set_orthoDis(Ultrasonic ulso[4], double orthoDis[4], int M, int N, int nowFace)
// {
//   // double *orthoDis = new double[4];
//   int i = 0;
//   double rawDis[4] = {};
//   for (i = 0; i < 4; i++)
//     rawDis[i] = ulso[i].getdist();
//   for (i = 0; i < 4; i++)
//   {
//     if ((i + nowFace) % 2 == 1)
//       orthoDis[(i + nowFace) % 4] = double(M) * rawDis[i] / (rawDis[i] + rawDis[(i + 2) % 4]);
//     else
//       orthoDis[(i + nowFace) % 4] = double(N) * rawDis[i] / (rawDis[i] + rawDis[(i + 2) % 4]);
//   }
//   return;
// }

// double get_angle(double orDisNow[4], double orDisOld[4])  // change into counterclockwise
// {
//   double vector[2] = {orDisNow[3] - orDisOld[3], orDisNow[2] - orDisOld[2]};
//   double angleWy = acos(vector[1] / sqrt(pow((vector[0]), 2) + pow(vector[1], 2))) * 180 / PI;
//   return (vector[0] < 0) ? (360 - angleWy) : angleWy;
// }

