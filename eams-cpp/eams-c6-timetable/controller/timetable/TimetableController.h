#pragma
#ifndef TIMETABLE_CONTROLLER_H
#define TIMETABLE_CONTROLLER_H
#include "domain/vo/BaseJsonVO.h"
#include "../../domain/vo/timetable/TimetableVO.h"
#include "../../domain/dto/timetable/TimetableDTO.h"


#include OATPP_CODEGEN_BEGIN(ApiController) 

#define API_TAG  ZH_WORDS_GETTER("timetable.api-tag")
class TimetableController :public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(TimetableController);

public:
	
	// 1. 预约接口描述文档
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("timetable.interface.reserve"),
		TimeReserve,
	      ReserveVO::Wrapper,
		API_TAG,
	);
	
	// 2. 预约接口实现
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/c6/timetable/reserve",
		TimeReserve,
		BODY_DTO(ReserveDTO::Wrapper, dto),
		executeReserve(dto)
	);
	// 1. 请假接口描述文档
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("timetable.interface.leave"),
		TimeLeave,
		LeaveVO::Wrapper,
		API_TAG,
		);

	// 2. 请假接口实现
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/c6/timetable/leave",
		TimeLeave,
		BODY_DTO(LeaveDTO::Wrapper, dto),
		executeLeave(dto),
		
	);
private:
	// 执行预约业务
	StringJsonVO::Wrapper TimetableController::executeReserve(const ReserveDTO::Wrapper& dto);
	//执行请假业务
	StringJsonVO::Wrapper TimetableController::executeLeave(const LeaveDTO::Wrapper& dto);
	
};
#include OATPP_CODEGEN_END(ApiController) 

#endif // RESERVATION_CONTROLLER_H


