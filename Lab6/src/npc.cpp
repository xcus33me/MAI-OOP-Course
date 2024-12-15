#include "npc.hpp"
#include "types.hpp"
#include "point.hpp"

std::string NPC_to_string(NPCType type) {
    switch (type) {
        case NPCType::Orc: return "Orc";
        case NPCType::Squirrel: return "Squirrel";
        case NPCType::Druid: return "Druid";
        default: throw std::invalid_argument("Unknown NPCType");
    }
}

NPCType string_to_NPC(const std::string& type_str) {
    if (type_str == "Orc") return NPCType::Orc;
    if (type_str == "Squirrel") return NPCType::Squirrel;
    if (type_str == "Druid") return NPCType::Druid;
    throw std::invalid_argument("Unknown NPCType string: " + type_str);
}

NPC::NPC(NPCType type, const std::string& name, const Point& pos)
    : Entity(pos), type(type), name(name), alive(true) {}

NPCType NPC::get_type() const {
    return type;
}

std::string NPC::get_name() const {
    return name;
}

bool NPC::is_alive() const {
    return alive;
}

Squirrel::Squirrel(const std::string& name, const Point& position) 
    : NPC(NPCType::Squirrel, name, position) {}

bool Squirrel::lets_fight(NPC* other) {
    return !other->defend(this);
}

bool Squirrel::defend(NPC* other) {
    bool result = alive;
    if (other->get_type() == NPCType::Druid) {
        result = false;
    }
    alive = result;
    return result;
}

Druid::Druid(const std::string& name, const Point& position)
    : NPC(NPCType::Druid, name, position) {}

bool Druid::lets_fight(NPC* other) {
    return !other->defend(this);
}

bool Druid::defend(NPC* other) {
    bool result = alive;
    if (other->get_type() == NPCType::Orc) {
        result = false;
    }
    alive = result;
    return result;
}

Orc::Orc(const std::string& name, const Point& position)
    : NPC(NPCType::Orc, name, position) {}

bool Orc::lets_fight(NPC* other) {
    return !other->defend(this);
}

bool Orc::defend(NPC* other) {
    return true;
}

std::shared_ptr<NPC> NPCFactory::create_npc(NPCType type, const std::string& name, const Point& pos) {
    static const auto npc_instances = init_instances();

    auto it = npc_instances.find(type);
    if (it != npc_instances.end()) {
        return it->second(type, name, pos);
    }

    throw std::invalid_argument("NPCType not recognized");
}

void NPCFactory::DumpToStream(std::ostream& out, const std::shared_ptr<NPC>& npc) {
    if (!npc) return;

    out << NPC_to_string(npc->get_type()) << " ";
    out << npc->get_name() << " ";
    
    Point position = npc->get_position();
    out << position.getX() << " " << position.getY() << " ";

    out << npc->is_alive();

    out << "\n";

    if (!out) {
        throw std::runtime_error("Failed to write NPC to stream!");
    }
}

std::shared_ptr<NPC> NPCFactory::LoadFromStream(std::istream& in) {
    std::string type_str, name;
    int x, y;
    bool alive;

    in >> type_str >> name >> x >> y >> alive;

    if (!in) {
        throw std::runtime_error("Failed to load NPC from stream!");
    }

    return create_npc(string_to_NPC(type_str), name, {x, y});
}

std::unordered_map<NPCType, std::function<std::shared_ptr<NPC>(NPCType, const std::string&, const Point&)>> NPCFactory::init_instances() {
    std::unordered_map<NPCType, std::function<std::shared_ptr<NPC>(NPCType, const std::string&, const Point&)>> instances;

    instances[NPCType::Orc] = [](NPCType type, const std::string& name, const Point& position) {
        return std::make_shared<Orc>(name, position);
    };
    instances[NPCType::Squirrel] = [](NPCType type, const std::string& name, const Point& position) {
        return std::make_shared<Squirrel>(name, position);
    };
    instances[NPCType::Druid] = [](NPCType type, const std::string& name, const Point& position) {
        return std::make_shared<Druid>(name, position);
    };

    return instances;
}