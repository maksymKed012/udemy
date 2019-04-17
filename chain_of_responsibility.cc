#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Creature;

struct StatQuery {
  enum Statistic { attack, defense } statistic;
  int result;
};

using QueryCallback = std::function<void(StatQuery &)>;

class EventDispatcher;

class EventConnection {
  EventDispatcher &dispatcher_;
  size_t connection_id_;

 public:
  EventConnection(EventDispatcher &dispatcher, size_t connection_id)
      : dispatcher_(dispatcher), connection_id_(connection_id) {}

  EventConnection(EventConnection &other) {
    dispatcher_ = other.dispatcher_;
    connection_id_ = other.connection_id_;
  }

  void disconnect() { dispatcher_.disconnect(*this); }

  bool operator<(const EventConnection &rhs) {
    return connection_id_ < rhs.connection_id_;
  }

  EventConnection &operator=(EventConnection &other) {
    dispatcher_ = other.dispatcher_;
    connection_id_ = other.connection_id_;
    return *this;
  }
};

class EventDispatcher {
  using EventConnectionMap = std::map<EventConnection, QueryCallback>;
  EventConnectionMap queries_;
  size_t current_connection_id_;

 public:
  EventConnection connect(QueryCallback cb) {
    EventConnection connection{*this, current_connection_id_++};
    queries_[connection] = cb;
    return connection;
  }

  void notify(StatQuery &q) {
    for (const auto &query : queries_) {
      query.second(q);
    }
  }

  void disconnect(EventConnection &connection) {
    const auto it = queries_.find(connection);
    if (it != queries_.end()) {
      queries_.erase(it);
    }
  }
};

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
        q.result += 1;
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
        q.result += 1;
      }
    });
  }

  ~IncreaseDefenseModifier() { game_.disconnect(connection_); }
};

int main() { return 0; }