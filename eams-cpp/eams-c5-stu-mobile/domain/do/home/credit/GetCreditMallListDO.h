#pragma once
#ifndef _GET_CREDIT_MALL_LIST_DO_H_
#define _GET_CREDIT_MALL_LIST_DO_H_

#include "../../DoInclude.h"
//#include "GetCreditMallListFileDO.h"

/**
 * 获取积分商品的数据实体
 */

class CreditMallListDO : public BaseDO
{
	// 商品主键
	MYSQL_SYNTHESIZE(int, id, Id);
	// 分类名称
	MYSQL_SYNTHESIZE(string, category_name, Category_name);
	// 商品名称
	MYSQL_SYNTHESIZE(string, name, Name);
	// 商品积分
	MYSQL_SYNTHESIZE(int, credit, Credit);
	// 剩余数量
	//MYSQL_SYNTHESIZE(int, sale_num, Sale_num);
	// 商品照片地址
	MYSQL_SYNTHESIZE(string, cover, Cover);
	// 详情内容
	//MYSQL_SYNTHESIZE(string, content, Content);

	//	// 关联一个文件实体，存储头像文件信息
	//CC_SYNTHESIZE(PtrCreditMallFileDO, file, File);


public:
	CreditMallListDO() : BaseDO("credit_mall")
	{
		MYSQL_ADD_FIELD("id", "i", id);
		MYSQL_ADD_FIELD("category_name", "s", category_name);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("credit", "i", credit);
		//MYSQL_ADD_FIELD("sale_num", "i", sale_num);
		MYSQL_ADD_FIELD("cover", "s", cover);
		//MYSQL_ADD_FIELD("content", "s", content);

	}
};

typedef std::shared_ptr<CreditMallListDO> PtrCreditMallListDO;



#endif // !_GET_CREDIT_MALL_LIST_DO_H_
