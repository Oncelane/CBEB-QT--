-- 供应商表创建
create table supplier (
    supplierID INT not null auto_increment PRIMARY KEY,
    supplierContactMan CHAR(8),
    supplierPhone CHAR(11),
    supplierCompany CHAR(40),
    supplierArea CHAR(8),
    supplierCompanyAddress CHAR(40)
) charset = utf8mb4;

-- 插入供应商
insert into
    supplier (
        supplierContactMan,
        supplierPhone,
        supplierCompany,
        supplierArea,
        supplierCompanyAddress
    )
values ('', '', '', '', '');
-- 删除供应商
delete from supplier where supplierID = '4';
-- 更新供应商
update supplier
set
    supplierContactMan = '',
    supplierPhone = '',
    supplierCompany = '',
    supplierArea = '',
    supplierCompanyAddress = ''
where
    supplierID = '';
-- 创建视图
create view supplierView (ID, 代理人, 电话, 公司名称, 产地, 公司地址) as
select
    supplierID,
    supplierContactMan,
    supplierPhone,
    supplierCompany,
    supplierArea,
    supplierCompanyAddress
from supplier;

-- 仓库表创建
create table stash (
    stashID INT not null auto_increment PRIMARY KEY,
    stashName CHAR(40),
    stashAddress CHAR(40),
    stashCapacity INT
) charset = utf8mb4;
-- 查询入库单出库单使用的仓库列表
select stashID, stashName from stash;
-- 创建入库单附加货物单
create table inStashOrderLinkGood (
    inStashOrderID INT,
    goodID INT,
    amount INT,
    value FLoat,
    FOREIGN KEY (inStashOrderID) references instashorder (instashorderID),
    FOREIGN KEY (goodID) references goods (goodID)
) charset = utf8mb4;

-- 添加入库单附加货物单
insert into
    inStashorderlinkgood (
        instashorderID,
        goodid,
        amount,
        value
    )
values ('', '', '', '');
-- 创建出库单附加货物单
create table outStashOrderLinkGood (
    outStashOrderID INT,
    goodID INT,
    amount INT,
    value FLoat,
    FOREIGN KEY (outStashOrderID) references outstashorder (outstashorderID),
    FOREIGN KEY (goodID) references goods (goodID)
) charset = utf8mb4;

-- 入库单创建
create table inStashOrder (
    inStashOrderID INT not null auto_increment PRIMARY KEY,
    stashID INT,
    userID INT,
    FOREIGN KEY (stashID) references stash (stashID),
    FOREIGN KEY (userID) references login_user (userID),
    createTime datetime
) charset = utf8mb4;
-- 出库单创建
create table outStashOrder (
    outStashOrderID INT not null auto_increment PRIMARY KEY,
    stashID INT references stash (stashID),
    userID INT references login_user (userID),
    FOREIGN KEY (stashID) references stash (stashID),
    FOREIGN KEY (userID) references login_user (userID),
    createTime datetime
) charset = utf8mb4;

-- 增加触发器，连带删除入库单的货品附加单
create trigger deleteinStashOrderLinkGood
BEFORE delete on instashorder
FOR EACH ROW
BEGIN
    delete from instashorderlinkgood where instashorderlinkgood.instashorderID=old.instashorderID;
end;

create trigger deleteoutStashOrderLinkGood
BEFORE delete on outstashorder
FOR EACH ROW
BEGIN
    delete from outstashorderlinkgood where outstashorderlinkgood.outstashorderID=old.outstashorderID;
end;

-- 创建视图
create view inStashOrderView as
select
    instashorder.instashorderID,
    stashName,
    stashAddress,
    SUM(value),
    SUM(amount),
    userName,
    createTime
from
    stash,
    instashorder,
    instashorderlinkgood,
    login_user
where
    stash.stashID = instashorder.stashID
    and instashorder.instashorderID = instashorderlinkgood.instashorderID
    and instashorder.userID = login_user.userID
group by
    instashorder.instashorderID;
-- 创建视图
create view outStashOrderView as
select
    outstashorder.outstashorderID,
    stashName,
    stashAddress,
    SUM(value),
    SUM(amount),
    userName,
    createTime
from
    stash,
    outstashorder,
    outstashorderlinkgood,
    login_user
where
    stash.stashID = outstashorder.stashID
    and outstashorder.outstashorderID = outstashorderlinkgood.outstashorderID
    and outstashorder.userID = login_user.userID
group by
    outstashorder.outstashorderID;

-- 查询最新创建的入库单
select instashorderID
from instashorder
order by createTime DESC
limit 1;

-- 添加入库单
insert into
    instashorder (stashID, userID, createTime)
values (
        '1',
        '4',
        STR_TO_DATE (
            '2023-12-03 17:04:08',
            '%Y-%m-%d %H:%i:%s'
        )
    );
-- 删除入库单
delete from inStashOrder where instashorderID = '%1';

