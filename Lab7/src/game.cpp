#include "game.hpp"
#include "npc.hpp"

#include <thread>
#include <shared_mutex>

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
    // Синхронизация доступа к ресурсам
    std::mutex game_mutex;
    
    // Поток для передвижения NPC
    auto move_thread = std::thread([this, &game_mutex]() {
        std::lock_guard<std::mutex> lock(game_mutex); // Используем lock_guard, так как game_mutex это std::mutex
        for (auto& i : game_objects) {
            std::shared_ptr<NPC> npc_obj = std::dynamic_pointer_cast<NPC>(i);
            if (npc_obj && npc_obj->is_alive()) {
                // Логика передвижения NPC
                npc_obj->set_position({npc_obj->get_position().getX() + 1, npc_obj->get_position().getY() + 1});
            }
        }
    });

    // Поток для проверки убийств и создания задач для боя
    auto check_fight_thread = std::thread([this, distance, &game_mutex]() {
        std::lock_guard<std::mutex> lock(game_mutex); // Используем lock_guard, так как game_mutex это std::mutex
        for (auto& i : game_objects) {
            std::shared_ptr<NPC> npc_obj = std::dynamic_pointer_cast<NPC>(i);
            if (!npc_obj || !npc_obj->is_alive()) continue;

            for (auto& j : game_objects) {
                if (i == j) continue;

                std::shared_ptr<NPC> opp_obj = std::dynamic_pointer_cast<NPC>(j);
                if (!opp_obj || !opp_obj->is_alive()) continue;
                if ((int)npc_obj->distance_to(*opp_obj) > distance) continue;

                // Задача для боя
                std::thread fight_thread([npc_obj, opp_obj, &game_mutex]() {
                    bool npc_died = npc_obj->lets_fight(opp_obj.get());
                    bool opp_died = opp_obj->lets_fight(npc_obj.get());

                    if (opp_died) {
                        std::lock_guard<std::mutex> guard(game_mutex); // Блокировка для вывода сообщения
                        std::string message = NPC_to_string(npc_obj->get_type()) + " (" + npc_obj->get_name() + ") was killed by " +
                                              NPC_to_string(opp_obj->get_type()) + " (" + opp_obj->get_name() + ")";
                        opp_obj->notify(message);
                    }
                    if (npc_died) {
                        std::lock_guard<std::mutex> guard(game_mutex); // Блокировка для вывода сообщения
                        std::string message = NPC_to_string(opp_obj->get_type()) + " (" + opp_obj->get_name() + ") was killed by " +
                                              NPC_to_string(npc_obj->get_type()) + " (" + npc_obj->get_name() + ")";
                        npc_obj->notify(message);
                    }
                });
                fight_thread.detach(); // Потоки для боев могут работать независимо, их можно отсоединить
            }
        }
    });

    // Поток для вывода карты
    auto print_thread = std::thread([this, &game_mutex]() {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Задержка в 1 секунду
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Печать карты каждую секунду
            std::lock_guard<std::mutex> lock(game_mutex); // Блокировка вывода
            for (auto& i : game_objects) {
                std::shared_ptr<NPC> npc_obj = std::dynamic_pointer_cast<NPC>(i);
                if (npc_obj && npc_obj->is_alive()) {
                    npc_obj->get_position().print(); // Печать позиции живого NPC
                }
            }
        }
    });

    // Ожидание завершения потоков
    move_thread.join();
    check_fight_thread.join();
    print_thread.join();
}

void Game::move_npc(std::shared_ptr<NPC> npc) {
    while (npc->is_alive()) {
        Point current_position = npc->get_position();
        Point new_position(current_position.getX() + 1, current_position.getY());
        npc->set_position(new_position);

        for (auto& other : game_objects) {
            if (auto other_npc = std::dynamic_pointer_cast<NPC>(other)) {
                if (npc != other_npc && npc->is_alive() && other_npc->is_alive()) {
                    double dist = npc->distance_to(*other_npc);
                    if (dist <= 10) {
                        std::thread(&Game::npc_battle, this, npc, other_npc).detach();
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Game::npc_battle(std::shared_ptr<NPC> npc1, std::shared_ptr<NPC> npc2) {
    if (npc1->lets_fight(npc2.get())) {
        std::lock_guard<std::mutex> guard(cout_mutex);
        std::string message = npc2->get_name() + " killed by " + npc1->get_name();
        npc1->notify(message);
    }
    if (npc2->lets_fight(npc1.get())) {
        std::lock_guard<std::mutex> guard(cout_mutex);
        std::string message = npc1->get_name() + " killed by " + npc2->get_name();
        npc2->notify(message);
    }
}