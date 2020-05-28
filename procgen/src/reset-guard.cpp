#include "reset-guard.h"

struct Level createLevel(int level_id){
    struct Level newLevel;
    newLevel.level_id=level_id;
    newLevel.step_count=0;
    newLevel.weight=1;
    return newLevel;
}

void LevelGuard::init(int startLevel, int numLevels, int randseed, bool setVerbose=false, int mode=modes::Random){
    for(int i=startLevel;i<startLevel+numLevels;i++){
        Levels.push_back(createLevel(i));
        if(setVerbose)
            std::cout<<"Added level "<<i<<" now have "<<Levels.size()<<" levels\n";
    }
    verbose=setVerbose;
    Mode=(modes)mode;
    active=true;
    randgen.seed(randseed);
}
LevelGuard::LevelGuard(){
    active=false;
    //std::cout<<"I got called too\n";
}
float LevelGuard::netWeight(){
    float sum=0;
    for(auto i=Levels.begin();i!=Levels.end();++i){
        sum+=i->weight;
    }
    return sum;
}
void LevelGuard::removeLevel(int index){
    int lsize = (int) Levels.size();
    if(lsize<=index){
        if(verbose)
            std::cout<<"Index "<<index<<" out of range for vector with "<<Levels.size()<<"elements. Skipping."<<std::endl;
        return;
    }
    if(verbose)
        std::cout<<"Setting weight for index "<<index<<"(level#"<<Levels[index].level_id<<") to zero. Previously this was "<<Levels[index].weight<<std::endl;
    Levels[index].weight=0;
}
int LevelGuard::addLevel(int level_id, int len_moves, int* moves, float weight){
    Level newLevel=createLevel(level_id);
    newLevel.step_count=len_moves;
    if(len_moves>0){
        for(int i=0;i<len_moves;i++)
            newLevel.steps.push_back(moves[i]);
    }
    int id=Levels.size();
    newLevel.weight=weight;
    Levels.push_back(newLevel);
    return id;
}
int LevelGuard::getIndex(float weight){
    float sum=0;
    int i=0;
    for(;sum<weight;++i){
        sum+=Levels[i].weight;
    }
    return i-1;
}
struct Level LevelGuard::nextLevel(){
    float seed=randgen.randrange(0,netWeight());
    int index=getIndex(seed);
    if(verbose){
        std::cout<<"Generated seed "<<seed<<" which corresponds to index "<<index<<" with level id "<<Levels[index].level_id<<std::endl;
    }
    return Levels[index];
}