-- 采购单表创建
create table inorder (
    inorderID INT not null auto_increment primary key,
    stashID INT references stash (stashID),
    userID INT references login_user (userID),
    createTime datetime
) charset = utf8mb4;
-- 销售单表创建
create table outOrder (
    outOrderID INT not null auto_increment primary key,
    stashID INT references stash (stashID),
    userID INT references login_user (userID),
    createTime datetime
) charset = utf8mb4;
-- 采购单货物表创建
create table inOrderLinkGood (
    inorderID INT references inorder (inorderID),
    goodID INT references goods (goodID),
    amount INT,
    value float
) charset = utf8mb4;
-- 销售单货物表创建
create table outOrderLinkGood (
    outOrderID INT references outorder (outorderID),
    goodID INT references goods (goodID),
    amount INT,
    value float
) charset = utf8mb4;

-- 采购单信息视图
create view inOrderView (
    采购单号,
    入库仓库,
    仓库地址,
    采购金额,
    入库数量,
    创建人,
    创建时间
) as
select
    inorder.inorderID,
    stashName,
    stashAddress,
    SUM(value),
    SUM(amount),
    userName,
    createTime
from
    stash,
    inorder,
    inorderlinkgood,
    login_user
where
    stash.stashID = inorder.stashID
    and inorder.inorderID = inorderlinkgood.inorderID
    and inorder.userID = login_user.userID
group by
    inorder.inorderID;
-- 销售单信息视图
create view outOrderView (
    销售单号,
    出库仓库,
    仓库地址,
    采购金额,
    出库数量,
    创建人,
    创建时间
) as
select
    outorder.outorderID,
    stashName,
    stashAddress,
    SUM(value),
    SUM(amount),
    userName,
    createTime
from
    stash,
    outorder,
    outorderlinkgood,
    login_user
where
    stash.stashID = outorder.stashID
    and outorder.outorderID = outorderlinkgood.outorderID
    and outorder.userID = login_user.userID
group by
    outorder.outorderID;

-- 添加采购单、销售单
insert into
    inorder (stashID, userID, createTime)
values (
        '1',
        '4',
        STR_TO_DATE (
            '2023-12-03 17:04:08',
            '%Y-%m-%d %H:%i:%s'
        )
    );

insert into
    outorder (stashID, userID, createTime)
values (
        '1',
        '4',
        STR_TO_DATE (
            '2023-12-03 17:04:08',
            '%Y-%m-%d %H:%i:%s'
        )
    );
-- 添加采购附属货物单、销售附属货物单
insert into
    inorderlinkgood (
        inorderID,
        goodid,
        amount,
        value
    )
values ('%1', '%2', '%3', '%4');

insert into
    outorderlinkgood (
        outorderID,
        goodid,
        amount,
        value
    )
values ('%1', '%2', '%3', '%4');
-- 查询最新采购单ID
select outorderID from outorder order by createTime DESC limit 1;
-- 查询最新销售单ID
select outorderID from outorder order by createTime DESC limit 1;
-- 删除采购单、销售单
delete from instashorder where instashorderID = '%1';

delete from outstashorder where outstashorderID = '%1';

-- 系统用户表
create table login_user (
    userID INT not null auto_increment PRIMARY KEY,
    userName CHAR(11),
    userPassword CHAR(15),
    userIdentity CHAR(20)
) charset = utf8mb4;

-- 用户表信息获取
select
    userPassword,
    userID,
    userIdentity
from login_user
where
    userName = '';

select userName, userIdentity from login_user where userID = '';

-- 商品表创建
create table goods (
    goodID INT not null auto_increment PRIMARY KEY,
    goodName CHAR(40) NOT NULL,
    goodPrice float,
    goodUnit CHAR(10) NOT NULL,
    goodType CHAR(100),
    goodDetail CHAR(200),
    goodSupplierID int not null,
    FOREIGN KEY (goodSupplierID) references supplier (supplierID)
) charset = utf8mb4;

-- 创建入库单使用的查询可选商品列表
CREATE VIEW InStashAvailableGood (
    货品编码,
    货品名称,
    单位,
    库存量,
    类型,
    参考价格,
    平均购入价格,
    供应商公司
) AS
SELECT
    g.goodID AS gid,
    g.goodName AS gname,
    g.goodUnit AS gunit,
    (
        COALESCE(SUM(iog.amount), 0) - COALESCE(SUM(oog.amount), 0)
    ) AS inventory,
    g.goodType AS gtype,
    g.goodprice AS price,
    AVG(iog.value) AS '平均购入价格',
    sup.supplierCompany AS comp
FROM
    goods g
    LEFT JOIN instashorderlinkgood iog ON g.goodID = iog.goodID
    LEFT JOIN outstashorderlinkgood oog ON g.goodID = oog.goodID
    LEFT JOIN instashorder iol ON iog.instashorderID = iol.instashorderID
    LEFT JOIN outstashorder ool ON oog.outstashorderID = ool.outstashorderID
    LEFT JOIN supplier sup ON g.goodSupplierID = sup.supplierID
GROUP BY
    g.goodID,
    g.goodName,
    g.goodUnit,
    g.goodType;

