#pragma once

#include "entity.hpp"
#include "observer.hpp"

#include <unordered_set>
#include <memory>
#include <vector>

class Game {
public:
    void attach_observer(std::shared_ptr<IEntityObserver> observer);
    
    void add_object(std::shared_ptr<Entity> object);

    void delete_object(std::shared_ptr<Entity> object);

    void run(int distance);

private:
    std::unordered_set<std::shared_ptr<Entity>> game_objects;
    std::vector<std::shared_ptr<IEntityObserver>> game_observers;
};