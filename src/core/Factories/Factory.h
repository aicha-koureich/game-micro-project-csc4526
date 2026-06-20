#ifndef FACTORY_HPP
#define FACTORY_HPP

#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "Weapons/Weapon.h"
#include "pugixml.hpp"

class Factory {
 public:
  using Weapon_create_method =
      std::function<std::unique_ptr<Weapon>(pugi::xml_node const& node)>;
  Factory() = delete;

  static bool register_class_name(std::string_view class_name,
                                  Weapon_create_method const& create_method) {
    if (get_name2create_methods().count(class_name)==0) {
      std::cout << class_name << " registered\n";
      get_name2create_methods()[class_name] = create_method;
      return true;
    }
    std::cerr << "ERROR : " << class_name << " registered\n";
    return false;
  }

  /**
   * @brief Given an XML node, returns a unique_ptr<Shape> pointing to the Shape
   * subclass corresponding to @node.
   * @param node XML node containing all of the attributes of the objet to
   * create (including its class name).
   * @return The pointer to the created objet or @nullptr if the class found in
   * @node is not handled by Shape_Factory.
   */
  static std::unique_ptr<Weapon> create(pugi::xml_node const& node) {
    return get_name2create_methods().count(node.name())>0
               ? get_name2create_methods()[node.name()](node)
               : nullptr;
  }

 private:
  static std::map<std::string_view, Weapon_create_method>&  //la map qui stockent les classes enregistrées et leur create
  get_name2create_methods() { //getter de la map
    static std::map<std::string_view, Weapon_create_method> name2create_method;
    return name2create_method;
  }
};
#endif 