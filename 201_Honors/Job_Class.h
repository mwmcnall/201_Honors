#pragma once
#ifndef JOB_CLASS_H
#define JOB_CLASS_H

#include "Hero.h"
class Job_Class
{
public:
	Hero Create_Fighter();
	Hero Create_B_Belt();
	Hero Create_Thief();
	Hero Create_R_Mage();
	Hero Create_W_Mage();
	Hero Create_B_Mage();
};

#endif