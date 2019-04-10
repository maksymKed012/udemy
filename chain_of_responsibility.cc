#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

struct Creature;
struct Game {
  std::vector<Creature *> creatures;
};

struct StatQuery {
  enum Statistic { attack, defense } statistic;
  int result;
};

using QueryCallback = std::function<void(StatQuery &)>;

class EventDispatcher {
  std::vector<QueryCallback> queries_;

 public:
  void connect(QueryCallback cb) { queries_.push_back(cb); }

  void disconnect(QueryCallback cb) {
    const auto it = std::find(queries_.begin(), queries_.end(), cb);
    if (it != queries_.end()) {
      queries_.erase(it);
    }
  }
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
  }

  int get_defense() override {
    // todo
  }
};

class GoblinKing : public Goblin {
 public:
  GoblinKing(Game &game) : Goblin(game, 3, 3) {}

  // todo
};

class CreatureModifier {
  Game &game_;
  Creature &creature_;

 public:
  virtual ~CreatureModifier() = default;

  CreatureModifier(Game &game, Creature &creature)
      : game_(game), creature_(creature) {}
};

class IncreaseAttackModifier : public CreatureModifier {
 public:
  IncreaseAttackModifier(Game &game, Creature &creature)
      : CreatureModifier(game, creature) {}
};

class IncreaseDefenseModifier : public CreatureModifier {
 public:
  IncreaseDefenseModifier(Game &game, Creature &creature)
      : CreatureModifier(game, creature) {}
};

int main() { return 0; }