package com.zeroone.star.stumanager.service.impl;

import com.zeroone.star.project.dto.j8.stumanager.SaveStu.ChangeStuStageDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.SaveStu.DictVO;
import com.zeroone.star.project.vo.j8.stumanager.ProspectiveStuVO;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.common.StudentListQuery;
import com.zeroone.star.project.vo.j8.stumanager.StudentListVO;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.mapper.StudentMapper;
import com.zeroone.star.stumanager.service.IStudentService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.validation.annotation.Validated;
import javax.annotation.Resource;
import javax.validation.Valid;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

/**
 * <p>
 * 学生表 服务实现类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Service
public class StudentServiceImpl extends ServiceImpl<StudentMapper, Student> implements IStudentService {
    @Resource
    private StudentMapper studentMapper;

    @Resource
    MsStuMapper msStuMapper;


    // 学生状态
    public static final Integer STAGE_INTENTION = 0; // 意向
    public static final Integer STAGE_STUDYING = 1;  // 在学
    public static final Integer STAGE_FINISH = 2;    // 结业

    /**
     * 修改学生信息并保存到数据库（完全适配课程报名接口模板）
     *
     * @param saveStuDTO 学生修改DTO（含前端传入的学生ID、修改后的信息等参数）
     * @return 包含修改结果的JSON响应对象
     */
    @Override
    @Transactional(rollbackFor = Exception.class) // 事务控制，异常回滚
    public JsonVO<SaveStuDTO> saveStudent(@Validated SaveStuDTO saveStuDTO) {
        // 1. DTO转换为实体对象
        Student student = msStuMapper.toStudent(saveStuDTO);

        // 2. 补充业务字段（前端未传但实体需要的字段）
        student.setEditTime(LocalDateTime.now()); // 更新时间（根据实际字段名调整）
        // 若有其他需补充的字段（如修改人、状态等），可在此处添加
        // student.setEditor("system");

        // 3. 执行业务操作：更新学生信息到数据库
        int updateCount = studentMapper.updateById(student);

        // 4. 校验更新结果，封装返回数据
        if (updateCount > 0) {
            // 实体转换为DTO（返回给前端最新的学生信息）
            SaveStuDTO resultDTO = msStuMapper.toSaveStuDTO(student);
            // 返回成功响应（包含DTO数据）
            return JsonVO.success(resultDTO);
        } else {
            // 返回失败响应
            return JsonVO.fail("学生信息修改失败，请重试");
        }
    }

    @Override
    public JsonVO<ChangeStuStageDTO> updateStudentStage(@Valid ChangeStuStageDTO changeStuStageDTO) {
        // 1. 先查学员是否存在
        Student student = studentMapper.selectById(changeStuStageDTO.getId());
        if (student == null) {
            return JsonVO.fail("学员不存在");
        }
        // 当前状态
        Integer currentStage = student.getStage();
        // 目标状态
        Integer targetStage = changeStuStageDTO.getStage();

        // 2. 设置新状态
        student.setStage(targetStage);
        student.setEditTime(LocalDateTime.now());

        // 3. 更新数据库
        boolean success = updateById(student);
        if (success) {
            ChangeStuStageDTO resultDTO = msStuMapper.StudentToStuStageDTO(student);
            return JsonVO.success(resultDTO);
        } else {
            return JsonVO.fail("状态转换失败");
        }
    }

    @Override
    public PageDTO<StudentListVO> listStudents(StudentListQuery query) {

        Page<StudentListVO> page = new Page<>(query.getPageIndex(), query.getPageSize());

        Page<StudentListVO> result = studentMapper.getList(page, query);

        return PageDTO.create(result);
    }

    // StudentServiceImpl 实现
    @Override
    public JsonVO<List<DictVO>> listFamilyRel() {
        List<DictVO> list = new ArrayList<>();
        // 按你截图的顺序添加选项
        list.add(new DictVO(0, "无"));
        list.add(new DictVO(1, "爸爸"));
        list.add(new DictVO(2, "妈妈"));
        list.add(new DictVO(3, "爷爷"));
        list.add(new DictVO(4, "奶奶"));
        list.add(new DictVO(5, "姥爷"));
        list.add(new DictVO(6, "姥姥"));
        list.add(new DictVO(7, "叔叔"));
        list.add(new DictVO(8, "姑姑"));
        list.add(new DictVO(9, "其他"));
        return JsonVO.success(list);
    }

    @Override
    public JsonVO<List<DictVO>> listGradeDict() {
        List<DictVO> list = new ArrayList<>();

        // 你可以按自己学校的年级随便增删
        list.add(new DictVO(1, "小班"));
        list.add(new DictVO(2, "中班"));
        list.add(new DictVO(3, "大班"));
        list.add(new DictVO(4, "一年级"));
        list.add(new DictVO(5, "二年级"));
        list.add(new DictVO(6, "三年级"));
        list.add(new DictVO(7, "四年级"));
        list.add(new DictVO(8, "五年级"));
        list.add(new DictVO(9, "六年级"));
        list.add(new DictVO(10, "初一"));
        list.add(new DictVO(11, "初二"));
        list.add(new DictVO(12, "初三"));

        return JsonVO.success(list);
    }

    @Override
    public JsonVO<List<DictVO>> listJoinWayDict() {
        List<DictVO> list = new ArrayList<>();

        // 常见来源（你可以自己增删）
        list.add(new DictVO(1, "地推"));
        list.add(new DictVO(2, "自然到访"));
        list.add(new DictVO(3, "线上推广"));
        list.add(new DictVO(4, "老学员介绍"));
        list.add(new DictVO(5, "活动报名"));
        list.add(new DictVO(6, "抖音/快手"));
        list.add(new DictVO(7, "微信朋友圈"));
        list.add(new DictVO(8, "其他"));

        return JsonVO.success(list);
    }

    @Override
    public List<ProspectiveStuVO> queryStudents(List<Long> ids) {
        List<ProspectiveStuVO> list = studentMapper.selectStudents(ids);
        return list;
    }
}
