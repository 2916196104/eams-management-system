#include "stdafx.h"
#include "GradeTable.h"

#include "service/GradeTable/GradeTableService.h"

/**
 * 分页查询成绩单列表执行函数实现
 * @param query 查询参数对象
 * @return 空实现，后续填充业务逻辑
 */
GradeTablePageJsonVO::Wrapper GradeTable::execQueryPageGradeTable(const GradeTableQuery::Wrapper& query)
{
    return {};
}

/* Delete List */
DeleteListJsonVO::Wrapper DeleteListController::ExecDeleteListQuery(
    const DeleteListQuery::Wrapper& query)
{
    DeleteListJsonVO::Wrapper vo = DeleteListJsonVO::createShared();

    if (!query || !query->ids || query->ids->empty())
    {
        auto empty = oatpp::Vector<oatpp::Int64>::createShared();
        vo->init(empty, RS_PARAMS_INVALID);
        return vo;
    }

    DeleteListService dls;
    vo->success(dls.DeleteListQuery(query));

    return vo;
}

/* Save List */
SaveListJsonVO::Wrapper SaveListController::ExecSaveListQuery(
    const SaveListQuery::Wrapper& query)
{
    SaveListJsonVO::Wrapper vo = SaveListJsonVO::createShared();

    if (!query)
    {
        oatpp::Int64 empty = -1;
        vo->init(empty, RS_FAIL);
        return vo;
    }

    SaveListService sls;
    vo->success(sls.SaveListQuery(query));

    return vo;
}