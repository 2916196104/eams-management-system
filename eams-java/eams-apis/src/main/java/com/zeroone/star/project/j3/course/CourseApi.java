package com.zeroone.star.project.j3.course;

import com.zeroone.star.project.dto.j3.course.CourseStatusDTO;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.web.bind.annotation.RequestBody;

public interface CourseApi {
    /**
     * 批量更新课程状态
     * @param stateDTO 包含ids和目标状态(1:启用, 0:禁用)
     * @return 操作结果
     */
    JsonVO<Void> updateStatus(@RequestBody CourseStatusDTO stateDTO);
}