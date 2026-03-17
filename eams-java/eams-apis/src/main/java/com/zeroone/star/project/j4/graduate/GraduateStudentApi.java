package com.zeroone.star.project.j4.graduate;

import com.zeroone.star.project.dto.j4.graduate.GraduateStudentImportBatchDTO;
import com.zeroone.star.project.query.j4.graduate.GraduateStudentExportQuery;
import com.zeroone.star.project.vo.j4.graduate.CommonResponseVO;
import com.zeroone.star.project.vo.j4.graduate.GraduateStudentImportResultVO;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import io.swagger.annotations.ApiResponse;
import io.swagger.annotations.ApiResponses;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.multipart.MultipartFile;

import javax.validation.Valid;

/**
 * 结业学员导入导出接口定义
 *
 */
@RequestMapping("/j4/graduate/student")
public interface GraduateStudentApi {

    /**
     * 结业学员批量导入
     */
    @PostMapping("/import")
    @ApiOperation(
            value = "结业学员批量导入",
            notes = "接收结业学员列表数据，完成批量导入，返回导入结果。返回示例：{\"code\":200,\"msg\":\"操作成功\",\"data\":{\"successCount\":1,\"failCount\":0,\"failMsgList\":[]}}"
    )
    @ApiResponses({
            @ApiResponse(
                    code = 200,
                    message = "导入成功"

            )
    })
    CommonResponseVO<GraduateStudentImportResultVO> importGraduateStudents(
            @ApiParam(
                    name = "importBatchDTO",
                    value = "结业学员批量导入参数",
                    required = true,  // 替代 3.x requiredMode = REQUIRED
                    example = "{\"graduateStudentList\":[{\"name\":\"张三\",\"studentNo\":\"2024001\"}]}" // 补充参数示例（原3.x content示例迁移）
            )
            @Valid @RequestBody GraduateStudentImportBatchDTO importBatchDTO
    );

    /**
     * 结业学员模板下载（可选，辅助导入）
     */
    @PostMapping("/import/template/download")
    @ApiOperation(
            value = "结业学员导入模板下载",
            notes = "下载标准的结业学员导入Excel模板。返回示例：{\"code\":200,\"msg\":\"操作成功\",\"data\":\"模板文件流\"}"
    )
    @ApiResponses({
            @ApiResponse(
                    code = 200,
                    message = "下载成功"

            )
    })
    CommonResponseVO<Void> downloadImportTemplate();

    /**
     * 结业学员导出
     */
    @PostMapping("/export")
    @ApiOperation(
            value = "结业学员导出",
            notes = "根据查询条件导出结业学员数据为Excel文件。返回示例：{\"code\":200,\"msg\":\"操作成功\",\"data\":\"Excel文件流\"}"
    )
    @ApiResponses({
            @ApiResponse(
                    code = 200,
                    message = "导出成功"

            )
    })
    CommonResponseVO<Void> exportGraduateStudents(
            @ApiParam(
                    name = "exportQuery",
                    value = "结业学员导出查询条件",
                    required = true,
                    example = "{\"className\":\"计算机一班\",\"graduateDate\":\"2024-06-01\"}"
            )
            @Valid @RequestBody GraduateStudentExportQuery exportQuery
    );
}