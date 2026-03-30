package com.zeroone.star.interact.mapper;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dataobject.j6.interact.GradeFormDO;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.GradeFormDTO;
import com.zeroone.star.project.dto.j6.interact.GradeListDTO;
import com.zeroone.star.project.query.j6.interact.GradeRecordQuery;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;
import java.util.Map;

/**
* @author 24232
* @description 针对表【grade(成绩单)】的数据库操作Mapper
* @createDate 2026-03-20 21:01:07
* @Entity generator.domain.Grade
*/
@Mapper
public interface GradeFormMapper extends BaseMapper<GradeFormDO> {

    /**
     * 分页查询成绩单列表
     * @param page
     * @param title
     * @param creator
     * @return
     */
    IPage<GradeFormDTO> queryForm(Page<GradeFormDTO> page,
                                  @Param("title") String title,
                                  @Param("creator") Long creator);
    /**
     * 分页查询成绩列表
     * @param page 分页条件
     * @param gradeId 成绩单id
     * @return 返回结果
     */
    IPage<GradeListDTO> getGradeRecordList(IPage<GradeListDTO> page, @Param("gradeId") Long gradeId);
}




