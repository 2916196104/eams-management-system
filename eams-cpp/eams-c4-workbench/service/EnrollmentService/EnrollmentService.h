#pragma once
#ifndef ENROLLMENTSERVICE_H_
#define ENROLLMENTSERVICE_H_

#include"../../domain/dto/EnrollmentDTO/EnrollmentDTO.h"

class EnrollmentService
{
	public:
	//定义保存报名信息接口
		std::string saveEnrollment(const EnrollDTO::Wrapper& dto);
		std::string addMonths(const std::string& dateStr, int months);
};

#endif // !ENROLLMENTSERVICE_H_
