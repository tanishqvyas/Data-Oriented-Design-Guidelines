#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdlib>


struct Agent {
    Agent() : points{100}, health{100}, x{0}, y{0}
    {}

    std::size_t points;
    std::size_t health;
    int x, y;
};

class AgentProcessor {
    public:
    AgentProcessor(std::size_t N) : agent{N}, flag{true}
    {}

    void take_damage(Agent& agent) {
        agent.health -= (std::rand() % 20) + 1;  // Min: 1, Max: 20
    }

    bool regenerate_health() {
        flag = false;
        for (auto it = std::begin(agent); it != std::end(agent); ++it) {
            if (it -> health < 100) {
                ++it->health;
                flag = true;
            }
        }
        // std::cout << std::boolalpha;
        // std::cout << flag << std::endl;
        return flag;
    }

    std::vector<Agent> agent; 
    bool flag;
};

// void regenerate_health(Agent& agents) {
//     for (auto& agent : agents) {
//         if (agent.health < 100)
//             ++agent.health;
//     }
// }

int main(int argc, char *argv[]) {
    std::size_t N = std::atoi(argv[argc - 1]);
    AgentProcessor obj{N};
    std::srand(1);

    for(std::size_t i = 0; i < N; i+=2000) {
        obj.take_damage(obj.agent[i]);
    }
    // std::cout << "Here" << std::endl;

    while(obj.regenerate_health());

    return 0;
}