/*
 @Author: abinng
 @Date: 2026/03/23 18:41:24
 @File: RegistrationService.h
*/
#pragma once

#ifndef _REGISTRATION_SERVICE_H_
#define _REGISTRATION_SERVICE_H_ 

#include "domain/dto/registration-records/registrationDTO.h"
#include "domain/query/registration-records/registrationquery.h"

class RegistrationService
{
public:
    // 分页查询学生成绩
    RegistrationRecordPageDTO::Wrapper listAll(const RegistrationRecordQuery::Wrapper& query);
};


#endif // !_REGISTRATION_SERVICE_H_