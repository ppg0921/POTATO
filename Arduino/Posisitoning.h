#include <Ultrasonic.h>
#include <QMC5883.h>

class Positioning
{
private:
    double* OrthoDis;
    float nowAngle = 0;
    int _UlsoNum;
    Ultrasonic *Ulso;
    DFRobot_QMC5883 MagSensor;
    int _M, _N;
public:
    Positioning(){};
    Positioning(const int, const int[], const int M, const int N);
    ~Positioning(){};
    void setOrthoDis(int);
    double* getOrthoDis(int);
    float getHeadingDegrees(void);
}

Positioning::Positioning(const int UlsoNum, const int UlsoPin[], const int M, const int N)
{
    _UlsoNum = UlsoNum;
    _M = M;
    _N = N;
    OrthoDis = new double[UlsoNum];
    Ulso = new Ultrasonic[UlsoNum];
    int i = 0, t = 0, e = 0;
    for (i = 0; i < UlsoNum; i++)
    {
        t = UlsoPin[2 * i];
        e = UlsoPin[2 * i + 1];
        Ulso[i] = Ultrasonic(t, e);
    }
    MagSensor.Setup();
}

void Positioning::setOrthoDis(int nowFace)
{
    int i = 0;
    double rawDis[4] = {};
    for (i = 0; i < 4; i++)
        rawDis[i] = Ulso[i].getdist();
    for (i = 0; i < 4; i++)
    {
        if ((i + nowFace) % 2 == 1)
            OrthoDis[(i + nowFace) % 4] = double(_M) * rawDis[i] / (rawDis[i] + rawDis[(i + 2) % 4]);
        else
            OrthoDis[(i + nowFace) % 4] = double(_N) * rawDis[i] / (rawDis[i] + rawDis[(i + 2) % 4]);
    }
    return;
}

double* Positioning::getOrthoDis() {return OrthoDis};

float Positioning::getHeadingDegrees(void) {return MagSensor.getRelativeDegrees();}






