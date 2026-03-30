#pragma once
#ifndef COMMON_RESPONSE_DTO_H
#define COMMON_RESPONSE_DTO_H

#include "../../GlobalInclude.h"
#include "ServerInfo.h" // 中文字典需要引入的头文件
#include "Macros.h"     // 中文字典需要引入的头文件

#include OATPP_CODEGEN_BEGIN(DTO)

class CommonResponseDTO : public oatpp::DTO {
  DTO_INIT(CommonResponseDTO, DTO);

  DTO_FIELD(Int32, code) = 0;
  DTO_FIELD_INFO(code) {
    info->description = u8"\u72B6\u6001\u7801";
  }
  DTO_FIELD(String, msg) = "success";
  DTO_FIELD_INFO(msg) {
    info->description = u8"\u63D0\u793A\u4FE1\u606F";
  }
  DTO_FIELD(String, data);
  DTO_FIELD_INFO(data) {
    info->description = u8"\u6570\u636E\u5BF9\u8C61";
  }
};

class HomeworkListRowDTO : public oatpp::DTO {
  DTO_INIT(HomeworkListRowDTO, DTO);
  // 作业ID
  API_DTO_FIELD(String, homework_id, ZH_WORDS_GETTER("homework.listRow.homework_id"), false, "");
  // 作业标题
  API_DTO_FIELD(String, title, ZH_WORDS_GETTER("homework.listRow.title"), false, "");
  // 班级名称
  API_DTO_FIELD(String, class_name, ZH_WORDS_GETTER("homework.listRow.class_name"), false, "");
  // 提交人数
  API_DTO_FIELD(Int32, submit_count, ZH_WORDS_GETTER("homework.listRow.submit_count"), false, 0);
  // 创建时间
  API_DTO_FIELD(String, create_time, ZH_WORDS_GETTER("homework.listRow.create_time"), false, "");
};


using HomeworkListRows = oatpp::List<oatpp::Object<HomeworkListRowDTO>>;

class HomeworkListPageDTO : public oatpp::DTO {
  DTO_INIT(HomeworkListPageDTO, DTO);
  API_DTO_FIELD(UInt64, pageIndex, ZH_WORDS_GETTER("homework.page.pageIndex"), false, 1);
  API_DTO_FIELD(UInt64, pageSize, ZH_WORDS_GETTER("homework.page.pageSize"), false, 5);
  /** Int64 默认值勿写裸 0，MSVC 下会与 oatpp::Int64 的 operator= 产生二义性 */
  API_DTO_FIELD(Int64, total, ZH_WORDS_GETTER("homework.page.total"), false, static_cast<v_int64>(0));
  API_DTO_FIELD(Int64, pages, ZH_WORDS_GETTER("homework.page.pages"), false, static_cast<v_int64>(0));
  API_DTO_FIELD(HomeworkListRows, rows, ZH_WORDS_GETTER("homework.page.rows"), false, {});
};

class HomeworkListPageJsonVO : public oatpp::DTO {
  DTO_INIT(HomeworkListPageJsonVO, DTO);
  // 状态码
  API_DTO_FIELD(Int32, code, ZH_WORDS_GETTER("homework.rsp.code"), false, 10000);
  // 提示信息
  API_DTO_FIELD(String, message, ZH_WORDS_GETTER("homework.rsp.message"), false, "success");
  // 分页数据
  API_DTO_FIELD_DEFAULT(Object<HomeworkListPageDTO>, data, ZH_WORDS_GETTER("homework.listPageVo.data"));
};

class HomeworkSubmitRecordDTO : public oatpp::DTO {
  DTO_INIT(HomeworkSubmitRecordDTO, DTO);
  // 提交记录ID
  API_DTO_FIELD(String, record_id, ZH_WORDS_GETTER("homework.submitRecord.record_id"), false, "");
  // 学生ID
  API_DTO_FIELD(String, student_id, ZH_WORDS_GETTER("homework.submitRecord.student_id"), false, "");
  // 提交内容
  API_DTO_FIELD(String, submit_content, ZH_WORDS_GETTER("homework.submitRecord.submit_content"), false, "");
  // 提交时间
  API_DTO_FIELD(String, submit_time, ZH_WORDS_GETTER("homework.submitRecord.submit_time"), false, "");
  // 点评分数
  API_DTO_FIELD(Int32, score, ZH_WORDS_GETTER("homework.submitRecord.score"), false, 0);
  // 点评文字
  API_DTO_FIELD(String, comment, ZH_WORDS_GETTER("homework.submitRecord.comment"), false, "");
  // 点评时间
  API_DTO_FIELD(String, comment_time, ZH_WORDS_GETTER("homework.submitRecord.comment_time"), false, "");
  // 点评教师
  API_DTO_FIELD(String, comment_teacher, ZH_WORDS_GETTER("homework.submitRecord.comment_teacher"), false, "");
};

