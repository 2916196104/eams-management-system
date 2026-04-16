#pragma once
#ifndef _GETTIMEABLE_SERVICE_
#define _GETTIMEABLE_SERVICE_
#include "domain/vo/schedule/GetTimeableVO.h"
#include "domain/query/schedule/GetTimeableQuery.h"
#include "domain/dto/schedule/GetTimeableDTO.h"

/**
 * 示例服务实现，演示基础的示例服务实现
 */
class GettimeableService
{
public:
	// 分页查询所有数据
	GetTimeablePageDTO::Wrapper listAll(const GetTimeableQuery::Wrapper& query);
	// 通过ID查询单个数据
	GetTimeableDTO::Wrapper getById(std::string id);
	//// 保存数据
	//std::string saveData(const SampleAddDTO::Wrapper& dto);
	//// 批量保存数据
	//bool saveDataBatch(const oatpp::List<SampleAddDTO::Wrapper>& datas);
	//// 修改数据
	//bool updateData(const SampleDTO::Wrapper& dto);
	//// 通过ID删除数据
	//bool removeData(const oatpp::List<oatpp::String>& ids);
};

#endif // !_GETTIMEABLE_SERVICE_