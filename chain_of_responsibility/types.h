#pragma once 

#include <map>
#include <functional>

struct StatQuery {
  enum Statistic { attack, defense } statistic;
  int result;
};

typedef std::function<void(StatQuery &)> QueryCallback;

class EventConnection;
class EventDispatcher {
  using EventConnectionMap = std::map<EventConnection, QueryCallback>;
  EventConnectionMap queries_;
  size_t current_connection_id_;

 public:
  EventConnection connect(QueryCallback cb);

  void notify(StatQuery &q) ;

  void disconnect(EventConnection &connection);
};

class EventConnection {
  EventDispatcher* dispatcher_;
  size_t connection_id_;

 public:
  EventConnection() : dispatcher_(nullptr), connection_id_(0) {}
  EventConnection(EventDispatcher *dispatcher, size_t connection_id)
      : dispatcher_(dispatcher), connection_id_(connection_id) {}

  void disconnect();

  bool operator<(const EventConnection &rhs) const;
};