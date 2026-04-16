#pragma once
#ifndef CLASSDETAILSERVICE_H_
#define CLASSDETAILSERVICE_H_

#include "../../domain/dto/classDTO/classDetailDTO.h"
class ClassDetailService
{

public:
	//获取班级详情数据
	ClassDetailDTO::Wrapper getClassDetail(const std::string &id);

};
#endif // !CLASSDETAILSERVICE_H_
