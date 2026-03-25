package com.zeroone.star.project.j6.eas;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.eas.ClassGradeDto;
import com.zeroone.star.project.dto.j6.eas.GradeNameDto;
import com.zeroone.star.project.query.j6.eas.GradeManagerQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * 年级管理接口
 */
public interface GradeManagerApis {

    /**
     * 获取年级列表
     * @param query
     * @return
     */
    JsonVO<PageDTO<ClassGradeDto>> queryPage(GradeManagerQuery query);

    /**
     * 获取年级详情
     */
    JsonVO<ClassGradeDto> getGradeById(Long id);

    /**
     * 获取年级名称列表
     */
    JsonVO<List<GradeNameDto>> QueryGradeNameList();

    /**
     * 保存年级信息
     * @param  gradeManagerDto 年级参数
     * @return 保存结果
     */
    JsonVO<Long> saveClassGrade(ClassGradeDto gradeManagerDto);

    /**
     * 删除年级信息
     * @param ids 年级id
     * @return 删除结果
     */
    JsonVO<List<Long>> deleteClassGrade(List<Long> ids);


    /**
     * 升级年级信息
     * @param ids 年级id
     * @return 升级结果
     */
    JsonVO<List<Long>> upgradeClassGrade(List<Long> ids);
}