-- 仓库信息视图创建
CREATE VIEW stashandgood AS
SELECT s.stashName AS '仓库', g.goodName AS '货品名称', COALESCE(
        SUM(inlink.amount) - COALESCE(SUM(outlink.amount), 0), 0
    ) AS '库存量', ROUND(
        COALESCE(AVG(inlink.value), 0), 2
    ) AS '平均入库价格', ROUND(
        COALESCE(AVG(outlink.value), 0), 2
    ) AS '平均出库价格'
FROM
    stash s
    JOIN instashorder i ON s.stashID = i.stashID
    LEFT JOIN instashorderlinkgood inlink ON i.instashorderID = inlink.instashorderID
    LEFT JOIN outstashorder o ON s.stashID = o.stashID
    LEFT JOIN outstashorderlinkgood outlink ON o.outstashorderID = outlink.outstashorderID
    AND inlink.goodID = outlink.goodID
    JOIN goods g ON inlink.goodID = g.goodID
    OR outlink.goodID = g.goodID
GROUP BY
    s.stashID,
    g.goodID;

-- 货物总视图创建
CREATE VIEW ProductInventoryView AS
SELECT
    g.goodID AS '货品编码',
    g.goodName AS '货品名称',
    g.goodUnit AS '单位',
    g.goodType AS '类型',
    IFNULL (
        SUM(inlink.amount) - SUM(outlink.amount),
        0
    ) AS '库存量',
    g.goodDetail AS '简介',
    g.goodprice AS '参考价格',
    AVG(inlink.value) AS '平均购入价格',
    AVG(outlink.value) AS '平均出售价格',
    s.supplierCompany AS '供应商公司'
FROM
    goods g
    LEFT JOIN instashorderlinkgood inlink ON g.goodID = inlink.goodID
    LEFT JOIN outstashorderlinkgood outlink ON g.goodID = outlink.goodID
    LEFT JOIN instashorder io ON inlink.instashorderID = io.instashorderID
    LEFT JOIN outstashorder oo ON outlink.outstashorderID = oo.outstashorderID
    LEFT JOIN supplier s ON g.goodSupplierID = s.supplierID
GROUP BY
    g.goodID;

-- 出库可用货品查询
CREATE VIEW OutStashAvailableGood AS
SELECT
    g.goodID AS '货品编码',
    g.goodName AS '货品名称',
    g.goodUnit AS '单位',
    COALESCE(SUM(ilg.amount), 0) - COALESCE(SUM(olg.amount), 0) AS '库存量',
    g.goodType AS '类型',
    g.goodprice AS '参考价格',
    COALESCE(AVG(ilg.value), 0) AS '平均购入价格',
    s.stashName AS '所属仓库'
FROM
    stash s
    JOIN instashorder io ON s.stashID = io.stashID
    LEFT JOIN instashorderlinkgood ilg ON io.instashorderID = ilg.instashorderID
    LEFT JOIN outstashorder oo ON s.stashID = oo.stashID
    LEFT JOIN outstashorderlinkgood olg ON oo.outstashorderID = olg.outstashorderID
    JOIN goods g ON g.goodID = COALESCE(ilg.goodID, olg.goodID)
GROUP BY
    s.stashID,
    g.goodID,
    g.goodName,
    g.goodUnit,
    g.goodType,
    g.goodprice;

-- 修改货品
update goods
set
    goodName = '',
    goodDetail = '',
    goodType = '',
    goodUnit = '',
    goodprice = '',
    goodSupplierID = ''
where
    goodID = '';
-- 可选供应商列表
select supplierID, supplierCompany from supplier;
-- 查询可用仓库列表
select DISTINCT
    stashID,
    所属仓库
from stash, OutStashAvailableGood
where
    stash.stashName = OutStashAvailableGood.所属仓库;

-- 创建客户表
create table custom (
    customID INT not null auto_increment PRIMARY KEY,
    customName CHAR(8),
    customPhone CHAR(11),
    customArea CHAR(8),
    customAddress CHAR(40),
    aboard Boolean
) charset = utf8mb4;

-- 创建客户视图
create view customView (ID, 名字, 手机号, 区域, 地址, 国外) as
select
    customID,
    customName,
    customPhone,
    customArea,
    customAddress,
    aboard
from custom;
-- 更新客户列表
update customView set 名字 = '', 手机号 = '', 区域 = '', 地址 = '', 国外 = '' where ID = '';
-- 查询客户列表
select customID, customName from custom;

-- 用于初始化数据库中的数据
INSERT INTO
    supplier (
        supplierContactMan,
        supplierPhone,
        supplierCompany,
        supplierArea,
        supplierCompanyAddress
    )
