package com.zeroone.star.project.j9.course;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.CourseLinkAddDTO;
import com.zeroone.star.project.query.j9.course.CourseLinkQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.course.CourseLinkedVO;

/**
 * 关联课程管理接口定义
 * @author yangxiao
 */
public interface CourseLinkApis {

    /**
     * 获取关联课程列表（条件查询 + 分页）
     * @param query 查询条件
     * @return 关联课程分页数据
     */
    JsonVO<PageDTO<CourseLinkedVO>> queryLinkedCourses(CourseLinkQuery query);

    /**
     * 添加关联课程（支持多选）
     * @param dto 添加参数
     * @return 操作结果
     */
    JsonVO<String> addLinkedCourses(CourseLinkAddDTO dto);
}
