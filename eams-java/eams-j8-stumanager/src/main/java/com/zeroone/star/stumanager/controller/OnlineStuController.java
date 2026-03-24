package com.zeroone.star.stumanager.controller;

import com.zeroone.star.project.dto.OnlineStu.StudentAdvisorDTO;
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
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.ss.usermodel.*;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;
import java.io.InputStream;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.io.ByteArrayOutputStream;
import java.util.List;
/**
 * 在线学员
 */
@RestController
@RequestMapping("online-stu")
@Api(tags = "在线学员")
public class OnlineStuController implements OnlineStuApis {

    @Autowired
    private IStudentService studentService;
    @Autowired
    private IUserService userService;

    @ApiOperation(value = "修改学员顾问", notes = "根据学员ID修改对应学员的顾问信息")
    @PutMapping("update-advisor")
    @Override
    public JsonVO<String> updateStudentAdvisor(@RequestBody StudentAdvisorDTO studentAdvisorDTO) {
        try {
            // 根据学员ID查询学员信息
            Student student = studentService.getById(studentAdvisorDTO.getStudentId());
            if (student == null) {
                return JsonVO.create("学员不存在", ResultStatus.FAIL.getCode(), "学员不存在");
            }

            // 更新顾问信息
            student.setCounselor(studentAdvisorDTO.getAdvisorId());
            studentService.updateById(student);

            return JsonVO.success("修改顾问成功");
        } catch (Exception e) {
            e.printStackTrace();
            return JsonVO.create("修改顾问失败", ResultStatus.FAIL.getCode(), e.getMessage());
        }
    }

//    @ApiOperation(value = "导入学员", notes = "通过Excel文件导入学员数据")
//    @PostMapping("import")
//    @Override
//    public JsonVO<String> importStudents(@ApiParam(value = "学员数据Excel文件", required = true) MultipartFile file) {
//        // TODO: 实现导入学员逻辑
//        return JsonVO.success("导入学员成功");
//    }
@ApiOperation(value = "导入学员", notes = "通过Excel文件导入学员数据")
@PostMapping("import")
@Override
public JsonVO<String> importStudents(@ApiParam(value = "学员数据Excel文件", required = true) MultipartFile file) {
    try {
        // 1. 校验文件类型
        String fileName = file.getOriginalFilename();
        if (fileName == null || (!fileName.endsWith(".xls") && !fileName.endsWith(".xlsx"))) {
            return JsonVO.create("文件类型错误，仅支持xls和xlsx格式", ResultStatus.FAIL.getCode(), "文件类型错误");
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
            return JsonVO.create("Excel文件为空", ResultStatus.FAIL.getCode(), "Excel文件为空");
        }

        int rowCount = sheet.getPhysicalNumberOfRows();
        if (rowCount < 2) {
            workbook.close();
            return JsonVO.create("Excel没有数据", ResultStatus.FAIL.getCode(), "Excel没有数据");
        }

        // 3. 日期格式化
        DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        int successCount = 0;
        int failCount = 0;

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
                    continue;
                }
                if (mobile == null || mobile.trim().isEmpty()) {
                    failCount++;
                    continue;
                }
                if (password == null || password.trim().isEmpty()) {
                    failCount++;
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
                    student.setBirthday(LocalDate.parse(birthdayStr, dateFormatter));
                }

                // 设置默认值
                student.setStage(1); // 1-在线学员
                student.setDeleted(0);

                studentService.save(student);
                successCount++;

            } catch (Exception e) {
                failCount++;
            }
        }

        workbook.close();

        return JsonVO.success("导入学员成功，成功：" + successCount + "条，失败：" + failCount + "条");
    } catch (Exception e) {
        e.printStackTrace();
        return JsonVO.create("导入学员失败", ResultStatus.FAIL.getCode(), e.getMessage());
    }
}
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
public JsonVO<byte[]> exportStudents(@ApiParam(value = "导出条件", required = false) @RequestParam(required = false) String condition) {
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

        return JsonVO.success(bytes);
    } catch (Exception e) {
        e.printStackTrace();
        return JsonVO.create(null, ResultStatus.FAIL.getCode(), "导出学员失败: " + e.getMessage());
    }
}
}
