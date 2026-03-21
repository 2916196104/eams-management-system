package com.zeroone.star.project.j8.stumanager;

import com.zeroone.star.project.dto.j8.stumanager.OnlineStu.StudentAdvisorDTO;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;

/**
 * 在线学员
 */
public interface OnlineStuApis {

    /**
     * 修改学员顾问
     * @param studentAdvisorDTO 学员顾问信息
     * @return 修改结果
     */
    @ApiOperation(value = "修改学员顾问", notes = "根据学员ID修改对应学员的顾问信息")
    JsonVO<String> updateStudentAdvisor(@RequestBody StudentAdvisorDTO studentAdvisorDTO);

    /**
     * 导入学员
     * @param file 学员数据文件
     * @return 导入结果
     */
    @ApiOperation(value = "导入学员", notes = "通过Excel文件导入学员数据")
    JsonVO<String> importStudents(@ApiParam(value = "学员数据Excel文件", required = true) MultipartFile file);

    /**
     * 导出学员
     * @param condition 导出条件
     * @return 导出的学员数据文件
     */
    @ApiOperation(value = "导出学员", notes = "根据条件导出学员数据为Excel文件")
    JsonVO<byte[]> exportStudents(@ApiParam(value = "导出条件", required = false) @RequestParam(required = false) String condition);

}
