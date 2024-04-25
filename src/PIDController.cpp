#include<Arduino.h>
class PIDController
{
public:
    PIDController(double Kp, double Ki, double Kd)
            : Kp(Kp), Ki(Ki), Kd(Kd), error(0.0), lastError(0.0) {}

    double calculate(double targetPosition, double currentPosition)
    {
        error = targetPosition - currentPosition;
        double pidOutput = Kp * error + Ki * error + Kd * (error - lastError);
        //lastError = error;
        return pidOutput;
    }

private:
    double Kp;
    double Ki;
    double Kd;
    double error;
    double lastError;
};