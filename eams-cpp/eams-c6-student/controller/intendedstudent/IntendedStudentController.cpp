#include "stdafx.h"
#include "IntendedStudentController.h"
#include "ExcelComponent.h"

using OutgoingResponse = oatpp::web::server::api::ApiController::OutgoingResponse;
using IncomingRequest = oatpp::web::server::api::ApiController::IncomingRequest;

std::shared_ptr<OutgoingResponse> execExportSample();
{
	// 不写数据库，直接生成 Excel 模板或假数据
	auto buff = ExcelComponent().writeVectorToBuff("intended_student",
		[](ExcelComponent* ex) {
			ex->addHeader({ "编号", "姓名", "年龄", "性别", "手机号", "意向课程" });
		});

	// 返回文件
	auto response = createResponse(Status::CODE_200,
		String(reinterpret_cast<const char*>(buff.data()), buff.size()));
	response->putHeader("Content-Disposition",
		"attachment; filename=意向学生导入模板.xlsx");
	response->putHeader(Header::CONTENT_TYPE,
		"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
	return response;
}

StringJsonVO::Wrapper execImportSample(std::shared_ptr<IncomingRequest> request);
{
    // 0 定义返回数据对象
    auto jvo = StringJsonVO::createShared();

    // 1 初始化
    API_MULTIPART_INIT(container, reader);

    // 2 配置读取器
    API_MULTIPART_CONFIG_MEMO_DEFAULT(reader, -1);

    // 3 读取数据
    request->transferBody(&reader);

    // 4 获取文件数据
    API_MULTIPART_PARSE_FILE_FIELD(container, "excel", file);
    if (!file)
    {
        jvo->init("not set excel file.", RS_PARAMS_INVALID);
        return jvo;
    }

    // 5 解析与校验数据
    std::string errmsg = "";
    int totalCount = 0;
    int validCount = 0;

    ExcelComponent::read(file->data(), file->size(), "sample",
        [&totalCount, &validCount, &errmsg](xlnt::worksheet* sheet)
        {
            // 逐行解析数据
            int rn = 0;
            for (auto row : sheet->rows())
            {
                // 跳过表头
                if (rn++ == 0) continue;

                totalCount++;

                // 解析数据
                std::string name = row[0].to_string();
                std::string ageStr = row[1].to_string();
                std::string sex = row[2].to_string();

                // 校验数据
                if (name.empty())
                {
                    errmsg = "row(" + std::to_string(rn) + ") data error, name is empty";
                    return;
                }
                if (ageStr.empty())
                {
                    errmsg = "row(" + std::to_string(rn) + ") data error, age is empty";
                    return;
                }
                int age = std::atoi(ageStr.c_str());
                if (age < 0 || age > 150)
                {
                    errmsg = "row(" + std::to_string(rn) + ") data error, age invalid";
                    return;
                }
                if (sex != "男" && sex != "女")
                {
                    errmsg = "row(" + std::to_string(rn) + ") data error, sex must be 男 or 女";
                    return;
                }

                validCount++;
                // 不保存，只计数
            }
        });

    if (errmsg != "")
    {
        jvo->init(errmsg, RS_PARAMS_INVALID);
        return jvo;
    }

    if (validCount == 0)
    {
        jvo->init("excel file no data or not excel file.", RS_PARAMS_INVALID);
        return jvo;
    }

    // 6 返回结果（不保存到数据库）
    jvo->success("total: " + std::to_string(totalCount) +
        ", valid: " + std::to_string(validCount));
    return jvo;
}