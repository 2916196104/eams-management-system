#pragma once
#ifndef _HOMEWORK_RECORD_DAO_H_
#define _HOMEWORK_RECORD_DAO_H_

#include "BaseDAO.h"
#include "../../domain/do/Homework/HomeworkRecordDO.h"

class HomeworkRecordDAO : public BaseDAO
{
public:
    // 插入提交记录
    bool insert(HomeworkRecordDO& record);
    // 根据ID查询记录
    PtrHomeworkRecordDO selectById(uint64_t id);
    // 根据作业ID查询所有提交记录
    std::list<HomeworkRecordDO> selectByHomeworkId(uint64_t homeworkId);
    // 根据作业ID和学生ID查询提交记录
    PtrHomeworkRecordDO selectByHomeworkIdAndStudentId(uint64_t homeworkId, int64_t studentId);
    // 更新提交记录（用于点评）
    bool update(const HomeworkRecordDO& record);
};

#endif // _HOMEWORK_RECORD_DAO_H_