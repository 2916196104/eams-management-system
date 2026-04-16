#pragma once
#ifndef _HOMEWORK_RECORD_DAO_H_
#define _HOMEWORK_RECORD_DAO_H_

#include "BaseDAO.h"
#include "domain/do/homework/HomeworkRecordDO.h"

/**
 * 作业记录表数据访问对象
 */
class HomeworkRecordDAO : public BaseDAO
{
public:
    // 提交作业（插入记录）
    bool submit(const HomeworkRecordDO& data);
    // 按学生ID+作业ID删除提交记录
    bool deleteByStudentAndHomework(uint64_t studentId, uint64_t homeworkId);
};

#endif // !_HOMEWORK_RECORD_DAO_H_