#include <gtest/gtest.h>
#include <memory>
#include "pugixml.hpp"
#include "Factory.h" 
#include "Weapon.h"

TEST(WeaponFactoryTest, CreatesSwordSuccessfully) {
    const char* xmlData = R"(
        <Weapons>
            <Sword name="Lame de Gascogne" effect="70" cost="150" />
        </Weapons>
    )";
    
    pugi::xml_document doc;
    ASSERT_TRUE(doc.load_string(xmlData)); 
    
    pugi::xml_node swordNode = doc.child("Weapons").first_child();

    std::unique_ptr<Weapon> weapon = Factory::create(swordNode);

    ASSERT_NE(weapon, nullptr); 
    EXPECT_EQ(weapon->getName(), "Lame de Gascogne");
    EXPECT_EQ(weapon->getCost(), 150);
}

TEST(WeaponFactoryTest, CreatesFeatherSuccessfully) {
    const char* xmlData = R"(
        <Weapons>
            <Feather name="Le Panache Blanc" effect="100" cost="400" />
        </Weapons>
    )";
    
    pugi::xml_document doc;
    ASSERT_TRUE(doc.load_string(xmlData)); 
    
    pugi::xml_node featherNode = doc.child("Weapons").first_child();

    std::unique_ptr<Weapon> weapon = Factory::create(featherNode);

    ASSERT_NE(weapon, nullptr); 
    
    EXPECT_EQ(weapon->getName(), "Le Panache Blanc");
    EXPECT_EQ(weapon->getCost(), 400);
}

TEST(WeaponFactoryTest, RejectsUnknownWeaponType) {
    const char* xmlData = R"(
        <Weapons>
            <Bazooka name="Lance-Roquettes" effect="9000" cost="5000" />
        </Weapons>
    )";
    
    pugi::xml_document doc;
    ASSERT_TRUE(doc.load_string(xmlData));
    
    pugi::xml_node unknownNode = doc.child("Weapons").first_child();

    std::unique_ptr<Weapon> weapon = Factory::create(unknownNode);

    EXPECT_EQ(weapon, nullptr);
}