#pragma once
#include <string>
#include <vector>


// 1. 作业列表查询参数
struct HomeworkListQuery {
    std::string admin_id;  // 管理员ID（权限校验）
    std::string class_id;  // 班级ID（筛选作业）
    int page = 1;          // 页码，默认1
    int size = 10;         // 每页条数，默认10
};

// 2. 作业详情查询参数
struct HomeworkDetailQuery {
    std::string homework_id;  // 作业ID
    std::string admin_id;     // 管理员ID
};

// 3. 布置作业参数
struct HomeworkAddQuery {
    std::string admin_id;    // 发布人ID
    std::string class_id;    // 班级ID（对应前端班级选择）
    std::string title;       // 作业标题
    std::string content;     // 作业要求
    std::string attachment;  // 附件URL
};

// 4. 班级列表查询参数
struct ClassListQuery {
    std::string admin_id;  // 管理员ID（查可管理班级）
};

// 5. 作业点评参数
struct HomeworkCommentQuery {
    std::string submit_id;  // 提交记录ID（关联学生作业）
    std::string admin_id;   // 点评老师ID
    int score;              // 评分（1-5星）
    std::string content;    // 评语
};


// 1. 班级VO（布置作业时的班级选项）
struct ClassVO {
    std::string class_id;   // 班级ID
    std::string class_name; // 班级名称（如“5班”）
    // 测试
    ClassVO() : class_id("class001"), class_name("5班") {}
};

// 2. 点评VO（嵌套在提交记录中）
struct HomeworkCommentVO {
    std::string comment_id; // 点评ID
    int score;              // 评分
    std::string content;    // 评语
    std::string create_time;// 点评时间
    // 测试默认值
    HomeworkCommentVO() : comment_id("comment001"), score(5), content("完成得很好！"), create_time("2026-03-16 19:46") {}
};

// 3. 提交记录VO（嵌套在作业详情中）
struct HomeworkSubmitVO {
    std::string student_name;  // 学生姓名
    std::string submit_content;// 提交内容
    std::string submit_time;   // 提交时间
    HomeworkCommentVO comment; // 点评信息
  
    HomeworkSubmitVO() : student_name("1111"), submit_content("666"), submit_time("2026-03-12 19:46"), comment(HomeworkCommentVO()) {}
};

// 4. 作业列表项VO（列表展示单条作业）
struct HomeworkListItemVO {
    std::string homework_id; // 作业ID
    std::string title;       // 作业标题
    std::string class_name;  // 班级名称
    int submit_count;        // 提交人数
    std::string create_time; // 创建时间
    
    HomeworkListItemVO() : homework_id("hw001"), title("测试作业标题"), class_name("5班"), submit_count(0), create_time("2026-03-16") {}
};

// 5. 作业详情VO（详情页展示）
struct HomeworkDetailVO {
    std::string homework_id;    // 作业ID
    std::string title;          // 标题
    std::string class_name;     // 班级名称
    std::string content;        // 作业要求
    std::string attachment;     // 附件URL
    std::vector<HomeworkSubmitVO> submit_list; // 提交记录列表
  
    HomeworkDetailVO() : homework_id("hw001"), title("测试作业标题"), class_name("5班"), content("作业要求内容"), attachment(""), submit_list({ HomeworkSubmitVO() }) {}
};

// 6. 布置作业响应VO（提交成功返回）
struct HomeworkAddVO {
    std::string homework_id; // 生成的作业ID
    std::string title;       // 作业标题
    std::string create_time; // 创建时间
    // 测试默认值
    HomeworkAddVO() : homework_id("hw002"), title("新作业"), create_time("2026-03-16") {}
};

// 统一响应VO（所有接口返回格式）
template <typename T>
struct CommonResponseVO {
    int code = 0;             // 0=成功，其他=失败
    std::string msg = "success"; // 提示信息
    T data;                   // 业务数据（泛型适配所有VO）
};