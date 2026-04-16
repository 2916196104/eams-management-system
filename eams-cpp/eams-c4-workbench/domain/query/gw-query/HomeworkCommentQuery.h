#pragma once

#include <string>

struct HomeworkCommentQuery {
  std::string submit_id;
  std::string admin_id;
  int score = 0;
  std::string content;
};

