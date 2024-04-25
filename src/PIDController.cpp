#include<Arduino.h>
class PIDController
{
public:
    PIDController(double Kp, double Ki, double Kd)
            : Kp(Kp), Ki(Ki), Kd(Kd), error(0.0), lastError(0.0) {}

    double calculate(double targetPosition, double currentPosition)
    {
        error = targetPosition - currentPosition;
        Serial.println(error);
        double pidOutput = Kp * error + Ki * error + Kd * (error - lastError);
        lastError = error;
        //lastError=0;
        return pidOutput;
    }

private:
    double Kp;
    double Ki;
    double Kd;
    double error;
    double lastError;
};