package com.zeroone.star.project.j3.course;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.CourseLinkDTO;
import com.zeroone.star.project.query.j3.course.CourseLinkQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * <p>
 * 描述：关联课程接口声明
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 *
 * @author j3组 KINGHOG
 * @version 1.0.0
 **/


public interface CourseLinkApis {
    /**
     * <p>
     * 分页查询关联课程信息
     * </p>
     * @param condition 查询条件
     * @return 关联课程信息列表
     */
    JsonVO<PageDTO<CourseLinkDTO>> queryPage(CourseLinkQuery condition);

    /**
     * <p>
     * 添加关联课程信息
     * </p>
     * @param courseLinkDTO 关联课程信息
     * @return 保存结果
     */
    JsonVO<Long> saveCourseLink(CourseLinkDTO courseLinkDTO);

    /**
     * <p>
     * 移除关联课程信息
     * </p>
     * @param ids 关联课程信息id
     * @return 删除结果
     */
    JsonVO<List<Long>> deleteCourseLink(List<Long> ids);


}
