#include<vector>
#include<iostream>
#include "randgen.h"
struct Level{
    int level_id;
    float weight;
    int step_count;
    std::vector<int> steps;
};
enum modes{
    Random=0,
    Permute=1,
    Sequential=2
};
class LevelGuard{
    std::vector<struct Level> Levels;
    bool verbose;
    modes Mode;
    RandGen randgen;
    int getIndex(float weight);
    public:
        LevelGuard();
        LevelGuard(int startLevel, int numLevels, bool setVerbose, int mode);
        float netWeight();
        void removeLevel(int index);
        int addLevel(int level_id, int len_moves, int* moves);
        struct Level nextLevel();
        bool active=false;
};