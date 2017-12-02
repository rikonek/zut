// implement hash_map/dictonary based on std::map:
// uses std::map<> as a container
// Key is a custom Hash  {} type; 
// Hash is calculated from key

#include <iostream>
#include <map>
#include <functional>

struct Hash {
  template<typename V>
  Hash(V&& v) {
    auto h = std::hash<
      typename std::decay<V>::type>{};
    _value = h(std::forward<V>(v));

  }
  std::int64_t _value;
};

struct StrCmp {
    bool operator()(string, string); 
};

template<typename Data>
using MyMap = 
  std::map<Hash, Data, ??>; // ?? zrobić samemu funkcję porównywania

template<typename Data>
struct HashMap {  
  Data& at(string key); //zwraca dane o zadanym napisie
  void put(string key, Data);
  bool check(Data) const noexcept;

  MyMap _map;
};

// HashMap::put(string key, Data)
// {

// }

int main()
{
    std::map<Hash,std::string> MyMap;
    // MyMap[key]="Ola";
    return 0;
}