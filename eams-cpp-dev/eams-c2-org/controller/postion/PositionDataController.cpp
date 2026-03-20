#include "stdafx.h"
#include "PositionDataController.h"
#include "service/datapermission/PermissionService.h"
#include "Message.h"

Uint64JsonVO::Wrapper PositionDataController::executesavePositionDataPermission(const PositionDataDTO::Wrapper& dto)
{
	// 呼叫职位数据权限相关服务来执行业务逻辑
	DataPermissionService ds;
	auto res = ds.savePermission(dto);

	auto uvo = Uint64JsonVO::createShared();
	if (res)
		if (dto->id)
			uvo->init(res, ResultStatus(ZH_WORDS_GETTER("datapermission.endpoint.resp.modifysuccess")));
		else
			uvo->init(res, ResultStatus(ZH_WORDS_GETTER("datapermission.endpoint.resp.addsuccess")));
	else
		if(dto->id)
			uvo->init({}, ResultStatus(ZH_WORDS_GETTER("datapermission.endpoint.resp.modifyfail"), 9999));
		else
			uvo->init({}, ResultStatus(ZH_WORDS_GETTER("datapermission.endpoint.resp.addfail"), 9999));
	return uvo;
}

ListJsonVO<UInt64>::Wrapper PositionDataController::execdeleteDataPermission(const List<UInt64>& ids)
{
	auto vo = ListJsonVO<UInt64>::createShared();

	// 检查ids是否为空
	if (ids->empty())
	{
		vo->init(nullptr, RS_PARAMS_INVALID);
		return vo;
	}

	// 呼叫职位数据权限相关服务来执行业务逻辑
	int res = DataPermissionService().deletePermissions(ids);
	if (res != ids->size())
	{
		unique_ptr<char> msg(new char[200]);
		sprintf(msg.get(), u8"删除失败，事务中只成功删除%d条数据，事务已回滚", res);
		vo->init({}, ResultStatus(msg.get(), 9999));
	}
	else
		vo->success(ids);
	return vo;
}

