#include<vector>

struct Level{
    int level_id;
    float weight;
    int step_count;
    std::vector<int> steps;
};

class LevelGuard{
    std::vector<struct Level> Levels;
    public:
        LevelGuard();
        LevelGuard(int startLevel, int numLevels);
        float netWeight();
}