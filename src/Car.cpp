#include <Arduino.h>

class Car
{
private:
    int MOTOR_LEFT_A = 13;
    int MOTOR_LEFT_B = 12;
    int MOTOR_RIGHT_A = 11;
    int MOTOR_RIGHT_B = 10;
    int LEFT_SENSOR_PIN = 8;
    int RIGHT_SENSOR_PIN = 9;
    int MOTOR_LEFT_EN = 5;
    int MOTOR_RIGHT_EN = 3;
    int carSpeed = 0;
    int TURNSPEED = 50;

public:
    Car()
    {
        pinMode(MOTOR_LEFT_A, OUTPUT);
        pinMode(MOTOR_LEFT_B, OUTPUT);
        pinMode(MOTOR_RIGHT_A, OUTPUT);
        pinMode(MOTOR_RIGHT_B, OUTPUT);
        pinMode(MOTOR_LEFT_EN, OUTPUT);
        pinMode(MOTOR_RIGHT_EN, OUTPUT);
        pinMode(LEFT_SENSOR_PIN, INPUT);
        pinMode(RIGHT_SENSOR_PIN, INPUT);
    }

    void forward()
    {
        digitalWrite(MOTOR_LEFT_A, HIGH);
        digitalWrite(MOTOR_LEFT_B, LOW);
        digitalWrite(MOTOR_RIGHT_A, LOW);
        digitalWrite(MOTOR_RIGHT_B, HIGH);
    }

    void backward()
    {
        digitalWrite(MOTOR_LEFT_A, LOW);
        digitalWrite(MOTOR_LEFT_B, HIGH);
        digitalWrite(MOTOR_RIGHT_A, HIGH);
        digitalWrite(MOTOR_RIGHT_B, LOW);
    }

    void turnLeft()
    {
        digitalWrite(MOTOR_LEFT_A, HIGH);
        digitalWrite(MOTOR_LEFT_B, LOW);
        digitalWrite(MOTOR_RIGHT_A, HIGH);
        digitalWrite(MOTOR_RIGHT_B, LOW);
        analogWrite(MOTOR_RIGHT_EN, TURNSPEED);
        analogWrite(MOTOR_LEFT_EN, TURNSPEED);
    }

    void turnRight()
    {
        digitalWrite(MOTOR_LEFT_A, LOW);
        digitalWrite(MOTOR_LEFT_B, HIGH);
        digitalWrite(MOTOR_RIGHT_A, LOW);
        digitalWrite(MOTOR_RIGHT_B, HIGH);
        analogWrite(MOTOR_RIGHT_EN, TURNSPEED);
        analogWrite(MOTOR_LEFT_EN, TURNSPEED);
    }

    void stop()
    {
        digitalWrite(MOTOR_LEFT_A, LOW);
        digitalWrite(MOTOR_LEFT_B, LOW);
        digitalWrite(MOTOR_RIGHT_A, LOW);
        digitalWrite(MOTOR_RIGHT_B, LOW);
    }

    int leftObstacle()
    {
        return digitalRead(LEFT_SENSOR_PIN) == LOW ? 1 : 0;
    }

    int rightObstacle()
    {
        return digitalRead(RIGHT_SENSOR_PIN) == LOW ? 1 : 0;
    }

    void setSpeed(int speed) // speed 0-100
    {
        if (!speed)
        {
            carSpeed = 0;
            return;
        }
        carSpeed = map(speed, 0, 100, 100, 255);
    }

    void setTurnSpeed(int speed) // speed 0-100
    {
        if (!speed)
        {
            carSpeed = 0;
            return;
        }
        TURNSPEED = map(speed, 0, 100, 100, 255);
    }

    void updateSpeed()
    {
        analogWrite(MOTOR_RIGHT_EN, carSpeed);
        analogWrite(MOTOR_LEFT_EN, carSpeed);
    }
};