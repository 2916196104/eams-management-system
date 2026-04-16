package com.zeroone.star.operation.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.operation.entity.CourseTrialDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.CourseTrialDTO;
import com.zeroone.star.project.query.j9.operation.CourseTrialQuery;
import com.zeroone.star.project.vo.j9.operation.CourseTrialVO;

import java.util.List;

/**
 * 课程体验卡 服务接口
 */
public interface ICourseTrialService extends IService<CourseTrialDO> {

    /**
     * 分页查询试听卡列表
     */
    PageDTO<CourseTrialVO> listCourseTrial(CourseTrialQuery condition);

    /**
     * 获取试听卡详情
     */
    CourseTrialVO getCourseTrial(Long id);

    /**
     * 保存试听卡（新增或修改）
     */
    boolean saveCourseTrial(CourseTrialDTO dto);

    /**
     * 批量删除试听卡，返回删除失败的ID列表
     */
    List<Long> removeCourseTrial(List<Long> ids);
}
