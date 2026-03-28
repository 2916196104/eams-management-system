#pragma once
#ifndef _REGISTERSERVICE_H_
#define _REGISTERSERVICE_H_

#include "../../domain/dto/course/RegisterDTO.h"

class RegisterService
{
public:
    std::string saveReg(const RegisterAddDTO::Wrapper& dto);
};

#endif