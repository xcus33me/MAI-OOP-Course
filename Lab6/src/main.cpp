#include "game.hpp"
#include "npc.hpp"
#include "observer.hpp"

int main() {
    auto orc1 = NPCFactory::create_npc(NPCType::Orc, "lolka", {1, 12});
    auto orc2 = NPCFactory::create_npc(NPCType::Orc, "meme", {3, 0});
    auto orc3 = NPCFactory::create_npc(NPCType::Orc, "solana", {12, 12});
    auto sq1 = NPCFactory::create_npc(NPCType::Squirrel, "chain", {0, 0});
    auto sq2 = NPCFactory::create_npc(NPCType::Squirrel, "diddy", {15, 3});
    auto sq3 = NPCFactory::create_npc(NPCType::Squirrel, "mango", {100, 12});
    auto dr1 = NPCFactory::create_npc(NPCType::Druid, "hihi", {0, 3});
    auto dr2 = NPCFactory::create_npc(NPCType::Druid, "kek", {6, 20});

    auto log_obs = std::make_shared<LogEntityObserver>("./log.txt");
    auto print_obs = std::make_shared<PrintEntityObserver>();

    Game game;
    game.attach_observer(log_obs);
    game.attach_observer(print_obs);

    game.add_object(std::move(orc1));
    game.add_object(std::move(orc2));
    game.add_object(std::move(orc3));
    game.add_object(std::move(sq1 ));
    game.add_object(std::move(sq2 ));
    game.add_object(std::move(sq3 ));
    game.add_object(std::move(dr1 ));
    game.add_object(std::move(dr2 ));

    game.run(15);
}