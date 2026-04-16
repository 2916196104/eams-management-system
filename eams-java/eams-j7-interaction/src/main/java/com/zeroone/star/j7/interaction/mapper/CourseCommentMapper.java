package com.zeroone.star.j7.interaction.mapper;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.core.toolkit.StringUtils;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j7.interaction.entity.CourseComment;
import com.zeroone.star.project.query.j7.interaction.CourseCommentQuery;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface CourseCommentMapper extends BaseMapper<CourseComment> {

    default IPage<CourseComment> selectPageList(Page<CourseComment> page, CourseCommentQuery query) {
        LambdaQueryWrapper<CourseComment> wrapper = new LambdaQueryWrapper<>();

        // 只查未删除
        wrapper.eq(CourseComment::getDeleted, 0);

        // 条件拼接
        if (StringUtils.isNotBlank(query.getContent())) {
            wrapper.like(CourseComment::getContent, query.getContent());
        }
        if (query.getCourseId() != null) {
            wrapper.eq(CourseComment::getCourseId, query.getCourseId());
        }
        if (query.getCreator() != null) {
            wrapper.eq(CourseComment::getCreator, query.getCreator());
        }
        if (query.getStudentId() != null) {
            wrapper.eq(CourseComment::getStudentId, query.getStudentId());
        }
        if (query.getAddTimeStart() != null) {
            wrapper.ge(CourseComment::getAddTime, query.getAddTimeStart());
        }
        if (query.getAddTimeEnd() != null) {
            wrapper.le(CourseComment::getAddTime, query.getAddTimeEnd());
        }

        // 绝对不写 select *，只查需要字段（满足你性能要求）
        wrapper.select(
                CourseComment::getId,
                CourseComment::getCourseId,
                CourseComment::getStudentId,
                CourseComment::getScore,
                CourseComment::getContent,
                CourseComment::getCreator,
                CourseComment::getAddTime,
                CourseComment::getOrderId,
                CourseComment::getState,
                CourseComment::getEditor,
                CourseComment::getEditTime,
                CourseComment::getDeleted
        );

        wrapper.orderByDesc(CourseComment::getAddTime);
        return selectPage(page, wrapper);
    }
}