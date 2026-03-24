#pragma once
#ifndef CommonDTO_h
#define CommonDTO_h
#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class StudentAddDTO : public oatpp::DTO {
	DTO_INIT(StudentAddDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("common.field.student.name"));
	API_DTO_FIELD_DEFAULT(String, phone, ZH_WORDS_GETTER("common.field.student.content"));
	API_DTO_FIELD_DEFAULT(String, picturePath, ZH_WORDS_GETTER("common.field.student.picture-path"));
    API_DTO_FIELD_DEFAULT(Int32, leftCourseCount , ZH_WORDS_GETTER("common.field.student.left-course-count"));
	API_DTO_FIELD_DEFAULT(Int32, leftPoints, ZH_WORDS_GETTER("common.field.student.left-points"));
	API_DTO_FIELD_DEFAULT(Int32, stage, ZH_WORDS_GETTER("common.field.student.stage"));
	API_DTO_FIELD_DEFAULT(Int32, sex, ZH_WORDS_GETTER("common.field.student.sex"));
	API_DTO_FIELD_DEFAULT(Int32, age, ZH_WORDS_GETTER("common.field.student.age"));
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("common.field.student.birthday"));
	API_DTO_FIELD_DEFAULT(String, identificationNumber, ZH_WORDS_GETTER("common.field.student.identification-number"));
	API_DTO_FIELD_DEFAULT(String, parentName, ZH_WORDS_GETTER("common.field.student.parent-name"));
	API_DTO_FIELD_DEFAULT(String, relationType, ZH_WORDS_GETTER("common.field.student.relation-type"));
	API_DTO_FIELD_DEFAULT(Int32, grade, ZH_WORDS_GETTER("common.field.student.grade"));
	API_DTO_FIELD_DEFAULT(String, enterTime, ZH_WORDS_GETTER("common.field.student.enter-time"));
	API_DTO_FIELD_DEFAULT(String, accurateEnterTime, ZH_WORDS_GETTER("common.field.student.accurate-enter-time"));
	API_DTO_FIELD_DEFAULT(String, note, ZH_WORDS_GETTER("common.field.student.note"));
	API_DTO_FIELD_DEFAULT(String, courseProgress, ZH_WORDS_GETTER("common.field.student.course-progress"));
};
class StudentDTO :public StudentAddDTO {
    DTO_INIT(StudentDTO, StudentAddDTO);
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.student.id"));
};
class RegistrationAddDTO : public oatpp::DTO {
	DTO_INIT(RegistrationAddDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("common.field.registration.add-time"));
	API_DTO_FIELD_DEFAULT(String, course, ZH_WORDS_GETTER("common.field.registration.course"));
	API_DTO_FIELD_DEFAULT(String, subject, ZH_WORDS_GETTER("common.field.registration.subject"));
	API_DTO_FIELD_DEFAULT(Int32, buyCount, ZH_WORDS_GETTER("common.field.registration.by-count"));
	API_DTO_FIELD_DEFAULT(Int32, UnitPrice, ZH_WORDS_GETTER("common.field.registration.unit-price"));
	API_DTO_FIELD_DEFAULT(Int32, coursePrice, ZH_WORDS_GETTER("common.field.registration.course-price"));
	API_DTO_FIELD_DEFAULT(Int32, salePrice, ZH_WORDS_GETTER("common.field.registration.sale-price"));
	API_DTO_FIELD_DEFAULT(Int32, realityPrice, ZH_WORDS_GETTER("common.field.registration.reality-price"));
	API_DTO_FIELD_DEFAULT(Int32, arrearage, ZH_WORDS_GETTER("common.field.registration.arrearage"));
	API_DTO_FIELD_DEFAULT(String, beginTime, ZH_WORDS_GETTER("common.field.registration.beginTime"));
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("common.field.registration.endTime"));
	API_DTO_FIELD_DEFAULT(Int32, refundPrice, ZH_WORDS_GETTER("common.field.registration.refund-price"));
	API_DTO_FIELD_DEFAULT(Int32, dropClassCount, ZH_WORDS_GETTER("common.field.registration.drop-class-count"));
	API_DTO_FIELD_DEFAULT(String, refundDescripe, ZH_WORDS_GETTER("common.field.registration.refundDescripe"));
    API_DTO_FIELD_DEFAULT(Int32, refundStatus, ZH_WORDS_GETTER("common.field.registration.refund-status"));
};
class RegistrationDTO :public RegistrationAddDTO {
    DTO_INIT(RegistrationDTO, RegistrationAddDTO);
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.registration.id"));
};
class RegistrationPageDTO : public PageDTO<RegistrationDTO::Wrapper> {
	DTO_INIT(RegistrationPageDTO, PageDTO<RegistrationDTO::Wrapper>);
	
};
class FileOnlyDTO :public oatpp::DTO {
	DTO_INIT(FileOnlyDTO, DTO);
    //API_DTO_FIELD_DEFAULT(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("common.field.file.file"),true);多出第四个参数导致编译错误
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("common.field.file.file"), true);
};
class CourseCountDTO :public oatpp::DTO {
	DTO_INIT(CourseCountDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("common.field.course.name"));
	API_DTO_FIELD_DEFAULT(Int32, totalCourseCount, ZH_WORDS_GETTER("common.field.course.total"));
	API_DTO_FIELD_DEFAULT(Int32, leftCourseCount, ZH_WORDS_GETTER("common.field.course.left"));
};
class SaveStudentDTO : public oatpp::DTO {
	DTO_INIT(SaveStudentDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, phone, ZH_WORDS_GETTER("common.field.student.phone"));
	API_DTO_FIELD_DEFAULT(String, parentName, ZH_WORDS_GETTER("common.field.student.parent-name"));
	API_DTO_FIELD_DEFAULT(String, relationType, ZH_WORDS_GETTER("common.field.student.relation-type"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("common.field.student.name"));
	API_DTO_FIELD_DEFAULT(Int32, sex, ZH_WORDS_GETTER("common.field.student.sex"));
	API_DTO_FIELD_DEFAULT(String, enterTime, ZH_WORDS_GETTER("common.field.student.enter-time"));
	API_DTO_FIELD_DEFAULT(Int32, grade, ZH_WORDS_GETTER("common.field.student.grade"));
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("common.field.student.birthday"));
	API_DTO_FIELD_DEFAULT(String, identificationNumber, ZH_WORDS_GETTER("common.field.student.identification-number"));
	API_DTO_FIELD_DEFAULT(Int32, source, ZH_WORDS_GETTER("common.field.student.source"));
	API_DTO_FIELD_DEFAULT(String, note, ZH_WORDS_GETTER("common.field.student.note"));
};
class SaveDTO :public SaveStudentDTO {
	DTO_INIT(SaveDTO, SaveStudentDTO);
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.student.id"));
};



