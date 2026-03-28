package com.zeroone.star.j5.classmanager.service;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.zeroone.star.project.dto.j5.classmanager.ClassStudentDTO;
import com.zeroone.star.project.dto.j5.classmanager.TransClassStudentDTO;
import com.zeroone.star.project.query.j5.classmanager.ClassStudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.classmanager.ClassStudentVO;
import org.springframework.web.bind.annotation.RequestBody;

import java.util.List;

public interface ClassStudentService {
    Integer addClassStudent(List<Long> studentIds, Long classId);

    Integer batchDeleteClassStudent(List<Long> studentIds, Long classId);

    Integer batchTransClassStudents(List<Long> studentIds, Long classId, Long targetClassId);
    IPage<ClassStudentVO> queryClassStudentPage(Long classId, ClassStudentQuery query) ;
}
