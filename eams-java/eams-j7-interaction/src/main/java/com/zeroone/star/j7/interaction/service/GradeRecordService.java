package com.zeroone.star.j7.interaction.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.interaction.GradeDTO;
import com.zeroone.star.project.dto.j7.interaction.GradeRecordSaveDTO;
import com.zeroone.star.project.entity.GradeRecord;
import com.zeroone.star.project.query.j7.interaction.GradeRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j7.interaction.GradeRecordVO;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.List;

/**
 * 成绩列表 Service 接口
 * 贴合数据库结构 + 原型图筛选/展示逻辑
 */
public interface GradeRecordService extends IService<GradeRecord> {

    /**
     * 分页查询成绩列表（学生成绩）
     * @param query 筛选条件（考核 ID、学生 ID + 分页）
     * @return 分页后的成绩列表
     */
    PageDTO<GradeRecordVO> pageList(GradeRecordQuery query);

    /**
     * 保存成绩单信息
     * @param gradeDTO 成绩单数据
     * @return 操作结果
     */
    JsonVO<Long> saveGrade(GradeDTO gradeDTO);

    /**
     * 删除成绩单信息
     * @param ids 成绩单 ID 列表
     * @return 删除结果
     */
    JsonVO<List<Long>> deleteGrade(List<Long> ids);

    Boolean saveOrUpdateByDTO(GradeRecordSaveDTO dto);

    void importGradeRecord(MultipartFile file, Long gradeId) throws IOException;
}
