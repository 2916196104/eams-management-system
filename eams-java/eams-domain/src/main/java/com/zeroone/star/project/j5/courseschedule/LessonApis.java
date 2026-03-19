package com.zeroone.star.project.j5.courseschedule;

import com.zeroone.star.project.dto.j5.courseschedule.LessonParamDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.dto.PageDTO;

import java.util.List;

/**
 * <p>
 * 描述：课次管理接口
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
public interface LessonApis {

    /**
     * 分页查询课次列表
     * @param param 查询参数
     * @return 课次分页结果
     */
    JsonVO<PageDTO<?>> listLesson(LessonParamDTO param);

    /**
     * 停课
     * @param lessonIds 课次ID列表
     * @return 影响行数
     */
    JsonVO<Integer> stopLesson(List<Long> lessonIds);

    /**
     * 复课
     * @param lessonIds 课次ID列表
     * @return 影响行数
     */
    JsonVO<Integer> resumeLesson(List<Long> lessonIds);

    /**
     * 获取课次详情
     * @param lessonId 课次ID
     * @return 课次详情
     */
    JsonVO<?> getLessonDetail(Long lessonId);
}
