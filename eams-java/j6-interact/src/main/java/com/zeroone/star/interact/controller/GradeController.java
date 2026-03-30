package com.zeroone.star.interact.controller;

import com.alibaba.excel.EasyExcel;
import com.baomidou.mybatisplus.extension.plugins.pagination.PageDTO;
import com.zeroone.star.interact.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.interact.service.IGradeRecordService;
import com.zeroone.star.project.dto.j6.interact.GradeListDTO;
import com.zeroone.star.project.dto.j6.interact.GradeFormDTO;
import com.zeroone.star.project.dto.j6.interact.GradeRecordDTO;
import com.zeroone.star.project.j6.interact.GradeApis;
import com.zeroone.star.project.query.j6.interact.GradeFormQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import java.io.IOException;
import java.util.List;

@RestController
@RequestMapping("j6/grade")
@Api(tags = "成绩单")
public class GradeController implements GradeApis {

    @Resource
    private IGradeRecordService gradeRecordService;
    @Resource
    EasyExcelComponent easyExcelComponent;
    /**
     * 获得成绩单列表（条件+分页）
     *
     * @param condition 查询条件
     * @return 成绩单列表
     */
    @GetMapping
    @ApiOperation("获取成绩单列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<GradeFormDTO>> queryForm(GradeFormQuery condition) {
        return null;
    }

    /**
     * 分页查询成绩信息
     *
     * @param id 成绩单id
     * @return 返回结果
     */
    @GetMapping("/{id}")
    @ApiOperation("获取成绩列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<GradeListDTO>> queryGrade(@PathVariable("id") Long id) {
        return null;
    }

    /**
     * 保存成绩单信息，新增和修改成绩单走这里
     *
     * @param gradeFormDTO 成绩单信息
     * @return 保存结果
     */
    @PostMapping("/form")
    @ApiOperation("保存成绩单")
    @Override
    public JsonVO<Long> saveGrade(@RequestBody GradeFormDTO gradeFormDTO) {
        return null;
    }

    /**
     * 删除成绩单
     *
     * @param ids 成绩单id列表
     * @return 返回结果
     */
    @DeleteMapping("/form")
    @ApiOperation("删除成绩单")
    @Override
    public JsonVO<List<Long>> deleteGrade(@RequestBody List<Long> ids) {
        return null;
    }


    /**
     * 保存成绩
     *
     * @param gradeRecordDTO 成绩数据对象
     * @return
     */
    @PostMapping("/record")
    @ApiOperation("保存成绩")
    @Override
    public JsonVO<String> saveGradeRecord( GradeRecordDTO gradeRecordDTO) {
        return gradeRecordService.saveGradeRecord(gradeRecordDTO);
    }

    /**
     * 删除成绩,支持批量删除
     *
     * @param ids
     * @return
     */
    @DeleteMapping("/record")
    @ApiOperation("删除成绩")
    @Override
    public JsonVO<List<Long>> deleteGradeRecord(@RequestBody List<Long> ids) {
       return  gradeRecordService.deleteGradeRecord(ids);
    }

    /**
     * 导入成绩
     * @return
     */
    @PostMapping("/file/{gradeId}")
    @ApiOperation("导入成绩")
    @ResponseBody

    public JsonVO<String> addGrades(@PathVariable Long gradeId, MultipartFile file) {
        try {
            // 【看这里】：调用组件的 3个参数 方法
            List<GradeRecordDTO> dataList = EasyExcel.read(file.getInputStream())
                    .head(GradeRecordDTO.class)
                    .sheet()
                    .headRowNumber(2) //
                    .doReadSync();

            if (dataList.isEmpty()) {
                return JsonVO.fail("文件内无有效数据");
            }

            // 往下传给 Service 处理业务逻辑
            return gradeRecordService.addGrades(gradeId, dataList);

        } catch (IOException e) {
            return JsonVO.fail("文件读取异常：" + e.getMessage());
        } catch (Exception e) { // 捕获可能出现的数据转换异常等
            e.printStackTrace();
            return JsonVO.fail("解析或导入失败：" + e.getMessage());
        }
    }

}
