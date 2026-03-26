package com.zeroone.star.interact.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.interact.entity.GradeRecord;
import com.zeroone.star.interact.mapper.GradeRecordMapper;
import com.zeroone.star.interact.service.IGradeRecordService;
import com.zeroone.star.project.dto.j6.interact.GradeRecordDTO;
import com.zeroone.star.project.vo.JsonVO;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.BeanUtils;
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
    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<Map<Long, Object>> addGrades(Long gradeId, List<GradeRecordDTO> gradeRecords) {
        Map<Long, Object> result = new HashMap<>();

        for (GradeRecordDTO dto : gradeRecords) {
            try {
                GradeRecord entity = new GradeRecord();
                BeanUtils.copyProperties(dto, entity);
                entity.setGradeId(gradeId);
                entity.setAddTime(LocalDateTime.now());
                save(entity);
                result.put(dto.getStudentId(), "导入成功");
            } catch (Exception e) {
                result.put(dto.getStudentId(), "导入失败：" + e.getMessage());
            }
        }
        return JsonVO.success(result);
    }
}