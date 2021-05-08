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
    AgentProcessor(std::size_t N) : damaged_agent{}, agent{N}
    {}

    void take_damage(Agent& agent) {
        agent.health -= (std::rand() % 20) + 1;  // Min: 1, Max: 20
        damaged_agent.push_back(&agent);
    }

    void regenerate_health() {
        for (auto it = std::begin(damaged_agent); it != std::end(damaged_agent);) {
            ++(*it)->health;
            if ((*it) -> health >= 100)
                it = damaged_agent.erase(it);
            else
                ++it;
        }
    }

    std::vector<Agent*> damaged_agent;
    std::vector<Agent> agent; 
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

    for(std::size_t i = 0; i < N; i+=200) {
        obj.take_damage(obj.agent[i]);
    }

    while(obj.damaged_agent.size())
        obj.regenerate_health();

    return 0;
}