#include "stdafx.h"
#include "exchangeService.h"
#include "dao/points-exchange/exchangeDAO.h"
#include "NacosClient.h"

// 获取文件服务器地址
std::string exchangeService::getDfsServerAddrssUrl()
{
	/** 定义一个Nacos客户端对象，用于获取配置 */
	NacosClient _ns(ServerInfo::getInstance().getNacosAddr(), ServerInfo::getInstance().getNacosNs());
#ifdef LINUX
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("third-services.yaml");
#else
	/** 读取配置数据节点 */
	auto _thirdServerConfig = _ns.getConfig("./conf/third-services.yaml");
#endif
	return "http://" + YamlHelper().getString(&_thirdServerConfig, "fastdfs.nginx-servers") + "/";
}

// 积分礼品列表
GoodsPageDTO::Wrapper exchangeService::listAllGoods(const PageQuery::Wrapper& query)
{
	auto page = GoodsPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	exchangeDAO dao;
	auto count = dao.count1();
	// 没有数据，则直接返回
	if (count <= 0)
		return page;

	page->total = count;
	page->calcPages();

	// 获取文件服务器地址
	std::string urlPrefix = getDfsServerAddrssUrl();

	// 获取积分礼品列表
	std::list<PtrGoodsDO> list = dao.selectAllGoods(query);

	// 将DO类型的数据转换为DTO
	for (PtrGoodsDO one : list)
	{
		GoodsDTO::Wrapper good = GoodsDTO::createShared();

		ZO_STAR_DOMAIN_DO_TO_DTO_1(good, one, id, Id, schoolId, SchoolId, materialId, MaterialId, categoryId,
			CategoryId, categoryName, CategoryName, name, Name, credit, Credit,
			state, State, saleNum, SaleNum, viewNum, ViewNum, cover, Cover, content,
			Content, creator, Creator, editor, Editor, addTime, AddTime, editTime,
			EditTime, deleted, Deleted, orgId, OrgId, schoolName, SchoolName, storage, Storage);

		// 修改路径地址为完整的URL
		if (good->cover != nullptr)
			good->cover = urlPrefix + good->cover;
		page->addData(good);
	}
	return page;
}


// 兑换记录列表
AcceptGoodsPageDTO::Wrapper exchangeService::listAcceptGoods(const AcceptGoodsQuery::Wrapper& query)
{
	auto page = AcceptGoodsPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	exchangeDAO dao;
	auto count = dao.count2(query);
	// 没有数据，则直接返回
	if (count <= 0)
		return page;

	page->total = count;
	page->calcPages();

	// 获取文件服务器地址
	std::string urlPrefix = getDfsServerAddrssUrl();

	std::list<PtrAcceptGoodsDO> list = dao.selectAcceptGoods(query);

	// 将DO类型数据转换为DTO
	for (auto one : list)
	{
		AcceptGoodsDTO::Wrapper acceptGoods = AcceptGoodsDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO_1(acceptGoods, one, id, Id, creditMallId, CreditMallId, schoolId, SchoolId, creator, Creator,
			editor, Editor, addTime, AddTime, editTime, EditTime, deleted, Deleted, studentId, StudentId, userId, UserId,
			num, Num, credit, Credit, verifyState, VerifyState, verifyStaff, VerifyStaff, verifyTime, VerifyTime, verifyRemark, VerifyRemark,
			creditMallName, CreditMallName, cover, Cover, studentName, StudentName, schoolName, SchoolName, mobile, Mobile, verifyStaffName, VerifyStaffName);

		// 修改路径地址为完整的URL
		if (acceptGoods->cover != nullptr)
			acceptGoods->cover = urlPrefix + acceptGoods->cover;
		page->addData(acceptGoods);
	}
	return page;
}

// 查询积分兑换规则
SettingDTO::Wrapper exchangeService::getSetting(uint64_t id)
{
	SettingDTO::Wrapper setting = SettingDTO::createShared();
	exchangeDAO dao;
	auto res = dao.selectById(id);

	if (!res)
		return nullptr;
	// 将DO类型数据转换为DTO
	ZO_STAR_DOMAIN_DO_TO_DTO_1(setting, res, id, Id, settingId, SettingId, name, Name, code, Code,
		value, Value, valueType, ValueType, info, Info, sortNum, SortNum);
	return setting;
}