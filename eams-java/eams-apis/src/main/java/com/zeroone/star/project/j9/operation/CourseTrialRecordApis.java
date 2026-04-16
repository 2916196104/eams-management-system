package com.zeroone.star.project.j9.operation;

import com.zeroone.star.project.query.j9.operation.CourseTrialRecordPageQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.operation.CourseTrialRecordVO;

import java.util.List;

/**
 * 课程体验卡领取记录API接口
 */
public interface CourseTrialRecordApis {

    /**
     * 课程体验卡领取记录条件分页查询
     */
    JsonVO<List<CourseTrialRecordVO>> queryTrialRecordPage(CourseTrialRecordPageQuery pageQuery);
}
