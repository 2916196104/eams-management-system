#pragma once
#ifndef __GRADE_TABLE_QUERY_H__
#define __GRADE_TABLE_QUERY_H__

#include "domain/GlobalInclude.h" 
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

//成绩单查询类：接收前端筛选+分页参数（所有字段非必传）
class GradeTableQuery : public PageQuery
{
    DTO_INIT(GradeTableQuery, PageQuery);

    // 1. 考核项（模糊查询，非必传）
    API_DTO_FIELD_DEFAULT(String, itemName, ZH_WORDS_GETTER("GradeTableDTO.itemName"));
    // 2. 发布者ID（精准查询，非必传）
    API_DTO_FIELD_DEFAULT(UInt64, publisherId, ZH_WORDS_GETTER("GradeTableDTO.publisherId"));
    // 3. 发布时间范围（非必传）
    API_DTO_FIELD_DEFAULT(String, startPublishTime, ZH_WORDS_GETTER("GradeTableDTO.startPublishTime"));
    API_DTO_FIELD_DEFAULT(String, endPublishTime, ZH_WORDS_GETTER("GradeTableDTO.endPublishTime"));
};


/* Delete List */
class DeleteListQuery : public PageQuery
{
	DTO_INIT(DeleteListQuery, PageQuery);

	API_DTO_FIELD_DEFAULT(Vector<Int64>, ids, ZH_WORDS_GETTER("grade_table.delete.ids"));
};

/* Save List */
class SaveListQuery : public PageQuery
{
	DTO_INIT(SaveListQuery, PageQuery);

	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("grade_table.save.id"));
    API_DTO_FIELD_DEFAULT(Int64, grade_id, ZH_WORDS_GETTER("grade_table.save.grade_id"));
    API_DTO_FIELD_DEFAULT(Int64, student_id, ZH_WORDS_GETTER("grade_table.save.student_id"));
    API_DTO_FIELD_DEFAULT(Int32, score, ZH_WORDS_GETTER("grade_table.save.score"));
    API_DTO_FIELD_DEFAULT(String, add_time, ZH_WORDS_GETTER("grade_table.save.add_time"));
    API_DTO_FIELD_DEFAULT(Int64, creator, ZH_WORDS_GETTER("grade_table.save.creator"));
};

#include OATPP_CODEGEN_END(DTO)

#endif 