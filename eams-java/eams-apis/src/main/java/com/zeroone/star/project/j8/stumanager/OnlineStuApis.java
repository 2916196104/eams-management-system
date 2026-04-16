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
    JsonVO<UpdateAdvisorResult> updateStudentAdvisor(@RequestBody StudentAdvisorDTO studentAdvisorDTO);

    /**
     * 导入学员
     * @param file 学员数据文件
     * @return 导入结果
     */
    @ApiOperation(value = "导入学员", notes = "通过Excel文件导入学员数据，支持xls和xlsx格式，模板包含：姓名、手机号、登录密码、家长姓名、性别、出生日期、身份证号")
    JsonVO<ImportStudentsResult> importStudents(@ApiParam(value = "学员数据Excel文件，支持xls和xlsx格式", required = true) MultipartFile file);


    /**
     * 导入学员返回结果
     */
    class ImportStudentsResult {
        private int successCount;
        private int failCount;
        private java.util.List<FailItem> failList;

        public int getSuccessCount() {
            return successCount;
        }

        public void setSuccessCount(int successCount) {
            this.successCount = successCount;
        }

        public int getFailCount() {
            return failCount;
        }

        public void setFailCount(int failCount) {
            this.failCount = failCount;
        }

        public java.util.List<FailItem> getFailList() {
            return failList;
        }

        public void setFailList(java.util.List<FailItem> failList) {
            this.failList = failList;
        }
    }

    /**
     * 失败项
     */
    class FailItem {
        private int rowIndex;
        private String reason;

        public int getRowIndex() {
            return rowIndex;
        }

        public void setRowIndex(int rowIndex) {
            this.rowIndex = rowIndex;
        }

        public String getReason() {
            return reason;
        }

        public void setReason(String reason) {
            this.reason = reason;
        }
    }

    /**
     * 导出学员
     * @param condition 导出条件
     * @return 导出的学员数据文件
     */
    @ApiOperation(value = "导出学员", notes = "根据条件导出学员数据为Excel文件")
    org.springframework.http.ResponseEntity<byte[]> exportStudents(@ApiParam(value = "导出条件", required = false) @RequestParam(required = false) String condition);

    /**
     * 修改顾问返回结果
     */
    class UpdateAdvisorResult {
        private Long studentId;
        private Long advisorId;
        private String advisorName;

        public Long getStudentId() {
            return studentId;
        }

        public void setStudentId(Long studentId) {
            this.studentId = studentId;
        }

        public Long getAdvisorId() {
            return advisorId;
        }

        public void setAdvisorId(Long advisorId) {
            this.advisorId = advisorId;
        }

        public String getAdvisorName() {
            return advisorName;
        }

        public void setAdvisorName(String advisorName) {
            this.advisorName = advisorName;
        }
    }

}
