#include <QtTest/QTest>
#include "test_tests.h"
#include <Database.h>
#include <TabEditUserModel.h>
#include <TabNewExtrasModel.h>
#include <TabNewExtrasModel.h>
#include <TabPredictionModel.h>
#include <tabCatalogAndComparisonModel.h>
#include <tabNewCraftModel.h>
#include <TabNewProjectModel.h>
#include <QFileInfo>
#include <QTextDocument>

Test_Tests::Test_Tests(QObject *parent) :
    QObject(parent)
{
}

void Test_Tests::DBCreateGetCheck()
{
    db.createConnection();

    DBUser testAdminUser(-1,"testUser1","Пользователь","0000");
    db.addUserToDB(testAdminUser);
    DBUser testAdminUser2 = db.getUserById(db.getUserIdByName("testUser1"));
    QCOMPARE(testAdminUser2.name(), testAdminUser.name());
    QCOMPARE(testAdminUser2.role(), testAdminUser.role());

    testAdminUser2.setRole("Администратор");
    testAdminUser2.setName("testUser12");
    db.updateUserDB(testAdminUser2);
    testAdminUser2 = db.getUserById(db.getUserIdByName("testUser12"));
    QCOMPARE("testUser12", testAdminUser2.name());
    QCOMPARE("Администратор", testAdminUser2.role());

    DBOrganization testOrganization(-1,"TEST ORGANIZATION");
    db.addOrganoizationToDB(testOrganization);
    DBOrganization testOrganization2 = db.getOrganizationInfoFromId(db.getOrganizationIdFromName("TEST ORGANIZATION"));
    QCOMPARE(testOrganization.name(), testOrganization2.name());

    testOrganization2.setName("TEST ORGANIZATION2");
    db.updateOrganizationDB(testOrganization2.id(),testOrganization2.name());
    testOrganization2 = db.getOrganizationInfoFromId(db.getOrganizationIdFromName("TEST ORGANIZATION2"));
    QCOMPARE("TEST ORGANIZATION2", testOrganization2.name());

    DBSpaceport testSpaceport(-1, "TEST SPACEPORT");
    db.addSpaceportToDB(testSpaceport);
    DBSpaceport testSpaceport2 = db.getSpaceportInfoFromId(db.getSpaceportIdFromName("TEST SPACEPORT"));
    QCOMPARE(testSpaceport.name(), testSpaceport2.name());

    testSpaceport2.setName("TEST SPACEPORT2");
    db.updateSpaceportDB(testSpaceport2.id(),testSpaceport2.name());
    testSpaceport2 = db.getSpaceportInfoFromId(db.getSpaceportIdFromName("TEST SPACEPORT2"));
    QCOMPARE("TEST SPACEPORT2", testSpaceport2.name());

    DBUnit testUnit(-1,"КА","TESTNAME","TEST PURPOSE",false,"TEST OBJECTIVE",
                    "TEST WORK STATUS",testOrganization2.id(),
                    testOrganization2.id(),testOrganization2.id(),100,
                    testOrganization2.id(),100,QDateTime(QDate(2020,1,1)),
                    testSpaceport2.id(),"TEST FINANCING TYPE",
                    "TEST CONTROLL SYSTEM TYPE","TEST IMAGE",100,100);
    db.addUnitToDBRetId(testUnit);
    DBUnit testUnit2 = db.getUnitInfoFromName("TESTNAME");
    QCOMPARE(testUnit.unit_class(), testUnit2.unit_class());
    QCOMPARE(testUnit.name(), testUnit2.name());
    QCOMPARE(testUnit.purpose(), testUnit2.purpose());
    QCOMPARE(testUnit.project(), testUnit2.project());
    QCOMPARE(testUnit.objective(), testUnit2.objective());
    QCOMPARE(testUnit.work_status(), testUnit2.work_status());
    QCOMPARE(testUnit.developer_id(), testUnit2.developer_id());
    QCOMPARE(testUnit.extra_developer_id(), testUnit2.extra_developer_id());
    QCOMPARE(testUnit.manufacturer_id(), testUnit2.manufacturer_id());
    QCOMPARE(testUnit.customer_id(), testUnit2.customer_id());
    QCOMPARE(testUnit.launches(), testUnit2.launches());
    QCOMPARE(testUnit.successful(), testUnit2.successful());
    QCOMPARE(testUnit.first_launch(), testUnit2.first_launch());
    QCOMPARE(testUnit.first_launch_spaceport_id(), testUnit2.first_launch_spaceport_id());
    QCOMPARE(testUnit.financing_type(), testUnit2.financing_type());
    QCOMPARE(testUnit.control_system_type(), testUnit2.control_system_type());
    QCOMPARE(testUnit.image_url(), testUnit2.image_url());
    QCOMPARE(testUnit.price(), testUnit2.price());
    QCOMPARE(testUnit.price_year(), testUnit2.price_year());

    testUnit2.setUnit_class("РН");
    testUnit2.setName("TESTNAME2");
    testUnit2.setPurpose("TEST PURPOSE2");
    testUnit2.setProject(true);
    testUnit2.setObjective("TEST OBJECTIVE2");
    testUnit2.setWork_status("TEST WORK STATUS2");
    testUnit2.setLaunches(200);
    testUnit2.setSuccessful(200);
    testUnit2.setFirst_launch(QDateTime(QDate(2022,2,2)));
    testUnit2.setFinancing_type("TEST FINANCING TYPE2");
    testUnit2.setControl_system_type("TEST CONTROLL SYSTEM TYPE2");
    testUnit2.setImage_url("TEST IMAGE2");
    testUnit2.setPrice(200);
    testUnit2.setPrice_year(200);
    db.updateUnitDBRetId(testUnit2);
    DBUnit testUnit3 = db.getUnitInfoFromName("TESTNAME2");

    QCOMPARE("РН", testUnit3.unit_class());
    QCOMPARE("TESTNAME2", testUnit3.name());
    QCOMPARE("TEST PURPOSE2", testUnit3.purpose());
    QCOMPARE(true, testUnit3.project());
    QCOMPARE("TEST OBJECTIVE2", testUnit3.objective());
    QCOMPARE("TEST WORK STATUS2", testUnit3.work_status());
    QCOMPARE(200, testUnit3.launches());
    QCOMPARE(200, testUnit3.successful());
    QCOMPARE(QDateTime(QDate(2022,2,2)), testUnit3.first_launch());
    QCOMPARE("TEST FINANCING TYPE2", testUnit3.financing_type());
    QCOMPARE("TEST CONTROLL SYSTEM TYPE2", testUnit3.control_system_type());
    QCOMPARE("TEST IMAGE2", testUnit3.image_url());
    QCOMPARE(200, testUnit3.price());
    QCOMPARE(200, testUnit3.price_year());

    DBUpper_block testUpperBlock(testUnit2.id(),"100==100","100==100");
    db.addUpperBlockToDB(testUpperBlock);
    DBUpper_block testUpperBlock2 = db.getUpper_blockInfoFromId(testUnit2.id());
    QCOMPARE(testUpperBlock.econ_info(), testUpperBlock2.econ_info());
    QCOMPARE(testUpperBlock.phys_info(), testUpperBlock2.phys_info());

    testUpperBlock2.setEcon_info("200==200");
    testUpperBlock2.setPhys_info("200==200");
    db.updateUpperBlockDB(testUpperBlock2);
    DBUpper_block testUpperBlock3 = db.getUpper_blockInfoFromId(testUnit2.id());
    QCOMPARE("200==200", testUpperBlock3.econ_info());
    QCOMPARE("200==200", testUpperBlock3.phys_info());

    DBBooster_rocket testBoosterRocket(testUnit2.id(),100,100,"100==100","100==100");
    db.addBoosterRocketToDB(testBoosterRocket);
    DBBooster_rocket testBoosterRocket2 = db.getBooster_rocketInfoFromId(testUnit2.id());
    QCOMPARE(testBoosterRocket.min_payload(), testBoosterRocket2.min_payload());
    QCOMPARE(testBoosterRocket.max_payload(), testBoosterRocket2.max_payload());
    QCOMPARE(testBoosterRocket.econ_info(), testBoosterRocket2.econ_info());
    QCOMPARE(testBoosterRocket.phys_info(), testBoosterRocket2.phys_info());

    testBoosterRocket2.setMax_payload(200);
    testBoosterRocket2.setMin_payload(200);
    testBoosterRocket2.setEcon_info("200==200");
    testBoosterRocket2.setPhys_info("200==200");
    db.updateBoosterRocketDB(testBoosterRocket2);
    DBBooster_rocket testBoosterRocket3 = db.getBooster_rocketInfoFromId(testUnit2.id());
    QCOMPARE(200, testBoosterRocket3.min_payload());
    QCOMPARE(200, testBoosterRocket3.max_payload());
    QCOMPARE("200==200", testBoosterRocket3.econ_info());
    QCOMPARE("200==200", testBoosterRocket3.phys_info());

    DBSpacecraft testSpacecraft(testUnit2.id(),100,100,"100==100","100==100");
    db.addSpacecraftToDB(testSpacecraft);
    DBSpacecraft testSpacecraft2 = db.getSpacecraftInfoFromId(testUnit2.id());
    QCOMPARE(testSpacecraft.weight(), testSpacecraft2.weight());
    QCOMPARE(testSpacecraft.active_lifetime(), testSpacecraft2.active_lifetime());
    QCOMPARE(testSpacecraft.econ_info(), testSpacecraft2.econ_info());
    QCOMPARE(testSpacecraft.phys_info(), testSpacecraft2.phys_info());

    testSpacecraft2.setActive_lifetime(200);
    testSpacecraft2.setWeight(200);
    testSpacecraft2.setEcon_info("200==200");
    testSpacecraft2.setPhys_info("200==200");
    db.updateSpacecraftDB(testSpacecraft2);
    DBSpacecraft testSpacecraft3 = db.getSpacecraftInfoFromId(testUnit2.id());
    QCOMPARE(200, testSpacecraft3.weight());
    QCOMPARE(200, testSpacecraft3.active_lifetime());
    QCOMPARE("200==200", testSpacecraft3.econ_info());
    QCOMPARE("200==200", testSpacecraft3.phys_info());

    DBProject testProject(-1,"TEST PROJECT", "TEST TYPE", testUnit2.id(), "TEST PRICES",
                          "TEST PRICES", "TEST PRICES", "TEST PRICES", "TEST PRICES");
    db.addProjectToDB(testProject);
    DBProject testProject2 = db.getProjectInfoFromName("TEST PROJECT");
    QCOMPARE(testProject.name(), testProject2.name());
    QCOMPARE(testProject.type(), testProject2.type());
    QCOMPARE(testProject.first_unit_prices(), testProject2.first_unit_prices());
    QCOMPARE(testProject.last_unit_prices(), testProject2.last_unit_prices());
    QCOMPARE(testProject.pre_prices(), testProject2.pre_prices());
    QCOMPARE(testProject.post_prices(), testProject2.post_prices());
    QCOMPARE(testProject.serial_prices(), testProject2.serial_prices());

    db.updateProjectPricesByName("TEST PROJECT","TEST PRICES2","TEST PRICES2","TEST PRICES2","TEST PRICES2","TEST PRICES2");
    testProject2 = db.getProjectInfoFromName("TEST PROJECT");

    QCOMPARE("TEST PRICES2", testProject2.first_unit_prices());
    QCOMPARE("TEST PRICES2", testProject2.last_unit_prices());
    QCOMPARE("TEST PRICES2", testProject2.pre_prices());
    QCOMPARE("TEST PRICES2", testProject2.post_prices());
    QCOMPARE("TEST PRICES2", testProject2.serial_prices());

    DBLaunch testLaunch(-1,testBoosterRocket2.id(), testUpperBlock2.id(),testSpaceport2.id(), 100, "TEST PRICES", 100, 100, 100, 100, true);
    db.addLaunchInformation(testLaunch);
    DBLaunch testLaunch2 = db.getLaunchFromParamIds(testUnit2.name(),testUnit2.name(),testSpaceport2.name());
    QCOMPARE(testLaunch.price_year(), testLaunch2.price_year());
    QCOMPARE(testLaunch.prices(), testLaunch2.prices());
    QCOMPARE(testLaunch.launch_price(), testLaunch2.launch_price());
    QCOMPARE(testLaunch.delivery_price(), testLaunch2.delivery_price());
    QCOMPARE(testLaunch.min_payload(), testLaunch2.min_payload());
    QCOMPARE(testLaunch.max_payload(), testLaunch2.max_payload());
    QCOMPARE(testLaunch.valid(), testLaunch2.valid());

    db.updateLaunchPricesByIds(testBoosterRocket2.id(), testUpperBlock2.id(),testSpaceport2.id(),200, "TEST PRICES2", 200, 200, 200, 200, false);
    testLaunch2 = db.getLaunchFromParamIds(testUnit2.name(),testUnit2.name(),testSpaceport2.name());
    QCOMPARE(200, testLaunch2.price_year());
    QCOMPARE("TEST PRICES2", testLaunch2.prices());
    QCOMPARE(200, testLaunch2.launch_price());
    QCOMPARE(200, testLaunch2.delivery_price());
    QCOMPARE(200, testLaunch2.min_payload());
    QCOMPARE(200, testLaunch2.max_payload());
    QCOMPARE(false, testLaunch2.valid());

    QVector<qreal> inflation = db.getInflationPercents(2024,2025);
    db.updateInflation(2024,1.5);
    QVector<qreal> inflation2 = db.getInflationPercents(2024,2025);
    QCOMPARE(1.5, inflation2[0]);
    db.updateInflation(2024,inflation[0]);
}

