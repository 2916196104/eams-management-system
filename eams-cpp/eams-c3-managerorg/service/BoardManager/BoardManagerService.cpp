#include "stdafx.h"
#include "service/BoardManager/BoardManagerService.h"
#include "dao/Board/NoticeDao.h"
#include "id/SnowFlake.h"
#include "SimpleDateTimeFormat.h"

BoardPageDTO::Wrapper BoardService::listAll(const BoardQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = BoardPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	NoticeDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<PtrNoticeDO> result = dao.selectAll(query);
	// 将DO转换成DTO
	for (PtrNoticeDO& sub : result)
	{
		auto dto = BoardDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, sub, boardAddId, Id, boardTitle, Title, boardText, Content, viewNum,ViewNum, boardPublisherId, Creator, boardEditorId, Editor, boardTime, AddTime, editTime, EditTime, deleted, Deleted);
		pages->addData(dto);
	}
	return pages;
}

oatpp::UInt64 BoardService::saveBoard(const BoardAddDTO::Wrapper& dto)
{
	NoticeDO data;
	if (dto->boardAddId.get())
	{
		// 修改
		ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Title, boardTitle, Content, boardText, Id, boardAddId);
		// 设置修改人
		data.setEditor(std::stoull(dto->getPayload()->getId()));
		// 设置修改时间
		data.setEditTime(SimpleDateTimeFormat::format());
		// 执行数据修改
		NoticeDAO dao;
		return dao.update(data) == 1 ? data.getId() : 0;
	}
	else
	{
		// 新增
		ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Title, boardTitle, Content, boardText);
		// 生成ID
		SnowFlake sf(1,1);
		data.setId(sf.nextId());
		// 设置创建人
		data.setCreator(std::stoull(dto->getPayload()->getId()));
		// 设置创建时间
		data.setAddTime(SimpleDateTimeFormat::format());
		// 执行数据添加
		NoticeDAO dao;
		return dao.insert(data) == 1 ? data.getId() : 0;
	}
	

}

bool BoardService::updateData1(const oatpp::List<oatpp::String>& ids, const BoardUpdateDTO::Wrapper& dto)
{
	for (auto one : *ids.get())
	{
		NoticeDO data;
		oatpp::UInt64 id = std::stoull(one);
		data.setId(id);
		// 设置修改人
		data.setEditor(std::stoull(dto->getPayload()->getId()));
		// 设置修改时间
		data.setEditTime(SimpleDateTimeFormat::format());
		// 执行数据修改
		NoticeDAO dao;
		if (!(dao.update2(data) == 1 ? data.getId() : 0))
		{
			return false;
		}
	}
	return true;
}

bool BoardService::updateData2(const oatpp::List<oatpp::String>& ids, const BoardUpdateDTO::Wrapper& dto)
{
	for (auto one : *ids.get())
	{
		NoticeDO data;
		oatpp::UInt64 id = std::stoull(one);
		data.setId(id);
		// 设置修改人
		data.setEditor(std::stoull(dto->getPayload()->getId()));
		// 设置修改时间
		data.setEditTime(SimpleDateTimeFormat::format());
		// 执行数据修改
		NoticeDAO dao;
		if (!(dao.update1(data) == 1 ? data.getId() : 0))
		{
			return false;
		}
	}
	return true;
}

bool BoardService::removeData(const oatpp::List<oatpp::String>& ids)
{
	NoticeDAO dao;
	std::list<std::string> datas;
	for (auto one : *ids.get())
		datas.emplace_back(one.getValue({}));
	int rows = dao.deleteByIds<NoticeDO>(datas);
	if (rows == ids->size())
		return true;
	return false;
}
