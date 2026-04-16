#ifndef __TeaJudgeStuDTO_H__
#define __TeaJudgeStuDTO_H__

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//教评学DTO
class TeaJudgeStuDTO : public oatpp::DTO
{
    DTO_INIT(TeaJudgeStuDTO, DTO);

        // 1. 主键ID（教评学记录唯一标识）
    API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("TeaJudgeStuDTO.id"));

        // 2. 学员信息
    API_DTO_FIELD_DEFAULT(UInt64, studentId, ZH_WORDS_GETTER("TeaJudgeStuDTO.studentId"));
    API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("TeaJudgeStuDTO.studentName"));

        // 3. 课次信息
    API_DTO_FIELD_DEFAULT(UInt64, lessonId, ZH_WORDS_GETTER("TeaJudgeStuDTO.lessonId"));
    API_DTO_FIELD_DEFAULT(String, lessonTitle, ZH_WORDS_GETTER("TeaJudgeStuDTO.lessonTitle"));

        // 4. 点评核心信息
    API_DTO_FIELD_DEFAULT(UInt32, evaluateScore, ZH_WORDS_GETTER("TeaJudgeStuDTO.evaluateScore"));
    API_DTO_FIELD_DEFAULT(String, evaluateContent, ZH_WORDS_GETTER("TeaJudgeStuDTO.evaluateContent"));
    API_DTO_FIELD_DEFAULT(String, lessonImage, ZH_WORDS_GETTER("TeaJudgeStuDTO.lessonImage"));

        // 5. 点评老师信息
    API_DTO_FIELD_DEFAULT(UInt64, teacherId, ZH_WORDS_GETTER("TeaJudgeStuDTO.teacherId"));
    API_DTO_FIELD_DEFAULT(String, teacherName, ZH_WORDS_GETTER("TeaJudgeStuDTO.teacherName"));

        // 6. 点评时间
    API_DTO_FIELD_DEFAULT(String, evaluateTime, ZH_WORDS_GETTER("TeaJudgeStuDTO.evaluateTime"));
};

//教评学分页类
class TeaJudgeStuPageDTO : public PageDTO<TeaJudgeStuDTO::Wrapper>
{
    DTO_INIT(TeaJudgeStuPageDTO, PageDTO<TeaJudgeStuDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif