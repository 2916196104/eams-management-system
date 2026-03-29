#ifndef _EXCHANGEMAPPER_H_
#define _EXCHANGEMAPPER_H_

#include "Mapper.h"
#include "domain/do/points-exchange/exchangeDo.h"

// 所有商品映射
class GoodsMapper : public Mapper<GoodsDO>
{
public:
	GoodsDO mapper(ResultSet* resultSet) const override {
		auto goodsDO = GoodsDO();
		goodsDO.setId(resultSet->getInt("id"));
		goodsDO.setSchoolId(resultSet->getInt("school_id"));
		goodsDO.setMaterialId(resultSet->getInt("material_id"));
		goodsDO.setCategoryId(resultSet->getInt("category_id"));
		goodsDO.setCategoryName(resultSet->getString("category_name"));
		goodsDO.setName(resultSet->getString("name"));
		goodsDO.setCredit(resultSet->getInt("credit"));
		goodsDO.setState(resultSet->getInt("state"));
		goodsDO.setSaleNum(resultSet->getInt("sale_num"));
		goodsDO.setViewNum(resultSet->getInt("view_num"));
		goodsDO.setCover(resultSet->getString("cover"));
		goodsDO.setContent(resultSet->getString("content"));
		goodsDO.setCreator(resultSet->getInt("creator"));
		goodsDO.setEditor(resultSet->getInt("editor"));
		goodsDO.setAddTime(resultSet->getString("add_time"));
		goodsDO.setEditTime(resultSet->getString("edit_time"));
		goodsDO.setDeleted(resultSet->getInt("deleted"));
		goodsDO.setOrgId(resultSet->getInt("org_id"));
		goodsDO.setSchoolName(resultSet->getString("school_name"));
		goodsDO.setStorage(resultSet->getInt("storage"));
		return goodsDO;
	}
};

class PtrGoodsMapper : public Mapper<PtrGoodsDO>
{
public:
	PtrGoodsDO mapper(ResultSet* resultSet) const override {
		auto goodsDO = std::make_shared<GoodsDO>();
		goodsDO->setId(resultSet->getInt("id"));
		goodsDO->setSchoolId(resultSet->getInt("school_id"));
		goodsDO->setMaterialId(resultSet->getInt("material_id"));
		goodsDO->setCategoryId(resultSet->getInt("category_id"));
		goodsDO->setCategoryName(resultSet->getString("category_name"));
		goodsDO->setName(resultSet->getString("name"));
		goodsDO->setCredit(resultSet->getInt("credit"));
		goodsDO->setState(resultSet->getInt("state"));
		goodsDO->setSaleNum(resultSet->getInt("sale_num"));
		goodsDO->setViewNum(resultSet->getInt("view_num"));
		goodsDO->setCover(resultSet->getString("cover"));
		goodsDO->setContent(resultSet->getString("content"));
		goodsDO->setCreator(resultSet->getInt("creator"));
		goodsDO->setEditor(resultSet->getInt("editor"));
		goodsDO->setAddTime(resultSet->getString("add_time"));
		goodsDO->setEditTime(resultSet->getString("edit_time"));
		goodsDO->setDeleted(resultSet->getInt("deleted"));
		goodsDO->setOrgId(resultSet->getInt("org_id"));
		goodsDO->setSchoolName(resultSet->getString("school_name"));
		goodsDO->setStorage(resultSet->getInt("storage"));
		return goodsDO;
	}
};

// 积分兑换记录
class PtrAcceptGoodsMapper : public Mapper<PtrAcceptGoodsDO>
{
public:
	PtrAcceptGoodsDO mapper(ResultSet* resultSet) const override
	{
		auto acceptGoodsDO = std::make_shared<AcceptGoodsDO>();
		acceptGoodsDO->setId(resultSet->getInt("id"));
		acceptGoodsDO->setCreditMallId(resultSet->getInt("credit_mall_id"));
		acceptGoodsDO->setSchoolId(resultSet->getInt("school_id"));
		acceptGoodsDO->setCreator(resultSet->getInt("creator"));
		acceptGoodsDO->setEditor(resultSet->getInt("editor"));
		acceptGoodsDO->setAddTime(resultSet->getString("add_time"));
		acceptGoodsDO->setEditTime(resultSet->getString("edit_time"));
		acceptGoodsDO->setDeleted(resultSet->getInt("deleted"));
		acceptGoodsDO->setStudentId(resultSet->getInt("student_id"));
		acceptGoodsDO->setUserId(resultSet->getInt("user_id"));
		acceptGoodsDO->setNum(resultSet->getInt("num"));
		acceptGoodsDO->setCredit(resultSet->getString("credit"));
		acceptGoodsDO->setVerifyState(resultSet->getInt("verify_state"));
		acceptGoodsDO->setVerifyStaff(resultSet->getInt("verify_staff"));
		acceptGoodsDO->setVerifyTime(resultSet->getString("verify_time"));
		acceptGoodsDO->setVerifyRemark(resultSet->getString("verify_remark"));
		acceptGoodsDO->setCreditMallName(resultSet->getString("credit_mall_name"));
		acceptGoodsDO->setCover(resultSet->getString("cover"));
		acceptGoodsDO->setStudentName(resultSet->getString("student_name"));
		acceptGoodsDO->setSchoolName(resultSet->getString("school_name"));
		acceptGoodsDO->setMobile(resultSet->getString("mobile"));
		acceptGoodsDO->setVerifyStaffName(resultSet->getString("verify_staff_name"));

		return acceptGoodsDO;
	}
};


// 积分兑换规则
class SettingMapper : public Mapper<SettingDO>
{
public:
	SettingDO mapper(ResultSet* resultSet) const override {
		SettingDO data;
		data.setId(resultSet->getInt("id"));
		data.setSettingId(resultSet->getInt("setting_id"));
		data.setName(resultSet->getString("name"));
		data.setValue(resultSet->getString("value"));
		data.setValueType(resultSet->getString("value_type"));
		data.setInfo(resultSet->getString("info"));
		data.setCode(resultSet->getString("code"));
		data.setSortNum(resultSet->getInt("sort_num"));
		return data;
	}
};

class PtrSettingMapper : public Mapper<PtrSettingDO> {
public:
	PtrSettingDO mapper(ResultSet* resultSet) const override {

		auto data = std::make_shared<SettingDO>();
		data->setId(resultSet->getInt("id"));
		data->setSettingId(resultSet->getInt("setting_id"));
		data->setName(resultSet->getString("name"));
		data->setValue(resultSet->getString("value"));
		data->setValueType(resultSet->getString("value_type"));
		data->setInfo(resultSet->getString("info"));
		data->setCode(resultSet->getString("code"));
		data->setSortNum(resultSet->getInt("sort_num"));
		return data;
	}
};


#endif
