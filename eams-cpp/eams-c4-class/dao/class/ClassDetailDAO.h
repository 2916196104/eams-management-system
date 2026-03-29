#pragma once
#ifndef CLASSDETAIL_DAO_
#define CLASSDETAIL_DAO_
#include"BaseDAO.h"
#include"../../domain/do/ViewDO/ClassDetailDO.h"

class ClassDetailDAO : public BaseDAO
{
private:

	public:
	//根据班级ID查询班级详情
		PtrClassDetailDO selectClassDetailById(std::string id);
};

#endif // !CLASSDETAIL_DAO_
