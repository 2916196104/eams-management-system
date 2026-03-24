package com.zeroone.star.eamsj3data.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zeroone.star.eamsj3data.entity.ContactRecord;
import com.zeroone.star.eamsj3data.entity.Student;
import com.zeroone.star.eamsj3data.mapper.ContactRecordMapper;
import com.zeroone.star.eamsj3data.mapper.StudentMapper;
import com.zeroone.star.eamsj3data.service.IBaseAnalysisService;
import com.zeroone.star.project.dto.j3.data.SalesFunnelDTO;
import com.zeroone.star.project.dto.j3.data.StudentAgeCompositionDTO;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * <p>
 * 学员统计基础分析服务实现类
 * </p>
 * @author yeyue
 * @version 1.0.0
 */
@Service
public class BaseAnalysisServiceImpl implements IBaseAnalysisService {

    /**
     * 在学学员阶段编码
     */
    private static final int STUDYING_STAGE = 2;

    /**
     * 销售漏斗阶段字典，按要求固定返回顺序
     */
    private static final Map<Integer, String> SALES_STAGE_MAP = buildSalesStageMap();

    /**
     * 学员数据访问对象
     */
    @Resource
    private StudentMapper studentMapper;

    /**
     * 跟进记录数据访问对象
     */
    @Resource
    private ContactRecordMapper contactRecordMapper;

    /**
     * 获取销售漏斗统计结果
     * 统计口径：按每个学员最新一条跟进记录的阶段进行统计，
     * 仅返回 10、20、30、40、50、60 六个阶段，不返回 0。
     *
     * @return 销售漏斗统计列表
     */
    @Override
    public List<SalesFunnelDTO> getSalesFunnelStats() {
        LambdaQueryWrapper<ContactRecord> queryWrapper = new LambdaQueryWrapper<ContactRecord>()
                .select(ContactRecord::getStudentId, ContactRecord::getStage, ContactRecord::getAddTime)
                .eq(ContactRecord::getDeleted, 0);

        List<ContactRecord> records = contactRecordMapper.selectList(queryWrapper);
        Map<Long, ContactRecord> latestRecordMap = new LinkedHashMap<>();

        // 以 studentId 为维度，保留 addTime 最新的一条跟进记录
        for (ContactRecord record : records) {
            Long studentId = record.getStudentId();
            if (studentId == null) {
                continue;
            }

            // 获取Map中最新的跟进记录
            ContactRecord latestRecord = latestRecordMap.get(studentId);
            // 最新跟进记录为空或者当前记录的 addTime 更新时间更晚 放入集合
            if (latestRecord == null || compareAddTime(record, latestRecord) > 0) {
                latestRecordMap.put(studentId, record);
            }
        }

        // 先把销售漏斗所有阶段都放进 map 里，并且默认人数全设成 0
        Map<Integer, Integer> stageCountMap = new LinkedHashMap<>();
        for (Integer code : SALES_STAGE_MAP.keySet()) {
            stageCountMap.put(code, 0);
        }

        // 只累计漏斗阶段字典中定义的阶段，未定义阶段自动忽略
        for (ContactRecord record : latestRecordMap.values()) {
            Integer stage = record.getStage();
            if (stage != null && stageCountMap.containsKey(stage)) {
                stageCountMap.put(stage, stageCountMap.get(stage) + 1);
            }
        }

        List<SalesFunnelDTO> result = new ArrayList<>(SALES_STAGE_MAP.size());
        // 按固定阶段顺序组装返回结果，人数为 0 也保留
        for (Map.Entry<Integer, String> entry : SALES_STAGE_MAP.entrySet()) {
            SalesFunnelDTO dto = new SalesFunnelDTO();
            dto.setCode(entry.getKey());
            dto.setName(entry.getValue());
            dto.setCount(stageCountMap.get(entry.getKey()));
            result.add(dto);
        }
        return result;
    }

    /**
     * 获取在学学员年龄构成
     * 统计口径：筛选在学学员，按“当前年份 - 出生年份”统计具体年龄人数，
     * 并按年龄从小到大返回。
     *
     * @return 在学学员年龄构成列表
     */
    @Override
    public List<StudentAgeCompositionDTO> getStudentAgeComposition() {
        LambdaQueryWrapper<Student> queryWrapper = new LambdaQueryWrapper<Student>()
                .select(Student::getBirthday)
                .eq(Student::getDeleted, 0)
                .eq(Student::getStage, STUDYING_STAGE)
                .isNotNull(Student::getBirthday);

        List<Student> students = studentMapper.selectList(queryWrapper);
        // 当前年份
        int currentYear = LocalDate.now().getYear();
        // 准备一个按年龄统计人数、并自动排序的 map
        Map<Integer, Integer> ageCountMap = new TreeMap<>();

        // 统计每个具体年龄对应的人数
        for (Student student : students) {
            LocalDate birthday = student.getBirthday();
            if (birthday == null) {
                continue;
            }

            int age = currentYear - birthday.getYear();
            if (age < 0) {
                continue;
            }
            ageCountMap.put(age, ageCountMap.getOrDefault(age, 0) + 1);
        }

        List<StudentAgeCompositionDTO> result = new ArrayList<>(ageCountMap.size());
        for (Map.Entry<Integer, Integer> entry : ageCountMap.entrySet()) {
            StudentAgeCompositionDTO dto = new StudentAgeCompositionDTO();
            dto.setAge(entry.getKey() + "岁");
            dto.setCount(entry.getValue());
            result.add(dto);
        }
        return result;
    }

    /**
     * 构建销售漏斗阶段字典
     *
     * @return 按固定顺序排列的阶段字典
     */
    private static LinkedHashMap<Integer, String> buildSalesStageMap() {
        LinkedHashMap<Integer, String> stageMap = new LinkedHashMap<>(6);
        stageMap.put(10, "目标客户阶段");
        stageMap.put(20, "潜在客户阶段");
        stageMap.put(30, "意向阶段");
        stageMap.put(40, "认可阶段");
        stageMap.put(50, "签约阶段");
        stageMap.put(60, "售后阶段");
        return stageMap;
    }

    /**
     * 比较两条跟进记录的创建时间先后
     *
     * @param current 当前记录
     * @param latest 已保存的最新记录
     * @return 大于 0 表示当前记录更晚
     */
    private int compareAddTime(ContactRecord current, ContactRecord latest) {
        LocalDateTime currentAddTime = current.getAddTime();
        LocalDateTime latestAddTime = latest.getAddTime();

        // 两个时间都为空：一样，返回 0
        if (currentAddTime == null && latestAddTime == null) {
            return 0;
        }
        // 当前为空：当前更早，返回 -1
        if (currentAddTime == null) {
            return -1;
        }
        // 已保存的为空：当前更新，返回 1
        if (latestAddTime == null) {
            return 1;
        }
        return currentAddTime.compareTo(latestAddTime);
    }
}
