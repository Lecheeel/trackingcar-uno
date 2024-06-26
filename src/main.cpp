#include <Arduino.h>
#include "Car.cpp"
#include "GraySensor.cpp"
#include "PIDController.cpp"

enum GrayValue
{
  BLACK = 1,
  WHITE = 0
};

Car car;
GraySensor sensor(7, 6);                 // clock=7, data=6
PIDController pidController(5, 0.03, 2); // Kp, Ki, Kd

void setup()
{
  Serial.begin(115200);
  car.setSpeed(100);
  car.setTurnSpeed(80);
}

void pid_trackLine()
{
  int *grayValues = sensor.getGrayValues();
  double targetPosition = 4; // 预期位置
  int currentPosition = 10;  // 当前位置
  for (int i = 0, j = 0; i < 8; i++)
  {
    if (grayValues[i] == BLACK)
    {
      currentPosition = i;
      j++;
      break;
    }
    if (j > 6)
    {
      car.stop();
      return;
    }
  }

  int err = currentPosition - targetPosition;
  if (currentPosition != 10)
    Serial.print(err);
  if (err > 1)
  {
    // car.turnRight();
    car.turnLeft();
    Serial.println("left");
  }
  else if (err < 0)
  {
    // car.turnLeft();
    car.turnRight();
    Serial.println("right");
  }
  else
  {
    car.forward();
    Serial.println("forward");
  }
}

void trackLine()
{
  int *grayValues = sensor.getGrayValues();

  if ((grayValues[3] || grayValues[4]))
  {
    car.forward();
  }
  else if ((grayValues[0] || grayValues[1] || grayValues[2]) && (~grayValues[7] && ~grayValues[6] && ~grayValues[5]))
  {
    car.turnLeft();
  }
  else if ((grayValues[7] || grayValues[6] || grayValues[5]) && (~grayValues[0] && ~grayValues[1] && ~grayValues[2]))
  {
    car.turnRight();
  }

  for (int i = 0, j = 0; i < 7; i++)
  {
    if (grayValues[i] && grayValues[i + 1])
      j++;

    if (j > 6)
    {
      car.stop();
      return;
    }
  }
}

void avoidObstacle()
{
  if (car.leftObstacle() && !car.rightObstacle())
  {
    car.turnRight();
  }
  else if (!car.leftObstacle() && car.rightObstacle())
  {
    car.turnLeft();
  }
  else if (car.leftObstacle() && car.rightObstacle())
  {
    car.backward();
  }
  else
  {
    car.forward();
  }
}

void loop()
{
  // car.updateSpeed();
  //  //trackLine();
  avoidObstacle();
  //pid_trackLine();
  // // trackLine();

  // car.forward();
  //  delay(1000);
  //  // car.setSpeed(100);
  //  delay(1000);
  // car.backward();
  //  delay(1000);
  //  car.turnLeft(200);
  //  delay(1000);
  //  car.turnRight(200);
  //  delay(1000);
  //  car.stop();
  //  delay(5000);

  // car.turnLeft();
  //   for(int i=0;i<100;i++){

  //   // Serial.println("speed: "+(String)i);
  //   car.setTurnSpeed(i);
  //   car.turnLeft();
  //   delay(50);
  // }
  // car.stop();

  // delay(5000);
}