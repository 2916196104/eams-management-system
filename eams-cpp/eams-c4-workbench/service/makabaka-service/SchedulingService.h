#pragma once
#ifndef _SCHEDULINGSERVICE_H_
#define _SCHEDULINGSERVICE_H_

#include"domain/dto/makabaka-dto/RepeatedSchedulingDTO.h"
#include"domain/dto/makabaka-dto/FreeSchedulingDTO.h"
class PayloadDTO;

class SchedulingService {
public:
	// 添加重复排课计划
	bool addRepeatScheduling(const RepeatedSchedulingDTO::Wrapper& dto, const PayloadDTO& payload);
	// 添加自由排课计划
	bool addFreeScheduling(const FreeSchedulingDTO::Wrapper& dto, const PayloadDTO& payload);
};

#endif // !_SCHEDULINGSERVICE_H_