#ifndef __BACKHOMEWORK_QUERY_H__
#define __BACKHOMEWORK_QUERY_H__

#include "../GlobalInclude.h"
#include "domain/GlobalInclude.h"
#include "../../../../lib-oatpp/include/domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业查询类*/

class BackhomeworkQuery : public PageQuery
{
	DTO_INIT(BackhomeworkQuery, PageQuery)

class BackhomeworkQuery : public
{
	DTO_INIT(BoardManager, )
//----------------------删除作业------------------------------
	// 作业ID列表
	DTO_FIELD(List<UInt64>, homeworkIds);
	DTO_FIELD_INFO(homeworkIds) {
		info->description = ZH_WORDS_GETTER("backhomework.field.homeworkIds");
	}

	//删除类型：0-逻辑删除（默认） 1-物理删除
	DTO_FIELD(Int32, deleteType) = 0;
	DTO_FIELD_INFO(deleteType) {
		info->description = ZH_WORDS_GETTER("backhomework.field.deleteType");
	}

	//删除某一课程下的所有作业
	DTO_FIELD(UInt64, courseId);
	DTO_FIELD_INFO(courseId) {
		info->description = ZH_WORDS_GETTER("backhomework.field.courseId");
	}

	//删除某一老师的作业
	DTO_FIELD(UInt64, teacherId);
	DTO_FIELD_INFO(teacherId) {
		info->description = ZH_WORDS_GETTER("backhomework.field.teacherId");
	}

//----------------------获取作业提交列表（条件+分页）------------------------------
	// 学生ID
	DTO_FIELD(UInt64, studentId);
	DTO_FIELD_INFO(studentId) {
		info->description = ZH_WORDS_GETTER("homework.list.query.studentId");
	}

	// 提交状态：-1-全部（默认），0-未提交，1-已提交，2-已批改
	// 点评作业功能也共用此字段（1=待批改，2=已批改）
	DTO_FIELD(Int32, status) = -1;
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("homework.list.query.status");
	}

//----------------------点评作业------------------------------
	DTO_FIELD(UInt64, homeworkId);        // 作业ID
	DTO_FIELD(String, studentName);       // 学生姓名（模糊搜索）
	DTO_FIELD(Int64, startTime);          // 提交开始时间
	DTO_FIELD(Int64, endTime);            // 提交结束时间
};

#include OATPP_CODEGEN_END(DTO)

#endif