VALUES (
        '李强',
        '13112345601',
        '山东机械制造有限公司',
        '山东',
        '山东省济南市历城区XX街道XX大道123号'
    ),
    (
        '王丽',
        '13212345602',
        '湖北电子科技股份有限公司',
        '湖北',
        '湖北省武汉市XX区XX路456号'
    ),
    (
        '刘伟',
        '13312345603',
        '上海化工集团有限公司',
        '上海',
        '上海市浦东新区XX路789号'
    ),
    (
        '赵芳',
        '13412345604',
        '广东新能源科技有限公司',
        '广东',
        '广东省广州市XX区XX街道101号'
    ),
    (
        '陈刚',
        '13512345605',
        '北京航天科技有限公司',
        '北京',
        '北京市海淀区XX路202号'
    ),
    (
        '张艳',
        '13612345606',
        '浙江新材料有限公司',
        '浙江',
        '浙江省杭州市XX区XX路303号'
    ),
    (
        '杨明',
        '13712345607',
        '江苏生物科技有限公司',
        '江苏',
        '江苏省南京市XX区XX路404号'
    ),
    (
        '徐雷',
        '13812345608',
        '福建智能科技有限公司',
        '福建',
        '福建省福州市XX区XX路505号'
    ),
    (
        '宋霞',
        '13912345609',
        '河南机电有限公司',
        '河南',
        '河南省郑州市XX区XX路606号'
    ),
    (
        '朱健',
        '13102345610',
        '重庆通信设备有限公司',
        '重庆',
        '重庆市渝中区XX街道707号'
    ),
    (
        '刘洋',
        '13112345611',
        '山西能源集团有限公司',
        '山西',
        '山西省太原市XX区XX路808号'
    ),
    (
        '许强',
        '13112345612',
        '吉林汽车制造有限公司',
        '吉林',
        '吉林省长春市XX区XX路909号'
    ),
    (
        '何燕',
        '13112345613',
        '云南能源开发有限公司',
        '云南',
        '云南省昆明市XX区XX路010号'
    ),
    (
        '吕娜',
        '13112345614',
        '贵州矿产资源有限公司',
        '贵州',
        '贵州省贵阳市XX区XX路111号'
    ),
    (
        '张刚',
        '13112345615',
        '内蒙古农业科技有限公司',
        '内蒙古',
        '内蒙古呼和浩特市XX区XX路222号'
    ),
    (
        '王霞',
        '13112345616',
        '新疆光电科技有限公司',
        '新疆',
        '新疆乌鲁木齐市XX区XX路333号'
    ),
    (
        '刘健',
        '13112345617',
        '青海新能源有限公司',
        '青海',
        '青海省西宁市XX区XX路444号'
    ),
    (
        '赵丽',
        '13112345618',
        '宁夏化工集团有限公司',
        '宁夏',
        '宁夏银川市XX区XX路555号'
    ),
    (
        '孙明',
        '13112345619',
        '西藏矿产资源有限公司',
        '西藏',
        '西藏拉萨市XX区XX路666号'
    ),
    (
        '李伟',
        '13112345620',
        '台湾电子科技有限公司',
        '台湾',
        '台湾省台北市XX区XX路777号'
    ),
    (
        '刘芳',
        '13112345621',
        '香港新能源科技有限公司',
        '香港',
        '香港特别行政区XX区XX路888号'
    ),
    (
        '陈明',
        '13112345622',
        '澳门机电有限公司',
        '澳门',
        '澳门特别行政区XX区XX路999号'
    ),
    (
        '张红',
        '13112345623',
        '四川通信设备有限公司',
        '四川',
        '四川省成都市XX区XX路123号'
    ),
    (
        '王强',
        '13112345624',
        '甘肃能源集团有限公司',
        '甘肃',
        '甘肃省兰州市XX区XX路234号'
    ),
    (
        '李萍',
        '13112345625',
        '海南汽车制造有限公司',
        '海南',
        '海南省海口市XX区XX路345号'
    ),
    (
        '刘洁',
        '13112345626',
        '香港新材料有限公司',
        '香港',
        '香港特别行政区XX区XX路456号'
    ),
    (
        '徐勇',
        '13112345627',
        '澳门智能科技有限公司',
        '澳门',
        '澳门特别行政区XX区XX路567号'
    ),
    (
        '宋军',
        '13112345628',
        '云南新能源科技有限公司',
        '云南',
        '云南省昆明市XX区XX路678号'
    ),
    (
        '陈丽',
        '13112345629',
        '贵州通信设备有限公司',
        '贵州',
        '贵州省贵阳市XX区XX路789号'
    ),
    (
        '许明',
        '13112345630',
        '湖南矿产资源有限公司',
        '湖南',
        '湖南省长沙市XX区XX路890号'
    );

INSERT INTO
    stash (
        stashName,
        stashAddress,
        stashCapacity
    )
