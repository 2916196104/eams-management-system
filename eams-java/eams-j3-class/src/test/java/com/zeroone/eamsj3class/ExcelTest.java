package com.homework.eamsj3class;

import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsFileInfo;
import com.zeroone.star.project.dto.j3.course.CourseExportDTO;
import lombok.SneakyThrows;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

/**
 * Excel测试类
 * @authore Longan
 * @description
 */
@SpringBootTest
public class ExcelTest {
    @Resource
    EasyExcelComponent excel;

    @Test
    void testExport(){
        //测试数据
        List<CourseExportDTO> list = new ArrayList<>();
        for (int i = 1; i < 11; i++) {
            CourseExportDTO courseExportDTO = new CourseExportDTO();
            courseExportDTO.setSubjectId(""+i);
            courseExportDTO.setName("课程"+i);
            courseExportDTO.setLessonCount(BigDecimal.valueOf(i));
            courseExportDTO.setLessonType(i);
            courseExportDTO.setPrice(BigDecimal.valueOf(i));
            courseExportDTO.setUnitPrice(BigDecimal.valueOf(i));
            list.add(courseExportDTO);
        }
        //导出
        excel.export("test.xlsx", "test", CourseExportDTO.class, list);
    }

    @Resource
    FastDfsClientComponent dfs;

    @SneakyThrows
    @Test
    void testUploadExcel(){
        //测试数据
        List<CourseExportDTO> list = new ArrayList<>();
        for (int i = 1; i < 11; i++) {
            CourseExportDTO courseExportDTO = new CourseExportDTO();
            courseExportDTO.setSubjectId(""+i);
            courseExportDTO.setName("课程"+i);
            courseExportDTO.setLessonCount(BigDecimal.valueOf(i));
            courseExportDTO.setLessonType(i);
            courseExportDTO.setPrice(BigDecimal.valueOf(i));
            courseExportDTO.setUnitPrice(BigDecimal.valueOf(i));
            list.add(courseExportDTO);
        }
        //导出到文件流中
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        excel.export("test", out, CourseExportDTO.class, list);
        //上传到DFS中
        FastDfsFileInfo info = dfs.uploadFile(out.toByteArray(), "xlsx");
        System.out.println(info);
        out.close();
    }
}
