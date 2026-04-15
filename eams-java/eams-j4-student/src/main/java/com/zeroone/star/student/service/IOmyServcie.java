package com.zeroone.star.student.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.LessonCountDTO;
import org.springframework.stereotype.Service;

public interface IOmyServcie {
    PageDTO<LessonCountDTO> PageLessonCount(String StudentID);
}