VALUES (
        '北京物流中心',
        '北京市朝阳区酒仙桥路10号',
        '15000'
    ),
    (
        '上海货运仓库',
        '上海市宝山区共和新路188号',
        '12000'
    ),
    (
        '广州仓储中心',
        '广东省广州市天河区珠江新城XX大道123号',
        '18000'
    ),
    (
        '深圳物流仓库',
        '广东省深圳市福田区新洲路456号',
        '20000'
    ),
    (
        '天津货物仓储',
        '天津市南开区卫津路789号',
        '13000'
    ),
    (
        '重庆配送中心',
        '重庆市渝中区解放碑步行街101号',
        '16000'
    ),
    (
        '南京仓储站',
        '江苏省南京市玄武区中山路202号',
        '15000'
    ),
    (
        '武汉物流仓库',
        '湖北省武汉市江汉区江汉路303号',
        '12000'
    ),
    (
        '成都货物中转站',
        '四川省成都市武侯区天府大道404号',
        '18000'
    ),
    (
        '西安货运中心',
        '陕西省西安市雁塔区雁塔路505号',
        '20000'
    ),
    (
        '郑州仓库物流',
        '河南省郑州市金水区农业路606号',
        '13000'
    ),
    (
        '济南货运站',
        '山东省济南市历下区泉城路707号',
        '16000'
    ),
    (
        '长沙物流配送中心',
        '湖南省长沙市天心区芙蓉南路808号',
        '15000'
    ),
    (
        '哈尔滨仓储中心',
        '黑龙江省哈尔滨市道里区中央大街909号',
        '12000'
    ),
    (
        '沈阳物流仓库',
        '辽宁省沈阳市和平区中华路010号',
        '18000'
    ),
    (
        '西宁货物储存站',
        '青海省西宁市城中区青海路111号',
        '20000'
    ),
    (
        '兰州物流中心',
        '甘肃省兰州市城关区临夏路222号',
        '13000'
    ),
    (
        '呼和浩特仓储站',
        '内蒙古自治区呼和浩特市赛罕区大学西路234号',
        '16000'
    ),
    (
        '南昌仓库物流',
        '江西省南昌市东湖区北京东路345号',
        '15000'
    ),
    (
        '合肥物流中心',
        '安徽省合肥市庐阳区望江路456号',
        '12000'
    ),
    (
        '太原货运站',
        '山西省太原市小店区滨河路567号',
        '18000'
    ),
    (
        '西藏仓储中转站',
        '西藏自治区拉萨市城关区北京中路678号',
        '20000'
    ),
    (
        '海口物流配送中心',
        '海南省海口市龙华区新海大道789号',
        '13000'
    ),
    (
        '贵阳货物储存站',
        '贵州省贵阳市云岩区北京西路890号',
        '16000'
    ),
    (
        '长春物流仓库',
        '吉林省长春市南关区解放路901号',
        '15000'
    ),
    (
        '银川仓库物流',
        '宁夏回族自治区银川市兴庆区宁夏大道012号',
        '12000'
    ),
    (
        '乌鲁木齐货运中心',
        '新疆维吾尔自治区乌鲁木齐市水磨沟区友谊路123号',
        '18000'
    ),
    (
        '香港物流仓库',
        '香港特别行政区中西区干诺道中234号',
        '20000'
    ),
    (
        '澳门仓储中心',
        '澳门特别行政区花地玛堂区友谊大马路345号',
        '13000'
    ),
    (
        '台北物流配送中心',
        '台湾省台北市中正区中山南路678号',
        '16000'
    );

INSERT INTO
    stash (
        stashName,
        stashAddress,
        stashCapacity
    )
VALUES (
        'London Logistics Hub',
        '123 Main Street, London, UK',
        20000
    ),
    (
        'Paris Distribution Center',
        '456 Rue de la Logistique, Paris, France',
        18000
    ),
    (
        'Berlin Supply Chain Hub',
        '789 Logistikstraße, Berlin, Germany',
        22000
    ),
    (
        'Tokyo Cargo Depot',
        '101 Sakura Avenue, Tokyo, Japan',
        16000
    ),
    (
        'Sydney Storage Solutions',
        '321 Logistics Street, Sydney, Australia',
        19000
    ),
    (
        'New York Warehouse Center',
        '555 Logistics Lane, New York, USA',
        21000
    ),
    (
        'Toronto Freight Hub',
        '789 Shipping Road, Toronto, Canada',
        17000
    ),
    (
        'São Paulo Distribution Facility',
        '987 Rua da Logística, São Paulo, Brazil',
        20000
    ),
    (
        'Cape Town Cargo Depot',
        '456 Logistics Avenue, Cape Town, South Africa',
        18000
    ),
    (
        'Dubai Logistics Center',
        '789 Supply Chain Street, Dubai, UAE',
        22000
    );

insert into
    goods (
        goodName,
        goodprice,
        goodUnit,
        goodType,
        goodDetail,
        goodSupplierID
    )
