package com.zeroone.star.stumanager.service.impl;

import com.zeroone.star.project.dto.j8.SaveStu.SaveStuAddDTO;
import com.zeroone.star.project.dto.j8.SaveStu.SaveStuDTO;
import com.zeroone.star.project.vo.j8.SaveStu.StuSaveVO;
import com.zeroone.star.stumanager.entity.Student;
import org.mapstruct.Mapper;

/**
 * <p>
 * 描述：Student 领域模型类型转换
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author tsfmn
 * @version 1.0.0
 */
@Mapper(componentModel = "spring")
public interface MsStuMapper {

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
     * AddDTO 转 DO（新增用，无ID）
     * @param saveStuAddDTO 新增传输对象
     * @return Student
     */
    Student toStudent(SaveStuAddDTO saveStuAddDTO);

}