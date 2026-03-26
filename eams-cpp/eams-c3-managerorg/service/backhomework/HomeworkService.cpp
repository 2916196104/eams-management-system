
#include "stdafx.h"
#include "HomeworkService.h"
#include "../../dao/homework/HomeworkRecordDAO.h"
#include "../../dao/homework/HomeworkDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

GetHomeworkListPageDTO::Wrapper HomeworkService::gethomeworklist(const GetHomeworkListQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = GetHomeworkListPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	HomeworkDao dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<HomeworkDO> result = dao.gethomeworklist(query);
	// 将DO转换成DTO
	for (HomeworkDO& sub : result)
	{
		auto dto = GetHomeworkListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, title, Title, classId, ClassId,creator,Creator);
		pages->addData(dto);
	}
	return pages;
}

GetHomeworkDetailDTO::Wrapper HomeworkService::gethomeworkdetail(int64_t id)
{
	// 查询数据
	HomeworkDao dao;
	auto res = dao.gethomeworkdetail(id);

	// 没有查询到数据
	if (!res)
		return nullptr;

	// 查询到数据转换成DTO
	auto dto = GetHomeworkDetailDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res, id, Id);
	return dto;
}

//保存作业--修改/新增作业
bool HomeworkService::saveHomework(const SaveHomeworkDTO::Wrapper& dto)
{
	if (dto->id) {   //如果id存在，说明是修改作业
		// 组装DO数据
		HomeworkDO data;
		ZO_STAR_DOMAIN_DTO_TO_DO(data, dto,Id, id ,Title, title, ClassId, classId, Content, content,Editor, editor);
		// 设置修改时间
		//data.setUpdateTime(SimpleDateTimeFormat::format());
		// 执行数据修改
		// 查询数据
		HomeworkDao dao;
		return dao.update(data) == 1;
	}
	else {       //如果id不存在，说明是新增作业
		// 组装DO数据
		HomeworkDO data;
		ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Title, title, ClassId, classId, Content, content, Creator, creator);
		// 生成ID，sample中的id是string类型，但是homework的id是int64类型的
		//UuidFacade uf;
		//data.setId(uf.genUuid());
		// 设置创建时间
		//data.setAddTime(SimpleDateTimeFormat::format());
		// 执行数据添加,
		HomeworkDao dao;
		return dao.insert(data);
	}
}
