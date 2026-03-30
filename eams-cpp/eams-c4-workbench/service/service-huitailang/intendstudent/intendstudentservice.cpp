#include "stdafx.h"
#include "intendstudentservice.h"
#include "dao/dao-huitailang/addintendstudent/intendstudentDAO.h"
#include "domain/do/StudentDO.h"
#include "id/SnowFlake.h"
#include "SimpleDateTimeFormat.h"
#include "dao/dao-huitailang/addintendstudent/userDAO.h"
#include "domain/do/UserDO.h"


uint64_t IntendstudentService::addintendstudent(const intendedstudentDTO::Wrapper& dto)
{
	// 组装DO数据
	StudentDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Name, studentName, Stage, studentType ,Gender, sex, Birthday,birthday, Idcard,cardId, Remark,text);
	// phonenumber
	// 生成ID
	SnowFlake uf(1,1);
	data.setId(uf.nextId());
	//根据手机号查找对应的用户id
	UserDAO udao;
	UserDO udo;
	//cout << dto->phonenumber.getValue("0") << endl;
	auto resutlt = udao.QueryUid(dto->phoneNumber.getValue("0"));
	if (resutlt.size() == 0)
	{
		udo.setId(uf.nextId());
		udo.setMobile(dto->phoneNumber.getValue("0"));
		if (udao.insert(udo) == 0)
		{
			return 0;
		}
		//resutlt.push_back(udo);
		resutlt = udao.QueryUid(dto->phoneNumber.getValue("0"));
	}
	data.setUserId(resutlt.front().getId());

	 //设置创建人
	data.setCreator(stoull(dto->getPayload()->getId()));
	// 设置创建时间
	data.setAddTime(SimpleDateTimeFormat::format());
	// 执行数据添加

	IntenstudentDAO dao;
	
	return dao.insert(data) == 1 ? data.getId() : 0;
}

