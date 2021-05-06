#include <iostream>
#include <string>
#include <vector>

class Player
{

private:
public:
    int player_health;
    std::string player_name;
    int player_power;
    std::string player_id;
    std::vector<int> kills;

    Player()
    {
        player_health = 100;
        player_name = "Raghav";
        player_power = 100;
        player_id = "kx22vv44ILOkjakjhef008292992";
        kills = std::vector<int>(100, 100);
    }

    void decrease_health()
    {
        // player_health -= (std::rand() % 40) + 1;
           player_health -=  10;
    }
};

int main(int argc, char const *argv[])
{
    // std::srand(1);
    int N = 1000000;

    std::vector<Player> v(N, Player());
    std::vector<bool> is_alive(N, true);

    // Appraoch 1
    // bool flag = true;
    // while (flag)
    // {
        // flag = false;
        for (int i = 0; i < N; i++)
        {
            if (is_alive[i])
            {
            	
                // v[i].decrease_health();
                // // flag = true;

                if (v[i].player_health <= 0)
                {
                    is_alive[i] = false;
                }
            }
        }
    // }

    return 0;
}
