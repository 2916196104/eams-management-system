#pragma once
#ifndef _TIMETABLE_MAPPER_
#define _TIMETABLE_MAPPER_

#include "Mapper.h"
#include "../../domain/do/timetable/TimetableDO.h"

// 定义用于映射课程视图的Mapper类，继承通用Mapper模板
class TimetableCourseViewMapper : public Mapper<TimetableCourseViewDO>
{
public:
	
	TimetableCourseViewDO mapper(ResultSet* resultSet) const override
	{
		
		TimetableCourseViewDO data;
		// 从第1列读取id并设置
		data.setId(resultSet->getString(1));
		// 从第2列读取标题并设置
		data.setTitle(resultSet->getString(2));
		// 从第3列读取序号并设置
		data.setSn(resultSet->getInt(3));
		// 从第4列读取班级id并设置
		data.setClassId(resultSet->getString(4));
		// 从第5列读取教室id并设置
		data.setRoomId(resultSet->getString(5));
		// 从第6列读取日期并设置
		data.setDate(resultSet->getString(6));
		// 第7列：开始时间
		data.setStartTime(resultSet->getString(7));
		// 第8列：结束时间
		data.setEndTime(resultSet->getString(8));
		// 第9列：备注
		data.setRemark(resultSet->getString(9));
		// 第10列：状态
		data.setState(resultSet->getInt(10));
		// 第11列：教师id
		data.setTeacherId(resultSet->getString(11));
		// 第12列：是否可预订
		data.setBookable(resultSet->getInt(12));
		// 第13列：课程id
		data.setCourseId(resultSet->getString(13));
		// 第14列：教师姓名
		data.setTeacherName(resultSet->getString(14));
		// 第15列：教室名称
		data.setClassroomName(resultSet->getString(15));
		// 第16列：班级名称
		data.setClassName(resultSet->getString(16));
		// 第17列：课次状态
		data.setLessonState(resultSet->getInt(17));
		// 第18列：课次状态文本
		data.setLessonStateText(resultSet->getString(18));
		// 第19列：签到状态
		data.setSignState(resultSet->getInt(19));
		// 第20列：签到状态文本
		data.setSignStateText(resultSet->getString(20));
		// 第21列：是否可签到
		data.setCanSign(resultSet->getInt(21));
		// 第22列：是否可请假
		data.setCanLeave(resultSet->getInt(22));
		// 第23列：是否可预约
		data.setCanReserve(resultSet->getInt(23));
		// 第24列：卡片类型
		data.setCardType(resultSet->getString(24));
		// 第25列：动作类型
		data.setActionType(resultSet->getString(25));
		// 第26列：动作文本
		data.setActionText(resultSet->getString(26));
		
		return data;
	}
};

// 定义用于日历计数映射的Mapper
class TimetableCalendarCountMapper : public Mapper<TimetableCalendarCountDO>
{
public:
	
	TimetableCalendarCountDO mapper(ResultSet* resultSet) const override
	{
		
		TimetableCalendarCountDO data;
		// 第1列：日期
		data.setDate(resultSet->getString(1));
		// 第2列：计数
		data.setCount(resultSet->getInt(2));
		// 返回对象
		return data;
	}
}; 

// 定义返回智能指针Lesson的Mapper
class PtrLessonMapper : public Mapper<PtrLessonDO>
{
public:
	
	PtrLessonDO mapper(ResultSet* resultSet) const override
	{
		// 创建shared_ptr<LessonDO>
		auto data = std::make_shared<LessonDO>();
		// 第1列：id
		data->setId(resultSet->getString(1));
		// 第2列：标题
		data->setTitle(resultSet->getString(2));
		// 第3列：序号
		data->setSn(resultSet->getInt(3));
		// 第4列：班级id
		data->setClassId(resultSet->getString(4));
		// 第5列：教室id
		data->setRoomId(resultSet->getString(5));
		// 第6列：日期
		data->setDate(resultSet->getString(6));
		// 第7列：开始时间
		data->setStartTime(resultSet->getString(7));
		// 第8列：结束时间
		data->setEndTime(resultSet->getString(8));
		// 第9列：备注
		data->setRemark(resultSet->getString(9));
		// 第10列：状态
		data->setState(resultSet->getInt(10));
		// 第11列：教师id
		data->setTeacherId(resultSet->getString(11));
		// 第12列：是否可预订
		data->setBookable(resultSet->getInt(12));
		// 第13列：课程id
		data->setCourseId(resultSet->getString(13));
	
		return data;
	}
};

// 定义用于映射学生签到信息的Mapper
class PtrLessonStudentMapper : public Mapper<PtrLessonStudentDO>
{
public:
	
	PtrLessonStudentDO mapper(ResultSet* resultSet) const override
	{
		// 创建shared_ptr<LessonStudentDO>
		auto data = std::make_shared<LessonStudentDO>();
		// 第1列：记录id
		data->setId(resultSet->getString(1));
		// 第2列：课次id
		data->setLessonId(resultSet->getString(2));
		// 第3列：班级id
		data->setClassId(resultSet->getString(3));
		// 第4列：学生id
		data->setStudentId(resultSet->getString(4));
		// 第5列：签到时间
		data->setSignTime(resultSet->getString(5));
		// 第6列：签到类型（整型）
		data->setSignType(resultSet->getInt(6));
		// 第7列：签到状态（整型）
		data->setSignState(resultSet->getInt(7));
		// 第8列：教师id（可能用于代签）
		data->setTeacherId(resultSet->getString(8));
		// 返回shared_ptr包装的学生签到DO
		return data;
	}
};

#endif // !_TIMETABLE_MAPPER_
