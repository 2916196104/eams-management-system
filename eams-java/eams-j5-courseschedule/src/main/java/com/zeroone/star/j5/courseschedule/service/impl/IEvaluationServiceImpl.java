package com.zeroone.star.j5.courseschedule.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseschedule.mapper.CourseStudentMapper;
import com.zeroone.star.j5.courseschedule.mapper.EvaluationMapper;
import com.zeroone.star.j5.courseschedule.mapper.StudentMapper;
import com.zeroone.star.j5.courseschedule.service.IEvaluationService;
import com.zeroone.star.project.DO.j5.classmanager.ClassStudentDO;
import com.zeroone.star.project.DO.j5.classmanager.Student;
import com.zeroone.star.project.DO.j5.courseschedule.CourseStudentDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.EvaluationDTO;
import com.zeroone.star.project.query.j5.courseschedule.EvaluationQuery;
import com.zeroone.star.project.vo.j5.courseschedule.EvaluationVO;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import javax.sql.DataSource;
import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
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

    /*
    保存点评
     */
    @Override
    public Long saveEvaluation(EvaluationDTO evaluationDTO){


//        判断是否已评价
        int isEvaluated = courseStudentMapper.selectById(evaluationDTO.getId()).getIsEvaluated();
        if(isEvaluated==1){
            throw new RuntimeException("该学生已完成评价");
        }

        // 构建条件
        LambdaUpdateWrapper<CourseStudentDO> wrapper = new LambdaUpdateWrapper<>();
        wrapper.eq(CourseStudentDO::getId, evaluationDTO.getId());

//        评语
        wrapper.set(CourseStudentDO::getEvaluation, evaluationDTO.getEvaluation());
//        已评价
        wrapper.set(CourseStudentDO::getIsEvaluated, 1);
//        更新时间
        wrapper.set(CourseStudentDO::getUpdateTime, LocalDateTime.now());
//        评价时间
        wrapper.set(CourseStudentDO::getEvaluationTime, LocalDateTime.now());
//        评分
        wrapper.set(CourseStudentDO::getScore,evaluationDTO.getScore());

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
//        是否仅查询已评价的点评
        if(condition.getOnlyEvaluate()){
            queryWrapper.eq(CourseStudentDO::getIsEvaluated, 1);
        }

        queryWrapper.eq(condition.getLessonId() != null, CourseStudentDO::getLessonId, condition.getLessonId());
        queryWrapper.eq(CourseStudentDO::getDeleted, 0);
        // 3. MyBatis-Plus 分页查询（查数据库 DO 对象）
        Page<CourseStudentDO> doPage = courseStudentMapper.selectPage(page, queryWrapper);


        // 取出所有学生ID
        List<Long> studentIds = doPage.getRecords().stream()
                .map(CourseStudentDO::getStudentId)
                .collect(Collectors.toList());


        log.info("获取所有学生id：{}",studentIds);
        // 批量查询
        List<Student> studentList = studentMapper.selectBatchIds(studentIds);
        // 转成 MAP<studentId, 学生对象>
        final Map<Long, Student> studentMap = studentList.stream()
                .collect(Collectors.toMap(Student::getId, s -> s));


        // 4. 转 VO 返回
        return PageDTO.create(doPage, src -> {
            EvaluationVO vo = new EvaluationVO();
            BeanUtil.copyProperties(src, vo);

            // 不同名字的属性手动映射
            vo.setCommentScore(src.getScore());
            vo.setCommentContent(src.getEvaluation());
            vo.setCommentTime(src.getEvaluationTime().toString());

            Student student = studentMap.get(src.getStudentId());
            if (student != null) {
                vo.setStudentPhone(student.getPhone());
                vo.setStudentName(student.getName());
            } else {
                vo.setStudentPhone("该学生不存在");
            }

            return vo;
        });
    }



}
