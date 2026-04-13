package com.zeroone.star.j5.courseschedule.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseschedule.entity.Lesson;
import com.zeroone.star.j5.courseschedule.mapper.*;
import com.zeroone.star.j5.courseschedule.service.IEvaluationService;
import com.zeroone.star.project.DO.j5.classmanager.StudentDO;
import com.zeroone.star.project.DO.j5.courseschedule.CourseStudentDO;
import com.zeroone.star.project.DO.j5.courseschedule.LessonDo;
import com.zeroone.star.project.DO.j5.courseschedule.StaffDO;

import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.EvaluationDTO;
import com.zeroone.star.project.query.j5.courseschedule.EvaluationQuery;
import com.zeroone.star.project.vo.j5.courseschedule.EvaluationVO;
import lombok.extern.slf4j.Slf4j;
import org.apache.catalina.security.SecurityUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.actuate.endpoint.SecurityContext;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

/**
 * @author silvan
 * @description 教学点评接口实现类
 */
@Slf4j
@Service
public class IEvaluationServiceImpl extends ServiceImpl<EvaluationMapper, CourseStudentDO> implements IEvaluationService {

    @Resource
    private EvaluationMapper evaluationMapper;

    @Resource
    private CourseStudentMapper courseStudentMapper;

    @Resource
    private StudentMapper studentMapper;

    @Resource
    private StaffMapper staffMapper;
    @Autowired
    private LessonMapper lessonMapper;

//    @Resource
//    private UserHolder userHolder;

    /*
    保存点评
     */
    @Override
    public Long saveEvaluation(EvaluationDTO evaluationDTO){

        // 1. 先获取你要更新的 选课记录（根据 studentId + lessonId）
        LambdaQueryWrapper<CourseStudentDO> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(CourseStudentDO::getId, evaluationDTO.getId());
        CourseStudentDO record = courseStudentMapper.selectOne(queryWrapper);

        if (record != null
                && record.getScore() != null
                && record.getEvaluation() != null
        ) {
            // 已经评价 → 直接拒绝
            throw new RuntimeException("该学生已评价，不可重复评价");
        }

        // 构建条件
        LambdaUpdateWrapper<CourseStudentDO> wrapper = new LambdaUpdateWrapper<>();
        wrapper.eq(CourseStudentDO::getId, evaluationDTO.getId());
//        评语
        wrapper.set(CourseStudentDO::getEvaluation, evaluationDTO.getEvaluation());
        wrapper.set(CourseStudentDO::getScore,evaluationDTO.getScore());
//        TODO 暂时将评价id设置为1，后续使用UserHolder获取当前用户id
        wrapper.set(CourseStudentDO::getEvaluateTeacher,1L);
        wrapper.set(CourseStudentDO::getEvaluationTime, LocalDateTime.now());
//        更新数据库表
        int count = evaluationMapper.update(null,wrapper);
        return (long)count;
    }

    @Override
    public PageDTO<EvaluationVO> queryPage(EvaluationQuery condition) {
        // 1. 构建分页
        Page<CourseStudentDO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());
        // 2. 构建条件：按 lesson_id 查询
        LambdaQueryWrapper<CourseStudentDO> queryWrapper = new LambdaQueryWrapper<>();

        // 是否仅查询已评价的点评
        if (condition.getOnlyEvaluate()) {
            queryWrapper.isNotNull(CourseStudentDO::getScore);
        }

        queryWrapper.eq(condition.getLessonId() != null, CourseStudentDO::getLessonId, condition.getLessonId());

        // 3. 分页查询
        Page<CourseStudentDO> doPage = courseStudentMapper.selectPage(page, queryWrapper);

        List<CourseStudentDO> records = doPage.getRecords();
        if (records == null || records.isEmpty()) {
            return new PageDTO<>();
        }


        // 取出所有学生ID
        List<Long> studentIds = records.stream()
                .map(CourseStudentDO::getStudentId)
                .collect(Collectors.toList());

        log.info("获取所有学生id：{}", studentIds);


        // 防止空集合导致in中无数据
        List<StudentDO> studentList = new ArrayList<>();
        if (!studentIds.isEmpty()) {
            studentList = studentMapper.selectBatchIds(studentIds);
        }

        // 转成 MAP
        final Map<Long, StudentDO> studentMap = studentList.stream()
                .collect(Collectors.toMap(StudentDO::getId, s -> s));

        // 转 VO 返回
        return PageDTO.create(doPage, src -> {
            EvaluationVO vo = new EvaluationVO();
            BeanUtil.copyProperties(src, vo);

            if (BeanUtil.isNotEmpty(src.getEvaluation())) {
                vo.setCommentScore(src.getScore());
                vo.setCommentContent(src.getEvaluation());
                if (BeanUtil.isNotEmpty(src.getEvaluationTime())) {
                    vo.setCommentTime(src.getEvaluationTime().toString());
                }
            }

            StudentDO student = studentMap.get(src.getStudentId());
            if (student != null) {
                vo.setStudentName(student.getName());
            } else {
                throw new RuntimeException("当前学生不存在");
            }

            Lesson lesson = lessonMapper.selectById(condition.getLessonId());
            if (lesson != null) {
                StaffDO teacher = staffMapper.selectById(lesson.getTeacherId());
                if (teacher != null) {
                    vo.setTeacherId(teacher.getId());
                    vo.setTeacherName(teacher.getName());
                }
            }


            return vo;
        });
    }



}
