package com.zeroone.star.project.j5.classmanager;

import com.zeroone.star.project.dto.j5.classmanager.ClassStudentDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

public interface ClassStudentApis {
    JsonVO<Integer> addClassStudent(List<ClassStudentDTO> classStudentDTOs);

    JsonVO<Integer> removeClassStudent(List<Integer> studentIds);

    JsonVO<Integer> transferClassBatch(List<ClassStudentDTO> classStudentDTOs, int targetClassId);
}
