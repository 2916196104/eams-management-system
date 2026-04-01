package com.zeroone.star.interact.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.interact.entity.GradeRecord;
import com.zeroone.star.project.dto.j6.interact.GradeRecordDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * <p>
 * 描述:
 * </p>
 *
 * @author upup
 * @version 1.0.0
 * @since 2026-03-22
 */
public interface IGradeRecordService extends IService<GradeRecord> {

    // 保存/修改成绩
    JsonVO<String> saveGradeRecord(GradeRecordDTO gradeRecordDTO);

    // 删除成绩（支持批量）
    JsonVO<List<Long>> deleteGradeRecord(List<Long> ids);

    // 导入成绩
    JsonVO<String> addGrades(Long grade_id, List<GradeRecordDTO> gradeRecords);
}