class RegistrationApplyDTO : public oatpp::DTO {

	DTO_INIT(RegistrationApplyDTO, DTO);

	// 学生姓名
	API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("common.field.student.name"));
	// 选择课程
	API_DTO_FIELD_DEFAULT(String, course, ZH_WORDS_GETTER("common.field.registration.course"));
	// 报名类型
	API_DTO_FIELD_DEFAULT(String, subject, ZH_WORDS_GETTER("common.field.registration.subject"));
	// 开始日期
	API_DTO_FIELD_DEFAULT(String, beginTime, ZH_WORDS_GETTER("common.field.registration.begin-time"));
	// 有效期至
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("common.field.registration.end-time"));
	// 购买课时数
	API_DTO_FIELD_DEFAULT(Int32, buyCount, ZH_WORDS_GETTER("common.field.registration.by-count"));
	//课程金额
	API_DTO_FIELD_DEFAULT(Int32, coursePrice, ZH_WORDS_GETTER("common.field.registration.course-price"));
	// 实收金额 (用于校验余额)
	API_DTO_FIELD_DEFAULT(Int32, realityPrice, ZH_WORDS_GETTER("common.field.registration.reality-price"));
	//优惠金额
	API_DTO_FIELD_DEFAULT(Int32, salePrice, ZH_WORDS_GETTER("common.field.registration.sale-price"));
	// 收款经手人
	API_DTO_FIELD_DEFAULT(String, handler, "common.field.registration.price-people");
	// 备注
	API_DTO_FIELD_DEFAULT(String, note, ZH_WORDS_GETTER("common.field.student.note"));

};


class StudentStageUpdateDTO : public oatpp::DTO {
	DTO_INIT(StudentStageUpdateDTO, DTO);

	// 学员 ID 列表 (多选项)
	API_DTO_FIELD_DEFAULT(List<String>, ids, ZH_WORDS_GETTER("common.field.student.id"));

	// 目标阶段：1-意向
	API_DTO_FIELD_DEFAULT(Int32, stage1, ZH_WORDS_GETTER("common.field.student.stage"));

};

/**
 * 删除跟进记录请求 DTO
 */
class DeleteContactRecordDTO : public oatpp::DTO {
	DTO_INIT(DeleteContactRecordDTO, DTO);

	// 跟进记录 ID 列表
	API_DTO_FIELD_DEFAULT(List<Int64>, ids, "contact-record.field.ids");
};







/**
 * 调整积分DTO
 */
class ModifyPointsDTO : public oatpp::DTO
{
	DTO_INIT(ModifyPointsDTO, DTO);
	//id
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.student.id"));
	// 调整积分数
	API_DTO_FIELD_DEFAULT(String, modify_points, ZH_WORDS_GETTER("common.field.student.modify-points"));
	// 调整原因
	API_DTO_FIELD_DEFAULT(String, modify_reason, ZH_WORDS_GETTER("common.field.student.modify-reason"));
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:

};






