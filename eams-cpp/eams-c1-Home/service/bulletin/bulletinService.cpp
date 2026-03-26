#include "stdafx.h"
#include "./bulletinService.h"
#include "dao/bulletin/bulletinDAO.h"
#include "domain/query/PageQuery.h"

// 接口1实现: 查询最新一条公告
titleDTO::Wrapper bulletinService::getLatest()
{
	// 创建DAO对象查询数据
	bulletinDAO dao;
	auto res = dao.selectLatest();  // 查询最新一条公告

	// 没有查询到数据
	if (!res) {
		return nullptr;  // 返回空指针，与SampleService保持一致
	}

	// 创建返回对象
	auto dto = titleDTO::createShared();

	// 使用宏将DO转换为DTO
	// 参数格式：dto字段名, DO的getter方法名（去掉get）
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res,
		id, Id,              // dto->id = res->getId();
		title, Title,        // dto->title = res->getTitle();
		type, Type,          // dto->type = res->getType();
		content, Content,    // dto->content = res->getContent();
		cover, Cover,        // dto->cover = res->getCover();
		creator, Creator,    // dto->creator = res->getCreator();
		addTime, AddTime,    // dto->addTime = res->getAddTime();
		deleted, Deleted,    // dto->deleted = res->getDeleted();
		editTime, EditTime,  // dto->editTime = res->getEditTime();
		editor, Editor,      // dto->editor = res->getEditor();
		state, State,        // dto->state = res->getState();
		sortNum, SortNum     // dto->sortNum = res->getSortNum();
	);

	return dto;
}

// 接口2实现: 分页查询所有公告
listPageDTO::Wrapper bulletinService::listAll(const PageQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = listPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	bulletinDAO dao;
	uint64_t count = dao.count();
	if (count <= 0) {
		return pages;  // 无数据直接返回
	}

	// 设置分页信息
	pages->total = count;
	pages->calcPages();

	// 分页查询数据
	list<bulletinDO> result = dao.selectWithPage(query);

	// 将DO转换成DTO，使用宏进行字段映射
	for (bulletinDO& sub : result) {
		auto dto = titleDTO::createShared();

		// 使用宏进行字段映射
		// 注意：这里用的是ZO_STAR_DOMAIN_DO_TO_DTO（不是_1），因为sub是对象不是指针
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
			id, Id,              // dto->id = sub.getId();
			title, Title,        // dto->title = sub.getTitle();
			type, Type,          // dto->type = sub.getType();
			content, Content,    // dto->content = sub.getContent();
			cover, Cover,        // dto->cover = sub.getCover();
			creator, Creator,    // dto->creator = sub.getCreator();
			addTime, AddTime,    // dto->addTime = sub.getAddTime();
			deleted, Deleted,    // dto->deleted = sub.getDeleted();
			editTime, EditTime,  // dto->editTime = sub.getEditTime();
			editor, Editor,      // dto->editor = sub.getEditor();
			state, State,        // dto->state = sub.getState();
			sortNum, SortNum     // dto->sortNum = sub.getSortNum();
		);

		pages->addData(dto);
	}

	return pages;
}

// 接口3实现: 获取三个功能模块的未读数
redDTO::Wrapper redService::getRed(int64_t studentId)
{
	// 参数校验
	if (studentId <= 0) {
		auto dto = redDTO::createShared();
		dto->grade_count = 0;
		dto->evaluate_count = 0;
		dto->homework_count = 0;
		return dto;
	}

	// 查询未读数
	redDAO dao;
	auto redDO = dao.getUnreadCounts(studentId);

	// 创建返回DTO对象
	auto dto = redDTO::createShared();

	if (redDO) {
		// 手动将DO转换为DTO
		dto->grade_count = redDO->getGradeCount();
		dto->evaluate_count = redDO->getEvaluateCount();
		dto->homework_count = redDO->getHomeworkCount();
	}
	else {
		cout<<"查询未读数失败,返回全-1"<<endl;
		// 如果查询失败，返回0值
		dto->grade_count = -1;
		dto->evaluate_count = -1;
		dto->homework_count = -1;
	}

	return dto;
}