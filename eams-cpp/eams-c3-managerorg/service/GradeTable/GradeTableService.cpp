#include "stdafx.h"
#include "GradeTableService.h"

#include "dao/Grade/GradeDao.h"
#include "dao/Grade/GradeRecordDao.h"

/* Delete List */
oatpp::Vector<oatpp::Int64> DeleteListService::DeleteListQuery(
    const DeleteListQuery::Wrapper& query)
{
    std::list<std::string> str_ids;

    /* change ids into string type */
    for (auto& id : *query->ids)
        str_ids.push_back(std::to_string(id));

    GradeRecordDao grade_record_dao;
    grade_record_dao.deleteByIds<GradeRecordDO>(str_ids);

    return query->ids;
}

oatpp::Int64 SaveListService::SaveListQuery(
    const SaveListQuery::Wrapper& query)
{
    GradeRecordDO grade_record_do;
    bool id_is_null = query->id ? false : true;

    if (query->id)
        grade_record_do.setId(static_cast<int64_t>(query->id.getValue(0)));
    if (query->grade_id)
        grade_record_do.setGradeId(static_cast<int64_t>(query->grade_id.getValue(0)));
    if (query->student_id)
        grade_record_do.setStudentId(static_cast<int64_t>(query->student_id.getValue(0)));
    if (query->score)
        grade_record_do.setScore(static_cast<int8_t>(query->score.getValue(0)));
    if (query->add_time)
        grade_record_do.setAddTime(query->add_time.getValue(""));
    if (query->creator)
        grade_record_do.setCreator(static_cast<int64_t>(query->creator.getValue(0)));

    GradeRecordDao grade_record_dao;
    oatpp::Int64 return_id;

    if (id_is_null)
    {
        return_id = grade_record_dao.insertAutoPk(grade_record_do);
    }
    else
    {
        grade_record_dao.insert(grade_record_do);
        return_id = query->id;
    }

    return return_id;
}