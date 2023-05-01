#include "test_tests.h"

#include <QtTest/QTest>
#include "test_tests.h"
#include "tests.h"
#include <Database.h>

Test_Tests::Test_Tests(QObject *parent) :
    QObject(parent)
{
}

void Test_Tests::DBCreateGetCheck()
{
    db.createConnection();

    DBUser testAdminUser(-1,"testUser1","Администратор","0000");
    db.addUserToDB(testAdminUser);
    DBUser testAdminUser2 = db.getUserById(db.getUserIdByName("testUser1"));
    QCOMPARE(testAdminUser2.name(), testAdminUser.name());
    QCOMPARE(testAdminUser2.role(), testAdminUser.role());


    DBUser testUser(-1,"testUser2","Пользователь","0000");
    db.addUserToDB(testUser);
    DBUser testUser2 = db.getUserById(db.getUserIdByName("testUser2"));
    QCOMPARE(testUser2.name(), testUser.name());
    QCOMPARE(testUser2.role(), testUser.role());


    DBOrganization testOrganization(-1,"TEST ORGANIZATION");
    db.addOrganoizationToDB(testOrganization);
    DBOrganization testOrganization2 = db.getOrganizationInfoFromId(db.getOrganizationIdFromName("TEST ORGANIZATION"));
    QCOMPARE(testOrganization.name(), testOrganization2.name());

    DBSpaceport testSpaceport(-1, "TEST SPACEPORT");
    db.addSpaceportToDB(testSpaceport);
    DBSpaceport testSpaceport2 = db.getSpaceportInfoFromId(db.getSpaceportIdFromName("TEST SPACEPORT"));
    QCOMPARE(testSpaceport.name(), testSpaceport2.name());

    DBUnit testUnit(-1,"КА","TESTNAME","TEST PURPOSE",false,"TEST OBJECTIVE",
                    "TEST WORK STATUS",testOrganization2.id(),
                    testOrganization2.id(),testOrganization2.id(),
                    100,testOrganization2.id(),100,QDateTime(QDate(2020,1,1)),
                    testSpaceport2.id(),"TEST FINANCING TYPE","TEST CONTROLL SYSTEM TYPE","TEST IMAGE",100,100);
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

    DBUpper_block testUpperBlock(testUnit2.id(),"100","100");
    db.addUpperBlockToDB(testUpperBlock);
    DBUpper_block testUpperBlock2 = db.getUpper_blockInfoFromId(testUnit2.id());
    QCOMPARE(testUpperBlock.econ_info(), testUpperBlock2.econ_info());
    QCOMPARE(testUpperBlock.phys_info(), testUpperBlock2.phys_info());

    DBBooster_rocket testBoosterRocket(testUnit2.id(),100,100,"100","100");
    db.addBoosterRocketToDB(testBoosterRocket);
    DBBooster_rocket testBoosterRocket2 = db.getBooster_rocketInfoFromId(testUnit2.id());
    QCOMPARE(testBoosterRocket.min_payload(), testBoosterRocket2.min_payload());
    QCOMPARE(testBoosterRocket.max_payload(), testBoosterRocket2.max_payload());
    QCOMPARE(testBoosterRocket.econ_info(), testBoosterRocket2.econ_info());
    QCOMPARE(testBoosterRocket.phys_info(), testBoosterRocket2.phys_info());

    DBSpacecraft testSpacecraft(testUnit2.id(),100,100,"100","100");
    db.addSpacecraftToDB(testSpacecraft);
    DBSpacecraft testSpacecraft2 = db.getSpacecraftInfoFromId(testUnit2.id());
    QCOMPARE(testSpacecraft.weight(), testSpacecraft2.weight());
    QCOMPARE(testSpacecraft.active_lifetime(), testSpacecraft2.active_lifetime());
    QCOMPARE(testSpacecraft.econ_info(), testSpacecraft2.econ_info());
    QCOMPARE(testSpacecraft.phys_info(), testSpacecraft2.phys_info());

    DBProject testProject(-1,"TEST PROJECT", "TEST TYPE", testUnit2.id(), "TEST PRICES", "TEST PRICES", "TEST PRICES", "TEST PRICES", "TEST PRICES");
    db.addProjectToDB(testProject);
    DBProject testProject2 = db.getProjectInfoFromName("TEST PROJECT");
    QCOMPARE(testProject.name(), testProject2.name());
    QCOMPARE(testProject.type(), testProject2.type());
    QCOMPARE(testProject.first_unit_prices(), testProject2.first_unit_prices());
    QCOMPARE(testProject.last_unit_prices(), testProject2.last_unit_prices());
    QCOMPARE(testProject.pre_prices(), testProject2.pre_prices());
    QCOMPARE(testProject.post_prices(), testProject2.post_prices());
    QCOMPARE(testProject.serial_prices(), testProject2.serial_prices());

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

}

void Test_Tests::DBDeleteCheck()
{
    db.deleteUserFromDB(db.getUserIdByName("testUser1"));
    DBUser testAdminUser2 = db.getUserById(db.getUserIdByName("testUser1"));
    QCOMPARE(testAdminUser2.name(), "");

    db.deleteUserFromDB(db.getUserIdByName("testUser2"));
    DBUser testUser2 = db.getUserById(db.getUserIdByName("testUser2"));
    QCOMPARE(testUser2.name(), "");

    db.deleteLaunchBySpaceport(db.getSpaceportIdFromName("TEST SPACEPORT"));
    DBLaunch testLaunch2 = db.getLaunchFromParamIds("TESTNAME","TESTNAME","TEST SPACEPORT");
    QCOMPARE(testLaunch2.prices(), "");

    db.deleteProjectWithUnitId(db.getUnitIdByName("TESTNAME"));
    DBProject testProject2 = db.getProjectInfoFromName("TEST PROJECT");
    QCOMPARE(testProject2.name(), "");

    db.deleteBoosterRocket(db.getUnitIdByName("TESTNAME"));
    DBBooster_rocket testBoosterRocket2 = db.getBooster_rocketInfoFromId(db.getUnitIdByName("TESTNAME"));
    QCOMPARE(testBoosterRocket2.min_payload(), 0);

    db.deleteUpperBlock(db.getUnitIdByName("TESTNAME"));
    DBUpper_block testUpperBlock2 = db.getUpper_blockInfoFromId(db.getUnitIdByName("TESTNAME"));
    QCOMPARE(testUpperBlock2.econ_info(), "");

    db.deleteSpacecraft(db.getUnitIdByName("TESTNAME"));
    DBSpacecraft testSpacecraft2 = db.getSpacecraftInfoFromId(db.getUnitIdByName("TESTNAME"));
    QCOMPARE(testSpacecraft2.weight(), 0);

    db.deleteUnit(db.getUnitIdByName("TESTNAME"));
    DBUnit testUnit2 = db.getUnitInfoFromName("TESTNAME");
    QCOMPARE(testUnit2.name(), "");

    db.deleteSpaceport(db.getSpaceportIdFromName("TEST SPACEPORT"));
    DBSpaceport testSpaceport2 = db.getSpaceportInfoFromId(db.getSpaceportIdFromName("TEST SPACEPORT"));
    QCOMPARE(testSpaceport2.name(), "");

    db.deleteOrganization(db.getOrganizationIdFromName("TEST ORGANIZATION"));
    DBOrganization testOrganization2 = db.getOrganizationInfoFromId(db.getOrganizationIdFromName("TEST ORGANIZATION"));
    QCOMPARE(testOrganization2.name(), "");
}
