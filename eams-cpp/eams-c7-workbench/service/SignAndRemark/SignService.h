#pragma once
#ifndef _SIGNSERVICE_H_
#define _SIGNSERVICE_H_

#include "domain/dto/SignAndRemark/SignDTO.h"
#include "domain/query/SignAndRemark/SignQuery.h"

class SignService
{
public:
	//获取点名列表
	SignPageDTO::Wrapper listAll(const SignQuery::Wrapper& query);
};

#endif
