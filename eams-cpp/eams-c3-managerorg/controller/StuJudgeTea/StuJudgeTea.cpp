#include "stdafx.h"       // ? 预编译头必须放在第一个
#include "StuJudgeTea.h"
#include "service/StuJudgeTea/StuJudgeTeaService.h"


// 实现获取学评教列表执行函数（空实现占位）
StuJudgeTeaPageJsonVO::Wrapper StuJudgeTea::execQueryPageStuJudgeTea(const StuJudgeTeaQuery::Wrapper& query)
{
    auto result = StuJudgeTeaService().listAll(query);
    auto jvo = StuJudgeTeaPageJsonVO::createShared();
    jvo->success(result);
    return jvo;
}