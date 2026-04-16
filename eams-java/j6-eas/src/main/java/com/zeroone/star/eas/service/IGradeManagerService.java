package com.zeroone.star.eas.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.eas.entity.ClassGrade;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.eas.ClassGradeDto;
import com.zeroone.star.project.dto.j6.eas.GradeNameDto;
import com.zeroone.star.project.query.j6.eas.GradeManagerQuery;

import java.util.List;

/**
 * 年级管理Service接口
 */
public interface IGradeManagerService extends IService<ClassGrade> {

    /**
     * 分页查询年级列表
     *
     * @param query 查询条件
     * @return 分页数据
     */
    PageDTO<ClassGradeDto> queryPage(GradeManagerQuery query);

    /**
     * 根据ID获取年级详情
     *
     * @param id 年级ID
     * @return 年级详情
     */
    ClassGradeDto getGradeById(Long id);

    /**
     * 获取年级名称列表（用于下拉框）
     *
     * @return 年级名称列表
     */
    List<GradeNameDto> queryGradeNameList();

    /**
     * 保存年级（新增或修改）
     *
     * @param classGradeDto 年级信息
     * @return 年级ID
     */
    Long saveClassGrade(ClassGradeDto classGradeDto);

    /**
     * 批量删除年级
     *
     * @param ids 年级ID列表
     * @return 删除的ID列表
     */
    List<Long> deleteClassGrade(List<Long> ids);

    /**
     * 批量升级年级
     *
     * @param ids 年级ID列表
     * @return 升级的ID列表
     */
    List<Long> upgradeClassGrade(List<Long> ids);
}
