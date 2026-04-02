#include "stdafx.h"
#include "homeworkservice.h"
#include "dao/homework/homeworkdao.h"
#include "dao/homework/HomeworkRecordDAO.h"
#include "SimpleDateTimeFormat.h" 
HomeworkPageJsonVO::Wrapper HomeworkService::queryPage(const HomeworkQuery::Wrapper& query)
{
    HomeworkDAO dao;
    auto count = dao.count(query);
    
    auto dto = HomeworkPageDTO::createShared();
    dto->rows = oatpp::List<HomeworkDTO::Wrapper>::createShared();
    
    if (count > 0)
    {
        auto pageData = dao.selectPage(query);
        for (auto& item : pageData)
        {
            dto->addData(item);
        }
    }
    
    dto->total = count;
    dto->pageIndex = query->pageIndex;
    dto->pageSize = query->pageSize;

    auto result = HomeworkPageJsonVO::createShared();
    result->success(dto);
    return result;
}

HomeworkDetailJsonVO::Wrapper HomeworkService::queryDetail(uint64_t id)
{
    HomeworkDAO dao;
    auto detail = dao.selectDetail(id);

    auto result = HomeworkDetailJsonVO::createShared();
    if (detail) {
        result->success(detail);
    } else {
        result->fail(detail);
        result->message = ZH_WORDS_GETTER("homework.detail.notfound");
    }
    return result;
}

// ====================== 工具方法：获取当前时间 ======================
std::string HomeworkService::getCurrentDateTime()
{
    return SimpleDateTimeFormat::format();
}

// ====================== 提交作业方法 ======================
HomeworkSubmitJsonVO::Wrapper HomeworkService::submitHomework(const HomeworkSubmitDTO::Wrapper& dto)
{
    auto vo = HomeworkSubmitJsonVO::createShared();
    try {
        // 校验
        if (!dto || !dto->homeworkId || !dto->studentId) {
            vo->fail(nullptr);
            return vo;
        }

        // 校验作业存在
        HomeworkDAO homeworkDAO;
        auto homework = homeworkDAO.selectById(dto->homeworkId);
        if (!homework || homework->getDeleted() == 1) {
            vo->fail(nullptr);
            return vo;
        }

        // 构建数据
        HomeworkRecordDO recordData;
        recordData.sethomework_id(dto->homeworkId);
        recordData.setstudent_id(dto->studentId);
        recordData.setcontent(dto->homework_record_content);
        recordData.setimages(dto->images);
        recordData.setadd_time(getCurrentDateTime());

        // 提交
        HomeworkRecordDAO recordDAO;
        recordDAO.submit(recordData);

        // 成功
        auto ret = HomeworkSubmitDTO::createShared();
        ret->homeworkId = dto->homeworkId;
        ret->homework_record_content = dto->homework_record_content;
        /*
        auto test=dto;
        vo->success(test);
        */
        vo->success(ret);
        return vo;
    }
    catch (std::exception& e) {
        // 捕获所有异常，返回失败
        vo->fail(dto);
        return vo;
    }
}

// ====================== 删除作业提交记录方法 ======================
HomeworkDeleteJsonVO::Wrapper HomeworkService::deleteHomework(const HomeworkDeleteQuery::Wrapper& query)
{

    // 1. 入参判空
    if (!query ||
        !query->homeworkId ||
        !query->studentId)
    {
        auto vo = HomeworkDeleteJsonVO::createShared();
        vo->fail(nullptr);
        return vo;
    }

    // 2. 安全取值
    uint64_t studentId = query->studentId.getValue(0);
    uint64_t homeworkId = query->homeworkId.getValue(0);


    // 3. 栈创建DAO
    HomeworkRecordDAO recordDao;

    // 4. 执行删除
    bool success = recordDao.deleteByStudentAndHomework(studentId, homeworkId);

    // 5. 构建返回结果
    auto dto = HomeworkDeleteDTO::createShared();
    dto->homeworkId = homeworkId;
    dto->studentId = studentId;
    dto->deletedCount = success ? 1 : 0;

    auto vo = HomeworkDeleteJsonVO::createShared();
    success ? vo->success(dto) : vo->fail(dto);
    return vo;
}