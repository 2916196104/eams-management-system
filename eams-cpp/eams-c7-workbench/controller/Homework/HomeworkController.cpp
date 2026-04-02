#include "stdafx.h"
#include "HomeworkController.h"
#include "dao/Homework/HomeworkDAO.h"
#include "dao/Homework/HomeworkRecordDAO.h"
#include "domain/do/Homework/HomeworkDO.h"
#include "domain/do/Homework/HomeworkRecordDO.h"
#include "id/SnowFlake.h"

// 临时辅助函数
static SnowFlake snowFlake(1, 1);
static int64_t getCurrentUserId() { return 1; }
static int64_t getCurrentOrgId() { return 1; }
static std::string getCurrentTime() {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return buf;
}

// 布置作业
StringJsonVO::Wrapper HomeworkController::execAssignHomework(const oatpp::Object<AssignHomeworkDTO>& dto)
{
    auto jvo = StringJsonVO::createShared();
    if (!dto || !dto->classId || !dto->title || !dto->content) {
        jvo->code = 400;
        jvo->message = "参数不完整";
        return jvo;
    }

    // 校验班级是否存在（需要 ClassDAO）
    /*ClassDAO classDao;
    auto classDO = classDao.selectById(dto->classId);
    if (!classDO) {
        jvo->code = 400;
        jvo->message = ZH_WORDS_GETTER("homework.error.class_not_exist");  // 可在字典中添加
        return jvo;
    }*/

    HomeworkDO homework;
    homework.setId(snowFlake.nextId());
    homework.setClassId(dto->classId);
    homework.setTitle(dto->title);
    homework.setContent(dto->content);
    homework.setCreator(getCurrentUserId());
    homework.setEditor(getCurrentUserId());
    homework.setAddTime(getCurrentTime());
    homework.setEditTime(getCurrentTime());
    homework.setDeleted(false);
    homework.setOrgId(getCurrentOrgId());

    HomeworkDAO dao;
    bool success = dao.insert(homework);
    if (success) {
        jvo->code = 200;
        jvo->message = "success";
        jvo->data = ZH_WORDS_GETTER("homework.success") + std::to_string(static_cast<uint64_t>(homework.getId()));
    }
    else {
        jvo->code = 500;
        jvo->message = "数据库操作失败";
    }
    return jvo;
}

// 获取作业详情
HomeworkDetailJsonVO::Wrapper HomeworkController::execGetHomeworkDetail(const oatpp::UInt64& homeworkId)
{
    auto jvo = HomeworkDetailJsonVO::createShared();
    if (!homeworkId) {
        jvo->code = 400;
        jvo->message = "作业ID不能为空";
        return jvo;
    }

    uint64_t id = homeworkId.getValue(0);

    HomeworkDAO homeworkDao;
    auto homeworkDO = homeworkDao.selectById(id);
    if (!homeworkDO) {
        jvo->code = 404;
        jvo->message = "作业不存在";
        return jvo;
    }

    // 1. 查询班级名称（需要 ClassDAO）
    // 假设 ClassDAO 有 selectById 方法，返回 ClassDO，其中有 name 字段
    // 暂时模拟
    std::string className = "示例班级";  // 实际应为 classDao.selectById(homeworkDO->getClassId())->getName();

    // 2. 查询教师姓名（需要 StaffDAO）
    std::string teacherName = "示例教师"; // 实际应为 staffDao.selectById(homeworkDO->getCreator())->getName();

    // 3. 查询提交记录列表
    HomeworkRecordDAO recordDao;
    auto recordsDO = recordDao.selectByHomeworkId(id);  // selectByHomeworkId 参数应为 uint64_t

    auto detail = HomeworkDetailDTO::createShared();
    detail->id = id;
    detail->classId = homeworkDO->getClassId();
    detail->title = homeworkDO->getTitle();
    detail->content = homeworkDO->getContent();
    detail->addTime = homeworkDO->getAddTime();
    // 班级名称、教师姓名等需要其他表
    detail->className = "";
    detail->teacherName = "";
    detail->totalStudents = 0;
    detail->submittedCount = 0;
    detail->reviewedCount = 0;

    auto records = Vector<oatpp::Object<HomeworkRecordDTO>>::createShared();
    for (const auto& recordDO : recordsDO) {
        auto record = HomeworkRecordDTO::createShared();
        record->id = recordDO.getId();          // uint64_t
        record->studentId = recordDO.getStudentId();
        // 学生姓名需查询 student 表
        // record->studentName = studentDao.selectById(recordDO.getStudentId())->getName();
        record->studentName = "";
        record->studentNo = "";
        record->content = recordDO.getContent();
        record->addTime = recordDO.getAddTime();
        record->score = recordDO.getScore();
        record->comment = recordDO.getComment();
        record->commentTime = recordDO.getCommentTime();
        // 点评教师姓名需查询 staff 表
        // record->teacherName = staffDao.selectById(recordDO.getCommentTeacher())->getName();
        record->teacherName = "";
        record->status = (recordDO.getScore() > 0) ? 2 : 1;
        records->push_back(record);
    }
    detail->records = records;

    jvo->code = 200;
    jvo->message = "success";
    jvo->data = detail;
    return jvo;
}


// 点评作业
ReviewResultJsonVO::Wrapper HomeworkController::execReviewHomework(const oatpp::Object<ReviewHomeworkDTO>& dto)
{
    auto jvo = ReviewResultJsonVO::createShared();

    if (!dto || !dto->recordId || !dto->score) {
        jvo->code = 400;
        jvo->message = "参数不完整";
        auto result = ReviewResultDTO::createShared();
        result->success = false;
        result->message = ZH_WORDS_GETTER("homework.review.param_incomplete");
        jvo->data = result;
        return jvo;
    }

    uint64_t recordId = dto->recordId.getValue(0);

    // 1. 查询提交记录是否存在
    HomeworkRecordDAO recordDao;
    auto recordDO = recordDao.selectById(recordId);
    if (!recordDO) {
        jvo->code = 404;
        jvo->message = "提交记录不存在";
        auto result = ReviewResultDTO::createShared();
        result->success = false;
        result->message = ZH_WORDS_GETTER("homework.review.record_not_found");
        jvo->data = result;
        return jvo;
    }

    // 2. 更新点评信息
    recordDO->setScore(dto->score);
    recordDO->setComment(dto->comment);
    recordDO->setCommentTime(getCurrentTime());
    recordDO->setCommentTeacher(getCurrentUserId());

    // 3. 执行更新
    bool success = recordDao.update(*recordDO);

    auto result = ReviewResultDTO::createShared();
    if (success) {
        result->success = true;
        result->message = ZH_WORDS_GETTER("homework.review.success");
        result->recordId = recordId;
        jvo->code = 200;
        jvo->message = "success";
    }
    else {
        result->success = false;
        result->message = ZH_WORDS_GETTER("homework.review.fail");
        jvo->code = 500;
        jvo->message = "数据库操作失败";
    }
    jvo->data = result;
    return jvo;
}