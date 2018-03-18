//
// Created by Zippo Xie on 2/18/18.
//

#include "studyService.h"

void studyService::study(card &a_card, performance level, const vector<int>& learning_steps) {
    if(a_card.status_ == 'U' || a_card.status_ == 'L' || level == bad)
        learn_relearn(a_card, level, learning_steps);
    else
        review(a_card, level);
}




void studyService::learn_relearn(card &a_card, performance level, const vector<int>& learning_steps) {
    int size_of_learning_steps = learning_steps.size();
    double new_interval = a_card.interval_;

    if(level == bad || a_card.learning_stage_ > size_of_learning_steps) {
        // Relearn a card or reset it due to the change of configs
        // cout << "First if statement"<< a_card.learning_stage_ << " "<< size_of_learning_steps <<"\n" ;
        a_card.learning_stage_ = 0;
        new_interval = learning_steps.at(a_card.learning_stage_);
        a_card.learning_stage_++;
        if(a_card.status_ != 'U' && a_card.status_ != 'L') {
            a_card.status_ = 'L';
            a_card.ease_ = max((double) 100, (a_card.ease() - 200));
        }
    } else if(a_card.learning_stage_ == size_of_learning_steps) {
        // Relearning process is done, recover interval to max(1day, original_value * 0.5)
        // cout << "2nd if statement"<< a_card.learning_stage_ << " "<< size_of_learning_steps <<"\n" ;
        a_card.interval_ = max(86400.0, new_interval * 0.50);
        new_interval = a_card.interval_;
        a_card.learning_stage_++;
        if(new_interval >= 2592000)
            a_card.status_ = 'M';
        else
            a_card.status_ = 'Y';

    } else {
        // cout << "Last if statement"<< a_card.learning_stage_ << " "<< size_of_learning_steps <<"\n" ;
        // next interval in the (re)learning steps
        if(a_card.status_ == 'U' && a_card.status_ != 'L')
            a_card.status_ = 'L';
        new_interval = learning_steps.at(a_card.learning_stage_);
        a_card.learning_stage_++;
    }

    a_card.due_ = static_cast<time_t>((double)time(0) + new_interval);
}

// helper functon for review
double studyService::next_interval(card &a_card, performance level, const vector<int>& learning_steps = {}) {
    double interval = a_card.interval_;
    double ease = a_card.ease_;
    double d = (time(0) - a_card.created_time_)/60;
    double hard_interval = max((interval + 86400), (interval + d/4));
    if(level == hard) {return hard_interval;}

    double reease = ease/1000;
    double good_interval = max((hard_interval + 86400), ((interval + d/2)*reease));
    if(level == good) {return good_interval;}

    double easey_interval = max((good_interval + 86400), ((interval + d)*reease));
    return easey_interval;
}

void studyService::review(card &a_card, performance level) {
    if(level == hard) a_card.ease_ = max((double)100, (a_card.ease() - 100));
    else if(level == easy) a_card.ease_ = max((double)1500, (a_card.ease() + 200));

    double new_interval = next_interval(a_card, level);
    if(new_interval >= 2592000)
        a_card.status_ = 'M';
    a_card.interval_ = new_interval;
    a_card.due_ = static_cast<time_t>((double)time(0) + new_interval);
}