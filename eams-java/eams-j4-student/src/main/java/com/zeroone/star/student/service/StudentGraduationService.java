package com.zeroone.star.student.service;

import com.zeroone.star.project.dto.j4.student.StudentQueryCondition;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;

public interface StudentGraduationService {
    void importGraduationStudent(MultipartFile file);

    void exportGraduationStudent(StudentQueryCondition condition, HttpServletResponse response);
}
