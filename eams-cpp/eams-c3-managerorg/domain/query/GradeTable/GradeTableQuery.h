#ifndef __GRADE_TABLE_QUERY_H__
#define __GRADE_TABLE_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*�ɼ�����ѯ��*/


class GradeTableQuery : public
{
	DTO_INIT(GradeTableQuery, )
};

/* query data transfer for grade list */
class GradeListQuery : public PageQuery
{
	/* initialization */
	DTO_INIT(GradeListQuery, PageQuery);

    /* maximum data in one page */
    API_DTO_FIELD_DEFAULT(Int32, max_data_count, ZH_WORDS_GETTER("grade_table.grade_list.max_data_count"));

    /* where clause condition */
    API_DTO_FIELD_DEFAULT(Int64, student_id, ZH_WORDS_GETTER("grade_table.grade_list.student_id"));
    API_DTO_FIELD_DEFAULT(Int64, grade_id, ZH_WORDS_GETTER("grade_table.grade_list.grade_id"));
    API_DTO_FIELD_DEFAULT(Int64, creator, ZH_WORDS_GETTER("grade_table.grade_list.creator"));
    API_DTO_FIELD_DEFAULT(Int64, org_id, ZH_WORDS_GETTER("grade_table.grade_list.org_id"));

    /* order by information */
    API_DTO_FIELD_DEFAULT(Boolean, order_by_student_id, ZH_WORDS_GETTER("grade_table.grade_list.group_by_student_id"));
    API_DTO_FIELD_DEFAULT(Boolean, order_by_grade_id, ZH_WORDS_GETTER("grade_table.grade_list.group_by_grade_id"));
    API_DTO_FIELD_DEFAULT(Boolean, order_by_creator, ZH_WORDS_GETTER("grade_table.grade_list.group_by_creator"));
    API_DTO_FIELD_DEFAULT(Boolean, order_by_org_id, ZH_WORDS_GETTER("grade_table.grade_list.grade_by_org_id"));
};

#include OATPP_CODEGEN_END(DTO)

#endif