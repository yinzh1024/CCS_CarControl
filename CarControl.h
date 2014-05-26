#ifndef _CAR_CONTROL_H_
#define _CAR_CONTROL_H_

enum CarSpeedControlDirectory
{
	left = 0,
	right
};

enum CarDriveWay
{
	//轮子数
	twoWheel = 2,
	threeWheel,
	fourWheel,
	//驱动方式
	rollWheel = 2, // 万向轮
	motorWheel = 3,// 舵机
	twoDrive = 2,  // 四轮两驱
	fourDrive = 4  // 四轮四驱
};

enum CarWheelDirectory
{
	frontMiddle = 0,
	backMiddle,
	frontLeft = 0,
	frontRight,
	backLeft,
	backRight
};

struct CarWheelRollDirectory
{
	void (*forward)(int gpio);
	void (*backward)(int gpio);
	//导向舵机转动方向控制
	void (*turnLeft)(float turnAngle);
	void (*turnRight)(float turnAngle);
	void (*toMiddle)(void);
};

struct CarSpeedControler
{
	//全功率输出时的PWM值
	int fullPWMValue;
	//全功率转速
	int fullPowerRPM;
	//速度控制函数, 参数为减速比
	void (*speedControl)(float);
};

struct CarWheel
{
	char *name;
	int gpio;
	//轮子的转动方向控制
	struct CarWheelRollDirectory *rollDirectory;
};

typedef struct Car
{
  //小车行动轮个数
  int wheelCount;
  //小车驱动方式
  int driveWay;
  //小车的车轮结构数组
  struct CarWheel *wheel;
  struct CarSpeedControler *speed;
}CarStruct;


extern void TurnLeft(float leftReductionRatio, float rightReductionRadio);
extern void TurnRight(float leftReductionRatio, float rightReductionRadio);
extern int CarRegist(struct Car *car);

#endif
