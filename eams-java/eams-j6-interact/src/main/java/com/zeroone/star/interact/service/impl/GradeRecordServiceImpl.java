package com.zeroone.star.interact.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.interact.entity.GradeRecord;
import com.zeroone.star.interact.entity.Student;
import com.zeroone.star.interact.mapper.GradeRecordMapper;
import com.zeroone.star.interact.mapper.StudentMapper;
import com.zeroone.star.interact.service.IGradeRecordService;
import com.zeroone.star.project.dto.j6.interact.GradeRecordDTO;
import com.zeroone.star.project.vo.JsonVO;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDateTime;
import java.util.*;

@Service
@RequiredArgsConstructor
public class GradeRecordServiceImpl extends ServiceImpl<GradeRecordMapper, GradeRecord> implements IGradeRecordService {

    /**
     * 保存/修改成绩
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<String> saveGradeRecord(GradeRecordDTO dto) {
        GradeRecord entity = new GradeRecord();

        if (dto.getId() == null) {
            // 新增
            BeanUtils.copyProperties(dto, entity);
            entity.setAddTime(LocalDateTime.now());
            save(entity);
            return JsonVO.success("保存成功");
        } else {
            // 修改
            GradeRecord exist = getById(dto.getId());
            if (exist == null) {
                return JsonVO.fail("成绩记录不存在");
            }
            exist.setScore(dto.getScore());
            updateById(exist);
            return JsonVO.success("修改成功");
        }
    }

    /**
     * 删除成绩（支持批量）
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<List<Long>> deleteGradeRecord(List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要删除的成绩");
        }
        removeByIds(ids);
        return JsonVO.success(ids);
    }

    /**
     * 导入成绩
     */
    // 假设你有一个可以查询学生信息的 Mapper
    @Autowired
    private StudentMapper studentMapper;

    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<String> addGrades(Long gradeId, List<GradeRecordDTO> gradeRecords) {
        if (gradeRecords == null || gradeRecords.isEmpty()) {
            return JsonVO.fail("导入数据为空");
        }

        for (GradeRecordDTO dto : gradeRecords) {
            Long finalStudentId = dto.getStudentId();

            // 1. 如果 Excel 没填 ID，根据姓名去查 Student 表
            if (finalStudentId == null) {
                LambdaQueryWrapper<Student> studentQuery = new LambdaQueryWrapper<>();
                studentQuery.eq(Student::getName, dto.getStudentName()).last("LIMIT 1");
                Student student = studentMapper.selectOne(studentQuery);

                // 逻辑：学生不存在则整体导入失败（触发事务回滚）
                if (student == null) {
                    throw new RuntimeException("导入失败：系统中找不到姓名为 [" + dto.getStudentName() + "] 的学生");
                }
                finalStudentId = student.getId();
            }

            // 2. 检查该学生在该考核项(gradeId)下是否已有成绩
            LambdaQueryWrapper<GradeRecord> gradeQuery = new LambdaQueryWrapper<>();
            gradeQuery.eq(GradeRecord::getGradeId, gradeId)
                    .eq(GradeRecord::getStudentId, finalStudentId);

            GradeRecord oldRecord = this.getOne(gradeQuery);

            if (oldRecord != null) {
                // 存在则覆盖成绩
                oldRecord.setScore(dto.getScore());
                this.updateById(oldRecord);
            } else {
                // 不存在则新增记录
                GradeRecord newRecord = new GradeRecord();
                newRecord.setGradeId(gradeId);
                newRecord.setStudentId(finalStudentId);
                newRecord.setScore(dto.getScore());
                newRecord.setAddTime(LocalDateTime.now());
                this.save(newRecord);
            }
        }

        return JsonVO.success("成绩同步成功");
    }
}