values (
        '草莓口味酸奶',
        '15',
        '瓶',
        '3 食品',
        '200ml/瓶，含有丰富的维生素和蛋白质，适合各个年龄段的人群。',
        7
    ),
    (
        '液晶显示器',
        '450',
        '台',
        '12 电子设备',
        '23英寸，分辨率1920x1080，适用于办公和娱乐用途。',
        15
    ),
    (
        '全自动咖啡机',
        '680',
        '台',
        '8 家用电器',
        '一键式操作，内置磨豆机，适用于各种咖啡豆，方便快捷。',
        22
    ),
    (
        '运动鞋',
        '120',
        '双',
        '5 服装、鞋帽和饰品',
        '男款，透气舒适，适合运动和日常穿着。',
        9
    ),
    (
        '移动充电宝',
        '30',
        '个',
        '15 信息技术设备',
        '10000mAh，轻便携带，支持快速充电，适用于手机和平板。',
        28
    ),
    (
        '不锈钢保温杯',
        '25',
        '个',
        '11 家用器皿及日用品',
        '500ml，保温效果良好，适用于办公和户外活动。',
        5
    ),
    (
        'LED吸顶灯',
        '80',
        '盏',
        '13 灯具',
        '18W，色温可调，适用于客厅、卧室等空间。',
        17
    ),
    (
        '手持振动按摩器',
        '35',
        '个',
        '9 医药',
        '舒缓肌肉疲劳，多档振动调节，方便携带。',
        14
    ),
    (
        '家用搅拌器',
        '40',
        '台',
        '7 机械设备',
        '450W，多功能搅拌，适用于烘焙和烹饪。',
        11
    ),
    (
        '折叠式办公桌',
        '120',
        '张',
        '14 家具',
        '可调节高度，方便携带，适用于办公和学习。',
        26
    ),
    (
        '电动牙刷',
        '50',
        '个',
        '4 医疗器械',
        '声波震动，智能定时，提供有效的口腔清洁。',
        8
    ),
    (
        '多功能健身器材',
        '350',
        '套',
        '16 体育和文娱用品',
        '包括哑铃、引体向上器等，适用于家庭健身。',
        18
    ),
    (
        '天然橄榄油',
        '22',
        '瓶',
        '2 农业、林业、渔业',
        '500ml，初榨橄榄油，适用于烹饪和沙拉。',
        10
    ),
    (
        'USB-C数据线',
        '8',
        '根',
        '15 信息技术设备',
        '1米，快充适配，适用于各种USB-C接口设备。',
        25
    ),
    (
        '婴儿纸尿裤',
        '30',
        '包',
        '1 制造业',
        '超薄透气，干爽舒适，适用于新生儿和婴儿。',
        3
    ),
    (
        '抗菌洗手液',
        '12',
        '瓶',
        '10 化学制品',
        '250ml，含有抗菌成分，有效清洁双手。',
        21
    ),
    (
        '折叠自行车',
        '180',
        '辆',
        '17 车辆、航空器、船舶及有关运输设备',
        '铝合金车架，轻便易折叠，适用于城市出行。',
        13
    ),
    (
        '蓝牙耳机',
        '60',
        '副',
        '15 信息技术设备',
        '无线蓝牙连接，高音质音响，适用于运动和娱乐。',
        6
    ),
    (
        '电热毯',
        '45',
        '张',
        '11 家用器皿及日用品',
        '双人床尺寸，可调温度，适用于寒冷季节。',
        29
    ),
    (
        '户外登山背包',
        '70',
        '个',
        '16 体育和文娱用品',
        '容量40L，防水设计，适用于徒步旅行和登山。',
        20
    ),
    (
        '无线路由器',
        '55',
        '台',
        '15 信息技术设备',
        '双频信号，高速传输，适用于家庭和办公网络。',
        12
    ),
    (
        '精油香薰灯',
        '28',
        '盏',
        '13 灯具',
        '木制底座，配合精油，提供宁静的氛围。',
        24
    ),
    (
        '智能手表',
        '150',
        '只',
        '15 信息技术设备',
        '多功能智能手表，支持健康监测和通讯。',
        16
    ),
    (
        '汽车蓄电池',
        '90',
        '个',
        '17 车辆、航空器、船舶及有关运输设备',
        '12V，容量60Ah，适用于各种汽车。',
        4
    ),
    (
        '儿童玩具积木',
        '20',
        '盒',
        '15 信息技术设备',
        '彩色积木，培养孩子创造力和想象力。',
        23
    ),
    (
        '防水运动手表',
        '85',
        '只',
        '15 信息技术设备',
        '多功能运动手表，适用于户外运动。',
        27
    ),
    (
        '风扇式空气净化器',
        '110',
        '台',
        '9 医药',
        '带有风扇功能，有效净化室内空气。',
        19
    ),
    (
        '手动剃须刀',
        '18',
        '把',
        '7 机械设备',
        '双层刀片，舒适剃须，适用于脸部和身体。',
        2
    ),
    (
        '瑜伽垫',
        '25',
        '张',
        '16 体育和文娱用品',
        '防滑设计，环保材料，适用于瑜伽和锻炼。',
        1
    ),
    (
        '电动扫地机器人',
        '150',
        '台',
        '7 机械设备',
        '智能导航，自动清扫，适用于家庭和办公场所。',
        30
    ),
    (
        '超高清数字摄像机',
        '600',
        '台',
        '12 电子设备',
        '4K分辨率，支持远程监控，适用于摄影和录像。',
        14
    ),
    (
        '太阳能充电板',
        '80',
        '块',
        '15 信息技术设备',
        '10W，可折叠设计，适用于户外充电。',
        8
    ),
    (
        '卫生纸',
        '10',
        '卷',
        '1 制造业',
        '三层，柔软舒适，适用于家庭和商业场所。',
        5
    ),
    (
        '电动割草机',
        '280',
        '台',
        '2 农业、林业、渔业',
        '电动推车式，适用于草坪和花园修剪。',
        17
    ),
    (
        '彩色水彩笔',
        '15',
        '盒',
        '15 信息技术设备',
        '24色，可水溶，适用于绘画和手工。',
        11
    ),
    (
        '高压蒸汽挂烫机',
        '55',
        '台',
        '11 家用器皿及日用品',
        '快速蒸汽，去除衣物皱褶，适用于家庭使用。',
        22
    ),
    (
        '户外防水帐篷',
        '120',
        '顶',
        '16 体育和文娱用品',
        '双层帐篷，防雨防风，适用于露营和徒步旅行。',
        9
    ),
    (
        '数码单反相机',
        '800',
        '台',
        '12 电子设备',
        '2400万像素，支持高清录像，适用于专业摄影。',
        18
    ),
    (
        '儿童电动玩具车',
        '90',
        '辆',
        '17 车辆、航空器、船舶及有关运输设备',
        '可充电，适用于室内和户外玩耍。',
        10
    ),
    (
        '风格各异的茶杯套装',
        '40',
        '套',
        '11 家用器皿及日用品',
        '陶瓷制造，多款设计，适用于日常用餐。',
        26
    ),
    (
        '4K高清智能电视',
        '600',
        '台',
        '12 电子设备',
        '55英寸，智能连接，适用于家庭娱乐。',
        28
    ),
    (
        '抗敏洗发水',
        '12',
        '瓶',
        '10 化学制品',
        '温和配方，适用于敏感头皮，保持头发健康。',
        14
    ),
    (
        '轻便登山杖',
        '30',
        '对',
        '16 体育和文娱用品',
        '可调节长度，碳素材质，适用于徒步和登山。',
        21
    ),
    (
        '婴儿安全座椅',
        '65',
        '个',
        '17 车辆、航空器、船舶及有关运输设备',
        '适用于汽车，保护婴儿乘坐安全。',
        7
    ),
    (
        '迷你冰箱',
        '90',
        '台',
        '11 家用器皿及日用品',
        '20升，便携式，适用于车辆和办公室。',
        13
    ),
    (
        '中草药洗面奶',
        '18',
        '瓶',
        '6 化学工业',
        '天然成分，温和清洁，适用于各种肌肤类型。',
        27
    ),
    (
        '电动按摩椅',
        '550',
        '张',
        '7 机械设备',
        '多功能按摩，舒缓肌肉疲劳，适用于家庭使用。',
        16
    ),
    (
        '户外防晒帽',
        '15',
        '顶',
        '5 服装、鞋帽和饰品',
        '防紫外线，透气舒适，适用于户外活动。',
        12
    ),
    (
        '复古手工皮革钱包',
        '35',
        '个',
        '5 服装、鞋帽和饰品',
        '手工制作，多卡位设计，时尚实用。',
        24
    ),
    (
        '空气清新剂',
        '8',
        '瓶',
        '11 家用器皿及日用品',
        '室内除味，淡雅香气，适用于家庭和办公场所。',
        23
    ),
    (
        '智能温控电热水壶',
        '45',
        '个',
        '11 家用器皿及日用品',
        '1.5升容量，可调温度，适用于沏茶和煮水。',
        29
    ),
    (
        '可折叠电动滑板车',
        '280',
        '辆',
        '17 车辆、航空器、船舶及有关运输设备',
        '30km/h最高速度，便携式，适用于城市出行。',
        20
    );

