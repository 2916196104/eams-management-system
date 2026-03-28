#pragma once
#ifndef ROLLCALLRECORDSERVICE_H
#define ROLLCALLRECORDSERVICE_H

#include "domain/vo/huitailang-vo/rollcallvo.h"
#include "domain/query/huitailang-query/rollcallquery.h"
#include "domain/dto/huitailang-dto/rollcalldto.h"


class RollcallrecordService
{
public:
	// 分页查询所有数据
	rollcallPageDTO::Wrapper listAll(const RollcallQuery::Wrapper& query);

};


#endif