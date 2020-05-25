#pragma once
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
    bool verbose;
    modes Mode;
    RandGen randgen;
    int getIndex(float weight);
    std::vector<struct Level> Levels;
    public:
        LevelGuard();
        void init(int startLevel, int numLevels, int randseed,bool setVerbose, int mode);
        void init(int startLevel, int numLevels, int randseed){init(startLevel,numLevels,randseed,false,modes::Random);};
        float netWeight();
        void removeLevel(int index);
        int addLevel(int level_id, int len_moves, int* moves);
        struct Level nextLevel();
        bool active=false;
};