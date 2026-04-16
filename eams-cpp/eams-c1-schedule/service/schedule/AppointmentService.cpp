#include "stdafx.h"
#include "AppointmentService.h"
#include "dao/schedule/AppointmentDAO.h"     
#include "SimpleDateTimeFormat.h"         
#include "id/SnowFlake.h"

bool AppointmentService::addAppointment(const ScheduleAppointmentDTO::Wrapper& dto)
{
	// 基础参数校验
	if (!dto->lessonId || !dto->studentId) {
		throw std::runtime_error(u8"参数校验失败：排课ID或学生ID不能为空！");
	}
	uint64_t lessonId = dto->lessonId.getValue(0);
	uint64_t studentId = dto->studentId.getValue(0);


	// 校验是否重复预约
	AppointmentDAO appointmentDao;
	if (appointmentDao.selectCountByStudentAndLesson(studentId, lessonId) > 0) {
		throw std::runtime_error(u8"您已预约过该课程，请勿重复操作！");
	}

	uint64_t courseId = appointmentDao.getCourseIdByScheduleId(lessonId);
	if (!courseId) {
		throw std::runtime_error(u8"该课次不存在或已取消！");
	}


	// 先查有没有可用的体验卡
	auto cardInfo = appointmentDao.getValidTrialCard(studentId, courseId);
	uint64_t trialRecordId = cardInfo.first;
	uint64_t trialId = cardInfo.second;

	// 如果没有体验卡，再去查正式课时余额
	bool hasCourseQuota = false;
	if (trialRecordId == 0) {
		hasCourseQuota = appointmentDao.getStudentCourseRemain(studentId, courseId) > 0;
	}

	// 既没有体验卡，也没有正式课时
	if (trialRecordId == 0 && !hasCourseQuota) {
		throw std::runtime_error(u8"您的课时余额不足，且无可用体验卡，无法预约！");
	}

	// 创建 DO 对象，准备装载数据
	AppointmentDO data;

	// 将 DTO 的数据转换成 DO
	data.setLessonId(lessonId);
	data.setStudentId(studentId);
	data.setCourseId(courseId);
	if (trialRecordId > 0) {
		data.setTrialRecordId(trialRecordId);
		data.setTrialId(trialId);
	}
	// 补全业务隐藏字段
	// 设置预约时间为当前系统时间
	data.setAddTime(SimpleDateTimeFormat::format());

	// 设置默认的审核状态：1（表示待审核/未处理）
	data.setVerifyState(1);
	SnowFlake sf(1, 1);
	uint64_t newId = sf.nextId();
	data.setId(newId);
	// 4. 执行数据库插入
	AppointmentDAO dao;
	// 继承自 BaseDAO 的 insert 方法会自动把 data 里的数据拼装成 INSERT SQL 发给 MySQL

	int rows = dao.insert(data);

	// 如果受影响的行数等于 1，说明插入成功
	return rows == 1;
}