package com.zeroone.star.eamsj3class.utils;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.eamsj3class.entity.Course;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.vo.j3.course.CourseListVO;
import org.springframework.beans.BeanUtils;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * <p>
 * 描述：课程工具类
 * </p>
 *
 * @author heavydrink
 * @version 1.0.0
 */
public class CourseUtils {

    /**
     * 根据int值获取课程类型
     * @param lessonType 课程类型int值
     * @return 课程类型名称
     */
    public static String getLessonTypeByInt(Integer lessonType) {
        switch (lessonType){
            case 1:
                return "大课";
            case 2:
                return "小班课";
            case 3:
                return "一对一";
            default:
                return "未知";
        }
    }

    public static PageDTO<CourseListVO> getPageDTOCourseListVO(PageTmpParam param){
        List<CourseListVO> records = new ArrayList<>();
        // 组装数据
        for (Course course : param.getCoursesRecords()) {
            CourseListVO courseListVO = new CourseListVO();
            BeanUtils.copyProperties(course, courseListVO);
            // 处理课型
            courseListVO.setLessonType(CourseUtils.getLessonTypeByInt(course.getLessonType()));
            // 销售截至
            courseListVO.setCloseDate(course.getCloseDate().toString());
            // 上架状态
            courseListVO.setForSale(course.getForSale() ? "上架中" : "未上架");
            // 课程状态
            courseListVO.setState(course.getState() == 1 ? "启用" : "禁用");
            // 可预约
            courseListVO.setBookable(course.getBookable() ? "开" : "关");
            // 总价
            courseListVO.setPrice(course.getPrice().toString());
            // 单价
            courseListVO.setUnitPrice(course.getUnitPrice().toString());
            // 科目名称
            courseListVO.setSubjectName(param.getSubjectMap().get(course.getSubjectId()));
            // 关联数
            if(param.getLinkCountMap().containsKey(course.getId())){
                courseListVO.setLinkCount(param.getLinkCountMap().get(course.getId()));
            }
            // 销售量 销售额
            if(param.getSaleCountMap().containsKey(course.getId())){
                courseListVO.setSaleCount(param.getSaleCountMap().get(course.getId()));
                courseListVO.setSaleAmount(param.getSaleAmountMap().get(course.getId()));
            }
            records.add(courseListVO);
        }

        Page<CourseListVO> result = new Page<>();
        result.setRecords(records);
        result.setCurrent(param.getCurrent());
        result.setSize(param.getSize());
        result.setPages(param.getPages());
        return PageDTO.create(result);
    }


}
