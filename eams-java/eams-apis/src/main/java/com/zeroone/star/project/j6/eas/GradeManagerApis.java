package com.zeroone.star.project.j6.eas;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.eas.GradeManagerDto;
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
    JsonVO<PageDTO<GradeManagerDto>> queryPage(GradeManagerQuery query);

    /**
     * 获取年级详情
     */
    JsonVO<GradeManagerDto> getGradeById(Integer id);

    /**
     * 获取年级名称列表
     */
    JsonVO<List<GradeManagerDto>> QueryGradeNameList(String name);
}
