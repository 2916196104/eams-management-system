package com.zeroone.star.student.service;

import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import io.seata.core.model.Result;

public interface StudentService {
    /** 更新学员阶段，返回执行成败 */
    boolean updateStudentStage(StudentDTO studentDTO);

    /** 保存报名信息，返回执行成败 */
    boolean saveStudentCourse(StudentDTO studentDTO);

    /** 获取学员详情，返回原始数据对象 */
    StudentDTO getStudentDetail(StudentQuery studentQuery);
}
