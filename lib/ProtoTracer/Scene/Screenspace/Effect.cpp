#include "Effect.h"

Effect::Effect(){}

void Effect::SetRatio(float ratio){
    this->ratio = Mathematics::Constrain(ratio, 0.0f, 1.0f);
}