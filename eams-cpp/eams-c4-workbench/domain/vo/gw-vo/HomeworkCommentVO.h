#pragma once

#include <string>

struct HomeworkCommentVO {
  std::string comment_id;
  int score = 0;
  std::string content;
  std::string create_time;
};