/**
 * 添加跟进记录
 */
class AddFollowUpRecordDTO : public oatpp::DTO
{
	DTO_INIT(AddFollowUpRecordDTO, DTO);
	//id
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.student.id"));
	// 跟进阶段
	API_DTO_FIELD_DEFAULT(String, follow_up_stage, ZH_WORDS_GETTER("common.field.student.follow-up-stage"));
	//联系途径
	API_DTO_FIELD_DEFAULT(String, contact_channel, ZH_WORDS_GETTER("common.field.student.contact-channel"));
	//联系时间
	API_DTO_FIELD_DEFAULT(String, contact_time, ZH_WORDS_GETTER("common.field.student.contact-time"));
	//下次联系时间
	API_DTO_FIELD_DEFAULT(String, next_contact_time, ZH_WORDS_GETTER("common.field.student.next-contact-time"));
	//联系方式
	API_DTO_FIELD_DEFAULT(String, contact_way, ZH_WORDS_GETTER("common.field.student.contact-way"));
	//跟进内容
	API_DTO_FIELD_DEFAULT(String, follow_up_content, ZH_WORDS_GETTER("common.field.student.follow-up-content"));

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:

};






/**
 * 查询跟进记录DTO
 */
class QueryDTO : public oatpp::DTO
{
	DTO_INIT(QueryDTO, DTO);
	// 跟进时间
	API_DTO_FIELD_DEFAULT(String, follow_up_time, ZH_WORDS_GETTER("common.field.student.follow-up-time"));
	//跟进人
	API_DTO_FIELD_DEFAULT(String, follow_up_person, ZH_WORDS_GETTER("common.field.student.follow-up-person"));
	//客户
	API_DTO_FIELD_DEFAULT(String, customer, ZH_WORDS_GETTER("common.field.student.customer"));
	//阶段
	API_DTO_FIELD_DEFAULT(String, follow_up_stage, ZH_WORDS_GETTER("common.field.student.follow-up-stage"));
	//跟进方式
	API_DTO_FIELD_DEFAULT(String, follow_up_way, ZH_WORDS_GETTER("common.field.student.follow-up-way"));
	//下次跟进时间
	API_DTO_FIELD_DEFAULT(String, next_follow_up_time, ZH_WORDS_GETTER("common.field.student.next-follow-up-time"));
	//记录时间
	API_DTO_FIELD_DEFAULT(String, record_time, ZH_WORDS_GETTER("common.field.student.record-time"));
	//跟进内容
	API_DTO_FIELD_DEFAULT(String, follow_up_content, ZH_WORDS_GETTER("common.field.student.follow-up-content"));


	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:

};class QueryFollowUprecordsDTO : public PageDTO<QueryDTO::Wrapper>
{
	DTO_INIT(QueryFollowUprecordsDTO, PageDTO<QueryDTO::Wrapper>);
};

/**
 * 班级列表新增传输对象
 */
class getClassListAddDTO : public oatpp::DTO
{
	DTO_INIT(getClassListAddDTO, DTO);
	// 序号
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("getClassList.id");
	}
	// 班级名称
	DTO_FIELD(String, className);
	DTO_FIELD_INFO(className) {
		info->description = ZH_WORDS_GETTER("getClassList.name");
	}
	// 科目
	DTO_FIELD(String, subject);
	DTO_FIELD_INFO(subject) {
		info->description = ZH_WORDS_GETTER("getClassList.subject");
	}
	// 教室
	DTO_FIELD(String, classroom);
	DTO_FIELD_INFO(classroom) {
		info->description = ZH_WORDS_GETTER("getClassList.classroom");
	}
	// 学生数
	DTO_FIELD(UInt32, studentCount);
	DTO_FIELD_INFO(studentCount) {
		info->description = ZH_WORDS_GETTER("getClassList.studentCount");
	}
	// 人数上限
	DTO_FIELD(UInt32, maxStudentCount);
	DTO_FIELD_INFO(maxStudentCount) {
		info->description = ZH_WORDS_GETTER("getClassList.maxStudentCount");
	}
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	// 数据校验
	std::string validate()
	{
		// 校验班级名称
		if (!className || className->empty())
			return "className invalidate.";

		// 校验科目
		if (!subject || subject->empty())
			return "subject invalidate.";

		// 校验教室
		if (!classroom || classroom->empty())
			return "classroom invalidate.";

		// 校验学生数
		if (!studentCount || studentCount > maxStudentCount)
			return "studentCount invalidate.";

		// 校验人数上限
		if (!maxStudentCount || maxStudentCount <= 0)
			return "maxStudentCount invalidate.";

		return "";
	}
};

