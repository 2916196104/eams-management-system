#pragma once
#ifndef STAFF_CONTROLLER_H
#define STAFF_CONTROLLER_H

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/query/PageQuery.h"
#include "domain/dto/staff/StaffDTO.h" 
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include"domain/query/staff/StaffQuery.h"
#include "domain/vo/staff/StaffVO.h"
#include "domain/query/staff/StaffBatchDeleteQuery.h"
using namespace oatpp;


// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("staff.tag")

class StaffController : public oatpp::web::server::api::ApiController
{
    // 添加访问定义
    API_ACCESS_DECLARE(StaffController);

public:
	// 定义接口:获取员工列表
	// 接口描述
	ENDPOINT_INFO(getEmpList) {
		// 接口描述
		info->summary = ZH_WORDS_GETTER("staff.getEmpList.controller.summary");

		// 支持授权(文档描述时显示锁)
		// 同时要向ENDPOINT加入参数五
		API_DEF_ADD_AUTH();

		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);// 文档中会展示响应参数格式

		// 定义请求参数格式
		// 分页参数："查询页码"、"每页的条数"
		API_DEF_ADD_PAGE_PARAMS();// 这个宏用于定义"分页相关"的查询参数文档(会向文档中加入"查询页码"、"每页的条数"参数)
		// 其他参数："姓名/手机号"、"状态"
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("staff.getEmpList.controller.empName"), ZH_WORDS_GETTER("getEmpList.controller.zhangsan"), false);
		API_DEF_ADD_QUERY_PARAMS(String, "phone", ZH_WORDS_GETTER("staff.getEmpList.controller.phone"), "13800138000", false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "status", ZH_WORDS_GETTER("staff.getEmpList.controller.status"), 1, false);

		API_DEF_ADD_TAG(API_TAG);
	}
	
	// 接口定义(路由注册)
	// 需要的查询参数有多个，所以参数四用QUERIES(变量类型, 变量名)
	ENDPOINT(API_M_GET, "/c2-org/staff/getEmpList", getEmpList, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		// 解析报文参数:params-->PageQuery类型的query变量
		API_HANDLER_QUERY_PARAM(query, StaffPageQuery, params); // PageQuery类是专为分页查询的数据对象,详情看其定义

		// 响应业务处理函数的处理结果(executeGetEmpList会返回VO，之后传参)
		API_HANDLER_RESP_VO(executeGetEmpList(query));

	}


	// 定义接口:保存员工

	// 3.1 定义新增接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("staff.saveEmp.controller.summary"), saveEmp, StringJsonVO::Wrapper, API_TAG);

	// 3.2 定义新增接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c2-org/staff/saveEmp", saveEmp, BODY_DTO(StaffSaveDTO::Wrapper, dto), executeSaveEmp(dto));
	

	// 定义修改头像接口
	ENDPOINT_INFO(modifyAvatar) {
		info->summary = ZH_WORDS_GETTER("institution.modifyAvatar.summary");
		// 支持授权
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
		//声明接收文件表单，定义参数请求格式
		API_DEF_ADD_FILE_FORM(AvatarUploadDTO::Wrapper);
		API_DEF_ADD_TAG(API_TAG);
	}
	ENDPOINT(API_M_POST, "/c2-org/staff/modifyAvatar", modifyAvatar, BODY_DTO(AvatarUploadDTO::Wrapper,dto), API_HANDLER_AUTH_PARAME) {
		// 直接调用处理函数
		API_HANDLER_RESP_VO(executeModifyAvatar(dto));
		//return createResponse(Status::CODE_200, ZH_WORDS_GETTER("modifyAvatar.resp"));

    }
	//定义修改密码接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("staff.change-psword.summary"), changePassword, StringJsonVO::Wrapper,ZH_WORDS_GETTER("staff.tag"));
	//定义修改密码接口
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c2-org/staff/changePassword", changePassword, BODY_DTO(StaffChangePasswordDTO::Wrapper, dto), executeStaffPassWordChange(dto));

	//定义员工列表导出接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("staff.export-list.summary"), exportList, StaffExportQueryDto, StringJsonVO::Wrapper, ZH_WORDS_GETTER("staff.tag"));

	//定义员工列表导出接口
	ENDPOINT(API_M_GET, "/c2-org/staff/list", exportList, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(exportQuery, StaffExportQueryDto, queryParams);
		API_HANDLER_RESP_VO(executeStaffListExport(exportQuery));
	}

    //定义获取代班记录接口
	ENDPOINT_INFO(getDutyRecord) {
	  info->summary = ZH_WORDS_GETTER("institution.getDutyRecord.summary");
	  //支持授权
	  API_DEF_ADD_AUTH();
	  //定义响应参数格式
	  API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
	  //定义请求参数格式
	  API_DEF_QUERY_PARAM_BUILD(DutyRecordQueryDTO);
	  API_DEF_ADD_TAG(API_TAG);
	}
    ENDPOINT(API_M_GET, "/c2-org/employee/getDutyRecord", getDutyRecord, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
        //解析查询参数
        API_HANDLER_QUERY_PARAM(query, DutyRecordQueryDTO, params);
        //相应结果
        API_HANDLER_RESP_VO(executegetDutyRecord(query));
        //return createResponse(Status::CODE_200, ZH_WORDS_GETTER("getDutyRecord.resp"));
    }

    // ==================== 根据ID查询员工详细信息 ====================
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("staff.query-one.summary"),
        getStaffDetail,
        StaffDetailJsonVO::Wrapper,
        API_TAG,
        API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("staff.field.id"), "", true);
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_GET,
        "/org/staff/detail",
        getStaffDetail,
        QUERY(String, id),
        execGetStaffDetail(id)
    );

    // ==================== 根据ID批量删除员工 ====================
    // 使用 DeleteResultJsonVO 返回删除结果
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("staff.delete-staff.summary"),
        removeStaffByIds,
        DeleteResultJsonVO::Wrapper,  // 使用专门的删除结果VO
        API_TAG
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_DEL,
        "/c2-org/staff/remove",
        removeStaffByIds,
        BODY_DTO(StaffBatchDeleteQuery::Wrapper, deleteQuery),  // 使用完整类型
        execRemoveStaffByIds(deleteQuery)
    );

	// 定义设置角色接口描述(支持批量)
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("staff.setRole"), setRole, ListJsonVO<String>::Wrapper, API_TAG);
	// 定义设置角色接口处理(支持批量)
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/c2-org/staff/setRole", setRole, BODY_DTO(List<String>, ids), execSetRole(ids, authObject->getPayload()));

	// 定义在职状态接口描述(支持批量)
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("staff.setOnJob"), setOnJob, ListJsonVO<String>::Wrapper, API_TAG);
	// 定义在职状态接口处理(支持批量)
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/c2-org/staff/setOnJob", setOnJob, BODY_DTO(List<String>, ids), execSetJob(ids, authObject->getPayload()));

	// 定义转出机构接口描述(支持批量)
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("staff.setInstitution"), setInstitution, ListJsonVO<String>::Wrapper, API_TAG);
	// 定义转出机构接口处理(支持批量)
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/c2-org/staff/setInstitution", setInstitution, BODY_DTO(List<String>, ids), execSetInstitution(ids, authObject->getPayload()));

