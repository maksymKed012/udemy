#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "types.h"

struct Creature;

EventConnection EventDispatcher::connect(QueryCallback cb) {
  EventConnection connection{this, current_connection_id_++};
  queries_[connection] = cb;
  return connection;
}

void EventDispatcher::notify(StatQuery &q) {
  for (const auto &query : queries_) {
    query.second(q);
  }
}

void EventDispatcher::disconnect(EventConnection &connection) {
  const auto it = queries_.find(connection);
  if (it != queries_.end()) {
    queries_.erase(it);
  }
}

void EventConnection::disconnect() { dispatcher_->disconnect(*this); }

bool EventConnection::operator<(const EventConnection &rhs) const {
  return connection_id_ < rhs.connection_id_;
}

struct Game : public EventDispatcher {
  std::vector<Creature *> creatures;
};

struct Creature {
protected:
  Game &game;
  int base_attack, base_defense;

public:
  Creature(Game &game, int base_attack, int base_defense)
      : game(game), base_attack(base_attack), base_defense(base_defense) {}
  virtual int get_attack() = 0;
  virtual int get_defense() = 0;
};

class Goblin : public Creature {
public:
  Goblin(Game &game, int base_attack, int base_defense)
      : Creature(game, base_attack, base_defense) {}

  Goblin(Game &game) : Creature(game, 1, 1) {}

  int get_attack() override {
    // todo
    StatQuery q{StatQuery::Statistic::attack, base_attack};
    game.notify(q);
    return q.result;
  }

  int get_defense() override {
    // todo
    StatQuery q{StatQuery::Statistic::defense, base_defense};
    game.notify(q);
    return q.result;
  }
};

class GoblinKing : public Goblin {
public:
  GoblinKing(Game &game) : Goblin(game, 3, 3) {}

  // todo
};

class CreatureModifier {
protected:
  Game &game_;
  Creature &creature_;
  EventConnection connection_;

public:
  virtual ~CreatureModifier() = default;

  CreatureModifier(Game &game, Creature &creature)
      : game_(game), creature_(creature) {}
};

class IncreaseAttackModifier : public CreatureModifier {
public:
  IncreaseAttackModifier(Game &game, Creature &creature)
      : CreatureModifier(game, creature) {
    connection_ = game.connect([&](StatQuery &q) {
      if (StatQuery::Statistic::attack == q.statistic) {
        for (const auto &creature : game.creatures) {
          if (dynamic_cast<GoblinKing *>(creature)) {
            q.result += 1;
          }
        }
      }
    });
  }

  ~IncreaseAttackModifier() { game_.disconnect(connection_); }
};

class IncreaseDefenseModifier : public CreatureModifier {
public:
  IncreaseDefenseModifier(Game &game, Creature &creature)
      : CreatureModifier(game, creature) {
    connection_ = game.connect([&](StatQuery &q) {
      if (StatQuery::Statistic::defense == q.statistic) {
        for (const auto &creature : game.creatures) {
          if (dynamic_cast<Goblin *>(creature) ||
              dynamic_cast<GoblinKing *>(creature)) {
            q.result += 1;
          }
        }
      }
    });
  }

  ~IncreaseDefenseModifier() { game_.disconnect(connection_); }
};

int main() { return 0; }