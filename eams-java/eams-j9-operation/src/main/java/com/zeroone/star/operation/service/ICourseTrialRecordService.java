package com.zeroone.star.operation.service;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.operation.entity.CourseTrialRecordDO;
import com.zeroone.star.project.query.j9.operation.CourseTrialRecordPageQuery;
import com.zeroone.star.project.vo.j9.operation.CourseTrialRecordVO;

/**
 * 课程体验卡领取记录Service接口
 */
public interface ICourseTrialRecordService extends IService<CourseTrialRecordDO> {
    /**
     * 条件分页查询课程体验卡领取记录
     * @param pageQuery 分页+筛选条件（已做参数校验）
     * @return 分页后的VO数据
     */
    IPage<CourseTrialRecordVO> listTrialRecordPage(CourseTrialRecordPageQuery pageQuery);
}