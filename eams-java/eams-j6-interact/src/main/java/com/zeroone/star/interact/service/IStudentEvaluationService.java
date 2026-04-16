package com.zeroone.star.interact.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dataobject.j6.interact.LessonStudentDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.StudentEvaluationDTO;
import com.zeroone.star.project.query.j6.interact.StudentEvaluationQuery;

public interface IStudentEvaluationService extends IService<LessonStudentDO> {
    /**
     * 获取教师点评列表（条件+分页）
     * @param condition 查询条件
     * @return 分页结果
     */
    PageDTO<StudentEvaluationDTO> queryPage(StudentEvaluationQuery condition);
}
