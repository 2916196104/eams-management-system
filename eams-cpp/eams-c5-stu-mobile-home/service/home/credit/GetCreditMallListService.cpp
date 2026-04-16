#include "stdafx.h"
#include "GetCreditMallListService.h"
#include "id/UuidFacade.h"
#include "dao/home/credit/GetCreditMallListDAO.h"

//#include "NacosClient.h"

//std::string UserService::getDfsServerAddrssUrl()
//{
//	/** 定义一个Nacos客户端对象，用于获取配置 */
//	NacosClient _ns(ServerInfo::getInstance().getNacosAddr(), ServerInfo::getInstance().getNacosNs());
//#ifdef LINUX
//	/** 读取配置数据节点 */
//	auto _thirdServerConfig = _ns.getConfig("third-services.yaml");
//#else
//	/** 读取配置数据节点 */
//	auto _thirdServerConfig = _ns.getConfig("./conf/third-services.yaml");
//#endif
//	return "http://" + YamlHelper().getString(&_thirdServerConfig, "fastdfs.nginx-servers") + "/";
//}

CreditMallListPageDTO::Wrapper CreditMallListService::listAll(const CreditMallListQuery::Wrapper& query)
{
	// 定义一个分页对象
	auto page = CreditMallListPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	// 获取数据总条数
	CreditMallListDAO cmd;
	auto count = cmd.count(query);
	if (count <= 0)
		return page;
	page->total = count;
	page->calcPages();
	// 获取文件服务器地址
	//std::string urlPrefix = getDfsServerAddrssUrl();

	// 获取分页数据
	auto list = cmd.selectAll(query);
	for (auto one : list)
	{
		auto creditmall = CreditMallListDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO_1(creditmall, one, category_name, Category_name, name, Name, credit, Credit, cover, Cover);
		page->addData(creditmall);
	}
	return page;
}

//CreditMallDetailDTO::Wrapper CreditMallService::getCreditMallDetail(const oatpp::Int32& id)
//{
//	CreditMallDAO cmd;
//	auto data = cmd.selectDetail(id.getValue(0));
//	
//	if (!data)
//		return nullptr;
//	auto dto = CreditMallDetailDTO::createShared();
//	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, data, name, Name, credit, Credit, cover, Cover, content, Content);
//
//
//	return dto;
//}
