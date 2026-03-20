#pragma once
//#include "ApiHelper.h"
//#include "Macros.h"
//#include "ServerInfo.h"
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 示例分页查询对象
 */
class StudentFilePageQuery : public PageQuery
{
	DTO_INIT(StudentFilePageQuery, PageQuery);
	//
	DTO_FIELD(String, sex);
	DTO_FIELD_INFO(sex) {
		info->description = ZH_WORDS_GETTER("StudentFile.dossier.sex");
	}
	// 姓名
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) {
		info->description = ZH_WORDS_GETTER("StudentFile.dossier.name");
	}

	DTO_FIELD(String, mobile);
	DTO_FIELD_INFO(mobile) {
		info->description = ZH_WORDS_GETTER("StudentFile.dossier.mobile");
	}
	DTO_FIELD(String, reclass);
	DTO_FIELD_INFO(reclass) {
		info->description = ZH_WORDS_GETTER("StudentFile.dossier.reclass");
	}
	
};
//class StudentFilePageQuery : public PageQuery
//{
//	DTO_INIT(StudentFilePageQuery, PageQuery);
//
//	DTO_FIELD(String, mobile);
//	DTO_FIELD_INFO(mobile) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.mobile");
//	}
//	DTO_FIELD(String, name);
//	DTO_FIELD_INFO(name) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.name");
//	}
//
//	DTO_FIELD(String, reclass);
//	DTO_FIELD_INFO(reclass) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.reclass");
//	}
//	DTO_FIELD(String, points);
//	DTO_FIELD_INFO(points) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.points");
//	}
//	DTO_FIELD(String, card);
//	DTO_FIELD_INFO(card) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.card");
//	}
//
//	DTO_FIELD(String, study);
//	DTO_FIELD_INFO(study) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.study");
//	}
//	DTO_FIELD(String, name2);
//	DTO_FIELD_INFO(name2) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.name2");
//	}
//	DTO_FIELD(String, relationship);
//	DTO_FIELD_INFO(relationship) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.relationship");
//	}
//	DTO_FIELD(String, grade);
//	DTO_FIELD_INFO(grade) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.grade");
//	}
//	DTO_FIELD(String, sex);
//	DTO_FIELD_INFO(sex) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.sex");
//	}
//	DTO_FIELD(String, old);
//	DTO_FIELD_INFO(old) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.old");
//	}
//	DTO_FIELD(String, birthday);
//	DTO_FIELD_INFO(birthday) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.birthday");
//	}
//	DTO_FIELD(String, number);
//	DTO_FIELD_INFO(number) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.number");
//	}
//	DTO_FIELD(String, time1);
//	DTO_FIELD_INFO(time1) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.time1");
//	}
//	DTO_FIELD(String, time2);
//	DTO_FIELD_INFO(time2) {
//		info->description = ZH_WORDS_GETTER("StudentFile.dossier2.time2");
//	}
//
//};

class StudentTimeTablePageQuery : public PageQuery
{
	DTO_INIT(StudentTimeTablePageQuery, PageQuery);
	//
	DTO_FIELD(String, course);
	DTO_FIELD_INFO(course) {
		info->description = ZH_WORDS_GETTER("StudentFile.class schedule.course");
	}
	DTO_FIELD(String, time);
	DTO_FIELD_INFO(time) {
		info->description = ZH_WORDS_GETTER("StudentFile.class schedule.time");
	}

	DTO_FIELD(String, state);
	DTO_FIELD_INFO(state) {
		info->description = ZH_WORDS_GETTER("StudentFile.class schedule.state");
	}
	DTO_FIELD(String, signin);
	DTO_FIELD_INFO(signin) {
		info->description = ZH_WORDS_GETTER("StudentFile.class schedule.signin");
	}

};


#include OATPP_CODEGEN_END(DTO)

