package com.zeroone.star.project.j3.data;

import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j3.data.NewStudentsVO;
import com.zeroone.star.project.vo.j3.data.StudentLessonCountsVO;

import java.time.LocalDateTime;
import java.util.List;

public interface StudentsStagesApis {
    /**
     * 获取本月新线索走势
     * @param beginTime 起始时间
     * @param endTime 结束时间
     * @return 新线索信息
     */
    JsonVO<List<NewStudentsVO>> getNewStudentsStagesInfo(LocalDateTime beginTime, LocalDateTime endTime);

    /**
     * 获取消课时学员排行
     * @param beginTime 初始时间
     * @param endTime 结束时间
     * @return 排行前20学员信息
     */
    JsonVO<List<StudentLessonCountsVO>> getStudentLessonCounts(LocalDateTime beginTime, LocalDateTime endTime);
}
