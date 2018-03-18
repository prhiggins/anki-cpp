//
// Created by Zippo Xie on 2/18/18.
//

#include "card.h"

card::card(time_t created_time, int learning_stage, double ease,
           string front, string back, time_t due_time, double interval,
           string id, char status) {
    created_time_ = created_time;
    learning_stage_ = learning_stage;
    ease_ = ease;
    front_ = front;
    back_ = back;
    due_ = due_time;
    interval_ = interval;
    id_ = id;
    status_ = status;
}
bool operator== ( const card &n1, const card &n2) {
    return n1.id_ == n2.id_;
}
ostream &operator<<(ostream &output, const card &A) {

    output << "**************" << endl;
    output << "Id:" << A.id_ << endl;
    output << "Status: " << A.status_ << endl;
    output << "Front:" << A.front_ << endl;
    output << "Back:" << A.back_ << endl;
    output << "Seconds since 1970: " << A.created_time_ << endl;
    output << "Creadted on: " << ctime(&A.created_time_);
    output << "Ease:" << A.ease_ << endl;
    output << "Stage:" << A.learning_stage_ << endl;
    output << "Next due day is on: " << ctime(&A.due_);
    output << "Interval: " << A.interval_ << endl;
    output << "**************" << endl;
    return output;
}
