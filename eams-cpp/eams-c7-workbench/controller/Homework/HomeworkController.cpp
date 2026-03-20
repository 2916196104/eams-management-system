#include "stdafx.h"
#include "HomeworkController.h"


// 布置作业
StringJsonVO::Wrapper HomeworkController::execAssignHomework(const oatpp::Object<AssignHomeworkDTO>& dto)
{
    return {};
}

HomeworkDetailJsonVO::Wrapper HomeworkController::execGetHomeworkDetail(Int64 homeworkId)
{
    return {};
}

HomeworkRecordListJsonVO::Wrapper HomeworkController::execGetHomeworkRecordList(const oatpp::Object<HomeworkRecordListQuery>& query)
{
    // 实际开发中从这里获取参数：query->homeworkId, query->status
    return {};
}

ReviewResultJsonVO::Wrapper HomeworkController::execReviewHomework(const oatpp::Object<ReviewHomeworkDTO>& dto)
{
    return {};
}