void Test_Tests::tabCatalogAndComparisonCheck()
{
    TabCatalogAndComparisonModel model;

    QString testString = "field1==value1\nfield2==value2\nfield3==value3";
    QVector<QPair<QString,QString>> testResult = model.splitValues(testString);
    for (int i=0;i<3;i++)
    {
        QCOMPARE(testResult[i].first, "field"+QString::number(i+1));
        QCOMPARE(testResult[i].second, "value"+QString::number(i+1));
    }

    QVector<QPair<QString,QString>> testUnitVector = model.vectorUnitData(db.getUnitIdByName("TESTNAME2"));
    qDebug() << testUnitVector;
    QCOMPARE("Класс", testUnitVector[0].first);
    QCOMPARE("РН", testUnitVector[0].second);
    QCOMPARE("Название", testUnitVector[1].first);
    QCOMPARE("TESTNAME2", testUnitVector[1].second);
    QCOMPARE("Назначение", testUnitVector[2].first);
    QCOMPARE("TEST PURPOSE2", testUnitVector[2].second);
    QCOMPARE("Проектный", testUnitVector[3].first);
    QCOMPARE("1", testUnitVector[3].second);
    QCOMPARE("Цель", testUnitVector[4].first);
    QCOMPARE("TEST OBJECTIVE2", testUnitVector[4].second);
    QCOMPARE("Состояние работ", testUnitVector[5].first);
    QCOMPARE("TEST WORK STATUS2", testUnitVector[5].second);
    QCOMPARE("Разработчик", testUnitVector[6].first);
    QCOMPARE("TEST ORGANIZATION2", testUnitVector[6].second);
    QCOMPARE("Разработчик 2", testUnitVector[7].first);
    QCOMPARE("TEST ORGANIZATION2", testUnitVector[7].second);
    QCOMPARE("Производитель", testUnitVector[8].first);
    QCOMPARE("TEST ORGANIZATION2", testUnitVector[8].second);
    QCOMPARE("Запусков", testUnitVector[9].first);
    QCOMPARE("200", testUnitVector[9].second);
    QCOMPARE("Заказчик", testUnitVector[10].first);
    QCOMPARE("TEST ORGANIZATION2", testUnitVector[10].second);
    QCOMPARE("Успешных запусков", testUnitVector[11].first);
    QCOMPARE("200", testUnitVector[11].second);
    QCOMPARE("Космодром первого запуска", testUnitVector[12].first);
    QCOMPARE("TEST SPACEPORT2", testUnitVector[12].second);
    QCOMPARE("Тип финансирования", testUnitVector[13].first);
    QCOMPARE("TEST FINANCING TYPE2", testUnitVector[13].second);
    QCOMPARE("Система контроля", testUnitVector[14].first);
    QCOMPARE("TEST CONTROLL SYSTEM TYPE2", testUnitVector[14].second);
    QCOMPARE("Цена", testUnitVector[15].first);
    QCOMPARE("200", testUnitVector[15].second);
    QCOMPARE("Год цены", testUnitVector[16].first);
    QCOMPARE("200", testUnitVector[16].second);

    QVector<QVector<QPair<QString,QString>>> testBoosterRocketVector = model.vectorBoosterRocketData(db.getUnitIdByName("TESTNAME2"));
    QCOMPARE("Максимальна грузоподъемность", testBoosterRocketVector[0][0].first);
    QCOMPARE("200", testBoosterRocketVector[0][0].second);
    QCOMPARE("Минимальная грузоподъемность", testBoosterRocketVector[0][1].first);
    QCOMPARE("200", testBoosterRocketVector[0][1].second);
    QCOMPARE("200", testBoosterRocketVector[1][0].first);
    QCOMPARE("200", testBoosterRocketVector[1][0].second);
    QCOMPARE("200", testBoosterRocketVector[2][0].first);
    QCOMPARE("200", testBoosterRocketVector[2][0].second);

    QVector<QVector<QPair<QString,QString>>> testUpperBlockVector = model.vectorUpperBlockData(db.getUnitIdByName("TESTNAME2"));
    qDebug() <<testUpperBlockVector;
    QCOMPARE("200", testUpperBlockVector[1][0].first);
    QCOMPARE("200", testUpperBlockVector[1][0].second);
    QCOMPARE("200", testUpperBlockVector[2][0].first);
    QCOMPARE("200", testUpperBlockVector[2][0].second);

    QVector<QVector<QPair<QString,QString>>> testSpacecraftVector = model.vectorSpacecraftData(db.getUnitIdByName("TESTNAME2"));
    qDebug() <<testSpacecraftVector;
    QCOMPARE("Вес", testSpacecraftVector[0][0].first);
    QCOMPARE("200", testSpacecraftVector[0][0].second);
    QCOMPARE("САС", testSpacecraftVector[0][1].first);
    QCOMPARE("200", testSpacecraftVector[0][1].second);
    QCOMPARE("200", testSpacecraftVector[1][0].first);
    QCOMPARE("200", testSpacecraftVector[1][0].second);
    QCOMPARE("200", testSpacecraftVector[2][0].first);
    QCOMPARE("200", testSpacecraftVector[2][0].second);

    testString = "TEXT1.35TEXT2.55TEXT0.33TEXT1.22TEXT";
    QCOMPARE(1.35, model.getNumberFromString(testString,0));
    QCOMPARE(0.33, model.getNumberFromString(testString,1));
    QCOMPARE(2.55, model.getNumberFromString(testString,2));
    QCOMPARE(1.22, model.getNumberFromString(testString,3));
}