private:
    StaffDetailJsonVO::Wrapper execGetStaffDetail(const String& id);
    DeleteResultJsonVO::Wrapper execRemoveStaffByIds(const StaffBatchDeleteQuery::Wrapper& deleteQuery);
private: // 定义接口执行函数
	// 设置角色
	ListJsonVO<String>::Wrapper execSetRole(const List<String>& ids, const PayloadDTO& payload);
	// 在职状态
	ListJsonVO<String>::Wrapper execSetJob(const List<String>& ids, const PayloadDTO& payload);
	// 转出机构
	ListJsonVO<String>::Wrapper execSetInstitution(const List<String>& ids, const PayloadDTO& payload);
private: // 定义接口执行函数
	// 获取员工列表
	StringJsonVO::Wrapper executeGetEmpList(const StaffPageQuery::Wrapper& query);

	// 保存员工(新增员工+更新员工)
	StringJsonVO::Wrapper executeSaveEmp(const StaffSaveDTO::Wrapper& dto);

	StringJsonVO::Wrapper executeModifyAvatar(const AvatarUploadDTO::Wrapper& dto);
    StringJsonVO::Wrapper executegetDutyRecord(const DutyRecordQueryDTO::Wrapper& query);
	StringJsonVO::Wrapper executeStaffPassWordChange(const StaffChangePasswordDTO::Wrapper& dto);
	StringJsonVO::Wrapper executeStaffListExport(const StaffExportQueryDto::Wrapper& exportQuery);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_STAFF_CONTROLLER_
