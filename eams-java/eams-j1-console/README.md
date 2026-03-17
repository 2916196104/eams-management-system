# eams-j1-console 模块

## 模块说明

本模块是教务管理系统（EAMS）J1组负责的控制台服务模块，提供控制台相关的核心业务功能。

## 功能列表

| 功能 | 接口路径 | 说明 |
|------|---------|------|
| 统计面板 | GET /console/statistics | 获取教务系统关键统计数据 |
| 本月报名 | POST /console/month-enrollment | 获取指定月份的报名趋势和每日报名数据 |
| 课程报名 | POST /console/course-enrollment | 获取所有课程的报名情况统计 |
| 我的课表 | POST /console/schedule | 获取指定用户的课程安排表 |
| 我的客户 | POST /console/customer | 获取负责的客户信息及跟进状态统计 |

## 技术栈

- Spring Boot
- Spring Cloud Alibaba Nacos
- MyBatis Plus
- Knife4j (API文档)

## 服务端口

- 默认端口：9080

## 启动方式

```bash
# 方式1：通过IDE运行 J1ConsoleApplication
# 方式2：Maven命令
mvn spring-boot:run -pl eams-j1-console
```