insert into
    customView (名字, 手机号, 区域, 地址, 国外)
values (
        'Alice',
        '15344345563',
        '美国',
        '123 Main Street, Apt 4B, Anytown',
        1
    ),
    (
        'Bob',
        '17775554444',
        '英国',
        '456 Park Lane, London',
        1
    ),
    (
        'Claire',
        '61487654321',
        '澳大利亚',
        '789 Beach Road, Sydney',
        1
    ),
    (
        'David',
        '61234567890',
        '加拿大',
        '567 Maple Street, Toronto',
        1
    ),
    (
        'Eva',
        '61239876543',
        '德国',
        '321 Glocken Strasse, Berlin',
        1
    ),
    (
        'Fernando',
        '5987612345',
        '西班牙',
        '234 Calle Principal, Madrid',
        1
    ),
    (
        'Gabriela',
        '5544332211',
        '墨西哥',
        '789 Avenida Principal, Mexico City',
        1
    ),
    (
        'Hugo',
        '47987654321',
        '巴西',
        '456 Rua Principal, Rio de Janeiro',
        1
    ),
    (
        'Isabella',
        '5566778899',
        '意大利',
        '123 Via Principale, Rome',
        1
    ),
    (
        'Julia',
        '987654321',
        '法国',
        '567 Rue Principale, Paris',
        1
    ),
    (
        'Kevin',
        '3366998877',
        '瑞士',
        '234 Hauptstrasse, Zurich',
        1
    ),
    (
        'Liam',
        '6677889900',
        '瑞典',
        '678 Huvudgatan, Stockholm',
        1
    ),
    (
        'Mia',
        '1122334455',
        '挪威',
        '890 Hovedveien, Oslo',
        1
    ),
    (
        'Noah',
        '1122334455',
        '荷兰',
        '345 Hoofdstraat, Amsterdam',
        1
    ),
    (
        'Olivia',
        '9988776655',
        '丹麦',
        '901 Hovedvej, Copenhagen',
        1
    ),
    (
        'Pablo',
        '1122998877',
        '阿根廷',
        '234 Avenida Principal, Buenos Aires',
        1
    ),
    (
        'Quinn',
        '9988776655',
        '新西兰',
        '567 Main Street, Auckland',
        1
    ),
    (
        'Rafael',
        '7788990011',
        '哥伦比亚',
        '789 Calle Principal, Bogota',
        1
    ),
    (
        'Sophie',
        '1144778899',
        '智利',
        '123 Avenida Principal, Santiago',
        1
    ),
    (
        'Thomas',
        '6677558899',
        '葡萄牙',
        '456 Rua Principal, Lisbon',
        1
    ),
    (
        'Uma',
        '8899776655',
        '印度',
        '789 Main Road, Mumbai',
        1
    ),
    (
        'Valeria',
        '7788990011',
        '俄罗斯',
        '567 Glavnyy Prospekt, Moscow',
        1
    ),
    (
        'William',
        '5544667788',
        '日本',
        '890 Main Street, Tokyo',
        1
    ),
    (
        'Xavier',
        '1122334455',
        '韩国',
        '345 Main-ro, Seoul',
        1
    ),
    (
        'Yara',
        '6677889900',
        '中国',
        '901 Main Street, Beijing',
        1
    ),
    (
        'Zoe',
        '9988776655',
        '南非',
        '234 Main Road, Johannesburg',
        1
    ),
    (
        'Adam',
        '1122334455',
        '芬兰',
        '567 Pääkatu, Helsinki',
        1
    ),
    (
        'Bella',
        '9988776655',
        '比利时',
        '890 Hoofdstraat, Brussels',
        1
    ),
    (
        'Carlos',
        '7788990011',
        '土耳其',
        '123 Ana Cadde, Istanbul',
        1
    ),
    (
        'Daisy',
        '1144778899',
        '泰国',
        '456 ถนนหลัก, Bangkok',
        1
    ),
    (
        'Ethan',
        '6677558899',
        '新加坡',
        '789 Main Street, Singapore',
        1
    ),
    (
        'Fiona',
        '8899776655',
        '马来西亚',
        '567 Jalan Utama, Kuala Lumpur',
        1
    ),
    (
        'George',
        '7788990011',
        '菲律宾',
        '890 Main Street, Manila',
        1
    ),
    (
        'Hannah',
        '5544667788',
        '印度尼西亚',
        '234 Jalan Utama, Jakarta',
        1
    ),
    (
        'Ian',
        '1122334455',
        '阿联酋',
        '567 Main Street, Dubai',
        1
    ),
    (
        'Jasmine',
        '9988776655',
        '沙特阿拉伯',
        '890 طريق رئيسي, Riyadh',
        1
    ),
    (
        'Kyle',
        '7788990011',
        '以色列',
        '123 רחוב ראשי, Tel Aviv',
        1
    ),
    (
        'Laura',
        '1144778899',
        '埃及',
        '456 الشارع الرئيسي, Cairo',
        1
    ),
    (
        'Max',
        '6677558899',
        '摩洛哥',
        '789 Rue Principale, Casablanca',
        1
    ),
    (
        'Nora',
        '8899776655',
        '尼日利亚',
        '567 Main Street, Lagos',
        1
    ),
    (
        'Oscar',
        '7788990011',
        '肯尼亚',
        '890 Main Road, Nairobi',
        1
    ),
    (
        'Paula',
        '5544667788',
        '塞内加尔',
        '234 Rue Principale, Dakar',
        1
    ),
    (
        'Quincy',
        '1122334455',
        '刚果民主共和国',
        '567 Avenue Principale, Kinshasa',
        1
    ),
    (
        'Rachel',
        '9988776655',
        '坦桑尼亚',
        '890 Main Street, Dar es Salaam',
        1
    ),
    (
        'Sam',
        '7788990011',
        '摩纳哥',
        '123 Rue Principale, Monaco',
        1
    ),
    (
        'Tina',
        '1144778899',
        '巴哈马',
        '456 Main Street, Nassau',
        1
    ),
    (
        'Uriel',
        '6677558899',
        '牙买加',
        '789 Main Street, Kingston',
        1
    ),
    (
        'Violet',
        '8899776655',
        '巴巴多斯',
        '567 Main Road, Bridgetown',
        1
    ),
    (
        'Winston',
        '7788990011',
        '特立尼达和多巴哥',
        '890 Main Street, Port of Spain',
        1
    ),
    (
        'Xander',
        '5544667788',
        '安提瓜和巴布达',
        '234 Main Street, St. John’s',
        1
    ),
    (
        'Yasmine',
        '1122334455',
        '多米尼加共和国',
        '567 Calle Principal, Santo Domingo',
        1
    );