/**
 *Cpp file of class Game
 *Author Alexey Titov
 *Version 3.0
 *Date 10.2018
**/
//library
#include "Game.h"
//defines
const string str1 = "How many players?";  
const string str2 = "How many cards?";
//Empty constructor
Game::Game():num_cards(0),num_players(0){}
//Constructor
Game::Game(int _num_cards, int _num_players){
    num_cards=_num_cards;
	num_players=_num_players;
}
//Copy constructor 
Game::Game(const Game& g){
    num_cards=g.num_cards;
	num_players=g.num_players;
    players.insert(players.begin(), g.players.begin(), g.players.end());   
}
//Overloading for '=' operator for Game type!
const Game& Game::operator=(const Game& other){
    num_cards=other.num_cards;
	num_players=other.num_players;
    players.clear();
    players.insert(players.begin(), other.players.begin(), other.players.end());
    return *this; 
}
//Destructor
Game::~Game(){
    players.clear();
}
//The function returns the number of cards
void Game::num_Cards(){
    cout << str2 << endl;
    cin>>num_cards;
    if(num_cards<1)
        num_cards=0;
}
//The function returns the number of players
void Game::num_Players(){
    cout << str1 << endl;
    cin>>num_players;
    if(num_players<1)
        num_players=0;
}
//The function returns the name of the player
string Game::name_Player(int i)const{
    string name;
    cout<<"player number "<<i<<" name?"<<endl;
    cin>>name;
    return name;
}
//The function retruns index of player
int Game::index_Player(int index, int course) const{
    index=(index+course)%num_players;
    return index;   
}
//The function does not use Player::play(Card&)
void Game::NoUsePlayStart(){
    bool flag=false;                //flag to end the game
    int course=1;                   //direction, 1 - clockwise; -1 - counterclock-wise
    int index=0;                    //index of player
    int option=0;                   //option according to the cards
    //initialization number of players and cards
    num_Players();
    num_Cards();
    //initialization players
    if (num_players && num_cards){
        for(int i=0; i!=num_players;++i)
            players.push_back(Player(name_Player(i+1),num_cards));
        flag=true;
    }
    Card FirstCard(generate_card());
    while(flag){
        cout<<"current: "<<FirstCard<<endl;
        players.at(index).your_Turn();
        option=players.at(index).choice(FirstCard);
        switch(option){
	        case 1:         //there is a winner
		        flag=false;
                cout<<players.at(index).getName()<<" wins!";
		        break;
	        case 2:         //changing the direction of the game
		        course*=-1;
                index=index_Player(index, course);
		        break;
	        case 3:         //next turn
                index=index_Player(index, course);
		        break;
	        case 4:         //stop, the next player misses the turn
                index=index_Player(index, course);
                index=index_Player(index, course);
		        break;
	        default:        //error
                flag=true;
	    }
    }
}
//The function use Player::play(Card&)
void Game::UsePlayStart(){
    bool flag=true;                 //flag to end the game
    int course=1;                   //direction, 1 - clockwise; -1 - counterclock-wise
    int index=0;                    //index of player
    bool _play=true;
    //initialization number of players and cards
    num_Players();
    num_Cards();
    //initialization players
    if (num_players && num_cards){
        for(int i=0; i!=num_players;++i)
            players.push_back(Player(name_Player(i+1),num_cards));
        flag=true;
    }
    Card FirstCard(generate_card());
    while(flag){
        cout<<"current: "<<FirstCard<<endl;
        players.at(index).your_Turn();
        _play=players.at(index).play(FirstCard);
        if (_play){                                         //the player threw the card
            if (players.at(index).getCards()==0){           //the player has not cards
                flag=false;
                cout<<players.at(index).getName()<<" wins!";
            }else{                                          //the player has several cards
                switch(FirstCard.get_sign()){
                    case CD:                                //changing the direction of the game
                        course*=-1;
                        index=index_Player(index, course);
                        break;
                    case STOP:                              //stop, the next player misses the turn
                        index=index_Player(index, course);
                        index=index_Player(index, course);
                        break;
                    default:                                //number and taki, the turn of the next player
                        index=index_Player(index, course);  
                }
            }
        }else                                               //the player took the card
           index=index_Player(index, course); 
    }
}
//The function creates a game
void Game::start(){
    //NoUsePlayStart();     //use TAKI and PLUS
    UsePlayStart();
}