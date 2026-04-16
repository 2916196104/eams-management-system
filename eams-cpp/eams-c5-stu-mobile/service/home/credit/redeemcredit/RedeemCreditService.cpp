#include "RedeemCreditService.h"
#include "stdafx.h"
#include "SimpleDateTimeFormat.h"
#include "dao/home/credit/redeemcredit/RedeemCreditDAO.h"
#include "id/SnowFlake.h"


std::string RedeemCreditService::saveData(const RedeemCreditDTO::Wrapper& dto)
{
	RedeemCreditDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, CreditMallId, credit_id, StudentId, student_id, SchoolId, school_id, Num, redeem_count);
	
	std::string tmp= dto->getPayload()->getId();
	uint64_t user_id = stoull(tmp);
	SnowFlake sf(1, 1);
	uint64_t id = sf.nextId();
	data.setId(id);
	data.setUserId(user_id);
	data.setCreator(user_id);
	std::string nowDateTime = SimpleDateTimeFormat::format();
	data.setAddTime(nowDateTime);
	data.setVerifyState(1);


	StudentCreditDAO student_dao;
	CreditMallDAO credit_mall_dao;
	int student_credit = (student_dao.selectByStudentId(data.getStudentId()))->getCredit();

	PtrCreditMallDO credit_mall= credit_mall_dao.selectByCreditMallId(data.getCreditMallId());
	uint64_t material_id = credit_mall->getMaritalId();
	int mall_credit = credit_mall->getCredit();
	std::string credit_name = credit_mall->getName();
	bool state = credit_mall->getState();

	data.setDeleted(0);

	data.setCredit(to_string(data.getNum() * mall_credit));


	StudentCreditLogDO data2;//积分变动记录表
	data2.setId(sf.nextId());
	data2.setStudentId(dto->student_id);
	data2.setUserId(user_id);
	data2.setCredit(0-data.getNum() * mall_credit);
	data2.setCurrentCredit(student_credit - data.getNum() * mall_credit);
	data2.setChangeType(2);
	data2.setAddTime(nowDateTime);
	data2.setRemark(ZH_WORDS_GETTER("redeemcredit.remark")+":"+ credit_name+","+ ZH_WORDS_GETTER("redeemcredit.num")+":"+to_string(data.getNum()));
	data2.setSourceId(id);
	data2.setSchoolId(dto->school_id);


	MaterialDAO material_dao;
	uint64_t material_school_id = material_dao.selectByMaterialId(material_id)->getSchoolId();

	MaterialLogDO data3;//出入库记录表
	data3.setId(sf.nextId());
	data3.setMaterialId(material_id);
	data3.setAmount(0 - data.getNum());
	data3.setReason(ZH_WORDS_GETTER("redeemcredit.reason"));
	data3.setChangeType(3);
	data3.setCreator(user_id);
	data3.setAddTime(nowDateTime);
	data3.setStudentId(dto->student_id);
	data3.setSchoolId(material_school_id);
	
	BaseDAO dao;
	dao.insert(data);
	dao.insert(data2);
	dao.insert(data3);

    student_dao.updateCredit(dto->student_id,student_credit - data.getNum() * mall_credit);
	material_dao.updateNum(material_id, data.getNum());

	return ZH_WORDS_GETTER("redeemcredit.request-success");

}