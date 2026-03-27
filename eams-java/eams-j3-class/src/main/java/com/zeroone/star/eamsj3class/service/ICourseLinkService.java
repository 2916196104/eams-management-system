package com.zeroone.star.eamsj3class.service;


import com.zeroone.star.eamsj3class.entity.CourseLink;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j3.course.CourseLinkDTO;
import com.zeroone.star.project.query.j3.course.CourseLinkQuery;
import com.zeroone.star.eamsj3class.entity.CourseLink;

import java.util.List;


/**
 * <p>
 * 课程关联表 服务类
 * </p>
 *
 */
public interface ICourseLinkService extends IService<CourseLink> {

    List<CourseLink> getCourseLinks(List<Long> courseIds);
    /**
     * 获取关联课程列表（条件 + 分页）
     * @param query 查询参数
     * @return 所有数据
     **/
    PageDTO<CourseLinkDTO> listAll(CourseLinkQuery query);
    /**
     * 添加关联课程（支持多选）
     * @param courseLinkDTO 添加参数
     * @return 添加数量
     **/
    Long add(CourseLinkDTO courseLinkDTO);
    /**
     * 移除关联课程（支持多选）
     * @param ids 移除的ids
     * @return 移除的数据
     **/
    List<Long> delete(List<Long> ids);

}
