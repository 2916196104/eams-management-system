package com.zeroone.star.j5.courseschedule.service;

import cn.hutool.db.PageResult;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.j5.courseschedule.entity.Lesson;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonQueryDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSaveDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonUpdateDTO;
import com.zeroone.star.project.vo.j5.courseschedule.LessonCalendarVO;
import com.zeroone.star.project.vo.j5.courseschedule.LessonDetailVO;
import com.zeroone.star.project.vo.j5.courseschedule.LessonListVO;

import java.util.List;


public interface ILessonService extends IService<Lesson> {


    /**
     * 查询课程日历列表
     * 用于前端日历视图展示排课数据
     * @param query 查询条件（日期、状态、教师、教室等）
     * @return 日历展示需要的课程VO集合
     */
    List<LessonCalendarVO> calendar(LessonQueryDTO query);

    /**
     * 分页查询课程列表
     * 用于管理端/列表页分页展示课程数据
     * @param query 分页+筛选条件
     * @return 分页结果（包含课程列表、总条数）
     */
    PageDTO<LessonListVO> pageList(LessonQueryDTO query);

    /**
     * 获取课程详情
     * @param id 课程ID
     * @return 课程详细信息VO
     */
    LessonDetailVO detail(Long id);

    /**
     * 保存（新增）课程
     * 包含课程基本信息、排课信息等业务逻辑
     * @param dto 课程新增参数
     * @return 保存成功/失败
     */
    boolean saveLesson(LessonSaveDTO dto);

    /**
     * 修改课程信息
     * 根据ID更新课程相关数据
     * @param dto 课程修改参数
     * @return 修改成功/失败
     */
    boolean updateLesson(LessonUpdateDTO dto);
}
