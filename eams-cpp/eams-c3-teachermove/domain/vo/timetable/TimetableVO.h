#ifndef __TIMETABLE_VO_H__
#define __TIMETABLE_VO_H__

#include "domain/GlobalInclude.h"

#include "domain/dto/timetable/TimetableDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

///*课表视图类*/
//class TimetableVO : public 
//{
//	DTO_INIT(TimetableVO, )
//};


/* 设置设置上课状态的返回值 */
class SetStudyStatusRspJsonVO : public JsonVO<SetStudyStatusRspDTO::Wrapper> {
	DTO_INIT(SetStudyStatusRspJsonVO, JsonVO<SetStudyStatusRspDTO::Wrapper>);
};


/* 设置查询课次点评的返回值 */
class EvaluatePageJsonVO : public JsonVO<EvaluatePageDTO::Wrapper> {
	DTO_INIT(EvaluatePageJsonVO, JsonVO<EvaluatePageDTO::Wrapper>);
};


/* 设置点评单人的返回值 */
class EvaluateRspJsonVO : public JsonVO<EvaluateRspDTO::Wrapper> {
	DTO_INIT(EvaluateRspJsonVO, JsonVO<EvaluateRspDTO::Wrapper>);
};




#include OATPP_CODEGEN_END(DTO)

#endif