package com.zeroone.star.stumanager.service;

import com.zeroone.star.project.dto.j8.SaveStu.SaveStuAddDTO;
import com.zeroone.star.project.dto.j8.SaveStu.SaveStuDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.SaveStu.DictVO;
import com.zeroone.star.stumanager.entity.Student;
import com.baomidou.mybatisplus.extension.service.IService;
import io.swagger.annotations.ApiOperation;

import javax.validation.Valid;
import java.util.List;

/**
 * <p>
 * 学生表 服务类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
public interface IStudentService extends IService<Student> {

    @ApiOperation("保存学员信息")
    JsonVO<SaveStuDTO> saveStudent(@Valid SaveStuDTO saveStuDTO);

    @ApiOperation("修改学员状态")
    JsonVO<SaveStuDTO> updateStudentStage(@Valid SaveStuDTO saveStuDTO);

    @ApiOperation("获取亲属关系字典")
    JsonVO<List<DictVO>> listFamilyRel();

    @ApiOperation("获取年级下拉字典")
    public JsonVO<List<DictVO>> listGradeDict();

    @ApiOperation("获取来源下拉字典")
    JsonVO<List<DictVO>> listJoinWayDict();
}
