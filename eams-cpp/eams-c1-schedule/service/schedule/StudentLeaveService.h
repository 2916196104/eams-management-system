#pragma once
#ifndef _STUDENT_LEAVE_SERVICE_H_
#define _STUDENT_LEAVE_SERVICE_H_

// 引入相关的 DTO（注意检查你的实际相对路径是不是这个）
#include "../../domain/dto/schedule/scheduleDTO.h" 
/**
 * @brief 学生请假业务逻辑层 (Service)
 * 负责处理请假相关的核心业务校验与数据组装
 */
class StudentLeaveService
{
public:
	/**
	 * 提交请假申请
	 * @param dto 包含请假课次(lessonId)、学生ID(studentId)、请假原因(reason)等信息
	 * @return bool 返回 true 表示请假成功并落库，抛出异常表示被拦截
	 */
	bool addLeave(const ScheduleLeaveDTO::Wrapper& dto);
};

#endif // !_STUDENT_LEAVE_SERVICE_H_