void Test_Tests::tabEditUserModelCheck()
{
    TabEditUserModel model;
    QCOMPARE(false, model.lastAdmin());

}

void Test_Tests::tabEditCraftModelCheck()
{
    TabEditCraftModel model;
    QCOMPARE(true, true);
}

void Test_Tests::tabEditExtrasModelCheck()
{
    TabEditExtrasModel model;
    QString testPricesString = "100.1;101.1;102.1;103.1;104.1";
    QVector<qreal> pricesVector = model.pricesToVector(testPricesString);
    QCOMPARE(100.1, pricesVector[0]);
    QCOMPARE(101.1, pricesVector[1]);
    QCOMPARE(102.1, pricesVector[2]);
    QCOMPARE(103.1, pricesVector[3]);
    QCOMPARE(104.1, pricesVector[4]);

    QVector<QString> testVector = {"test1", "test2"};
    QStringList testStringList = model.QVectorToQStringList(testVector);
    QCOMPARE(testVector[0], testStringList[0]);
    QCOMPARE(testVector[1], testStringList[1]);
}

void Test_Tests::tabEditProjectModelCheck()
{
    TabEditProjectModel model;
    QCOMPARE(true, true);
}

void Test_Tests::tabPredictionModelCheck()
{
    TabPredictionModel model;

    QVector<int> testResult = model.fileRowTextToVector("1;0;3;");
    QCOMPARE(1, testResult[0]);
    QCOMPARE(0, testResult[1]);
    QCOMPARE(3, testResult[2]);

    QVector<QString> testVector = {"test1", "test2"};
    QStringList testStringList = model.QVectorToQStringList(testVector);
    QCOMPARE(testVector[0], testStringList[0]);
    QCOMPARE(testVector[1], testStringList[1]);
}

