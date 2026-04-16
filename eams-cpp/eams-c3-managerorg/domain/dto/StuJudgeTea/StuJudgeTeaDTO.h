#ifndef __STU_JUDGE_TEA_DTO_H__
#define __STU_JUDGE_TEA_DTO_H__

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//学评教DTO
class StuJudgeTeaDTO : public oatpp::DTO
{
	DTO_INIT(StuJudgeTeaDTO, DTO)

		// 1. 主键ID（学评教记录唯一标识）
		API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("StuJudgeTeaDTO.id"))

		// 2. 学员信息
		API_DTO_FIELD_DEFAULT(UInt64, studentId, ZH_WORDS_GETTER("StuJudgeTeaDTO.studentId"))
		API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("StuJudgeTeaDTO.studentName"))

		// 3. 授课老师信息
		API_DTO_FIELD_DEFAULT(UInt64, teacherId, ZH_WORDS_GETTER("StuJudgeTeaDTO.teacherId"))
		API_DTO_FIELD_DEFAULT(String, teacherName, ZH_WORDS_GETTER("StuJudgeTeaDTO.teacherName"))

		// 4. 课次信息
		API_DTO_FIELD_DEFAULT(UInt64, lessonId, ZH_WORDS_GETTER("StuJudgeTeaDTO.lessonId"))
		API_DTO_FIELD_DEFAULT(String, lessonTitle, ZH_WORDS_GETTER("StuJudgeTeaDTO.lessonTitle"))

		// 5. 评分项（均为1-5星，用UInt32存储星级数）
		API_DTO_FIELD_DEFAULT(UInt32, comprehensiveScore, ZH_WORDS_GETTER("StuJudgeTeaDTO.comprehensiveScore"))
		API_DTO_FIELD_DEFAULT(UInt32, classAtmosphere, ZH_WORDS_GETTER("StuJudgeTeaDTO.classAtmosphere"))
		API_DTO_FIELD_DEFAULT(UInt32, teachingAttitude, ZH_WORDS_GETTER("StuJudgeTeaDTO.teachingAttitude"))
		API_DTO_FIELD_DEFAULT(UInt32, teachingEffect, ZH_WORDS_GETTER("StuJudgeTeaDTO.teachingEffect"))

		// 6. 评价内容
		API_DTO_FIELD_DEFAULT(String, evaluateContent, ZH_WORDS_GETTER("StuJudgeTeaDTO.evaluateContent"))

		// 7. 评价时间（格式：yyyy-MM-dd HH:mm:ss）
		API_DTO_FIELD_DEFAULT(String, evaluateTime, ZH_WORDS_GETTER("StuJudgeTeaDTO.evaluateTime"))
		// 8. 教师所属组织id
		API_DTO_FIELD_DEFAULT(UInt64, orgId, ZH_WORDS_GETTER("StuJudgeTeaDTO.orgId"))
		API_DTO_FIELD_DEFAULT(String, orgName, ZH_WORDS_GETTER("StuJudgeTeaDTO.orgName"))
		// 9. 是否匿名
		API_DTO_FIELD_DEFAULT(Int8, anonymity, ZH_WORDS_GETTER("StuJudgeTeaDTO.anonymity"))
};

//学评教分页类
class StuJudgeTeaPageDTO : public PageDTO<StuJudgeTeaDTO::Wrapper>
{
	DTO_INIT(StuJudgeTeaPageDTO, PageDTO<StuJudgeTeaDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif