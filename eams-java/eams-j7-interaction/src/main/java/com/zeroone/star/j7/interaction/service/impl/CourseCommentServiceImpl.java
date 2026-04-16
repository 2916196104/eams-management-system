package com.zeroone.star.j7.interaction.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.zeroone.star.j7.interaction.entity.CourseComment;
import com.zeroone.star.j7.interaction.mapper.CourseCommentMapper;
import com.zeroone.star.j7.interaction.service.CourseCommentService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j7.interaction.CourseCommentQuery;
import com.zeroone.star.project.vo.j7.interaction.CourseCommentVO;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.util.CollectionUtils;

import javax.annotation.Resource;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

@Slf4j
@Service
public class CourseCommentServiceImpl implements CourseCommentService {

    @Resource
    private CourseCommentMapper courseCommentMapper;

    @Override
    public PageDTO<CourseCommentVO> pageList(CourseCommentQuery query) {
        // 分页校验
        long pageIndex = query.getPageIndex() < 1 ? 1 : query.getPageIndex();
        long pageSize = query.getPageSize() < 1 ? 30 : query.getPageSize();

        List<Long> allow = Arrays.asList(30L, 50L, 100L, 200L);
        if (!allow.contains(pageSize)) {
            pageSize = 30L;
        }

        // 查询条件
        QueryWrapper<CourseComment> wrapper = new QueryWrapper<>();

        // 手动查总数
        long total = courseCommentMapper.selectCount(wrapper);

        // 手动分页
        int start = (int) ((pageIndex - 1) * pageSize);
        wrapper.last("LIMIT " + start + "," + pageSize);
        List<CourseComment> records = courseCommentMapper.selectList(wrapper);

        // 转VO
        List<CourseCommentVO> rows = records.stream().map(this::toVo).collect(Collectors.toList());

        // 封装结果
        PageDTO<CourseCommentVO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(pageIndex);
        pageDTO.setPageSize(pageSize);
        pageDTO.setTotal(total);
        pageDTO.setPages((total + pageSize - 1) / pageSize);
        pageDTO.setRows(rows);

        // 序号
        if (!CollectionUtils.isEmpty(rows)) {
            long startNo = (pageIndex - 1) * pageSize;
            for (int i = 0; i < rows.size(); i++) {
                rows.get(i).setSerialNumber((int) (startNo + i + 1));
            }
        }

        return pageDTO;
    }

    private CourseCommentVO toVo(CourseComment comment) {
        CourseCommentVO vo = new CourseCommentVO();
        vo.setScore(comment.getScore());
        vo.setContent(comment.getContent());
        vo.setAddTime(comment.getAddTime());
        vo.setOrderId(comment.getOrderId());
        vo.setState(comment.getState());
        vo.setEditor(comment.getEditor());
        vo.setEditTime(comment.getEditTime());
        vo.setDeleted(comment.getDeleted());

        vo.setStudentName("学生ID：" + comment.getStudentId());
        vo.setCourseTitle("课次ID：" + comment.getCourseId());
        vo.setCreatorName("教师ID：" + comment.getCreator());
        return vo;
    }
}