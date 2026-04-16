#pragma once

#include <string>
#include "HomeworkCommentVO.h"

struct HomeworkSubmitVO {
  std::string student_name;
  std::string submit_content;
  std::string submit_time;
  HomeworkCommentVO comment;
};

