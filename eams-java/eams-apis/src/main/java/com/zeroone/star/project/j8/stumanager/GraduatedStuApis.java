package com.zeroone.star.project.j8.stumanager;

import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;

/**
 * 结业学员API接口
 */
@Api(tags = "结业学员")
public interface GraduatedStuApis {

    /**
     * 导出结业学员列表
     *
     * @param response HTTP响应
     */
    @ApiOperation(value = "导出结业学员列表", notes = "导出Excel格式的结业学员列表")
    void exportGraduatedStudents(HttpServletResponse response);


    /**
     * 导入结业学员
     *
     * @param file Excel文件
     * @return 导入结果
     */
    @ApiOperation(value = "导入结业学员", notes = "通过Excel文件批量导入结业学员")
    JsonVO<String> importGraduatedStudents(MultipartFile file);
}
