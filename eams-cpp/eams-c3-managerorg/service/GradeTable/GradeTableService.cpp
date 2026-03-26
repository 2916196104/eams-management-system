#include "stdafx.h"
#include "GradeTableService.h"

#include "dao/Grade/GradeDAO.h"
#include "dao/Grade/GradeRecordDao.h"

/* Delete List */
oatpp::Vector<oatpp::Int64> DeleteListService::DeleteListQuery(
    const DeleteListQuery::Wrapper& query)
{
    std::list<std::string> str_ids;

    /* change ids into string type */
    for (auto& id : *query->ids)
        str_ids.push_back(std::to_string(id));
    
    //GradeDAO grade_dao;
    //GradeRecordDAO grade_record_dao;

    //grade_dao.deleteByIds<GradeDO>(str_ids);
    //grade_record_dao.deleteByIds<GradeRecordDO>(str_ids);

    return query->ids;
}