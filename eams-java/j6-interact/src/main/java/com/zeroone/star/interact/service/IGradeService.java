package com.zeroone.star.interact.service;
import com.zeroone.star.project.dto.PageDTO;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dataobject.j6.interact.GradeDO;
import com.zeroone.star.project.dto.j6.interact.GradeFormDTO;
import com.zeroone.star.project.query.j6.interact.GradeFormQuery;
public interface IGradeService extends IService<GradeDO> {
    /**
     * 获取成绩单列表（条件+分页）
     * @param condition 查询条件
     * @return
     */
    PageDTO<GradeFormDTO> queryForm(GradeFormQuery condition);
}