package com.zeroone.star.operation.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.operation.entity.CourseTrialRecordDO;
import com.zeroone.star.operation.mapper.CourseTrialRecordMapper;
import com.zeroone.star.operation.service.ICourseTrialRecordService;
import com.zeroone.star.project.query.j9.operation.CourseTrialRecordPageQuery;
import com.zeroone.star.project.vo.j9.operation.CourseTrialRecordVO;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;

import java.util.Date;
import java.util.List;
import java.util.stream.Collectors;
import java.time.ZoneId;

/**
 * 课程体验卡领取记录Service实现类
 */
@Service
public class CourseTrialRecordServiceImpl extends ServiceImpl<CourseTrialRecordMapper, CourseTrialRecordDO>
        implements ICourseTrialRecordService {

    /**
     * 核心逻辑：条件分页查询 + DO转VO（处理日期类型差异）
     */
    @Override
    public IPage<CourseTrialRecordVO> listTrialRecordPage(CourseTrialRecordPageQuery pageQuery) {
        // 1. 构建MyBatis-Plus分页对象（适配PageQuery的pageIndex/pageSize）
        Page<CourseTrialRecordDO> page = new Page<>(pageQuery.getPageIndex(), pageQuery.getPageSize());

        // 2. 构建条件查询器（仅处理非空条件，避免无效筛选）
        QueryWrapper<CourseTrialRecordDO> queryWrapper = new QueryWrapper<>();
        // 卡ID筛选
        if (pageQuery.getTrialId() != null) {
            queryWrapper.eq("trial_id", pageQuery.getTrialId());
        }
        // 学生ID筛选
        if (pageQuery.getStudentId() != null) {
            queryWrapper.eq("student_id", pageQuery.getStudentId());
        }
        // 课程ID筛选
        if (pageQuery.getCourseId() != null) {
            queryWrapper.eq("course_id", pageQuery.getCourseId());
        }
        // 学校ID筛选
        if (pageQuery.getSchoolId() != null) {
            queryWrapper.eq("school_id", pageQuery.getSchoolId());
        }
        // 顾问ID筛选
        if (pageQuery.getCounselor() != null) {
            queryWrapper.eq("counselor", pageQuery.getCounselor());
        }
        // 领取时间范围筛选（Date → LocalDateTime，适配DO的字段类型）
        if (pageQuery.getAddTimeStart() != null) {
            queryWrapper.ge("add_time",
                    pageQuery.getAddTimeStart().toInstant().atZone(ZoneId.systemDefault()).toLocalDateTime());
        }
        if (pageQuery.getAddTimeEnd() != null) {
            queryWrapper.le("add_time",
                    pageQuery.getAddTimeEnd().toInstant().atZone(ZoneId.systemDefault()).toLocalDateTime());
        }
        // 到期时间范围筛选（Date → LocalDate，适配DO的字段类型）
        if (pageQuery.getExpiredDateStart() != null) {
            queryWrapper.ge("expired_date",
                    pageQuery.getExpiredDateStart().toInstant().atZone(ZoneId.systemDefault()).toLocalDate());
        }
        if (pageQuery.getExpiredDateEnd() != null) {
            queryWrapper.le("expired_date",
                    pageQuery.getExpiredDateEnd().toInstant().atZone(ZoneId.systemDefault()).toLocalDate());
        }

        // 3. 执行分页查询（自动触发MyBatis-Plus分页插件）
        IPage<CourseTrialRecordDO> doPage = this.page(page, queryWrapper);

        // 4. DO转VO（重点处理日期类型转换：LocalDateTime/LocalDate → Date）
        List<CourseTrialRecordVO> voList = doPage.getRecords().stream().map(doObj -> {
            CourseTrialRecordVO vo = new CourseTrialRecordVO();
            // 复制基础属性
            BeanUtils.copyProperties(doObj, vo);

            // LocalDateTime（addTime）→ Date
            if (doObj.getAddTime() != null) {
                vo.setAddTime(Date.from(doObj.getAddTime().atZone(ZoneId.systemDefault()).toInstant()));
            }
            // LocalDate（expiredDate）→ Date
            if (doObj.getExpiredDate() != null) {
                vo.setExpiredDate(Date.from(doObj.getExpiredDate().atStartOfDay(ZoneId.systemDefault()).toInstant()));
            }
            return vo;
        }).collect(Collectors.toList());

        // 5. 封装VO分页对象（保留分页元数据：总条数、总页数、当前页等）
        IPage<CourseTrialRecordVO> voPage = new Page<>();
        BeanUtils.copyProperties(doPage, voPage);
        voPage.setRecords(voList);

        return voPage;
    }
}