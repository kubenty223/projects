#include "Score.h"

Score* Score::score_ = nullptr;;

Score* Score::GetInstance()
{
    if (score_ == nullptr) {
        score_ = new Score();
    }
    return score_;
}