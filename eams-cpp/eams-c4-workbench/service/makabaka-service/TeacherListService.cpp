#include"stdafx.h"
#include"TeacherListService.h"
#include"../../dao/makabaka-dao/TeacherListDAO.h"

TeacherPageDTO::Wrapper TeacherListService::listAll(const TeacherQuery::Wrapper& query) {
	auto pages = TeacherPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	//查询数据总条数
	TeacherListDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0) {
		return pages;
	}

	//计算总页数
	pages->total = count;
	pages->calcPages();
	list<TeacherDTO::Wrapper> result = dao.selectWithPage(query);
	for (TeacherDTO::Wrapper& sub : result)
		pages->addData(sub);
	return pages;
}