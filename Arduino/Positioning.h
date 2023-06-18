#include "Ultrasonic.h"
#include "QMC5883.h"
#include <math.h>

class Positioning
{
private:
    double *OrthoDis;
    float nowAngle = 0;
    int _UlsoNum;
    Ultrasonic *Ulso;
    DFRobot_QMC5883 MagSensor;
    int _M, _N;

public:
    Positioning(){};

    /**
     * @fn Positioning
     * @brief setup ultraSonics and magSensor
     * @return none
     * @param ultraNum Number of UltraSonic devices
     * @param Pin the TRIG and ECHO Pin for each UltraSonics
     * @param MN the length and width of the site
     */
    Positioning(const int ultraNum, const int Pin[], const int M, const int N);
    ~Positioning(){};

    /**
     * @fn setOrthoDis
     * @brief set the orthogonal distance to the four wall in the order of [north, east, south, west]
     * @return void
     * @param nowFace the direction that Potato currently faces
     */
    void setOrthoDis(int nowFace);

    /**
     * @fn getOrthoDis
     * @brief return the orthogonal distance to the four wall in the order of [north, east, south, west]
     * @return double*
     * @retval pointer to the distance array
     */
    double *getOrthoDis(void);

    /**
     * @fn getHeadingDegrees
     * @brief get the Heading Degrees of Potato relative to the North of the site
     * @return float
     * @retval the the Heading Degrees of Potato relative to the North of the site in degrees
     */
    float getHeadingDegrees(void);

    /**
     * @fn getHeadingBySonic
     * @brief get the Heading Degrees of Potato by Sonic
     * @return float
     * @retval the the Heading Degrees of Potato
     */
    float getHeadingBySonic(void);
};

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

double *Positioning::getOrthoDis(){return OrthoDis};

float Positioning::getHeadingDegrees(void) { return MagSensor.getRelativeDegrees(); }

float Positioning::getHeadingBySonic(void)
{
    int i = 0;
    float angle = 0;
    double oldDis = {};
    for (i = 0; i < _UlsoNum; i++)
        oldDis[i] = OrthoDis[i];
    setOrthoDis();
    for (i = 0; i < _UlsoNum; i++)
        oldDis[i] = OrthoDis[i] - oldDis[i];
    angle = 180 * atan(oldDis[2], oldDis[1]) / PI;
    return angle;
}
