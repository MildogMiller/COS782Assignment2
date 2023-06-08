#include <iostream>
#include <list>
#include <memory>


/* -------------------------------------------------------------------------- */
/*                                  Observer                                  */
/* -------------------------------------------------------------------------- */
class Observer
{
private:
public:
    virtual void Update() = 0;
    ~Observer(){}
};

/* -------------------------------------------------------------------------- */
/*                                   Subject                                  */
/* -------------------------------------------------------------------------- */
class Subject
{
private:
    std::list<Observer *> _observers;
public:
    ~Subject(){}
    virtual void Attach(Observer* o){
        _observers.push_back(o);
    }
    virtual void Detach(Observer* o){
        _observers.remove(o);
    }
    virtual void Notify(){
        for (std::list<Observer*>::iterator i = _observers.begin(); i != _observers.end(); ++i)
        {
            (*i)->Update();
        }
        
    }
};

/* -------------------------------------------------------------------------- */
/*                              Concrete Subject                              */
/* -------------------------------------------------------------------------- */
class BingoCaller:public Subject{
private:
    std::string currstate;
public:
    std::string getState(){
        return currstate;
    }
    void ChooseNewWord(std::string inword){
        std::cout<<"I am the caller and i just got the word "<<inword<<std::endl;
        currstate=inword;
        Notify();//Call all observers
    }
};



/* -------------------------------------------------------------------------- */
/*                             Concreate Observers                            */
/* -------------------------------------------------------------------------- */
class BingoPlayer:public Observer{
private:
    std::string currentword;
    BingoCaller& state;
    std::string name;
public:
    BingoPlayer(BingoCaller& instate,std::string inname):state(instate){
        name=inname;
    }
    ~BingoPlayer(){

    }
    void Update(){
        currentword=state.getState();
        std::cout<<"I am a bingo player ("<<name<<") and got a new word "<<currentword<<std::endl;
    }
};

class OldBingoPlayer:public Observer{
private:
    std::string currentword;
    BingoCaller& state;
    std::string name;
public:
    OldBingoPlayer(BingoCaller& instate,std::string inname):state(instate){
        name=inname;
    }
    ~OldBingoPlayer(){}
    void Update(){
        currentword=state.getState();
        std::cout<<"I am an old bingo player ("<<name<<") and got a new word "<<currentword<<std::endl;
    }
};


/* -------------------------------------------------------------------------- */
/*                                   Client                                   */
/* -------------------------------------------------------------------------- */



int main()
{
    /* ---------------------------- Make the objects ---------------------------- */
    std::unique_ptr<BingoCaller> caller=std::make_unique<BingoCaller>();
    std::unique_ptr<BingoPlayer> bob=std::make_unique<BingoPlayer>(*caller.get(),"Bob");
    std::unique_ptr<BingoPlayer> jack=std::make_unique<BingoPlayer>(*caller.get(),"Jack");
    std::unique_ptr<OldBingoPlayer> steve=std::make_unique<OldBingoPlayer>(*caller.get(),"steve");
    std::unique_ptr<OldBingoPlayer> tim=std::make_unique<OldBingoPlayer>(*caller.get(),"Tim");

    /* -------------------------- Attach the observers -------------------------- */
    caller->Attach(bob.get());
    caller->Attach(jack.get());
    caller->Attach(steve.get());
    caller->Attach(tim.get());

    /* ------------------------------ Do some calls ----------------------------- */
    
    std::cout<<"--------------------------------------------"<<std::endl;
    std::cout<<"Choosing new word"<<std::endl;
    caller->ChooseNewWord("Lamp");
    std::cout<<"Word chosen"<<std::endl;
    std::cout<<"--------------------------------------------"<<std::endl;


    std::cout<<"--------------------------------------------"<<std::endl;
    std::cout<<"Choosing new word"<<std::endl;
    caller->ChooseNewWord("Pad");
    std::cout<<"Word chosen"<<std::endl;
    std::cout<<"--------------------------------------------"<<std::endl;

    std::cout<<"Detaching bob, lol bye bob"<<std::endl;
    caller->Detach(bob.get());

    std::cout<<"--------------------------------------------"<<std::endl;
    std::cout<<"Choosing new word"<<std::endl;
    caller->ChooseNewWord("Jokes");
    std::cout<<"Word chosen"<<std::endl;
    std::cout<<"--------------------------------------------"<<std::endl;
 
    std::cout<<"--------------------------------------------"<<std::endl;
    std::cout<<"Choosing new word"<<std::endl;
    caller->ChooseNewWord("Emotional damage");
    std::cout<<"Word chosen"<<std::endl;
    std::cout<<"--------------------------------------------"<<std::endl;

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                                   Output                                   */
/* -------------------------------------------------------------------------- */
/*
--------------------------------------------
Choosing new word
I am the caller and i just got the word Lamp
I am a bingo player (Bob) and got a new word Lamp
I am a bingo player (Jack) and got a new word Lamp
I am an old bingo player (steve) and got a new word Lamp
I am an old bingo player (Tim) and got a new word Lamp
Word chosen
--------------------------------------------
--------------------------------------------
Choosing new word
I am the caller and i just got the word Pad
I am a bingo player (Bob) and got a new word Pad
I am a bingo player (Jack) and got a new word Pad
I am an old bingo player (steve) and got a new word Pad
I am an old bingo player (Tim) and got a new word Pad
Word chosen
--------------------------------------------
Detaching bob, lol bye bob
--------------------------------------------
Choosing new word
I am the caller and i just got the word Jokes
I am a bingo player (Jack) and got a new word Jokes
I am an old bingo player (steve) and got a new word Jokes
I am an old bingo player (Tim) and got a new word Jokes
Word chosen
--------------------------------------------
--------------------------------------------
Choosing new word
I am the caller and i just got the word Emotional damage
I am a bingo player (Jack) and got a new word Emotional damage
I am an old bingo player (steve) and got a new word Emotional damage
I am an old bingo player (Tim) and got a new word Emotional damage
Word chosen
--------------------------------------------
*/