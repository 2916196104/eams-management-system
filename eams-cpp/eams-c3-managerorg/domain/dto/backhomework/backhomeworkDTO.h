#ifndef _BACKHOMEWORKDTO_H_
#define _BACKHOMEWORKDTO_H_

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业DTO类*/
class Backhomework : public oatpp::DTO
{
	DTO_INIT(Backhomework, DTO)

public:
	//----------------------删除作业dto------------------------------
	API_DTO_FIELD_REQUIRE(oatpp::List<oatpp::UInt64>, homeworkIds, ZH_WORDS_GETTER("backhomework.field.homeworkIds"), true)

	// 删除类型：0-逻辑删除（默认） 1-物理删除
	DTO_FIELD(oatpp::Int32, deleteType) = 0;
	DTO_FIELD_INFO(deleteType) {
		info->description = ZH_WORDS_GETTER("backhomework.field.deleteType");
	}

	//----------------------查询作业提交列表 DTO------------------------------
	API_DTO_FIELD_REQUIRE(oatpp::UInt64, courseId, ZH_WORDS_GETTER("homework.list.query.courseId"), true)
	API_DTO_FIELD_REQUIRE(oatpp::UInt64, studentId, ZH_WORDS_GETTER("homework.list.query.studentId"), false)

	// 提交状态：-1-全部（默认），0-未提交，1-已提交，2-已批改
	DTO_FIELD(oatpp::Int32, status) = -1;
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("homework.list.query.status");
	}

	// 分页参数
	DTO_FIELD(oatpp::UInt32, pageNum) = 1;
	DTO_FIELD_INFO(pageNum) {
		info->description = ZH_WORDS_GETTER("common.pageNum");
	}

	DTO_FIELD(oatpp::UInt32, pageSize) = 10;
	DTO_FIELD_INFO(pageSize) {
		info->description = ZH_WORDS_GETTER("common.pageSize");
	}

	//----------------------点评作业------------------------------
	API_DTO_FIELD_REQUIRE(oatpp::UInt64, id, ZH_WORDS_GETTER("review.field.id"), true)
	API_DTO_FIELD_REQUIRE(oatpp::Float32, score, ZH_WORDS_GETTER("review.field.score"), false)
	API_DTO_FIELD_REQUIRE(oatpp::String, teacherComment, ZH_WORDS_GETTER("review.field.teacherComment"), false)
};

/*点评作业DTO类*/
class ReviewHomeworkDTO : public oatpp::DTO
{
	DTO_INIT(ReviewHomeworkDTO, DTO)

public:
	API_DTO_FIELD_REQUIRE(oatpp::UInt64, id, ZH_WORDS_GETTER("review.field.id"), true)
	API_DTO_FIELD_REQUIRE(oatpp::Float32, score, ZH_WORDS_GETTER("review.field.score"), false)
	API_DTO_FIELD_REQUIRE(oatpp::String, teacherComment, ZH_WORDS_GETTER("review.field.teacherComment"), false)
};

#include OATPP_CODEGEN_END(DTO)

#endif /* _BACKHOMEWORKDTO_H_ */