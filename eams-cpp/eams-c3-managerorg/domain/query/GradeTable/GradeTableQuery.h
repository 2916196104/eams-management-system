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

/* Delete List */
class DeleteListQuery : public PageQuery
{
	DTO_INIT(DeleteListQuery, PageQuery);

	DTO_FIELD(Vector<Int64>, ids);
	DTO_FIELD_INFO(ids)
	{
		info->description = ZH_WORDS_GETTER("grade_table.delete.ids");
	}
};

/* Save List */
class SaveListQuery : public PageQuery
{
	DTO_INIT(SaveListQuery, PageQuery);

	DTO_FIELD(Int64, id);
	DTO_FIELD_INFO(id)
	{
		info->description = ZH_WORDS_GETTER("grade_table.save.id");
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif