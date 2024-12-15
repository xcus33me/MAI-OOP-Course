#include "game.hpp"
#include "npc.hpp"

void Game::attach_observer(std::shared_ptr<IEntityObserver> observer) {
    game_observers.push_back(observer);
    for (auto& obj : game_objects) {
        obj->attach_observer(observer);
    }
}
    
void Game::add_object(std::shared_ptr<Entity> object) {
    game_objects.insert(object);
    for (auto& obs : game_observers) {
        object->attach_observer(obs);
    }
}

void Game::delete_object(std::shared_ptr<Entity> object) {
    game_objects.erase(object);
}

void Game::run(int distance) {
    for (auto& i : game_objects) {
        std::shared_ptr<NPC> npc_obj = std::dynamic_pointer_cast<NPC>(i);
        if (!npc_obj) continue;

        for (auto& j : game_objects) {
            if (i == j) continue;

            std::shared_ptr<NPC> opp_obj = std::dynamic_pointer_cast<NPC>(j);

            if (!opp_obj) continue;
            if (!npc_obj->is_alive() || !opp_obj->is_alive()) continue;
            if ((int)npc_obj->distance_to(*opp_obj) > distance) continue;

            bool npc_died = npc_obj->lets_fight(opp_obj.get());
            bool opp_died = opp_obj->lets_fight(npc_obj.get());

            if (opp_died) {
                std::string message = NPC_to_string(npc_obj->get_type()) + " (" + npc_obj->get_name() + ") was killed by " +
                                      NPC_to_string(opp_obj->get_type()) + " (" + opp_obj->get_name() + ")";
                opp_obj->notify(message);
            } 
            if (npc_died) {
                std::string message = NPC_to_string(opp_obj->get_type()) + " (" + opp_obj->get_name() + ") was killed by " +
                                      NPC_to_string(npc_obj->get_type()) + " (" + npc_obj->get_name() + ")";
                npc_obj->notify(message);
            }
        }
    }
}