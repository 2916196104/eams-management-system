#include "service/UsageGuideService.h"
#include "dao/manualDao.h"
#include "domain/dto/manual/ManualDTO.h"
#include "domain/do/manualDO.h"

//查询数据库，将所有列表信息封装为dto返回
UsageListDTO::Wrapper UsageGuideService::listAll(const ListQuery::Wrapper& query)
{
	// 【步骤1】创建返回对象
	auto pages = UsageListDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 【步骤2】查询总数
	manualDAO dao;
	uint64_t count = dao.count();
	if (count <= 0) {
		return pages; // 无数据直接返回
	}

	// 【步骤3】计算分页信息
	pages->total = count;
	pages->calcPages(); // 计算总页数

	// 【步骤4】查询分页数据
	list<ManualDO> result = dao.showList(query);

	// 【步骤5】DO转DTO
	for (ManualDO& sub : result) {
		auto dto = UsageGuideDto::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
			//id, Id,
			title, Title
			//,
			//add_time, AddTime,
			//edit_time, EditTime
		);
		/*if (!dto->edit_time) {
			dto->edit_time = oatpp::String("no edit_time");
		}*/
		pages->addData(dto);
	}

	// 【步骤6】返回结果
	return pages;
}

//查询数据库，将某一详细信息封装为dto返回
UsageGuideDetailDto::Wrapper UsageGuideService::getById(std::string id)
{
	// 【步骤1】调用DAO查询
	manualDAO dao;
	auto res = dao.selectById(id);

	// 【步骤2】检查查询结果
	if (!res) {
		return nullptr; // 未找到数据
	}

	// 【步骤3】DO转DTO
	auto dto = UsageGuideDetailDto::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res,
		//id, Id,
		title, Title,
		content, Content
		//,
		//type, Type,
		//creator, Creator,
		//add_time, AddTime,
		//deleted, Deleted,
		//edit_time, EditTime,
		//editor, Editor,
		//state, State,
		//sort_num,SortNum
	);

	// 【步骤4】返回结果
	return dto;
}

