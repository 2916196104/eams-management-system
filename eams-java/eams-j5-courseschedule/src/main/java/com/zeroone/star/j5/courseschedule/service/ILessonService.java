package com.zeroone.star.j5.courseschedule.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.j5.courseschedule.entity.Lesson;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonChangeStateDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonParamDTO;
import com.zeroone.star.project.vo.j5.courseschedule.LessonDetailVO;

/**
 * <p>
 * 描述：课次服务接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
public interface ILessonService extends IService<Lesson> {

    /**
     * 分页查询课次列表
     */
    PageDTO<?> queryList(LessonParamDTO param);

    /**
     * 批量变更课次状态
     */
    Integer changeLessonState(LessonChangeStateDTO dto);

    /**
     * 查询单个课次详情
     */
    LessonDetailVO queryDetail(Long lessonId);
}
