#ifndef LIGHTCONFIG_H
#define LIGHTCONFIG_H

class lightConfig
{
public:
    float color[4];
    float position[4];
    float config[4];
    bool active;
    lightConfig(){
        active=false;
        color[0]=color[1]=color[2]=0.0f;
        color[3]=1.0f;
        position[0]=position[1]=position[2]=0.0f;
        position[3]=1.0f;
        config[0]=config[1]=config[2]=0.0f;
        config[3]=1.0f;
    }
    lightConfig(bool act){
        active=act;
        color[0]=color[1]=color[2]=0.0f;
        color[3]=1.0f;
        position[0]=position[1]=position[2]=0.0f;
        position[3]=1.0f;
        config[0]=config[1]=config[2]=0.0f;
        config[3]=1.0f;
    }
};

#endif // LIGHTCONFIG_H
