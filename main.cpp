
#include "main.h"


int main() {
    // testing loading userinfo from local file
    if(!jobPool::is_logined()) {
        cout << "No saved username/password found:\n";
        string username, password;
        cout << "enter username: ";
        getline(cin, username);
        cout << "enter password: ";
        getline(cin, password);
        if(jobPool::set_user_credentials_to(username, password))
            cout << "Entered a user's credentials\n"; 
    }
    jobPool test_controller(jobPool::get_credential().at(0),  jobPool::get_credential().at(1));
    
    sleep(1);

    // test jobPool
    cout << "Logined!" << endl;
    cout << test_controller;

    // test modification of config
    cout << "Testing modification of config:\n";
    if(test_controller.modify_config(max_new_setting, 60, -1, {})) {
        cout << "Succeed!\n";
    } else cout << "Cannot modify config\n";

    if(test_controller.modify_config(max_review_setting, -1, 200, {})) {
        cout << "Succeed!\n";
    } else cout << "Cannot modify config\n";

    if(test_controller.modify_config(learning_steps_setting, -1, -1, {10})) {
        cout << "Succeed!\n";
    } else cout << "Cannot modify config\n";

    cout << test_controller;

    sleep(1);

    // test adding new card
    cout << "Testing adding cards:\n";
    cout << "Enter the front: ";
    string front, back;
    getline(cin, front);
    cout << "Enter the back: ";
    getline(cin, back);
    test_controller.add_new_card(front, back);
    cout << "Added" << endl;
    cout << test_controller;

    sleep(1);

    // test looking up that card
    cout << "Testing looking up the card just added:";
    vector<card> target = test_controller.look_up_cards(front, back);
    if(target.size() != 0) {
        cout << "Found! Here is the result:\n";
        for(auto it = target.begin(); it != target.end(); ++it)
            cout << *it << endl;
    }

    sleep(1);

    // test get the next card
    cout << "Testing getting the next card:\n";
    card* top_card = test_controller.get_next_card();
    if(top_card == nullptr) cout << "No card is availiable for now.\n";
    else {
        cout << "The top card is:" << *top_card;
    }

    sleep(1);

    // test study a card
    cout << "Testing studying cards:\n";
    srand(time(0));
    while(top_card != nullptr) {
        int rngs = rand() % 4;
        cout << "Performance is[1:bad; 2:hard; 3:good; 4:easy] " << rngs << endl;
        test_controller.study(*top_card, (performance)rngs);
        cout << "Studied!\n";
        cout << *top_card;
        top_card = test_controller.get_next_card();
    }

    sleep(1);
    
    // test change the user
    // When next time you run the program
    // The user will be "New testing username"
    // So, don't forget to run 'make clean' before next time running
    cout << "Changing user now ...\n";
    string old_credentials1 = jobPool::get_credential().at(0);
    string old_credentials2 = jobPool::get_credential().at(1);
    test_controller.change_to_another_user("New testing username", "New testing password");
    cout << test_controller;
    test_controller.change_to_another_user(old_credentials1, old_credentials2);
    cout << "Switched back!\n";
    cout << test_controller;

    
    // // test deletion
    // cout << "Testing deleting the card just added:\n";
    // vector<card> target = test_controller.look_up_cards(front, back);
    // if(target.size() != 0) {
    //     cout << "Trying to delete ->" << target.front();
    //     if(test_controller.delete_a_card(target.front()))
    //         cout << "Deleted" << endl;
    //     else
    //         cout << "Deletion failed" << endl;
    // } else {cout << "Cannot find such a card!" << endl;}
    

    return 0;

}