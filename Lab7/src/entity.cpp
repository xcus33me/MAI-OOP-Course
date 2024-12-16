#include "entity.hpp"

Entity::Entity() : position({0, 0}) {}

Entity::Entity(const Point& position) : position(position) {}

Point Entity::get_position() const {
    return position;
}

void Entity::set_position(const Point& pos) {
    position = pos;
}

double Entity::distance_to(const Entity& other) const {
    return position.distance_to(other.get_position());
}

void Entity::attach_observer(std::shared_ptr<IEntityObserver> observer) {
    observers.push_back(observer);
}

void Entity::notify(const std::string& message) {
        for (const auto& observer : observers) {
            observer->update(message);
        }
    }