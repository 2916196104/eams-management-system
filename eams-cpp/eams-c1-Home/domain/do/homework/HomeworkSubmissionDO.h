#pragma once
#ifndef _HOMEWORK_SUBMISSION_DO_
#define _HOMEWORK_SUBMISSION_DO_
#include"../DoInclude.h"
class HomeworkSubmissionDO :public BaseDO {
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, homeworkId, HomeworkId); // 外键，关联HomeworkDO
    MYSQL_SYNTHESIZE(string, studentName, StudentName); 
    MYSQL_SYNTHESIZE(string, submitContent, SubmitContent); //提交作业详情 如"已经联系了三遍了"
    MYSQL_SYNTHESIZE(int, rating, Rating); // 星星数量
public:
	HomeworkSubmissionDO() :BaseDO("homework_submission") {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("homework_id", "s", homeworkId);
        MYSQL_ADD_FIELD("student_name", "s", studentName);
        MYSQL_ADD_FIELD("submit_content", "s", submitContent);
        MYSQL_ADD_FIELD("rating", "i", rating);
	}
};

typedef std::shared_ptr<HomeworkSubmissionDO> PtrHomeworkSubmissionDO;






#endif