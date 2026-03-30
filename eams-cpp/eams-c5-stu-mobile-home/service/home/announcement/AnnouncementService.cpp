#include "stdafx.h"
#include "AnnouncementService.h"
#include "../../../dao/home/announcement/AnnouncementDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

AnnouncementPageDTO::Wrapper AnnouncementService::listAll(const AnnouncementQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = AnnouncementPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	AnnouncementDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<AnnouncementDO> result = dao.selectWithPage(query);
	// 将DO转换成DTO
	for (AnnouncementDO& sub : result)
	{
		auto dto = AnnouncementDTO::createShared();
		// 1. DO.id → DTO.Id（公告ID）
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id);

		// 2. DO.title → DTO.Title（公告标题）
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, title, Title);

		// 3. DO.type → DTO.Type（公告类型）
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, type, Type);

		// 4. DO.content → DTO.Content（公告内容）
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, content, Content);

		// 5. DO.add_time → DTO.Add_time（添加时间）
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, add_time, Add_time);

		// 6. DO.edit_time → DTO.Edit_time（编辑时间）
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, edit_time, Edit_time);

		// 7. DO.editor → DTO.Editor（编辑人ID）
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, editor, Editor);

		//8.cover图片地址
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, cover, Cover);
		pages->addData(dto);
	}
	return pages;
}
AnnouncementDTO::Wrapper AnnouncementService::listone(const AnnouncementQuery::Wrapper& query)
{
	// 构建返回对象（单条DTO，无分页属性）
	auto dto = AnnouncementDTO::createShared();

	// 查询单条数据
	AnnouncementDAO dao;
	AnnouncementDO announcementDO = dao.selectone(query);
	// 校验查询结果（无数据返回空DTO）

	// 将DO转换成DTO
	// 1. DO.id → DTO.Id（公告ID）
	ZO_STAR_DOMAIN_DO_TO_DTO(dto, announcementDO, id, Id);

	// 2. DO.title → DTO.Title（公告标题）
	ZO_STAR_DOMAIN_DO_TO_DTO(dto, announcementDO, title, Title);

	// 3. DO.type → DTO.Type（公告类型）
	ZO_STAR_DOMAIN_DO_TO_DTO(dto, announcementDO, type, Type);

	// 4. DO.content → DTO.Content（公告内容）
	ZO_STAR_DOMAIN_DO_TO_DTO(dto, announcementDO, content, Content);

	// 5. DO.add_time → DTO.Add_time（添加时间）
	ZO_STAR_DOMAIN_DO_TO_DTO(dto, announcementDO, add_time, Add_time);

	// 6. DO.edit_time → DTO.Edit_time（编辑时间）
	ZO_STAR_DOMAIN_DO_TO_DTO(dto, announcementDO, edit_time, Edit_time);

	// 7. DO.editor → DTO.Editor（编辑人ID）
	ZO_STAR_DOMAIN_DO_TO_DTO(dto, announcementDO, editor, Editor);

	return dto;
}