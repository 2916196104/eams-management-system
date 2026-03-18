#ifndef __GRADE_TABLE_QUERY_H__
#define __GRADE_TABLE_QUERY_H__

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*�ɼ�����ѯ��*/


class GradeTableQuery : public PageQuery
{
    DTO_INIT(GradeTableQuery, PageQuery);
};

/* query data transfer for grade list */
class RecordListQuery : public PageQuery
{
	/* initialization */
	DTO_INIT(RecordListQuery, PageQuery);

	DTO_FIELD(Int64, gradeId);
	DTO_FIELD_INFO(gradeId)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.grade_id");
	}

	DTO_FIELD(Int64, page);
	DTO_FIELD_INFO(page)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.page");
	}

	DTO_FIELD(Int64, pageSize);
	DTO_FIELD_INFO(pageSize)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.page_size");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif