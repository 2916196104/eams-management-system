#ifndef __GRADE_TABLE_DTO_H__
#define __GRADE_TABLE_DTO_H__

#include "domain/GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*�ɼ���DTO��*/


class GradeTableDTO : public oatpp::DTO
{
	DTO_INIT(GradeTableDTO, DTO);
};

class RecordDTO : public oatpp::DTO
{
	DTO_INIT(RecordDTO, DTO);

	DTO_FIELD(Int64, gradeId);
	DTO_FIELD_INFO(gradeId)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.grade_id");
	}

	DTO_FIELD(String, gradeTitle);
	DTO_FIELD_INFO(gradeTitle)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.grade_title");
	}

	DTO_FIELD(String, studentName);
	DTO_FIELD_INFO(studentName)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.student_name");
	}

	DTO_FIELD(Int8, score);
	DTO_FIELD_INFO(score)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.score");
	}

	//DTO_FIELD(Int64, grade_id, "grade_id");
	//DTO_FIELD(String, grade_title, "grade_title");
	//DTO_FIELD(String, student_name, "student_name");
	//DTO_FIELD(Int8, score, "score");
};

class RecordListDTO : public oatpp::DTO
{
	/* GradeDTO extends from DTO */
	DTO_INIT(RecordListDTO, DTO);

	DTO_FIELD(Int64, page);
	DTO_FIELD_INFO(page)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.page");
	}

	DTO_FIELD(Int64, pageCount);
	DTO_FIELD_INFO(pageCount)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.page_count");
	}

	DTO_FIELD(Int64, pageSize);
	DTO_FIELD_INFO(pageSize)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.page_size");
	}

	DTO_FIELD(Vector<RecordDTO::Wrapper>, records);
	DTO_FIELD_INFO(records)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.records");
	}

	DTO_FIELD(Int64, total);
	DTO_FIELD_INFO(total)
	{
		info->description = ZH_WORDS_GETTER("grade_table.record_list.total");
	}

	//DTO_FIELD(Int64, page, "page");
	//DTO_FIELD(Int64, pageCount, "page_count");
	//DTO_FIELD(Int64, pageSize, "page_size");
	//DTO_FIELD(Vector<RecordDTO::Wrapper>, records, "records");
	//DTO_FIELD(Int64, total, "total");
};

#include OATPP_CODEGEN_END(DTO)

#endif