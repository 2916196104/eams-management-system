package com.zeroone.star.j7.interaction.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j7.interaction.entity.Student;
import com.zeroone.star.j7.interaction.mapper.GradeMapper;
import com.zeroone.star.j7.interaction.mapper.GradeRecordMapper;
import com.zeroone.star.j7.interaction.service.GradeRecordService;
import com.zeroone.star.j7.interaction.service.StudentService;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.interaction.GradeDTO;
import com.zeroone.star.project.dto.j7.interaction.GradeRecordSaveDTO;
import com.zeroone.star.project.dto.j7.interaction.ScoreImportExcelDTO;
import com.zeroone.star.project.entity.Grade;
import com.zeroone.star.project.entity.GradeRecord;
import com.zeroone.star.project.query.j7.interaction.GradeRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j7.interaction.GradeRecordVO;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import java.io.IOException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class GradeRecordServiceImpl extends ServiceImpl<GradeRecordMapper, GradeRecord> implements GradeRecordService {

    @Resource
    private GradeRecordMapper gradeRecordMapper;

    @Resource
    private GradeMapper gradeMapper;

    @Resource
    private StudentService studentService;

    @Resource
    private EasyExcelComponent easyExcelComponent;

    @Override
    public PageDTO<GradeRecordVO> pageList(GradeRecordQuery query) {
        // 分页参数
        long pageIndex = query.getPageIndex() < 1 ? 1 : query.getPageIndex();
        long pageSize = query.getPageSize() < 1 ? 30 : query.getPageSize();

        // 查询条件
        QueryWrapper<GradeRecord> wrapper = new QueryWrapper<>();
        if (query.getCreator() != null) {
            wrapper.eq("creator", query.getCreator());
        }

        // 1. 查询总数
        long total = gradeRecordMapper.selectCount(wrapper);

        // 2. 分页查询
        int start = (int) ((pageIndex - 1) * pageSize);
        wrapper.last("LIMIT " + start + "," + pageSize);
        List<GradeRecord> records = gradeRecordMapper.selectList(wrapper);

        // 3. 封装结果
        PageDTO<GradeRecordVO> dto = new PageDTO<>();
        dto.setPageIndex(pageIndex);
        dto.setPageSize(pageSize);
        dto.setTotal(total);
        dto.setPages((total + pageSize - 1) / pageSize);

        // 4. 转VO
        List<GradeRecordVO> rows = records.stream().map(item -> {
            GradeRecordVO vo = new GradeRecordVO();
            BeanUtils.copyProperties(item, vo);

            vo.setCreatorName("教师 ID：" + item.getCreator());
            vo.setGradeItem("考核项 ID：" + item.getGradeId());
            vo.setGradeDescription("暂无说明");
            return vo;
        }).collect(Collectors.toList());

        dto.setRows(rows);
        return dto;
    }
    @Override
    public JsonVO<Long> saveGrade(GradeDTO gradeDTO) {
        try {
            // 参数校验
            if (gradeDTO == null ||
                gradeDTO.getTitle() == null || gradeDTO.getTitle().trim().isEmpty()) {
                return JsonVO.fail("title 不能为空");
            }
            if (gradeDTO.getInfo() == null || gradeDTO.getInfo().trim().isEmpty()) {
                return JsonVO.fail("info 不能为空");
            }

            Grade grade = new Grade();
            BeanUtils.copyProperties(gradeDTO, grade);

            // 设置创建时间和逻辑删除标志
            grade.setAddTime(LocalDateTime.now());
            grade.setDeleted(0);

            // TODO: 从登录上下文中获取 creator 和 org_id，暂时设置默认值
            // 后续需要从用户认证信息中获取
            if (grade.getCreator() == null) {
                grade.setCreator(1L); // 默认创建者 ID，实际应从登录用户获取
            }
            if (grade.getOrgId() == null) {
                grade.setOrgId(1L); // 默认组织 ID，实际应从登录用户所属组织获取
            }

            int result;
            // 如果是修改操作，使用 updateById；否则使用 insert
            if (gradeDTO.getId() > 0) {
                grade.setId(gradeDTO.getId());
                // 修改时设置编辑时间和编辑者
                grade.setEditTime(LocalDateTime.now());
                grade.setEditor(grade.getCreator());
                result = gradeMapper.updateById(grade);
            } else {
                result = gradeMapper.insert(grade);
            }

            if (result > 0) {
                return JsonVO.success(grade.getId());
            } else {
                return JsonVO.fail("保存失败");
            }
        } catch (Exception e) {
            e.printStackTrace();
            return JsonVO.fail("保存异常：" + e.getMessage());
        }
    }


    @Override
    public JsonVO<List<Long>> deleteGrade(List<Long> ids) {
        try {
            // 参数校验
            if (ids == null || ids.isEmpty()) {
                return JsonVO.fail("删除 ID 列表不能为空");
            }

            // 逻辑删除：将 deleted 字段设置为 1
            int count = gradeMapper.deleteLogicBatchIds(ids);
            if (count > 0) {
                return JsonVO.success(ids);
            } else {
                return JsonVO.fail("删除失败，可能记录不存在");
            }
        } catch (Exception e) {
            e.printStackTrace();
            return JsonVO.fail("删除异常：" + e.getMessage());
        }
    }
    @Override
    public Boolean saveOrUpdateByDTO(GradeRecordSaveDTO dto) {
        // 校验学生是否存在
        Student student = studentService.getById(dto.getStudentId());
        if (student == null) {
            throw new RuntimeException("学生不存在，学生 ID:" + dto.getStudentId());
        }

        GradeRecord item = new GradeRecord();
        BeanUtils.copyProperties(dto, item);
        return this.saveOrUpdate(item);
    }
    @Override
    public void importGradeRecord(MultipartFile file, Long gradeId) throws IOException {
        // 1. 校验参数
        if (file == null || file.isEmpty() || gradeId == null) {
            throw new RuntimeException("文件为空或成绩单ID无效");
        }
        // 校验文件类型（xls/xlsx）
        String originalFilename = file.getOriginalFilename();
        if (originalFilename == null || (!originalFilename.endsWith(".xls") && !originalFilename.endsWith(".xlsx"))) {
            throw new RuntimeException("请上传合法的Excel文件（xls/xlsx）");
        }
        // 2. 调用EasyExcelComponent解析Excel（sheet名称为模板的sheet1）
        List<ScoreImportExcelDTO> excelDataList = easyExcelComponent.parseExcelWithSkipRows(
                file.getInputStream(),
                "sheet1",
                ScoreImportExcelDTO.class

        );
        // 3. 校验解析后的Excel数据是否为空
        if (excelDataList == null || excelDataList.isEmpty()) {
            throw new RuntimeException("未导入数据");
        }

        // 初始化成绩记录集合
        List<GradeRecord> records = new ArrayList<>();

        // 4. 遍历Excel数据，处理每一条学生成绩
        for (ScoreImportExcelDTO dto : excelDataList) {
            Student student;
            String studentName = dto.getStudentName();
            Long studentId = dto.getStudentCode();
            Integer score = dto.getScore();

            // 4.1 根据学生姓名查询学生列表
            List<Student> findList = studentService.getStudentListByExactName(studentName);
            // 学生不存在，抛异常
            if (findList == null || findList.isEmpty()) {
                throw new RuntimeException("学生不存在:" + studentName);
            }

            // 4.2 处理学生查询结果（单学生/重名学生）
            if (findList.size() == 1) {
                // 唯一学生，直接获取
                student = findList.get(0);
            } else {
                // 重名：校验学生编号是否为空
                if (studentId == null) {
                    throw new RuntimeException("因学生有重名身份无法确认，需要输入学生编号。学生姓名:" + studentName);
                }
                // 根据学生编号查询精准匹配的学生
                student = studentService.getById(studentId);
                if (student == null) {
                    throw new RuntimeException("学生编号不存在，学生姓名:" + studentName + "，学生编号:" + studentId);
                }
            }
            // 4.4 构建新的成绩记录对象
            GradeRecord item = new GradeRecord();
            item.setGradeId(gradeId);
            item.setStudentId(student.getId());
            item.setScore(score);
            records.add(item);
        }

        // 5. 批量保存所有成绩记录
        boolean saveSuccess = this.saveBatch(records);
        if (!saveSuccess) {
            throw new RuntimeException("导入出错");
        }

    }
}
