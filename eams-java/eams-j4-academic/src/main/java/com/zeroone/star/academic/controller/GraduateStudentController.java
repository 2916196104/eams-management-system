package com.zeroone.star.academic.controller;

import com.zeroone.star.project.dto.j4.graduate.GraduateStudentImportBatchDTO;
import com.zeroone.star.project.j4.graduate.GraduateStudentApi;
import com.zeroone.star.project.query.j4.graduate.GraduateStudentExportQuery;
import com.zeroone.star.project.vo.j4.graduate.CommonResponseVO;
import com.zeroone.star.project.vo.j4.graduate.GraduateStudentImportResultVO;
import io.swagger.annotations.Api;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.Valid;

/**
 * 结业学员导入导出Controller
 *
 * @author 开发者
 * @date 2024-XX-XX
 */
@RestController
@Api(tags = "结业学员管理", description = "结业学员导入、导出、模板下载接口")
public class GraduateStudentController implements GraduateStudentApi {

    /**
     * 结业学员批量导入
     */
    @Override
    public CommonResponseVO<GraduateStudentImportResultVO> importGraduateStudents(
            @Valid GraduateStudentImportBatchDTO importBatchDTO
    ) {
        // 注：仅完成接口定义，暂不实现service层逻辑，保证语法无错即可
        GraduateStudentImportResultVO resultVO = new GraduateStudentImportResultVO();
        resultVO.setSuccessCount(importBatchDTO.getStudentList().size());
        resultVO.setFailCount(0);
        return CommonResponseVO.success(resultVO);
    }

    /**
     * 结业学员导入模板下载
     */
    @Override
    public CommonResponseVO<Void> downloadImportTemplate() {
        // 仅接口实现占位，无业务逻辑
        return CommonResponseVO.success(null);
    }

    /**
     * 结业学员导出
     */
    @Override
    public CommonResponseVO<Void> exportGraduateStudents(
            @Valid GraduateStudentExportQuery exportQuery
    ) {
        // 仅接口实现占位，无业务逻辑
        return CommonResponseVO.success(null);
    }
}