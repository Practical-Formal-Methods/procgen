#include "reset-guard.h"

struct Level createLevel(int level_id){
    struct Level newLevel;
    newLevel.level_id=level_id;
    newLevel.step_count=0;
    newLevel.weight=1;
    return newLevel;
}

LevelGuard::LevelGuard(int startLevel, int numLevels){
    for(int i=startLevel;i<startLevel+numLevels;i++){
        Levels.push_back(createLevel(i));
    }
}
LevelGuard::LevelGuard(){
    LevelGuard(0,500);
}
float LevelGuard::netWeight(){
    float sum=0;
    for(auto i=Levels.begin();i!=Levels.end();++i){
        sum+=i->weight;
    }
    return sum;
}