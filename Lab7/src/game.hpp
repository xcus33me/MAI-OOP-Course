#pragma once

#include "entity.hpp"
#include "npc.hpp"
#include "observer.hpp"

#include <unordered_set>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>

class Game {
public:
    void attach_observer(std::shared_ptr<IEntityObserver> observer);
    
    void add_object(std::shared_ptr<Entity> object);

    void delete_object(std::shared_ptr<Entity> object);

    void run(int distance);

private:
    void move_npc(std::shared_ptr<NPC> npc);
    void npc_battle(std::shared_ptr<NPC> npc1, std::shared_ptr<NPC> npc2);
    void print_map();

    std::unordered_set<std::shared_ptr<Entity>> game_objects;
    std::vector<std::shared_ptr<IEntityObserver>> game_observers;
    std::mutex cout_mutex;
};