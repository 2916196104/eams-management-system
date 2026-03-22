#include "stdafx.h"
#include "CourseRecordService.h"
#include "../../dao/CourseRecord/CourseRecordDAO.h"

CourseRecordPageDTO::Wrapper CourseRecordService::listAll(const CourseRecordQuery::Wrapper& query)
{
	// 构建返回对象
	auto pages = CourseRecordPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	// 查询数据总条数
	CourseRecordDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	// 分页查询数据
	pages->total = count;
	pages->calcPages();
	list<CourseRecordDO> result = dao.selectWithPage(query);

	// 将DO转换成DTO
	for (CourseRecordDO& sub : result)
	{
		auto dto = CourseRecordDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
			id, Id,
			title, Title,
			sn, Sn,
			course_id, CourseId,
			schedule_id, ScheduleId,
			class_id, ClassId,
			room_id, RoomId,
			date, Date,
			start_time, StartTime,
			end_time, EndTime,
			creator, Creator,
			editor, Editor,
			add_time, AddTime,
			edit_time, EditTime,
			deleted, Deleted,
			dec_count, DecCount,
			remark, Remark,
			teach_type, TeachType,
			on_trial, OnTrial,
			trial_result, TrialResult,
			state, State,
			close_time, CloseTime,
			close_operator, CloseOperator,
			teacher_id, TeacherId,
			bookable, Bookable,
			school_id, SchoolId,
			org_id, OrgId);
		pages->addData(dto);
	}
	return pages;
}
