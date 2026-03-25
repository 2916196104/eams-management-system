#pragma once
#include "domain/do/BaseDO.h"
#include"../../../../lib-mysql/include/BaseDO.h"
class RefundDO: public BaseDO {
	uint64_t id; // 主键
	uint64_t studentId; //学生id
	uint64_t studentCourseId; //学生课程关联表id
	uint64_t operator_; //退费办理人
	int refundLessonCount; // 退费课时
	std::string applyTime; // 退费发起时间
	double refundAmount; //退费金额 负数
	std::string remark; //退费说明
	std::string done_time; //退费办完时间
	int typeNum; //类型
	int verifyState; //退款状态
	std::string verifyTime; //审核时间
	uint64_t verifyStaff; //审核人
};
class StudentCourseDO : public BaseDO {
	uint64_t id; //主键
	uint64_t studentId; //学生id
	uint64_t courseId; //课程id
	uint64_t subjectId; //科目id
	std::string startDate; //开始时间
	std::string expireDate; //过期时间
	std::string remark; //备注
	uint64_t countLessonTotal; //购买总课次
	uint64_t countLessonComplete; //已上课次
	uint64_t countLessonRefund; //退款次数
	double courseAmount; //套餐金额
	double discordAmount; //优惠金额
	double amount; //成交、合约金额
	double paidAmount; //实付金额
	int payOff; //是否付清 0否1是
	uint64_t operator_; //经手人
	uint64_t creator; //创建人
	std::string addTime; //录入时间
	uint64_t editor; //编辑人
	std::string editTime; //编辑时间
	int deleted; //删除标记
	int verifyState; //审核状态
	int warningTimes; //不足时已提醒次数
	int priority; //消课优先级
	double unitPrice; //单价
	int fromTrial; //是否来自于体验使用
	uint64_t orgId; //报名老师所属组长Id
};