class HomeworkDetailDataDTO : public oatpp::DTO {
  DTO_INIT(HomeworkDetailDataDTO, DTO);
  // 作业ID
  API_DTO_FIELD(String, homework_id, ZH_WORDS_GETTER("homework.detailData.homework_id"), false, "");
  // 作业标题
  API_DTO_FIELD(String, title, ZH_WORDS_GETTER("homework.detailData.title"), false, "");
  // 班级名称
  API_DTO_FIELD(String, class_name, ZH_WORDS_GETTER("homework.detailData.class_name"), false, "");
  // 班级ID
  API_DTO_FIELD(String, class_id, ZH_WORDS_GETTER("homework.detailData.class_id"), false, "");
  // 作业内容
  API_DTO_FIELD(String, content, ZH_WORDS_GETTER("homework.detailData.content"), false, "");
  // 发布时间
  API_DTO_FIELD(String, create_time, ZH_WORDS_GETTER("homework.detailData.create_time"), false, "");
  // 附件说明（无表字段时可为空）
  API_DTO_FIELD(String, attachment, ZH_WORDS_GETTER("homework.detailData.attachment"), false, "");
  // 提交记录列表（无提交时为空列表）
  API_DTO_FIELD(List<Object<HomeworkSubmitRecordDTO>>, submit_list, ZH_WORDS_GETTER("homework.detailData.submit_list"), false, {});
};

class HomeworkDetailJsonVO : public oatpp::DTO {
  DTO_INIT(HomeworkDetailJsonVO, DTO);
  // 状态码
  API_DTO_FIELD(Int32, code, ZH_WORDS_GETTER("homework.rsp.code"), false, 10000);
  // 提示信息
  API_DTO_FIELD(String, message, ZH_WORDS_GETTER("homework.rsp.message"), false, "success");
  // 详情数据
  API_DTO_FIELD_DEFAULT(Object<HomeworkDetailDataDTO>, data, ZH_WORDS_GETTER("homework.detailVo.data"));
};

class HomeworkAddDataDTO : public oatpp::DTO {
  DTO_INIT(HomeworkAddDataDTO, DTO);
  // 作业ID
  API_DTO_FIELD(String, homework_id, ZH_WORDS_GETTER("homework.addData.homework_id"), false, "");
  // 作业标题
  API_DTO_FIELD(String, title, ZH_WORDS_GETTER("homework.addData.title"), false, "");
};

class HomeworkAddJsonVO : public oatpp::DTO {
  DTO_INIT(HomeworkAddJsonVO, DTO);
  // 状态码
  API_DTO_FIELD(Int32, code, ZH_WORDS_GETTER("homework.rsp.code"), false, 10000);
  // 提示信息
  API_DTO_FIELD(String, message, ZH_WORDS_GETTER("homework.rsp.message"), false, "success");
  // 新增作业数据
  API_DTO_FIELD_DEFAULT(Object<HomeworkAddDataDTO>, data, ZH_WORDS_GETTER("homework.addVo.data"));
};

class HomeworkCommentDataDTO : public oatpp::DTO {
  DTO_INIT(HomeworkCommentDataDTO, DTO);
  // 点评ID
  API_DTO_FIELD(String, comment_id, ZH_WORDS_GETTER("homework.commentData.comment_id"), false, "");
  // 评分
  API_DTO_FIELD(Int32, score, ZH_WORDS_GETTER("homework.commentData.score"), false, 0);
  // 点评内容
  API_DTO_FIELD(String, content, ZH_WORDS_GETTER("homework.commentData.content"), false, "");
};

class HomeworkCommentJsonVO : public oatpp::DTO {
  DTO_INIT(HomeworkCommentJsonVO, DTO);
  // 状态码
  API_DTO_FIELD(Int32, code, ZH_WORDS_GETTER("homework.rsp.code"), false, 10000);
  // 提示信息
  API_DTO_FIELD(String, message, ZH_WORDS_GETTER("homework.rsp.message"), false, "success");
  // 点评数据
  API_DTO_FIELD_DEFAULT(Object<HomeworkCommentDataDTO>, data, ZH_WORDS_GETTER("homework.commentVo.data"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // COMMON_RESPONSE_DTO_H

