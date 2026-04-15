package com.zeroone.star.j5.classmanager.service.impl;

import com.alibaba.nacos.shaded.org.checkerframework.checker.units.qual.C;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.conditions.query.QueryChainWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.zeroone.star.j5.classmanager.mapper.ClassStudentMapper;
import com.zeroone.star.j5.classmanager.service.ClassStudentService;
import com.zeroone.star.project.DO.j5.classmanager.ClassStudentDO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.j5.classmanager.ClassStudentDTO;
import com.zeroone.star.project.dto.j5.classmanager.TransClassStudentDTO;
import com.zeroone.star.project.query.j5.classmanager.ClassStudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.project.vo.j5.classmanager.ClassStudentVO;
import lombok.extern.slf4j.Slf4j;
import org.apache.poi.hpsf.ClassID;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Slf4j
@Service
public class ClassStudentServiceImpl extends ServiceImpl<ClassStudentMapper, ClassStudentDO> implements ClassStudentService {
    @Resource
    private ClassStudentMapper classStudentMapper;
    @Resource
    private UserHolder userHolder;

    @Override
    public Integer addClassStudent(List<Long> studentIds, Long classId) {
//        return null;
        // 1. 参数校验
        if (studentIds == null || studentIds.isEmpty()) {
            throw new IllegalArgumentException("学生 ID 列表不能为空");
        }

        if (classId <= 0) {
            throw new IllegalArgumentException("班级 ID 必须大于 0");
        }

//
//        // 2. 获取当前登录用户 ID
//        Long currentUserId = null;
//        try {
//            String userIdStr = userHolder.getCurrentUser().getId();
//            if (userIdStr != null && !userIdStr.isEmpty()) {
//                currentUserId = Long.valueOf(userIdStr);
//            } else {
//                throw new RuntimeException("用户 ID 为空");
//            }
//        } catch (Exception e) {
//            log.error("获取当前用户信息失败", e);
//            throw new RuntimeException("获取当前用户信息失败：" + e.getMessage(), e);
//        }

        // 3. 创建待插入的学员记录列表
        List<ClassStudentDO> studentRecords = new ArrayList<>();
        Long consumeCourseId = 114514L;//暂时值,之后需要获取当前班级的默认消费课程
        Long currentUserId = 114514L;//暂时值,之后需要获取当前登录用户的userId
        // 4. 遍历学生 ID 列表，为每个学生创建记录
        for (Long studentId : studentIds) {
            if (studentId == null || studentId <= 0) {
                continue; // 跳过无效的学生 ID
            }

            ClassStudentDO classStudent = new ClassStudentDO();
            classStudent.setClassId(classId);           // 设置班级 ID
            classStudent.setStudentId(studentId); // 设置学生 ID
            classStudent.setAddTime(LocalDateTime.now());      // 设置添加时间
            classStudent.setCreator(currentUserId);            // 设置创建人
            classStudent.setDeleted(0);                        // 设置删除标记 (0-未删除)
            classStudent.setReason(1);                         // 设置加入原因 (1-正常加入)
            classStudent.setRemark("加入班级");               // 设置备注
            classStudent.setConsume_course_id(consumeCourseId);           // 设置消费课程 ID
            studentRecords.add(classStudent);
        }

        // 5. 如果没有有效记录，返回 0
        if (studentRecords.isEmpty()) {
            return 0;
        }

        // 6. 批量插入数据
        boolean success = this.saveBatch(studentRecords);

        // 7. 返回成功插入的记录数
        return success ? studentRecords.size() : 0;

    }

    @Override
    public Integer batchDeleteClassStudent(List<Long> studentIds, Long classId) {
        // 1. 参数校验
        if (studentIds == null || studentIds.isEmpty()) {
            throw new IllegalArgumentException("学生 ID 列表不能为空");
        }

        if (classId == null || classId <= 0) {
            throw new IllegalArgumentException("班级 ID 不能为空");
        }

        int deletedCount = 0;
        // 判断班级 ID 是否存在，若不存在则提示用户
        QueryWrapper<ClassStudentDO> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("class_id", classId);
        long count = count(queryWrapper);
        if(count <= 0) {
            throw new IllegalArgumentException("班级 ID 不存在");
        }

        // 2. 执行批量删除，收集不存在的学生 ID
        List<Long> notFoundStudentIds = new ArrayList<>();
        
        for(Long studentId : studentIds) {
            LambdaQueryWrapper<ClassStudentDO> qw = new LambdaQueryWrapper<>();
            qw.eq(ClassStudentDO::getClassId, classId)
              .eq(ClassStudentDO::getStudentId, studentId);
                    
            int delete = classStudentMapper.delete(qw);
            if(delete <= 0) {
                log.warn("删除学生 id= {} 不存在", studentId);
                // 收集不存在的学生 ID
                notFoundStudentIds.add(studentId);
                continue;
            }
            deletedCount++;
        }

        // 4. 返回删除数量和不存在的 ID 列表
        if (!notFoundStudentIds.isEmpty()) {
            log.warn("批量删除完成，有 {} 个学生不存在：{}", notFoundStudentIds.size(), notFoundStudentIds);
        }
        
        return deletedCount;
    }

    @Override
    public Integer batchTransClassStudents(List<Long> studentIds, Long classId, Long targetClassId) {
        if (studentIds == null || studentIds.isEmpty()) {
            throw new IllegalArgumentException("学生 ID 列表不能为空");
        }
        if (classId == null || classId <= 0) {
            throw new IllegalArgumentException("班级 ID 不能为空, 班级 ID 必须大于 0");
        }
        if (targetClassId == null || targetClassId <= 0) {
            throw new IllegalArgumentException("目标班级 ID 不能为空, 目标班级 ID 必须大于 0");
        }

        QueryWrapper<ClassStudentDO> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("class_id", classId)
                .in("student_id", studentIds);
        ClassStudentDO classStudentDO = new ClassStudentDO();
        classStudentDO.setClassId(targetClassId);

        int update = classStudentMapper.update(classStudentDO, queryWrapper);
        return update;

    }
    /**
     * 分页查询班级学生
     * @param classId 班级ID
     * @param query 查询参数
     * @return 分页结果
     */
    @Override
    public IPage<ClassStudentVO> queryClassStudentPage(Long classId, ClassStudentQuery query) {
        Page<ClassStudentVO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        return classStudentMapper.selectClassStudentPage(page, classId, query);
    }

}
