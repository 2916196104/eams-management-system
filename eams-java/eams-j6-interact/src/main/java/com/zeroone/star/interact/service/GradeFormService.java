package com.zeroone.star.interact.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dataobject.j6.interact.GradeFormDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.GradeFormDTO;
import com.zeroone.star.project.dto.j6.interact.GradeListDTO;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.query.j6.interact.GradeFormQuery;
import com.zeroone.star.project.query.j6.interact.GradeRecordQuery;

import java.util.List;

/**
* @author 24232
* @description 针对表【grade(成绩单)】的数据库操作Service
* @createDate 2026-03-20 21:01:07
*/
public interface GradeFormService extends IService<GradeFormDO> {
    /**
     * 获取成绩单列表（条件+分页）
     * @param condition 查询条件
     * @return
     */
    PageDTO<GradeFormDTO> queryForm(GradeFormQuery condition);
    /**
     * 保存成绩单
     * @param gradeFormDTO  成绩单传递对象
     * @return 返回结果
     */
    Long saveGrade(GradeFormDTO gradeFormDTO);

    /**
     * 删除成绩单
     * @param ids 成绩单ID列表
     * @return  返回结果
     */
    List<Long> deleteGrade(List<Long> ids);

    /**
     * 获取成绩列表
     *
     * @param gradeRecordQuery 查询条件
     * @return 返回分页结果
     */
    PageDTO<GradeListDTO> getGradeRecordList(GradeRecordQuery gradeRecordQuery);
}
