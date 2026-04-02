#pragma once
#include "Mapper.h"
#include "domain/do/homework/HomeworkRecordDO.h"

class HomeworkRecordMapper : public Mapper<shared_ptr<HomeworkRecordDO>>
{
public:
    shared_ptr<HomeworkRecordDO> mapper(ResultSet* res) const override
    {
        auto data = make_shared<HomeworkRecordDO>();
        data->setId(res->getUInt64("id"));
        data->setHomeworkId(res->getUInt64("homework_id"));
        data->setStudentId(res->getUInt64("student_id"));
        data->setContent(res->getString("content"));
        data->setImages(res->getString("images"));
        data->setAddTime(res->getString("add_time"));
        data->setScore(res->getUInt64("score"));
        data->setComment(res->getString("comment"));
        data->setCommentTime(res->getString("comment_time"));
        data->setCommentTeacher(res->getUInt64("comment_teacher"));
        return data;
    }
};