#include "stdafx.h"
#include "ScheduleController.h"
// 后续引入 Service 层
// #include "..."

// ==============================================================================
// 接口 1：获取课表列表 (GET /schedule/query)
// ==============================================================================

// 实现 execQuerySchedule 函数
ListJsonVO<ScheduleVO::Wrapper>::Wrapper ScheduleController::execQuerySchedule(const ScheduleQuery::Wrapper& query, const PayloadDTO& payload)
{
	// 可能的参数校验：用于检查 query->queryDate 是否是合法的日期格式
	// 考虑到日期往往是选取合法值而非手动输入，这里仅做保留提示

	// 调用 Service 层
	// 暂无 Service 实现，仅做保留
	auto result = oatpp::List<ScheduleVO::Wrapper>::createShared();

	// 构造统一的 JSON 返回对象
	auto jvo = ListJsonVO<ScheduleVO::Wrapper>::createShared();
	jvo->success(result); // 使用你们 BaseJsonVO.h 里的 success 方法包装数据
	return jvo;
}


// ==============================================================================
// 接口 2：学生签到 (POST /schedule/sign-in)
// ==============================================================================

// 实现 execSignIn 函数
StringJsonVO::Wrapper ScheduleController::execSignIn(const SignInDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();

	// 参数校验 (在 DTO 里写的 validate 函数)
	std::string errmsg = dto->validate();
	if (errmsg != "")
	{
		// 使用 JsonVO.h 里的 init 方法返回参数错误
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}

	// 调用 Service 层
	// 
	bool isSuccess = true; // 模拟成功

	// 响应结果
	if (isSuccess) {
		jvo->success(ZH_WORDS_GETTER("schedule.signin.success"));
	}
	else {
		jvo->fail(ZH_WORDS_GETTER("schedule.signin.fail"));
	}

	return jvo;
}