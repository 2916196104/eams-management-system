#pragma
#ifndef TIMETABLE_CONTROLLER_H
#define TIMETABLE_CONTROLLER_H
#include "domain/vo/BaseJsonVO.h"
#include "../../domain/vo/timetable/TimetableVO.h"
#include "../../domain/dto/timetable/TimetableDTO.h"
#include "../../domain/query/timetable/TimetableQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController) 

#define API_TAG  ZH_WORDS_GETTER("timetable.api-tag")
class TimetableController :public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(TimetableController);

public:
	
	// 1.1 按日期获取课表接口描述文档
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("timetable.interface.query-lesson"),
		queryTimetable,
		TimetableDayQuery,
		TimetableVO::Wrapper,
		API_TAG
	);

	// 1.2 按日期获取课表接口实现
	API_HANDLER_ENDPOINT_QUERY_AUTH(
		API_M_GET,
		"/c6/timetable/query",
		queryTimetable,
		TimetableDayQuery,
		executeQuery(query)
	);

	// 2.1 课表签到接口描述文档
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("timetable.interface.sign"),
		signTimetable,
		TimetableSignVO::Wrapper,
		API_TAG
	);

	// 2.2 课表签到接口实现
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/c6/timetable/sign",
		signTimetable,
		BODY_DTO(TimetableSignDTO::Wrapper, dto),
		executeSign(dto)
	);

	// 3.1 预约接口描述文档
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("timetable.interface.reserve"),
		TimeReserve,
	      ReserveVO::Wrapper,
		API_TAG,
	);
	
	// 3.2 预约接口实现
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/c6/timetable/reserve",
		TimeReserve,
		BODY_DTO(ReserveDTO::Wrapper, dto),
		executeReserve(dto)
	);
	// 4.1 请假接口描述文档
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("timetable.interface.leave"),
		TimeLeave,
		LeaveVO::Wrapper,
		API_TAG,
		);

	// 4.2 请假接口实现
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
	// 执行请假业务
	StringJsonVO::Wrapper TimetableController::executeLeave(const LeaveDTO::Wrapper& dto);
	// 执行按日期查询课表业务
	TimetableVO::Wrapper executeQuery(const TimetableDayQuery::Wrapper& query);
	// 执行签到业务
	TimetableSignVO::Wrapper executeSign(const TimetableSignDTO::Wrapper& dto);


};




#include OATPP_CODEGEN_END(ApiController) 

#endif // RESERVATION_CONTROLLER_H


