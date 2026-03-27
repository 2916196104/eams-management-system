package com.zeroone.star.stumanager.controller;

import com.zeroone.star.project.dto.j8.stumanager.OnlineStu.StudentAdvisorDTO;
import com.zeroone.star.project.j8.stumanager.OnlineStuApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.entity.User;
import com.zeroone.star.stumanager.service.IStudentService;
import com.zeroone.star.stumanager.service.IUserService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.ss.usermodel.*;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;
import java.io.InputStream;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.io.ByteArrayOutputStream;
import java.net.URLEncoder;
import java.util.List;
/**
 * 在线学员
 */
@RestController
@RequestMapping("/atu/online-stu")
@Api(tags = "在线学员")
public class OnlineStuController implements OnlineStuApis {

    @Autowired
    private IStudentService studentService;
    @Autowired
    private IUserService userService;

    @ApiOperation(value = "修改学员顾问", notes = "根据学员ID修改对应学员的顾问信息")
    @PutMapping("update-advisor")
    @Override
    public JsonVO<OnlineStuApis.UpdateAdvisorResult> updateStudentAdvisor(@RequestBody StudentAdvisorDTO studentAdvisorDTO) {
        try {
            // 根据学员ID查询学员信息
            Student student = studentService.getById(studentAdvisorDTO.getStudentId());
            if (student == null) {
                return JsonVO.create(null, ResultStatus.FAIL.getCode(), "学员不存在");
            }

            // 更新顾问信息
            student.setCounselor(studentAdvisorDTO.getAdvisorId());
            studentService.updateById(student);

            // 构建返回结果
            OnlineStuApis.UpdateAdvisorResult result = new OnlineStuApis.UpdateAdvisorResult();
            result.setStudentId(studentAdvisorDTO.getStudentId());
            result.setAdvisorId(studentAdvisorDTO.getAdvisorId());
            result.setAdvisorName(studentAdvisorDTO.getAdvisorName());

            return JsonVO.success(result);
        } catch (Exception e) {
            e.printStackTrace();
            return JsonVO.create(null, ResultStatus.FAIL.getCode(), "修改顾问失败: " + e.getMessage());
        }
    }

//    @ApiOperation(value = "导入学员", notes = "通过Excel文件导入学员数据")
//    @PostMapping("import")
//    @Override
//    public JsonVO<String> importStudents(@ApiParam(value = "学员数据Excel文件", required = true) MultipartFile file) {
//        // TODO: 实现导入学员逻辑
//        return JsonVO.success("导入学员成功");
//    }
@ApiOperation(value = "导入学员", notes = "通过Excel文件导入学员数据，支持xls和xlsx格式，模板包含：姓名、手机号、登录密码、家长姓名、性别、出生日期、身份证号")
@PostMapping("import")
@Override
public JsonVO<OnlineStuApis.ImportStudentsResult> importStudents(@ApiParam(value = "学员数据Excel文件，支持xls和xlsx格式", required = true) MultipartFile file) {
    try {
        // 1. 校验文件类型
        String fileName = file.getOriginalFilename();
        if (fileName == null || (!fileName.endsWith(".xls") && !fileName.endsWith(".xlsx"))) {
            OnlineStuApis.ImportStudentsResult result = new OnlineStuApis.ImportStudentsResult();
            result.setSuccessCount(0);
            result.setFailCount(1);
            java.util.List<OnlineStuApis.FailItem> failList = new java.util.ArrayList<>();
            OnlineStuApis.FailItem failItem = new OnlineStuApis.FailItem();
            failItem.setRowIndex(0);
            failItem.setReason("文件类型错误，仅支持xls和xlsx格式");
            failList.add(failItem);
            result.setFailList(failList);
            return JsonVO.success(result);
        }

        // 2. 解析Excel
        InputStream inputStream = file.getInputStream();
        Workbook workbook;
        if (fileName.endsWith(".xls")) {
            workbook = new HSSFWorkbook(inputStream);
        } else {
            workbook = new XSSFWorkbook(inputStream);
        }

        Sheet sheet = workbook.getSheetAt(0);
        if (sheet == null) {
            workbook.close();
            OnlineStuApis.ImportStudentsResult result = new OnlineStuApis.ImportStudentsResult();
            result.setSuccessCount(0);
            result.setFailCount(1);
            java.util.List<OnlineStuApis.FailItem> failList = new java.util.ArrayList<>();
            OnlineStuApis.FailItem failItem = new OnlineStuApis.FailItem();
            failItem.setRowIndex(0);
            failItem.setReason("Excel文件为空");
            failList.add(failItem);
            result.setFailList(failList);
            return JsonVO.success(result);
        }

        int rowCount = sheet.getPhysicalNumberOfRows();
        if (rowCount < 2) {
            workbook.close();
            OnlineStuApis.ImportStudentsResult result = new OnlineStuApis.ImportStudentsResult();
            result.setSuccessCount(0);
            result.setFailCount(1);
            java.util.List<OnlineStuApis.FailItem> failList = new java.util.ArrayList<>();
            OnlineStuApis.FailItem failItem = new OnlineStuApis.FailItem();
            failItem.setRowIndex(0);
            failItem.setReason("Excel没有数据");
            failList.add(failItem);
            result.setFailList(failList);
            return JsonVO.success(result);
        }

        // 3. 日期格式化
        DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        int successCount = 0;
        int failCount = 0;
        java.util.List<OnlineStuApis.FailItem> failList = new java.util.ArrayList<>();

        // 4. 从第二行开始遍历（第一行是表头）
        for (int i = 1; i < rowCount; i++) {
            Row row = sheet.getRow(i);
            if (row == null) continue;

            try {
                // 读取Excel列数据
                // 列0: 姓名, 列1: 手机号, 列2: 登录密码, 列3: 家长姓名
                // 列4: 性别, 列5: 出生日期, 列6: 身份证号
                String studentName = getCellStringValue(row.getCell(0));
                String mobile = getCellStringValue(row.getCell(1));
                String password = getCellStringValue(row.getCell(2));
                String parentName = getCellStringValue(row.getCell(3));
                String genderStr = getCellStringValue(row.getCell(4));
                String birthdayStr = getCellStringValue(row.getCell(5));
                String idcard = getCellStringValue(row.getCell(6));

                // 校验必填字段
                if (studentName == null || studentName.trim().isEmpty()) {
                    failCount++;
                    OnlineStuApis.FailItem failItem = new OnlineStuApis.FailItem();
                    failItem.setRowIndex(i + 1); // 行号从1开始
                    failItem.setReason("姓名不能为空");
                    failList.add(failItem);
                    continue;
                }
                if (mobile == null || mobile.trim().isEmpty()) {
                    failCount++;
                    OnlineStuApis.FailItem failItem = new OnlineStuApis.FailItem();
                    failItem.setRowIndex(i + 1);
                    failItem.setReason("手机号不能为空");
                    failList.add(failItem);
                    continue;
                }
                if (password == null || password.trim().isEmpty()) {
                    failCount++;
                    OnlineStuApis.FailItem failItem = new OnlineStuApis.FailItem();
                    failItem.setRowIndex(i + 1);
                    failItem.setReason("登录密码不能为空");
                    failList.add(failItem);
                    continue;
                }

                // 5. 创建User记录（家长账号）
                User user = new User();
                user.setName(parentName != null ? parentName : studentName); // 家长姓名默认为学员姓名
                user.setMobile(mobile);
                user.setPassword(password); // 实际生产环境应加密
                user.setState(true);
                userService.save(user);

                // 6. 创建Student记录
                Student student = new Student();
                student.setName(studentName);
                student.setUserId(user.getId());
                student.setGender("男".equals(genderStr) ? 1 : 0); // 转换性别
                student.setIdcard(idcard);

                // 解析出生日期
                if (birthdayStr != null && !birthdayStr.trim().isEmpty()) {
                    try {
                        student.setBirthday(LocalDate.parse(birthdayStr, dateFormatter));
                    } catch (Exception e) {
                        failCount++;
                        OnlineStuApis.FailItem failItem = new OnlineStuApis.FailItem();
                        failItem.setRowIndex(i + 1);
                        failItem.setReason("出生日期格式错误，应为yyyy-MM-dd");
                        failList.add(failItem);
                        continue;
                    }
                }

                // 设置默认值
                student.setStage(1); // 1-在线学员
                student.setDeleted(0);

                studentService.save(student);
                successCount++;

            } catch (Exception e) {
                failCount++;
                OnlineStuApis.FailItem failItem = new OnlineStuApis.FailItem();
                failItem.setRowIndex(i + 1);
                failItem.setReason("导入失败: " + e.getMessage());
                failList.add(failItem);
            }
        }

        workbook.close();

        // 构建返回结果
        OnlineStuApis.ImportStudentsResult result = new OnlineStuApis.ImportStudentsResult();
        result.setSuccessCount(successCount);
        result.setFailCount(failCount);
        result.setFailList(failList);

        return JsonVO.success(result);
    } catch (Exception e) {
        e.printStackTrace();
        OnlineStuApis.ImportStudentsResult result = new OnlineStuApis.ImportStudentsResult();
        result.setSuccessCount(0);
        result.setFailCount(1);
        java.util.List<OnlineStuApis.FailItem> failList = new java.util.ArrayList<>();
        OnlineStuApis.FailItem failItem = new OnlineStuApis.FailItem();
        failItem.setRowIndex(0);
        failItem.setReason("导入学员失败: " + e.getMessage());
        failList.add(failItem);
        result.setFailList(failList);
        return JsonVO.success(result);
    }
}

//@ApiOperation(value = "下载导入模板", notes = "下载学员导入Excel模板")
//@GetMapping("download-template")
//@Override
//public ResponseEntity<byte[]> downloadTemplate() {
//    try {
//        // 创建工作簿
//        Workbook workbook = new HSSFWorkbook();
//        Sheet sheet = workbook.createSheet("学员导入模板");
//
//        // 创建表头
//        Row headerRow = sheet.createRow(0);
//        String[] headers = {"姓名", "手机号", "登录密码", "家长姓名", "性别", "出生日期", "身份证号"};
//        for (int i = 0; i < headers.length; i++) {
//            Cell cell = headerRow.createCell(i);
//            cell.setCellValue(headers[i]);
//        }
//
//        // 添加示例数据
//        Row exampleRow = sheet.createRow(1);
//        exampleRow.createCell(0).setCellValue("张三");
//        exampleRow.createCell(1).setCellValue("13800138000");
//        exampleRow.createCell(2).setCellValue("123456");
//        exampleRow.createCell(3).setCellValue("张父");
//        exampleRow.createCell(4).setCellValue("男");
//        exampleRow.createCell(5).setCellValue("2000-01-01");
//        exampleRow.createCell(6).setCellValue("110101200001011234");
//
//        // 转换为字节数组
//        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
//        workbook.write(outputStream);
//        workbook.close();
//        byte[] bytes = outputStream.toByteArray();
//        outputStream.close();
//
//        // 设置响应头
//        HttpHeaders header = new HttpHeaders();
//        header.setContentType(MediaType.APPLICATION_OCTET_STREAM);
//        String fileName = URLEncoder.encode("学员导入模板.xls", "UTF-8");
//        header.setContentDispositionFormData("attachment", fileName);
//        header.setContentLength(bytes.length);
//
//        // 返回ResponseEntity
//        return new ResponseEntity<>(bytes, header, HttpStatus.OK);
//    } catch (Exception e) {
//        e.printStackTrace();
//        return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
//    }
//}
    /**
     * 获取单元格字符串值
     */
    private String getCellStringValue(Cell cell) {
        if (cell == null) {
            return null;
        }
        switch (cell.getCellType()) {
            case STRING:
                return cell.getStringCellValue().trim();
            case NUMERIC:
                if (DateUtil.isCellDateFormatted(cell)) {
                    return cell.getDateCellValue().toString();
                }
                // 防止科学计数法
                double value = cell.getNumericCellValue();
                if (value == Math.floor(value)) {
                    return String.valueOf((long) value);
                }
                return String.valueOf(value);
            case BOOLEAN:
                return String.valueOf(cell.getBooleanCellValue());
            case FORMULA:
                return cell.getCellFormula();
            default:
                return null;
        }
    }

//    @ApiOperation(value = "导出学员", notes = "根据条件导出学员数据为Excel文件")
//    @GetMapping("export")
//    @Override
//    public JsonVO<byte[]> exportStudents(@ApiParam(value = "导出条件", required = false) @RequestParam(required = false) String condition) {
//        // TODO: 实现导出学员逻辑
//        return JsonVO.success(new byte[0]);
//    }
@ApiOperation(value = "导出学员", notes = "根据条件导出学员数据为Excel文件")
@GetMapping("export")
@Override
public ResponseEntity<byte[]> exportStudents(@ApiParam(value = "导出条件", required = false) @RequestParam(required = false) String condition) {
    try {
        // 1. 查询所有在线学员
        List<Student> studentList = studentService.list();

        // 2. 创建工作簿
        Workbook workbook = new HSSFWorkbook();
        Sheet sheet = workbook.createSheet("在线学员信息");

        // 3. 创建表头
        Row headerRow = sheet.createRow(0);
        String[] headers = {"姓名", "手机号", "登录密码", "家长姓名", "性别", "出生日期", "身份证号"};
        for (int i = 0; i < headers.length; i++) {
            Cell cell = headerRow.createCell(i);
            cell.setCellValue(headers[i]);
        }

        // 4. 填充数据
        int rowNum = 1;
        for (Student student : studentList) {
            Row row = sheet.createRow(rowNum++);

            // 获取对应的用户信息
            User user = null;
            if (student.getUserId() != null) {
                user = userService.getById(student.getUserId());
            }

            // 列0: 姓名
            row.createCell(0).setCellValue(student.getName() != null ? student.getName() : "");

            // 列1: 手机号
            row.createCell(1).setCellValue(user != null && user.getMobile() != null ? user.getMobile() : "");

            // 列2: 登录密码
            row.createCell(2).setCellValue(user != null && user.getPassword() != null ? user.getPassword() : "");

            // 列3: 家长姓名
            row.createCell(3).setCellValue(user != null && user.getName() != null ? user.getName() : "");

            // 列4: 性别 (0-女, 1-男)
            String genderStr = "";
            if (student.getGender() != null) {
                genderStr = student.getGender() == 1 ? "男" : "女";
            }
            row.createCell(4).setCellValue(genderStr);

            // 列5: 出生日期
            row.createCell(5).setCellValue(student.getBirthday() != null ? student.getBirthday().toString() : "");

            // 列6: 身份证号
            row.createCell(6).setCellValue(student.getIdcard() != null ? student.getIdcard() : "");
        }

        // 5. 转换为字节数组
        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        workbook.write(outputStream);
        workbook.close();
        byte[] bytes = outputStream.toByteArray();
        outputStream.close();

        // 6. 设置响应头
        HttpHeaders header = new HttpHeaders();
        header.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        String fileName = URLEncoder.encode("在线学员信息.xls", "UTF-8");
        header.setContentDispositionFormData("attachment", fileName);
        header.setContentLength(bytes.length);

        // 7. 返回ResponseEntity
        return new ResponseEntity<>(bytes, header, HttpStatus.OK);
    } catch (Exception e) {
        e.printStackTrace();
        // 返回错误响应
        return new ResponseEntity<>(HttpStatus.INTERNAL_SERVER_ERROR);
    }
}
}
