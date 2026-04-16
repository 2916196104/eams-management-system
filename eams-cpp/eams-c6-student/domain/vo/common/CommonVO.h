#pragma once
#ifndef __COMMON_VO_H__
#define __COMMON_VO_H__ 
#include"../../GlobalInclude.h"
#include"../../dto/common/CommonDTO.h"
#include "oatpp/core/macro/codegen.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)
class StudentJsonVO:public JsonVO<StudentDTO::Wrapper>
{
public:
    DTO_INIT(StudentJsonVO, JsonVO<StudentDTO::Wrapper>)
};
class RegistrationPageJsonVO:public JsonVO<RegistrationPageDTO::Wrapper>
{
public:
    DTO_INIT(RegistrationPageJsonVO, JsonVO<RegistrationPageDTO::Wrapper>)
};
class FileJsonVO:public JsonVO<FileOnlyDTO::Wrapper>
{
public:
    DTO_INIT(FileJsonVO, JsonVO<FileOnlyDTO::Wrapper>)
};
class PayFeesJsonVO :public JsonVO<PayFeesDTO::Wrapper> {
    DTO_INIT(PayFeesJsonVO,JsonVO<PayFeesDTO::Wrapper>)
};
class RefundJsonVO :public JsonVO<RefundDTO::Wrapper> {
    DTO_INIT(RefundJsonVO, JsonVO<RefundDTO::Wrapper>)
};

class CourseCountJsonVO : public JsonVO<CourseCountDTO::Wrapper> {
public:
    DTO_INIT(CourseCountJsonVO, JsonVO<CourseCountDTO::Wrapper>)
};





/**
 * 示例分页显示JsonVO，用于响应给客户端的Json对象
 */
class QueryFollowUprecordsJsonVO : public JsonVO<QueryFollowUprecordsDTO::Wrapper> {
    DTO_INIT(QueryFollowUprecordsJsonVO, JsonVO<QueryFollowUprecordsDTO::Wrapper>);
};


/**
 * 班级列表响应VO
 **/
class getClassListPageJsonVO : public JsonVO<getClassListPageDTO::Wrapper> {
    DTO_INIT(getClassListPageJsonVO, JsonVO<getClassListPageDTO::Wrapper>);
};

/**
 * 课程统计响应VO
 **/
class getCourseStatisticsPageJsonVO : public JsonVO<getCourseStatisticsPageDTO::Wrapper> {
    DTO_INIT(getCourseStatisticsPageJsonVO, JsonVO<getCourseStatisticsPageDTO::Wrapper>);
};

/**
 * 加入班级响应VO
 */
class JoinclassJsonVO : public JsonVO<JoinclassDTO::Wrapper> {
    DTO_INIT(JoinclassJsonVO, JsonVO<JoinclassDTO::Wrapper>);
};
/**
 * 加入班级分页查询响应VO
 */
class JoinclassPageJsonVO : public JsonVO<JoinclassPageDTO::Wrapper> {
    DTO_INIT(JoinclassPageJsonVO, JsonVO<JoinclassPageDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)
#endif