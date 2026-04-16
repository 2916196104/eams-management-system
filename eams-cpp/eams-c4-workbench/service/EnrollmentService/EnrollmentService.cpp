#include"EnrollmentService.h"
#include"stdafx.h"
#include"../../dao/EnrollmentDAO/EnrollmentDAO.h"
#include"../../../lib-common/include/id/UuidFacade.h"
#include"SimpleDateTimeFormat.h"
#include"../../domain/do/StudentCourseDO.h"
std::string EnrollmentService::saveEnrollment(const EnrollDTO::Wrapper& dto)
{
	// 组装DO数据
	StudentCourseDO data;
	//校验课程和学生是否存在
	auto course = EnrollmentDAO().selectCourseById(std::to_string(dto->courseId));
	if (!course)
	{
		throw std::runtime_error(ZH_WORDS_GETTER("enrollment.error.courseNotFound"));
	}
	auto student = EnrollmentDAO().selectStudentById(std::to_string(dto->studentId));
	if (!student)
	{
		throw std::runtime_error(ZH_WORDS_GETTER("enrollment.error.studentNotFound"));
	}
	//重复报名校验
	/*if (EnrollmentDAO().countByStudentAndCourse(dto->studentId, dto->courseId) == 0)
	{
		throw std::runtime_error(ZH_WORDS_GETTER("enrollment.error.RepeatedEnrolled"));
	}*/
	//生成唯一ID
	UuidFacade uf;
	auto id = uf.genUuid();
	int idInt = std::stoi(id);//string转int类型
	if (idInt <= 0)
	{
		throw std::runtime_error(ZH_WORDS_GETTER("enrollment.error.idGenerationFailed"));
	}
	data.setId(10);
	data.setStudentId(dto->studentId);
	data.setCourseId(dto->courseId);
	int subjectIdInt = std::stoi(course->getSubject_id());
	data.setSubjectId(subjectIdInt);

	//时间相关
	data.setAddTime(SimpleDateTimeFormat::format());
	data.setStartDate(SimpleDateTimeFormat::format());
	if (course->getExpire_months() > 0)
	{
		data.setExpireDate(addMonths(SimpleDateTimeFormat::format(), course->getExpire_months()));
	}
	else
	{
		data.setExpireDate(NULL);
	}
	//金额相关
	double courseAmount = std::stod(course->getPrice());
	data.setCourseAmount(courseAmount);
	if (course->getDiscount() == "")
	{
		data.setDiscountAmount(0);
	}
	else {
		double discountAmount = std::stod(course->getDiscount());
		data.setDiscountAmount(discountAmount);
	}
	if (course->getDiscount() == "")
	{
		data.setAmount(courseAmount);
		double paidAmount = std::stod(dto->paidCourseAmount);
		data.setPaidAmount(paidAmount);

		bool PayOff = paidAmount >= courseAmount;
		data.setPayOff(PayOff);
	}
	else {
		double amountAfterDiscount = courseAmount - std::stod(course->getDiscount());
		data.setAmount(amountAfterDiscount);
		double paidAmount = std::stod(dto->paidCourseAmount);
		data.setPaidAmount(paidAmount);

		bool PayOff = paidAmount >= amountAfterDiscount;
		data.setPayOff(PayOff);
	}
		data.setUnitPrice(std::stod(course->getUnit_price()));
		data.setCountLessonTotal(course->getLesson_count());
		data.setCountLessonComplete(0);
		data.setCountLessonRefund(0);
		//状态相关
		data.setDeleted(0);
		data.setVerifyState(1);      // 待审核
		data.setWarningTimes(0); // 不足时已提醒次数
		data.setPriority(1);         // 默认优先级
		data.setFromTrial(0);
		//创建人以及组织相关
		auto CreatorId = dto->getPayload()->getId();
		int creatorIdInt = std::stoi(CreatorId);
		data.setCreator(creatorIdInt);
		data.setOrgId(dto->OrgId); // 组织ID
		data.setOperatorId(dto->Operator);  // 经手人ID

		data.setEditor(0);           // 或 NULL
		data.setEditTime("2025-01-01");
		//调用DAO保存数据
		EnrollmentDAO dao;
		//将longlong数据类型进行转换
		idInt = data.getId();
		if (dao.insert(data) > 0)
		{
			return std::to_string(idInt);
		}
		else {
			return "insert fail";
		}
	
}

// 判断闰年
bool isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// 获取某年某月的天数
int getDaysInMonth(int year, int month) {
	static const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && isLeapYear(year)) return 29;
	return days[month - 1];
}
std::string EnrollmentService::addMonths(const std::string& dateStr, int months)
{
	// 1. 解析起始时间
	std::tm tm = {};
	std::istringstream ss(dateStr);
	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
	if (ss.fail()) {
		throw std::runtime_error("Invalid date format: " + dateStr);
	}

	// 2. 提取年月日时分秒
	int year = tm.tm_year + 1900;
	int month = tm.tm_mon + 1;
	int day = tm.tm_mday;
	int hour = tm.tm_hour;
	int min = tm.tm_min;
	int sec = tm.tm_sec;

	// 3. 计算新的年月
	int totalMonths = month + months - 1;        // 从0开始计算
	int new_year = year + totalMonths / 12;
	int new_month = totalMonths % 12 + 1;

	// 4. 处理日期溢出：如果原日大于新月份的天数，则取新月份的最后一天
	int daysInNewMonth = getDaysInMonth(new_year, new_month);
	int new_day = std::min(day, daysInNewMonth);

	// 5. 构造新的 tm 结构
	std::tm new_tm = {};
	new_tm.tm_year = new_year - 1900;
	new_tm.tm_mon = new_month - 1;
	new_tm.tm_mday = new_day;
	new_tm.tm_hour = hour;
	new_tm.tm_min = min;
	new_tm.tm_sec = sec;

	// 6. 格式化为字符串并返回
	std::ostringstream oss;
	oss << std::put_time(&new_tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

