#pragma once
#include"../../../../lib-mysql/include/BaseDO.h"
class StudentCourseDO : public BaseDO {
private:
	//主键
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	//学生id
	MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId);
	//课程id
	MYSQL_SYNTHESIZE(uint64_t, courseId, CourseId);
	//科目id
	MYSQL_SYNTHESIZE(uint64_t, subjectId, SubjectId);
	//开始时间
	MYSQL_SYNTHESIZE(std::string, startDate, StartDate);
	//过期时间
	MYSQL_SYNTHESIZE(std::string, expireDate, ExpireDate);
	//备注
	MYSQL_SYNTHESIZE(uint64_t, remark, Remark);
	//购买总课次
	MYSQL_SYNTHESIZE(uint64_t, countLessonTotal, CountLessonTotal);
	//已上课次
	MYSQL_SYNTHESIZE(uint64_t, countLessonComplete, CountLessonComplete);
	//退款次数
	MYSQL_SYNTHESIZE(uint64_t, countLessonRefund, CountLessonRefund);
	//套餐金额
	MYSQL_SYNTHESIZE(double, courseAmount, CourseAmount);
	//优惠金额
	MYSQL_SYNTHESIZE(double, discountAmount, DiscountAmount);
	//成交/合约金额
	MYSQL_SYNTHESIZE(double, amount, Amount);
	//实付金额
	MYSQL_SYNTHESIZE(double, paidAmount, PaidAmount);
	//是否付清 0否1是
	MYSQL_SYNTHESIZE(int, payOff, PayOff);
	//经手人
	MYSQL_SYNTHESIZE(uint64_t, opt, Opt);
	//创建人
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	//录入时间
	MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
	//编辑人
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
	//编辑时间
	MYSQL_SYNTHESIZE(std::string, editTime, EditTime);
	//删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	//审核状态
	MYSQL_SYNTHESIZE(int, verifyState, VerifyState);
	//不足时已提醒次数
	MYSQL_SYNTHESIZE(int, warningTimes, WarningTimes);
	//消课优先级
	MYSQL_SYNTHESIZE(int, priority, Priority);
	//单价
	MYSQL_SYNTHESIZE(double, unitPrice, UnitPrice);
	//是否来自体验试用
	MYSQL_SYNTHESIZE(int, fromTrial, FromTrial);
	//报名老师所属组织ID
	MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);

public:
	StudentCourseDO() : BaseDO("student_course") {
		// 主键 (不能为空)
		MYSQL_ADD_FIELD_PK("id", "i", id);

		// 必须填写的核心字段
		MYSQL_ADD_FIELD("student_id", "i", studentId);
		MYSQL_ADD_FIELD("course_id", "i", courseId);
		MYSQL_ADD_FIELD("subject_id", "i", subjectId);

		// 时间 (允许为空)
		/*MYSQL_ADD_FIELD_NULLABLE("start_date", "s", startDate, false);
		MYSQL_ADD_FIELD_NULLABLE("expire_date", "s", expireDate, false);*/

		// 备注 (不允许为空)
		/*MYSQL_ADD_FIELD_NULLABLE("remark", "i", remark, false);*/

		// 课次
		/*MYSQL_ADD_FIELD_NULLABLE("count_lesson_total", "i", countLessonTotal, false);
		MYSQL_ADD_FIELD_NULLABLE("count_lesson_complete", "i", countLessonComplete, false);
		MYSQL_ADD_FIELD_NULLABLE("count_lesson_refund", "i", countLessonRefund, false);*/

		// 金额
		/*MYSQL_ADD_FIELD_NULLABLE("course_amount", "d", courseAmount, false);
		MYSQL_ADD_FIELD_NULLABLE("discount_amount", "d", discountAmount, false);
		MYSQL_ADD_FIELD_NULLABLE("amount", "d", amount, false);*/
		MYSQL_ADD_FIELD_NULLABLE("paid_amount", "d", paidAmount, false);

		// 支付状态
		MYSQL_ADD_FIELD_NULLABLE("pay_off", "i", payOff, false);

		// 操作人 (允许为空)
		//MYSQL_ADD_FIELD_NULLABLE("operator", "i", opt, false);

		//// 创建信息
		//MYSQL_ADD_FIELD_NULLABLE("creator", "i", creator, false);
		//MYSQL_ADD_FIELD_NULLABLE("add_time", "s", addTime, false);

		//// 编辑信息 (允许为空，刚创建没有编辑)
		//MYSQL_ADD_FIELD_NULLABLE("editor", "i", editor, false);
		//MYSQL_ADD_FIELD_NULLABLE("edit_time", "s", editTime, false);

		//// 状态
		//MYSQL_ADD_FIELD_NULLABLE("deleted", "i", deleted, false);
		//MYSQL_ADD_FIELD_NULLABLE("verify_state", "i", verifyState, false);

		//// 提醒与优先级
		//MYSQL_ADD_FIELD_NULLABLE("warning_times", "i", warningTimes, false);
		//MYSQL_ADD_FIELD_NULLABLE("priority", "i", priority, false);

		//// 单价与体验
		//MYSQL_ADD_FIELD_NULLABLE("unit_price", "d", unitPrice, false);
		//MYSQL_ADD_FIELD_NULLABLE("from_trial", "i", fromTrial, false);

		//// 组织 (允许为空)
		//MYSQL_ADD_FIELD_NULLABLE("org_id", "i", orgId, false);
	}
};
typedef std::shared_ptr<StudentCourseDO> PtrStudentCourseDO;
class RefundDO : public BaseDO {
private:
	//主键
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	//学生id
	MYSQL_SYNTHESIZE(uint64_t, studentId, StudentId);
	//学生课程关联表id
	MYSQL_SYNTHESIZE(uint64_t, studentCourseId, StudentCourseId);
	//退费金额
	MYSQL_SYNTHESIZE(double, refundAmount, RefundAmount);
	//退费课时
	MYSQL_SYNTHESIZE(uint64_t, refundLessonCount, RefundLessonCount);
	//退费发起时间
	MYSQL_SYNTHESIZE(std::string, applyTime, ApplyTime);
	//退费说明
	MYSQL_SYNTHESIZE(std::string, remark, Remark);
	//退费状态
	MYSQL_SYNTHESIZE(int, verifyState, VerifyState);
public:
	RefundDO():BaseDO("refund") {
		MYSQL_ADD_FIELD_PK("id", "i", id);

		// 必须填写的核心字段
		MYSQL_ADD_FIELD("student_id", "i", studentId);
		MYSQL_ADD_FIELD("student_course_id", "i", studentCourseId);
		MYSQL_ADD_FIELD("refund_amount", "d", refundAmount);
		MYSQL_ADD_FIELD("refund_lesson_count", "i", refundLessonCount);
		MYSQL_ADD_FIELD("apply_time", "s", applyTime);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("verify_state", "i", verifyState);
	}
};
typedef std::shared_ptr<RefundDO> PtrRefundDO;