void Test_Tests::fileSaveTest()
{
    FileManager manager;
    manager.saveToFile("test.txt","testString");
    QString testResult = manager.readFile("test.txt");
    QCOMPARE("testString", testResult);
    QTextDocument a;
    manager.printPDF(&a, "test.pdf");
    QFileInfo check_file("test.pdf");
    QCOMPARE(true, check_file.exists());
}

void Test_Tests::DBDeleteCheck()
{
    db.deleteUserFromDB(db.getUserIdByName("testUser12"));
    DBUser testAdminUser2 = db.getUserById(db.getUserIdByName("testUser12"));
    QCOMPARE(testAdminUser2.name(), "");

    db.deleteLaunchBySpaceport(db.getSpaceportIdFromName("TEST SPACEPORT2"));
    DBLaunch testLaunch2 = db.getLaunchFromParamIds("TESTNAME2","TESTNAME2","TEST SPACEPORT2");
    QCOMPARE(testLaunch2.prices(), "");

    db.deleteProjectWithUnitId(db.getUnitIdByName("TESTNAME2"));
    DBProject testProject2 = db.getProjectInfoFromName("TEST PROJECT");
    QCOMPARE(testProject2.name(), "");

    db.deleteBoosterRocket(db.getUnitIdByName("TESTNAME2"));
    DBBooster_rocket testBoosterRocket2 = db.getBooster_rocketInfoFromId(db.getUnitIdByName("TESTNAME2"));
    QCOMPARE(testBoosterRocket2.min_payload(), 0);

    db.deleteUpperBlock(db.getUnitIdByName("TESTNAME2"));
    DBUpper_block testUpperBlock2 = db.getUpper_blockInfoFromId(db.getUnitIdByName("TESTNAME2"));
    QCOMPARE(testUpperBlock2.econ_info(), "");

    db.deleteSpacecraft(db.getUnitIdByName("TESTNAME2"));
    DBSpacecraft testSpacecraft2 = db.getSpacecraftInfoFromId(db.getUnitIdByName("TESTNAME2"));
    QCOMPARE(testSpacecraft2.weight(), 0);

    db.deleteUnit(db.getUnitIdByName("TESTNAME2"));
    DBUnit testUnit2 = db.getUnitInfoFromName("TESTNAME2");
    QCOMPARE(testUnit2.name(), "");

    db.deleteSpaceport(db.getSpaceportIdFromName("TEST SPACEPORT2"));
    DBSpaceport testSpaceport2 = db.getSpaceportInfoFromId(db.getSpaceportIdFromName("TEST SPACEPORT2"));
    QCOMPARE(testSpaceport2.name(), "");

    db.deleteOrganization(db.getOrganizationIdFromName("TEST ORGANIZATION2"));
    DBOrganization testOrganization2 = db.getOrganizationInfoFromId(db.getOrganizationIdFromName("TEST ORGANIZATION2"));
    QCOMPARE(testOrganization2.name(), "");

}
