#pragma once

#include "point.hpp"
#include "observer.hpp"

#include <iostream>
#include <vector>
#include <memory>

class Entity {
public:
    Entity(); 

    virtual ~Entity() = default;

    Entity(const Point& position);

    Point get_position() const;

    void set_position(const Point& pos);

    double distance_to(const Entity& other) const;

    void attach_observer(std::shared_ptr<IEntityObserver> observer);

    void notify(const std::string& message);

private:
    Point position;
    std::vector<std::shared_ptr<IEntityObserver>> observers;
};