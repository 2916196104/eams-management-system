#include "stdafx.h"
#include "PointService.h"
#include "id/UuidFacade.h"
#include "dao/PointDAO.h"
#include "domain/do/PointDO.h"
// 放到最后导入防止编译冲突
#include "NacosClient.h"

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

PointPageDTO::Wrapper PointService::listAll(const PointQuery::Wrapper& query)
{
	// 定义一个分页对象
	auto page = PointPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	// 获取数据总条数
	PointDAO ud;
	auto count = ud.count(query);
	if (count <= 0)
		return page;
	page->total = count;
	page->calcPages();

	// 获取文件服务器地址
	//std::string urlPrefix = getDfsServerAddrssUrl();
	// 获取分页数据
	auto list = ud.selectWithPage(query);
	for (auto& one : list)
	{
		auto point = PointDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(point, one, student_id, StudentId, credit, Credit,  current_credit, CurrentCredit,  add_time, AddTime,  remark,Remark);
		//if (one->getFile())
		//{
		//	user->avatarUrl = urlPrefix + one->getFile()->getSavePath();
		//}

		page->addData(point);
	}
	return page;
}


