#include"stdafx.h"
#include"ClassListService.h"
#include"../../dao/makabaka-dao/ClassListDAO.h"

ClassPageDTO::Wrapper ClassListService::listAll(const ClassQuery::Wrapper& query) {
	//构建返回对象
	auto pages = ClassPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	//查询数据总条数
	ClassListDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0) {
		return pages;
	}

	//分页查询
	pages->total = count;
	pages->calcPages();
	list<ClassDO> result = dao.selectWithPage(query);
	//将DO转化为DTO
	for (ClassDO& sub : result) {
		auto dto = ClassDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id, name, Name, grade_id, Grade_id);
		pages->addData(dto);
	}
	return pages;
}