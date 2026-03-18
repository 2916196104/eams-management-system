package com.zeroone.star.project.j5.classmanager;

import com.zeroone.star.project.dto.j5.classmanager.ClassStudentDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

public interface ClassStudentApis {
    JsonVO<Integer> addClassStudent(List<Integer> studentIds, int classId);

    JsonVO<Integer> removeClassStudent(List<Integer> studentIds, int classId);

    JsonVO<Integer> transferClassBatch(List<ClassStudentDTO> classStudentDTOs, int targetClassId);
}
