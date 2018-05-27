/*
 * Utils.h
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 *
 *      Used by: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 3
 */

#ifndef UTILS_H_
#define UTILS_H_


inline float clamp(float value, float lower, float upper)
{
	if (value > upper)
		return upper;
	if (value < lower)
		return lower;

	return value;
}

inline float makeAnglePosNeg(float angle)
{
    while (angle > Ogre::Math::PI)
        angle -= Ogre::Math::TWO_PI;
    while (angle < -Ogre::Math::PI)
        angle += Ogre::Math::TWO_PI;

    return angle;
}

inline float FixAngle(float radiansAngle)
{

	while (radiansAngle > Ogre::Math::TWO_PI)
		radiansAngle -= Ogre::Math::TWO_PI;
	while (radiansAngle < 0)
		radiansAngle += Ogre::Math::TWO_PI;

	return radiansAngle;
}

inline float differenceBetweenAngles(float angle1, float angle2)
{
    return makeAnglePosNeg(angle1 - angle2);
}

#endif /* UTILS_H_ */
