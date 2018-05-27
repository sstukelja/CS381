/*
 * UnitAI.cpp
 *
 *  Created on: Apr 2, 2017
 *      Authors: Stefan Stukelja and Alex Crupi
 *      For: CS 381 - Assignment 4
 */

#include "UnitAI.h"

UnitAI::UnitAI(Entity381* ent)
	:Aspect(ent)
{
	commands.clear();
}

UnitAI::~UnitAI()
{

}

void UnitAI::Tick(float dt)
{
	if(!commands.empty())
		commands.front()->tick(dt);
}

void UnitAI::SetCommand(Command *c)
{
	commands.clear();
	commands.push_back(c);
}

void UnitAI::AddCommand(Command *c)
{
	commands.push_back(c);
}


