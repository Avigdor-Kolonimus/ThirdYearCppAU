/**
 *Cpp file of class  Player
 *Author Alexey Titov
 *Version 3.0
 *Date 10.2018
**/
//library
#include "Player.h"
//define
const string str3 = ", your turn -\nYour cards:";  
//Destructor
Player::~Player(){
    cards.clear();
}
//Empty constructor
Player::Player():name("Default"),num_of_cards(0){}
//Constructor 1
Player::Player(string _name, int _num_of_cards){
    name=_name;			
	num_of_cards=_num_of_cards;
    while(_num_of_cards){
        cards.push_back(generate_card());
        _num_of_cards--;
    }
}
//Constructor 2
Player::Player(char* _name, int _num_of_cards){
    name=string(_name);			
	num_of_cards=_num_of_cards;
    while(_num_of_cards){
        cards.push_back(generate_card());
        _num_of_cards--;
    }
}
//Copy constructor 
Player::Player(const Player& p){
    name=p.name;			
	num_of_cards=p.num_of_cards;
    cards.insert(cards.begin(), p.cards.begin(), p.cards.end());  
}
//Overloading for '=' operator for player type
const Player& Player::operator=(const Player& other){
    name=other.name;			
	num_of_cards=other.num_of_cards;
    cards.clear();
    cards.insert(cards.begin(), other.cards.begin(), other.cards.end());
    return *this;
}
//The function prints cards of the player 
void Player::your_Turn()const{
    cout<< name << str3;
    for(int i=0; i!=num_of_cards; ++i)
        cout<<" ("<<i+1<<")"<<cards.at(i);
    cout<<endl;
}
//The function return name of player
string Player::getName()const{
    return name;
}
//The function return size of vector<Card> cards
int Player::getCards()const{
    return num_of_cards;
}
//The function allows the player to lay out additional cards 
int Player::taki_card(Card& currentCard){
    int n=0;
    bool flag=true;
    while(flag){
        cin>>n;
        if (n<=0 || n>num_of_cards){                    //next turn
            n=3;
            if (currentCard.get_sign()==10){            //plus card
                cards.push_back(generate_card());
                num_of_cards++;
            }else
                if (currentCard.get_sign()==11)         //stop card
                    n=4;
                else
                  if (currentCard.get_sign()==12)       //CD card
                    n=2;  
            flag=false;
        }else{
            if (!cards.at(n-1).is_leggal(currentCard))  //card is illegal
                cout<<"You can't put "<<cards.at(n-1)<<" on "<<currentCard<<endl;
            else{
                //new color, stop taki action
                if (currentCard.get_color()!=cards.at(n-1).get_color() && cards.at(n-1).get_sign()!=13){
                    currentCard=cards.at(n-1);
                    cards.erase(cards.begin() + (n-1));
                    --num_of_cards;
                    n=3;
                    flag=false;
                }else{      //taki action
                    currentCard=cards.at(n-1);
                    cards.erase(cards.begin() + (n-1));
                    --num_of_cards;
                    if (currentCard.get_sign()==13){
                        if (num_of_cards==0)
                            n=1;
                        else{
                            cout<<"current: "<<currentCard<<endl;
                            your_Turn();
                            n=taki_card(currentCard);
                        }
		                flag=false;
                    }
                }
            }
        }
    }
    if (num_of_cards==0)            //win
        n=1;
    return n;
}
//The function returns option for game
int Player::choice(Card& currentCard){
    int n=0;
    bool flag=true;
    while(flag){
        cin>>n;
        if (n<=0 || n>num_of_cards){                    //take a card from the deck
            cards.push_back(generate_card());
            num_of_cards++;
            n=3;
            flag=false;
        }else{
            if (!cards.at(n-1).is_leggal(currentCard))  //card is illegal
                cout<<"You can't put "<<cards.at(n-1)<<" on "<<currentCard<<endl;
            else{
                currentCard=cards.at(n-1);
                cards.erase(cards.begin() + (n-1));
                --num_of_cards;
                switch (currentCard.get_sign()){
	                //plus, the player must put one more card
                    case PLUS:
                        if (num_of_cards==0)
                            flag=false;
                        else{
                            cout<<"current: "<<currentCard<<endl;
                            your_Turn();
                        }
		                break;
                    //stop, the next player misses the turn
                    case STOP:
		                n=4;
                        flag=false;
		                break;
	                //changing the direction of the game
                    case CD:
		                n=2;
                        flag=false;
		                break;
	                //TAKI, it is possible to lay out additional cards
                    case TAKI:
                        if (num_of_cards==0)
                            n=1;
                        else{
                            cout<<"current: "<<currentCard<<endl;
                            your_Turn();
                            n=taki_card(currentCard);
                        }
		                flag=false;
		                break;
                    //next turn
	                default:
                        n=3;
                        flag=false;
	            }
            }
        }
    }
    if (num_of_cards==0)        //win
        n=1;
    return n;
}
//The function is responsible for the turn of the game, 
//returns true if the player threw a card and false if the player took a card
bool Player::play(Card& currentCard){
    int n=0;
    bool flag=true, _play=true;
    while(flag){
        cin>>n;
        if (n<=0 || n>num_of_cards){                    //take a card from the deck
            cards.push_back(generate_card());
            num_of_cards++;
            flag=false;
            _play=false;
        }else{
            if (!cards.at(n-1).is_leggal(currentCard))  //card is illegal
                cout<<"You can't put "<<cards.at(n-1)<<" on "<<currentCard<<endl;
            else{
                currentCard=cards.at(n-1);
                cards.erase(cards.begin() + (n-1));
                --num_of_cards;
                switch (currentCard.get_sign()){
	                //plus, the player must put one more card
                    case PLUS:
                        if (num_of_cards==0)
                            flag=false;
                        else{
                            cout<<"current: "<<currentCard<<endl;
                            your_Turn();
                        }
		                break;
                    //next turn
	                default:
                        flag=false;
                }
            }
        }
    }
    return _play;
}