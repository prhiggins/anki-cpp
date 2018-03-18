//
// Created by Zippo Xie on 2/18/18.
//

#ifndef CARD_ANKI_CARD_H
#define CARD_ANKI_CARD_H

#include <string>
#include <time.h>
#include <sstream>
#include <iostream>
using namespace std;


class card {
public:
    friend class studyService;
    card(time_t created_time, int learning_stage, double ease, string front, string back, time_t due_time, double interval, string id, char status);

    friend bool operator== ( const card &n1, const card &n2);
    friend ostream &operator<<(ostream &output, const card &A);

    time_t created_time() const{return created_time_;}
    int learning_stage() const{return learning_stage_;}
    double ease() const{return ease_;}
    string front() const{return front_;}
    string back() const{return back_;}
    time_t due() const{return due_;}
    double interval() const{return interval_;}
    string id() const{return id_;}
    char status() const{return status_;}

private:
    string front_, back_, id_;
    time_t created_time_, due_;;
    char status_;
    // 'U':Unseen; 'L':(Re)Learning; 'Y':Young card, with interval less than 1 month;
    // 'M':Mature card with interval longer than 1 month;

    int learning_stage_;//it is used to determine next interval when learning or relearning a card
    // It depends on user's setting on learning steps

    double ease_, interval_;
    // ease: a unit that measures users' command on this card
    // interval: time interval to next review


};


#endif //CARD_ANKI_CARD_H
