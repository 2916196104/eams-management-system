#include "exchangeService.h"
#include "dao/points-exchange/GoodsDAO.h"
#include "dao/points-exchange/exchangeDAO.h"
#include "id/SnowFlake.h"
#include"service/points-exchange/points-ExchangeService.h"
#include "../../dao/points-exchange/points-ExchangeDAO.h"
#include "../../domain/do/points-exchange/exchangeDo.h"
ExchangeResultDTO::Wrapper ExchangeService::submitExchange(
    const ExchangeSubmitDTO::Wrapper& request,
    const std::int64_t& userid)
{
    ExchangeResultDTO::Wrapper result = ExchangeResultDTO::createShared();

    //创建事务指针
    //  正确：创建实际的对象
    auto m_goodsDao = std::make_shared<GoodsDAO>();
    auto m_exchangeDao = std::make_shared<ExchangeDAO>();

   
    auto session_good = m_goodsDao->getSqlSession();
    auto sesion_exchange= m_exchangeDao->getSqlSession();

    try
    {
        //商品详情开始事务
        session_good->beginTransaction();
        // 业务逻辑开始

        //商品是否存在
        if (!request->goodsId || request->goodsId <= 0)
            throw std::invalid_argument("Goods ID cannot be 0");

        
        if (!request->num || request->num <= 0)
            throw std::invalid_argument("Exchange quantity must be greater than 0");


        // 查询商品（纯查询）
        auto goods = m_goodsDao->selectById(request->goodsId);
        if (!goods)
            throw std::invalid_argument("Product does not exist");

        if (goods->getState() != 1)
            throw std::invalid_argument("Product has been taken off the shelf");

        
        //查询用户积分是否勾
        if(m_exchangeDao->getStudentCurrentCredit(userid)< goods->getCredit() * request->num)
            throw std::invalid_argument("Insufficient points");

        
        m_goodsDao->updateStorage(request->goodsId, request->num);
        m_goodsDao->updateSaleNum(request->goodsId, request->num);

        session_good->commitTransaction();


        // 兑换记录开始事务
        sesion_exchange->beginTransaction();
       
         // 创建兑换记录
        auto exchangeDO = std::make_shared<AcceptGoodsDO>();

        //雪花生成兑换记录id
        SnowFlake idGenerator(1, 1);
        uint64_t id = idGenerator.nextId();
        exchangeDO->setId(id);

        // 核心兑换信息
        exchangeDO->setCreditMallId(request->goodsId);
        exchangeDO->setNum(request->num);
        exchangeDO->setCredit(to_string(goods->getCredit()));   // credit 是 varchar(255)

        // 用户相关（必须设置）
        exchangeDO->setUserId(userid);                    // 当前登录用户ID
        exchangeDO->setStudentId(request->studentId);                 // 大多数情况下 

       //可选备注
        exchangeDO->setVerifyRemark(request->remark);

        // 审核状态
        exchangeDO->setVerifyState(0);

        //插入兑换记录
        m_exchangeDao->insert(exchangeDO);

        // 扣除学生积分，更新学生积分表
        m_exchangeDao->deductStudentCredit(userid, goods->getCredit() * request->num);
        m_exchangeDao->insertCreditChangeRecord(exchangeDO, m_exchangeDao->getStudentCurrentCredit(userid));

        // 全部成功 → 提交
        sesion_exchange ->commitTransaction();


        //构建相应
        //雪花构建订单号
        SnowFlake orderNoGenerator(1, 1);
        auto orderon = idGenerator.nextId();
        result->status = 1;
        result->message = "Exchange successful";
        result->exchangeId = exchangeDO->getId();
        result->totalCredit= goods->getCredit() * request->num;
        result->orderNo = to_string(orderon);
    }
    catch (const std::invalid_argument& e)
    {
        session_good->rollbackTransaction();   // 回滚
        sesion_exchange->rollbackTransaction();
        result->status = 0;
        result->message = e.what();
    }
   
 
    return result;
}

GoodsDetailDTO::Wrapper ExchangeService::getGoodsDetail(const int64_t& id)
{
    // 1. 参数校验
    if (id <= 0)
    {
        throw std::invalid_argument("Goods ID cannot be empty");
    }

    // 2. 从数据库查询礼品信息
    GoodsDAO dao;
    auto goodsDO = dao.selectById(id);
    if (!goodsDO)
    {
        throw std::runtime_error("Product does not exist");
    }

    // 3. 检查礼品是否下架
    if (goodsDO->getDeleted() == 1)
    {
        throw std::runtime_error("Product has been deleted");
    }

    // 4. 增加浏览次数
    dao.incrementViewNum(id);

    // 5. 将 do 对象转为 dto
    GoodsDetailDTO::Wrapper detailDTO = GoodsDetailDTO::createShared();

    // 基础信息
    detailDTO->id = goodsDO->getId();
    detailDTO->deleted = goodsDO->getDeleted();
    detailDTO->schoolId = goodsDO->getSchoolId();
    detailDTO->addTime = goodsDO->getAddTime();
    detailDTO->editTime = goodsDO->getEditTime();
    detailDTO->creator = goodsDO->getCreator();
    detailDTO->editor = goodsDO->getEditor();
    detailDTO->materialId = goodsDO->getMaterialId();
    detailDTO->categoryId = goodsDO->getCategoryId();
    detailDTO->categoryName = goodsDO->getCategoryName();
    detailDTO->name = goodsDO->getName();
    detailDTO->credit = goodsDO->getCredit();
    detailDTO->saleNum = goodsDO->getSaleNum();
    detailDTO->viewNum = goodsDO->getViewNum();
    detailDTO->cover = goodsDO->getCover();
    detailDTO->content = goodsDO->getContent();
    detailDTO->state = goodsDO->getState();
    detailDTO->orgId = goodsDO->getOrgId();
  
   

    
    detailDTO->exchangeStartTime = goodsDO->getAddTime();
    detailDTO->exchangeEndTime = goodsDO->getEditTime();

    return detailDTO;
};