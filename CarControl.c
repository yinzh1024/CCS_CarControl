/*
 * CarControl.c
 *
 *  Created on: 2014-5-25
 *      Author: YIN
 */
#include <msp430g2553.h>
#include "CarControl.h"
#include <stdio.h>

CarStruct myCar;

void TurnLeft(float leftReductionRatio, float rightReductionRadio)
{
	switch (myCar.wheelCount) {
		//两轮车
		case twoWheel:
			(*(myCar.wheel[frontLeft].rollDirectory)).backward(myCar.wheel[frontLeft].gpio);
			(*(myCar.wheel[frontRight].rollDirectory)).forward(myCar.wheel[frontRight].gpio);
			myCar.speed[left].speedControl(leftReductionRatio);
			myCar.speed[right].speedControl(rightReductionRadio);
			break;
		//三轮车
		case threeWheel:
			// 万向轮
			if (myCar.driveWay == rollWheel)
			{
				(*(myCar.wheel[frontLeft].rollDirectory)).backward(myCar.wheel[frontLeft].gpio);
				(*(myCar.wheel[frontRight].rollDirectory)).forward(myCar.wheel[frontRight].gpio);
			}
			// 舵机控制导向轮
			else if (myCar.driveWay == motorWheel)
			{
				(*(myCar.wheel[frontMiddle].rollDirectory)).turnLeft(45.0f); // 这还应该需要判断是前置导向轮还是后置导向轮
				(*(myCar.wheel[frontLeft].rollDirectory)).forward(myCar.wheel[frontLeft].gpio);
				(*(myCar.wheel[frontRight].rollDirectory)).forward(myCar.wheel[frontRight].gpio);
			}
			myCar.speed[left].speedControl(leftReductionRatio);
			myCar.speed[right].speedControl(rightReductionRadio);
			break;
		//四轮车
		case fourWheel:
			// 两驱
			if (myCar.driveWay == twoDrive)
			{
				(*(myCar.wheel[backLeft].rollDirectory)).backward(myCar.wheel[backLeft].gpio); // 这还应该需要判断是两轮前驱还是两轮后驱
				(*(myCar.wheel[backRight].rollDirectory)).forward(myCar.wheel[backRight].gpio);
			}
			else if (myCar.driveWay == fourDrive)
			{
				(*(myCar.wheel[frontLeft].rollDirectory)).backward(myCar.wheel[frontLeft].gpio);
				(*(myCar.wheel[backLeft].rollDirectory)).backward(myCar.wheel[backLeft].gpio);
				(*(myCar.wheel[frontRight].rollDirectory)).forward(myCar.wheel[frontRight].gpio);
				(*(myCar.wheel[backRight].rollDirectory)).forward(myCar.wheel[backRight].gpio);
			}
			myCar.speed[left].speedControl(leftReductionRatio);
			myCar.speed[right].speedControl(rightReductionRadio);
			break;
		default:
			break;
	}
}

void TurnRight(float leftReductionRatio, float rightReductionRadio)
{
	switch (myCar.wheelCount) {
		//两轮车
		case twoWheel:
			(*(myCar.wheel[frontLeft].rollDirectory)).forward(myCar.wheel[frontLeft].gpio);
			(*(myCar.wheel[frontRight].rollDirectory)).backward(myCar.wheel[frontRight].gpio);
			myCar.speed[left].speedControl(leftReductionRatio);
			myCar.speed[right].speedControl(rightReductionRadio);
			break;
		//三轮车
		case threeWheel:
			// 万向轮
			if (myCar.driveWay == rollWheel)
			{
				(*(myCar.wheel[frontLeft].rollDirectory)).forward(myCar.wheel[frontLeft].gpio);
				(*(myCar.wheel[frontRight].rollDirectory)).backward(myCar.wheel[frontRight].gpio);
			}
			// 舵机控制导向轮
			else if (myCar.driveWay == motorWheel)
			{
				(*(myCar.wheel[frontMiddle].rollDirectory)).turnRight(45.0f); // 这还应该需要判断是前置导向轮还是后置导向轮
				(*(myCar.wheel[frontLeft].rollDirectory)).forward(myCar.wheel[frontLeft].gpio);
				(*(myCar.wheel[frontRight].rollDirectory)).forward(myCar.wheel[frontRight].gpio);
			}
			myCar.speed[left].speedControl(leftReductionRatio);
			myCar.speed[right].speedControl(rightReductionRadio);
			break;
		//四轮车
		case fourWheel:
			// 两驱
			if (myCar.driveWay == twoDrive)
			{
				(*(myCar.wheel[backLeft].rollDirectory)).forward(myCar.wheel[backLeft].gpio); // 这还应该需要判断是两轮前驱还是两轮后驱
				(*(myCar.wheel[backRight].rollDirectory)).backward(myCar.wheel[backRight].gpio);;
			}
			else if (myCar.driveWay == fourDrive)
			{
				(*(myCar.wheel[frontLeft].rollDirectory)).forward(myCar.wheel[frontLeft].gpio);
				(*(myCar.wheel[backLeft].rollDirectory)).forward(myCar.wheel[backLeft].gpio);
				(*(myCar.wheel[frontRight].rollDirectory)).backward(myCar.wheel[frontRight].gpio);
				(*(myCar.wheel[backRight].rollDirectory)).backward(myCar.wheel[backRight].gpio);
			}
			myCar.speed[left].speedControl(leftReductionRatio);
			myCar.speed[right].speedControl(rightReductionRadio);
			break;
		default:
			break;
	}
}

