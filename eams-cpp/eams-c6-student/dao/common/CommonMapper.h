#pragma once
#ifndef COMMONMAPPER_H
#define COMMONMAPPER_H
#include "Mapper.h"
#include "../../domain/dto/common/CommonDTO.h"
class RegistrationRecordMapper : public Mapper<RegistrationDTO::Wrapper> {
public:
	RegistrationDTO::Wrapper mapper(ResultSet* rs) const override {
		auto dto = RegistrationDTO::createShared();

		// SQL 顺序（保持你当前 CommonDAO.cpp 的 SELECT 字段顺序）
		// 1 sc.add_time
		// 2 c.name
		// 3 sub.name
		// 4 sc.count_lesson_total
		// 5 sc.unit_price
		// 6 sc.course_amount
		// 7 sc.discount_amount
		// 8 sc.paid_amount
		// 9 sc.amount-sc.paid_amount
		// 10 sc.start_date
		// 11 sc.expire_date
		// 12 ref.refund_amount
		// 13 ref.refund_amount/sc.unit_price
		// 14 ref.remark
		// 15 ref.verify_state

		dto->addTime = rs->getString(1).c_str();
		dto->course = rs->getString(2).c_str();
		dto->subject = rs->getString(3).c_str();

		dto->buyCount = rs->getInt(4);
		dto->UnitPrice = rs->getInt(5);
		dto->coursePrice = rs->getInt(6);

		dto->salePrice = rs->getInt(7);
		dto->realityPrice = rs->getInt(8);
		dto->arrearage = rs->getInt(9);

		dto->beginTime = rs->getString(10).c_str();
		dto->endTime = rs->getString(11).c_str();

		dto->refundPrice = rs->getInt(12);
		dto->dropClassCount = rs->getInt(13);
		dto->refundDescripe = rs->getString(14).c_str();
		dto->refundStatus = rs->getInt(15);

		// 当前 SQL 未返回 sc.id，因此 dto->id 不赋值（可在需要时把 sc.id 加到 SELECT 前面并同步调整下标）
		return dto;
	}
};


#endif
