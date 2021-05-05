// This program shows off the basics of data-oriented-design in C++
// By: Nick from CoffeeBeforeArch

#include <cstddef>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <cstdlib>


// A simple struct aligned in such a way no two instances will be on
// the same cache line (64 bytes cache lines, 64 byte alignment)
struct player {
    player() : player_id(), name(), type(), age(), health(), damage(), points()
    {}
    std::string player_id;
    std::string name;
    std::string type;
    unsigned short age;
    unsigned short health;
    unsigned short damage;
    unsigned long int points;

    void inc_health() {
        ++health;
    }
};

// A simple struct that contains an array the fields stored in the
// other object
struct SoA {
    // Simple constructor that resizes the vector to store N values
    SoA(std::size_t N) : player_id(N), name(N), type(N), age(N), health(N), damage(N), points(N)
    {}

    // Update method that increments each value
    // Only for health for brevity
    void inc_health() {
        for (auto &i : health) {
            ++i;
        }
    }

  // Vector of values
  std::vector<std::string> player_id;
  std::vector<std::string> name;
  std::vector<std::string> type;
  std::vector<unsigned short> age;
  std::vector<unsigned short> health;
  std::vector<unsigned short> damage;
  std::vector<unsigned long int> points;
};

// Benchmark for classic OO approach
void ArrayOfStructs_Bench(int &obj_count, int &iter_count) {
  // Create a vector for the PaddedStruct
  std::vector<player> v(obj_count);

  // Profile the update for each field
  for(int  i = 0; i < iter_count; ++i) {
    // Increment the field for each struct
    for (auto &i : v) {
      i.inc_health();
    }
  }
}

// Benchmark for DoD approach
void StructOfArrays_Bench(int &obj_count, int &iter_count) {
  // Create an Struct of Arrays
  SoA struct_of_arrays(obj_count);

  for(int  i = 0; i < iter_count; ++i) {
    // Increment the field for each struct
    struct_of_arrays.inc_health();
  }
}


int main(int argc, char *argv[]) {
    int no_of_objs = atoi(argv[argc-2]);
    int no_of_iterations  = atoi(argv[argc-1]);

    #if 0
        ArrayOfStructs_Bench(no_of_objs, no_of_iterations);
    #endif
    #if 1
        StructOfArrays_Bench(no_of_objs, no_of_iterations);
    #endif
}