void Forward(float reductionRadio)
{
	switch (myCar.wheelCount) {
		//两轮车
		case twoWheel:
			(*(myCar.wheel[frontLeft].rollDirectory)).forward(myCar.wheel[frontLeft].gpio);
			(*(myCar.wheel[frontRight].rollDirectory)).forward(myCar.wheel[frontRight].gpio);
			myCar.speed[left].speedControl(reductionRadio);
			myCar.speed[right].speedControl(reductionRadio);
			break;
		//三轮车
		case threeWheel:
			// 万向轮
			if (myCar.driveWay == rollWheel)
			{
				(*(myCar.wheel[frontLeft].rollDirectory)).forward(myCar.wheel[frontLeft].gpio);
				(*(myCar.wheel[frontRight].rollDirectory)).forward(myCar.wheel[frontRight].gpio);
			}
			// 舵机控制导向轮
			else if (myCar.driveWay == motorWheel)
			{
				(*(myCar.wheel[frontMiddle].rollDirectory)).toMiddle(); // 这还应该需要判断是前置导向轮还是后置导向轮
			}
			myCar.speed[left].speedControl(reductionRadio);
			myCar.speed[right].speedControl(reductionRadio);
			break;
		//四轮车
		case fourWheel:
			// 两驱
			if (myCar.driveWay == twoDrive)
			{
				(*(myCar.wheel[backLeft].rollDirectory)).forward(myCar.wheel[backLeft].gpio); // 这还应该需要判断是两轮前驱还是两轮后驱
				(*(myCar.wheel[backRight].rollDirectory)).forward(myCar.wheel[backRight].gpio);
			}
			else if (myCar.driveWay == fourDrive)
			{
				(*(myCar.wheel[frontLeft].rollDirectory)).forward(myCar.wheel[frontLeft].gpio);
				(*(myCar.wheel[backLeft].rollDirectory)).forward(myCar.wheel[backLeft].gpio);
				(*(myCar.wheel[frontRight].rollDirectory)).forward(myCar.wheel[frontRight].gpio);
				(*(myCar.wheel[backRight].rollDirectory)).forward(myCar.wheel[backRight].gpio);
			}
			myCar.speed[left].speedControl(reductionRadio);
			myCar.speed[right].speedControl(reductionRadio);
			break;
		default:
			break;
	}
}

void Backward(float reductionRadio)
{
	switch (myCar.wheelCount) {
		//两轮车
		case twoWheel:
			(*(myCar.wheel[frontLeft].rollDirectory)).backward(myCar.wheel[frontLeft].gpio);
			(*(myCar.wheel[frontRight].rollDirectory)).backward(myCar.wheel[frontRight].gpio);
			myCar.speed[left].speedControl(reductionRadio);
			myCar.speed[right].speedControl(reductionRadio);
			break;
		//三轮车
		case threeWheel:
			// 万向轮
			if (myCar.driveWay == rollWheel)
			{
				(*(myCar.wheel[frontLeft].rollDirectory)).backward(myCar.wheel[frontLeft].gpio);
				(*(myCar.wheel[frontRight].rollDirectory)).backward(myCar.wheel[frontRight].gpio);
			}
			// 舵机控制导向轮
			else if (myCar.driveWay == motorWheel)
			{
				(*(myCar.wheel[frontMiddle].rollDirectory)).toMiddle(); // 这还应该需要判断是前置导向轮还是后置导向轮
			}
			myCar.speed[left].speedControl(reductionRadio);
			myCar.speed[right].speedControl(reductionRadio);
			break;
		//四轮车
		case fourWheel:
			// 两驱
			if (myCar.driveWay == twoDrive)
			{
				(*(myCar.wheel[backLeft].rollDirectory)).backward(myCar.wheel[backLeft].gpio); // 这还应该需要判断是两轮前驱还是两轮后驱
				(*(myCar.wheel[backRight].rollDirectory)).backward(myCar.wheel[backRight].gpio);
			}
			else if (myCar.driveWay == fourDrive)
			{
				(*(myCar.wheel[frontLeft].rollDirectory)).backward(myCar.wheel[frontLeft].gpio);
				(*(myCar.wheel[backLeft].rollDirectory)).backward(myCar.wheel[backLeft].gpio);
				(*(myCar.wheel[frontRight].rollDirectory)).backward(myCar.wheel[frontRight].gpio);
				(*(myCar.wheel[backRight].rollDirectory)).backward(myCar.wheel[backRight].gpio);
			}
			myCar.speed[left].speedControl(reductionRadio);
			myCar.speed[right].speedControl(reductionRadio);
			break;
		default:
			break;
	}
}

int CarRegist(struct Car *car)
{
	if (car != NULL)
	{
		myCar = *car;
		return 1;
	}
	else
	{
		return -1;
	}
}
