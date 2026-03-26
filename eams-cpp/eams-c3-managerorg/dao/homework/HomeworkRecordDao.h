#pragma once

#ifndef _HOMEWORK_DAO_
#define _HOMEWORK_DAO_
#include "BaseDAO.h"
#include "../../domain/do/homework/HomeworkRecordDO.h"
#include "../../domain/do/homework/HomeworkDO.h"
#include "../../domain/query/backhomework/backhomeworkQuery.h"
#include "../../domain/dto/backhomework/backhomeworkDTO.h"
#include "HomeworkDao.h"
#include "HomeworkMapper.h"

/**
 * 本人负责实现获取作业列表（条件+分页），获取作业详情，保存作业三个功能
 * 本人也负责homeworkrecord表的数据库操作实现，但上述的三个功能是用到homework表
 * 这个表现在没有用到，但后续可能会用到
 */
class HomeworkRecordDAO : public BaseDAO
{

};
#endif // !_HOMEWORK_DAO_
