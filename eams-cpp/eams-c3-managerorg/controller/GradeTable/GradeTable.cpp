#include "stdafx.h"
#include "GradeTable.h"

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
Vector<Int64> DeleteListController::ExecDeleteListQuery(
    const DeleteListQuery::Wrapper& query,
    const PayloadDTO& payload)
{
    /* TODO: finish implementation */
    return nullptr;
}

/* Save List */
Vector<Int64> SaveListController::ExecSaveListQuery(
    const SaveListQuery::Wrapper& query,
    const PayloadDTO& payload)
{
    /* TODO: finish implementation */
    return {};
}