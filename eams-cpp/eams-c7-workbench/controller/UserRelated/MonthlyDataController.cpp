//#include "stdafx.h"
//#include "MonthlyDataController.h"
//#include "../../service/user-related/MonthlyDataService.h"
//MonthlyDataListJsonVO::Wrapper MonthlyDataController::executeQueryMonthlyDataList(const MonthlyDataQuery::Wrapper& query)
//{
//
//	// 查询数据
//	auto result = MonthlyDataService().listAll(query);
//	// 响应结果
//	auto jvo = MonthlyDataListJsonVO::createShared();
//	// 将单个对象包装成列表
//	std::list<MonthlyDataDTO::Wrapper> resultList;
//	if (result != nullptr) {
//		resultList.push_back(result);
//	}
//	jvo->success(resultList);
//	return jvo;
//}

//#include "stdafx.h"
//#include "MonthlyDataController.h"
//#include "../../service/user-related/MonthlyDataService.h"
//
//MonthlyDataListJsonVO::Wrapper MonthlyDataController::executeQueryMonthlyDataList(const MonthlyDataQuery::Wrapper& query)
//{
//    // 查询数据
//    auto result = MonthlyDataService().listAll(query);
//
//    // 响应结果
//    auto jvo = MonthlyDataListJsonVO::createShared();
//    jvo->success(result);  // result 应该是 ListObjectWrapper 类型
//
//    return jvo;
//}


#include "stdafx.h"
#include "MonthlyDataController.h"
#include "service/UserRelated/MonthlyDataService.h"

MonthlyDataListJsonVO::Wrapper MonthlyDataController::executeQueryMonthlyDataList(const MonthlyDataQuery::Wrapper& query)
{
    // 查询数据（返回单个DTO）
    auto result = MonthlyDataService().listAll(query);

    // 创建列表并添加数据
    auto list = oatpp::data::mapping::type::ListObjectWrapper<MonthlyDataDTO::Wrapper, oatpp::data::mapping::type::__class::List<MonthlyDataDTO::Wrapper>>::createShared();
    if (result != nullptr) {
        list->push_back(result);
    }

    // 响应结果
    auto jvo = MonthlyDataListJsonVO::createShared();
    jvo->success(list);

    return jvo;
}