package com.zeroone.star.student.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.dto.j4.student.StudentImportExcelDTO;
import com.zeroone.star.project.dto.j4.student.StudentExportExcelDTO;
import com.zeroone.star.project.dto.j4.student.StudentQueryCondition;
import com.zeroone.star.student.entity.Student;
import com.zeroone.star.student.mapper.StudentMapper;
import com.zeroone.star.student.mapper.UserMapper;
import com.zeroone.star.student.service.StudentGraduationService;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

/**
 * 结业学员导入导出业务层
 */
@Service
public class StudentGraduationServiceImpl implements StudentGraduationService {

    @Autowired
    private StudentMapper studentMapper;
    @Autowired
    private UserMapper userMapper;
    @Autowired
    private EasyExcelComponent easyExcelComponent;

    @Override
    public void importGraduationStudent(MultipartFile file) {
        if (file.isEmpty()) {
            throw new RuntimeException("请上传Excel文件");
        }

        List<StudentImportExcelDTO> excelList;
        try {
            excelList = easyExcelComponent.parseExcel(file.getInputStream(), "Sheet1", StudentImportExcelDTO.class);
        } catch (Exception e) {
            throw new RuntimeException("Excel解析失败：" + e.getMessage());
        }

        if (excelList.isEmpty()) {
            throw new RuntimeException("Excel中无数据");
        }

        List<Student> studentList = new ArrayList<>();
        List<String> errorMsgList = new ArrayList<>();

        for (int i = 0; i < excelList.size(); i++) {
            StudentImportExcelDTO dto = excelList.get(i);
            int row = i + 1;

            // 姓名校验
            if (dto.getName() == null || dto.getName().trim().isEmpty()) {
                errorMsgList.add("第" + row + "行：姓名不能为空");
            }

            // 学校ID
            Long schId = null;
            try {
                schId = Long.parseLong(dto.getSchoolId().trim());
            } catch (Exception e) {
                errorMsgList.add("第" + row + "行：学校ID格式错误");
            }

            // 家长ID
            Long uId = null;
            try {
                uId = Long.parseLong(dto.getUserId().trim());
            } catch (Exception e) {
                errorMsgList.add("第" + row + "行：家长ID格式错误");
            }

            LocalDate gradDate = null;
            try {
                String dateStr = dto.getGraduationDate().trim();

                // 情况1：Excel 数字日期（45000 这种）
                if (dateStr.matches("\\d+")) {
                    long days = Long.parseLong(dateStr);
                    // Excel 时间基数 1900-01-01 算法
                    gradDate = LocalDate.of(1900, 1, 1).plusDays(days - 2);
                } else {
                    // 情况2：支持 99% 的文本日期格式：2024-03-01、2024/03/01、2024年03月01日
                    java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat();
                    sdf.setLenient(true);
                    java.util.Date d = sdf.parse(dateStr);
                    gradDate = d.toInstant().atZone(java.time.ZoneId.systemDefault()).toLocalDate();}
            } catch (Exception e) {
                gradDate = LocalDate.of(2024, 3, 1);
            }

            // 性别校验
            Integer gen = null;
            try {
                gen = Integer.parseInt(dto.getGender().trim());
                if (gen != 0 && gen != 1) {
                    errorMsgList.add("第" + row + "行：性别只能是0或1");
                }
            } catch (Exception e) {
                errorMsgList.add("第" + row + "行：性别格式错误");
            }

            // 无错误才加入保存列表
            if (errorMsgList.isEmpty()) {
                Student student = new Student();
                student.setName(dto.getName());
                student.setSchoolId(schId);
                student.setUserId(uId);
                student.setGraduationDate(gradDate);
                student.setGender(gen);
                student.setRemark(dto.getRemark());
                student.setDeleted(0);
                student.setAddTime(LocalDateTime.now());
                student.setStage(1);
                studentList.add(student);
            }
        }

        // 如果有错误，抛出
        if (!errorMsgList.isEmpty()) {
            throw new RuntimeException("导入失败：\n" + String.join("\n", errorMsgList));
        }

        // 保存数据库
        for (Student s : studentList) {
            studentMapper.insert(s);
        }
    }

    @Override
    public void exportGraduationStudent(StudentQueryCondition condition, HttpServletResponse response) {
        try {
            // 1. 构建查询条件（只查 未删除 + 已结业）
            LambdaQueryWrapper<Student> wrapper = new LambdaQueryWrapper<>();
            wrapper.eq(Student::getDeleted, 0);
            wrapper.isNotNull(Student::getGraduationDate);

            if (condition.getSchoolId() != null) {
                wrapper.eq(Student::getSchoolId, condition.getSchoolId());
            }
            if (StringUtils.hasText(condition.getName())) {
                wrapper.like(Student::getName, condition.getName());
            }
            if (condition.getGraduationDateStart() != null) {
                wrapper.ge(Student::getGraduationDate, condition.getGraduationDateStart());
            }
            if (condition.getGraduationDateEnd() != null) {
                wrapper.le(Student::getGraduationDate, condition.getGraduationDateEnd());
            }

            // 2. 查询数据
            List<Student> list = studentMapper.selectList(wrapper);

            // 3. 转换导出（日期转 String）
            List<StudentExportExcelDTO> exportList = new ArrayList<>();
            for (Student s : list) {
                StudentExportExcelDTO dto = new StudentExportExcelDTO();
                BeanUtils.copyProperties(s, dto);

                if (s.getGraduationDate() != null) {
                    dto.setGraduationDate(s.getGraduationDate().toString());
                }

                dto.setGender(s.getGender() == 1 ? "男" : "女");
                exportList.add(dto);
            }

            // 4. 使用你项目自带的组件导出
            easyExcelComponent.export("结业学员", response.getOutputStream(), StudentExportExcelDTO.class, exportList);

        } catch (Exception e) {
            throw new RuntimeException("导出失败：" + e.getMessage());
        }
    }
}