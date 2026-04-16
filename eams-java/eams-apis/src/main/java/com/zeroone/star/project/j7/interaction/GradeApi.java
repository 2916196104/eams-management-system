package com.zeroone.star.project.j7.interaction;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.interaction.GradeDTO;
import com.zeroone.star.project.dto.j7.interaction.GradeRecordSaveDTO;
import com.zeroone.star.project.query.j7.interaction.GradeQuery;
import com.zeroone.star.project.query.j7.interaction.GradeRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j7.interaction.GradeRecordVO;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;

import javax.validation.Valid;
import java.util.List;

public interface GradeApi {

    /**
     * 获取成绩单列表
     * <p>分页查询，支持按标题、发布者 ID 筛选</p>
     * @param query 查询条件（分页 + 筛选）
     * @return 成绩单列表
     */
    JsonVO<PageDTO<GradeRecordVO>> pageList(GradeRecordQuery query);


    /**
     * 保存成绩单信息
     *
     * @param gradeDTO 成绩单数据
     * @return 成功数量
     */
    JsonVO<Long> saveGrade(@RequestBody GradeDTO gradeDTO);

    /**
     * 删除成绩单信息
     *
     * @param ids 职位 id
     * @return 删除结果
     */
    JsonVO<List<Long>> deleteGrade(@RequestParam("ids") List<Long> ids);

    /**
     * 分页获取成绩列表（考核项下的学生成绩）
     *
     * @param condition 查询条件（支持 gradeId、studentId 筛选）
     * @return 学生成绩列表
     */
    JsonVO<PageDTO<GradeRecordVO>> queryPage(GradeRecordQuery condition);


    /**
     * 导入成绩单
     *
     * @param file 成绩文件
     * @return
     */
    public JsonVO importExcel(@RequestParam("file") MultipartFile file, @RequestParam(value = "gradeId") Long gradeId);

    /**
     * 删除成绩信息
     *
     * @param ids 成绩id
     * @return 删除结果
     */
    public JsonVO deleteRecord(@RequestBody List<Long> ids);

    /**
     * 保存成绩信息
     *
     * @param dto 成绩数据
     * @return
     */
    public JsonVO saveRecord(@Valid @RequestBody GradeRecordSaveDTO dto, BindingResult bindingResult);


}
