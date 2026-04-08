#include "stdafx.h"
#include "StudentLeaveService.h"
#include "dao/schedule/StudentLeaveDAO.h"
#include "id/SnowFlake.h"
#include "SimpleDateTimeFormat.h"

bool StudentLeaveService::addLeave(const ScheduleLeaveDTO::Wrapper& dto)
{

	uint64_t lessonId = dto->lessonId.getValue(0);
	uint64_t studentId = dto->studentId.getValue(0);
	std::string reason = dto->reason;

	StudentLeaveDAO leaveDao;

	// 课次实体校验
	if (!leaveDao.checkLessonExists(lessonId)) {
		throw std::runtime_error(u8"该课次不存在或已被系统取消，无法请假！");
	}

	// 防重复请假
	if (leaveDao.checkHasLeaveRecord(studentId, lessonId) > 0) {
		throw std::runtime_error(u8"您已提交过该课次的请假申请，请勿重复操作！");
	}

	// 创建 DO 对象，装配数据
	StudentLeaveDO data;
	data.setLessonId(lessonId);
	data.setStudentId(studentId);
	data.setReason(reason);

	data.setAddTime(SimpleDateTimeFormat::format());
	data.setState(1); // 1 表示正常生效的请假记录

	// 4. 生成唯一主键 (雪花算法)
	SnowFlake sf(1, 2); // 为了和预约模块区分，你可以给个不同的机器ID
	data.setId(sf.nextId());

	// 5. 执行插入落库
	return leaveDao.insert(data) == 1;
}