package com.zeroone.star.stumanager.service.impl;


import com.zeroone.star.project.dto.j8.stumanager.SaveStu.ChangeStuStageDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuAddDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuDTO;
import com.zeroone.star.project.vo.j8.stumanager.SaveStu.StuSaveVO;
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
     * DO 转 DTO（修改/查询用，包含ID）
     * @param student 实体对象
     * @return SaveStuDTO
     */
    SaveStuDTO toSaveStuDTO(Student student);
    /**
     * DTO 转 DO（修改/查询用，包含ID）
     * @param saveStuDTO 传输对象
     * @return Student
     */
    Student toStudent(SaveStuDTO saveStuDTO);

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
     * AddDTO 转 DO（新增用，无ID）
     * @param saveStuAddDTO 新增传输对象
     * @return Student
     */
    Student toStudent(SaveStuAddDTO saveStuAddDTO);

    /**
     * VO 映射 DTO
     * @param studentVO 前端展示对象
     * @return 传输对象
     */
    SaveStuDTO studentVOToSaveStuDTO(StuSaveVO studentVO);

    /**
     * DTO 转 DO（新增用，无ID）
     * @param changeStuStageDTO 新增传输对象
     * @return Student
     */
    Student stuStageDTOToStudent(ChangeStuStageDTO changeStuStageDTO);

    /**
     * DO映射DTO（只转学生ID + 状态stage）
     * @param student 实体
     * @return DTO
     */
    SaveStuAddDTO StudentToStuAddDTO(Student student);
    /**
     * DO 转 DTO（新增用，无ID）
     * @param student 新增传输对象
     * @return Student
     */
    ChangeStuStageDTO StudentToStuStageDTO(Student student);

    /**
     * DTO映射实体（只转学生ID + 状态stage）
     * @param saveStuAddDTO DTO
     * @return 实体
     */
    Student StuAddDTOToStudent(SaveStuAddDTO saveStuAddDTO);
}