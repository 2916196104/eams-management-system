#pragma once
#ifndef _HOMEWORKRECORD_DAO_H_
#define _HOMEWORKRECORD_DAO_H_

#include "BaseDAO.h"
#include "../../domain/do/homework/HomeworkRecordDO.h"
#include "../../domain/query/backhomework/backhomeworkQuery.h"

class HomeworkRecordDAO : public BaseDAO
{
public:
    //分页查询作业提交记录
    std::list<PtrHomeworkRecordDO> getSendHomeworkList(const BackhomeworkQuery::Wrapper& query);

    //统计作业提交记录总数
    uint64_t countSendHomework(const BackhomeworkQuery::Wrapper& query);

    // 根据 ID 查询单条提交记录
    PtrHomeworkRecordDO getSendHomeworkById(oatpp::UInt64 id);

    //更新点评信息（comment, score, comment_teacher, comment_time）
    bool updateComment(const HomeworkRecordDO& record);
};

#endif // _HOMEWORKRECORD_DAO_H_
