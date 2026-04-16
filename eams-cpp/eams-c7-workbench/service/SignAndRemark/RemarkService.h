#pragma once
#ifndef _REMARKSERVICE_H_
#define _REMARKSERVICE_H_

#include "domain/dto/SignAndRemark/RemarkDTO.h"
#include "domain/query/SignAndRemark/RemarkQuery.h"

class RemarkService
{
public:
	//获取点名列表
	RemarkPageDTO::Wrapper listAll(const RemarkQuery::Wrapper& query);
};

#endif // !_REMARKSERVICE_H_

