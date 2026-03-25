package com.zeroone.star.stumanager.service.impl;

import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuAddDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuDTO;
import com.zeroone.star.project.vo.j8.stumanager.SaveStu.StuSaveVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentListVO;
import com.zeroone.star.stumanager.entity.Student;
import org.mapstruct.Mapper;
/**
 * Student领域模型类型转换
 */
@Mapper(componentModel = "spring")
public interface MsStuMapper {
    /**
     * DO映射DTO
     * @param student 实体
     * @return DTO
     */
    SaveStuDTO StudentToSaveStuDTO(Student student);

    /**
     * DTO映射实体
     * @param saveStuDTO
     * @return Student
     */
     Student StudentToSaveStuDTO(SaveStuDTO saveStuDTO);

    /**
     * DTO 映射 VO
     * @param saveStuDTO 传输对象
     * @return 前端展示对象
     */
    StuSaveVO saveStuDTOToStudentVO(SaveStuDTO saveStuDTO);

    /**
     * VO 映射 DTO
     * @param studentVO 前端展示对象
     * @return 传输对象
     */
    SaveStuDTO studentVOToSaveStuDTO(StuSaveVO studentVO);

    /**
     * DO映射DTO（只转学生ID + 状态stage）
     * @param student 实体
     * @return DTO
     */
    SaveStuAddDTO StudentToStuAddDTO(Student student);

    /**
     * DTO映射实体（只转学生ID + 状态stage）
     * @param saveStuAddDTO DTO
     * @return 实体
     */
    Student StuAddDTOToStudent(SaveStuAddDTO saveStuAddDTO);

}
