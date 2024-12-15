#pragma once

#include "entity.hpp"
#include "types.hpp"

#include <functional>

std::string NPC_to_string(NPCType type);
NPCType string_to_NPC(const std::string& type_str);

class NPC : public Entity {
public:
    NPC(NPCType type, const std::string& name, const Point& pos);

    NPCType get_type() const;

    std::string get_name() const;

    bool is_alive() const;

    // accept
    virtual bool lets_fight(NPC* other) = 0;

    // visit
    virtual bool defend(NPC* other) = 0;

private:
    std::string name;
    NPCType type;

protected:
    bool alive;
};

class NPCFactory {
public:
    static std::shared_ptr<NPC> create_npc(NPCType type, const std::string& name, const Point& pos);

    static void DumpToStream(std::ostream& out, const std::shared_ptr<NPC>& npc);

    static std::shared_ptr<NPC> LoadFromStream(std::istream& in);

private:
    static std::unordered_map<NPCType, std::function<std::shared_ptr<NPC>(NPCType, const std::string&, const Point&)>> init_instances();
};

class Orc : public NPC {
public:
    Orc(const std::string& name, const Point& position);

    bool lets_fight(NPC* other) override;
    bool defend(NPC* other) override;
};

class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, const Point& position);

    bool lets_fight(NPC* other) override;
    bool defend(NPC* other) override;
};

class Druid : public NPC {
public:
    Druid(const std::string& name, const Point& position);

    bool lets_fight(NPC* other) override;
    bool defend(NPC* other) override;
};