/**
 *  班级列表传输对象
 */
class getClassListDTO : public getClassListAddDTO
{
	DTO_INIT(getClassListDTO, getClassListAddDTO);
	// 编号
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("getClassList.id");
	}
};

/**
 * 班级列表分页查询传输对象
 */
class getClassListPageDTO : public PageDTO<getClassListDTO::Wrapper>
{
	DTO_INIT(getClassListPageDTO, PageDTO<getClassListDTO::Wrapper>);
};



/**
 * 课程统计新增传输对象
 */
class getCourseStatisticsAddDTO : public oatpp::DTO
{
	DTO_INIT(getCourseStatisticsAddDTO, DTO);
	// 课程
	DTO_FIELD(String, course);
	DTO_FIELD_INFO(course) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.course");
	}
	// 总课时
	DTO_FIELD(UInt32, totalHours);
	DTO_FIELD_INFO(totalHours) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.totalHours");
	}
	// 剩余课时
	DTO_FIELD(UInt32, remainingHours);
	DTO_FIELD_INFO(remainingHours) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.remainingHours");
	}
	// 已上课时
	DTO_FIELD(UInt32, attendedHours);
	DTO_FIELD_INFO(attendedHours) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.attendedHours");
	}
	// 到期日期
	DTO_FIELD(String, expireDate);
	DTO_FIELD_INFO(expireDate) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.expireDate");
	}
	//清课优先级
	DTO_FIELD(UInt32, cancelPriority);
	DTO_FIELD_INFO(cancelPriority) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.cancelPriority");
	}

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	// 数据校验
	std::string validate()
	{
		// 校验课程名称
		if (!course || course->empty())
			return "course invalidate.";

		// 校验总课时
		if (!totalHours || totalHours <= 0)
			return "totalHours invalidate.";

		// 校验剩余课时
		if (!remainingHours)
			return "remainingHours invalidate.";

		// 校验已上课时
		if (!attendedHours)
			return "attendedHours invalidate.";

		// 校验到期日期格式（简单非空校验，如需严格格式可扩展）
		if (!expireDate || expireDate->empty())
			return "expireDate invalidate.";

		// 校验清课优先级
		if (!cancelPriority || cancelPriority > 5) // 假设优先级范围为1-5，可根据业务调整
			return "cancelPriority invalidate.";

		// 校验课时逻辑关系：已上课时 + 剩余课时 <= 总课时
		if (totalHours && attendedHours && remainingHours) {
			if (attendedHours + remainingHours > totalHours) {
				return "The sum of attendedHours and remainingHours cannot exceed totalHours.";
			}
		}

		// 校验已上课时不能大于总课时
		if (totalHours && attendedHours && attendedHours > totalHours) {
			return "attendedHours cannot exceed totalHours.";
		}

		// 校验剩余课时不能大于总课时
		if (totalHours && remainingHours && remainingHours > totalHours) {
			return "remainingHours cannot exceed totalHours.";
		}

		return "";
	}
};
/**
 * 课程统计传输对象
 */
class getCourseStatisticsDTO : public getCourseStatisticsAddDTO
{
	DTO_INIT(getCourseStatisticsDTO, getCourseStatisticsAddDTO);
	// 编号
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("getCourseStatistics.id");
	}
};
/**
 * 课程统计分页查询传输对象
 */
class getCourseStatisticsPageDTO : public PageDTO<getCourseStatisticsDTO::Wrapper>
{
	DTO_INIT(getCourseStatisticsPageDTO, PageDTO<getCourseStatisticsDTO::Wrapper>);
};




/**
 * 加入班级新增传输对象
 */
class JoinclassAddDTO : public oatpp::DTO
{
	DTO_INIT(JoinclassAddDTO, DTO);
	// 班级名称
	DTO_FIELD(String, className);
	DTO_FIELD_INFO(className) {
		info->description = ZH_WORDS_GETTER("JoinClass.name");
	}
	// 分校
	DTO_FIELD(String, school);
	DTO_FIELD_INFO(school) {
		info->description = ZH_WORDS_GETTER("JoinClass.school");
	}

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	// 数据校验
	std::string validate()
	{
		if (!className || className->empty())
			return "className invalidate.";
		if (!school || school->empty())
			return "school invalidate.";
		return "";
	}
};
/**
 * 加入班级传输对象
 */
class  JoinclassDTO : public  JoinclassAddDTO
{
	DTO_INIT(JoinclassDTO, JoinclassAddDTO);
	// 编号
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("JoinClass.id");
	}
};
/**
 * 加入班级分页传输对象
 */
class JoinclassPageDTO : public PageDTO<JoinclassDTO::Wrapper>
{
	DTO_INIT(JoinclassPageDTO, PageDTO<JoinclassDTO::Wrapper>);
};



#include OATPP_CODEGEN_END(DTO)
#endif