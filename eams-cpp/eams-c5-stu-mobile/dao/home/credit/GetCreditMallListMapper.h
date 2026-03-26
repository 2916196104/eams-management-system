#pragma once
#ifndef _GET_CREDIT_MALL_LIST_MAPPER_H_
#define _GET_CREDIT_MALL_LIST_MAPPER_H_

#include "Mapper.h"
#include "domain/do/home/credit/GetCreditMallListDO.h"

class CreditMallListMapper : public Mapper<PtrCreditMallListDO>
{
public:
	PtrCreditMallListDO mapper(ResultSet* resultSet) const override
	{
		PtrCreditMallListDO creditmallDO = std::make_shared<CreditMallListDO>();
		creditmallDO->setId(resultSet->getInt("id"));
		creditmallDO->setCategory_name(resultSet->getString("category_name"));
		creditmallDO->setName(resultSet->getString("name"));
		creditmallDO->setCredit(resultSet->getInt("credit"));
		//creditmallDO->setSale_num(resultSet->getInt("sale_num"));
		creditmallDO->setCover(resultSet->getString("cover"));// 商品照片地址
		//creditmallDO->setContent(resultSet->getString("content"));

		// 商品图片文件信息
		//if (creditmallDO->getCover() != "")
		//{
		//	PtrCreditMallFileDO fd = std::make_shared<CreditMallFileDO>();
		//	fd->setId(creditmallDO->getCover());
		//	fd->setName(resultSet->getString("name"));
		//	fd->setSavePath(resultSet->getString("save_path"));
		//	creditmallDO->setFile(fd);
		//}
		return creditmallDO;
	}
};

#endif // !_GET_CREDIT_MALL_LIST_MAPPER_H_
