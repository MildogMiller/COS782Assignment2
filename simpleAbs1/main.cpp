#include <iostream>
#include <list>
#include <memory>


/* -------------------------------------------------------------------------- */
/*                                  Observer                                  */
/* -------------------------------------------------------------------------- */
template <class T>
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
template <class T>
class Subject
{
private:
    std::list<Observer<T>*> _observers;
protected:
public:
    T currstate;
    ~Subject(){}
    virtual void Attach(Observer<T>* o){
        _observers.push_back(o);
    }
    virtual void Detach(Observer<T>* o){
        _observers.remove(o);
    }
    virtual void Notify(){
        typename std::list<Observer<T>*>::iterator i;
        for (i= _observers.begin(); i != _observers.end(); ++i)
        {
            (*i)->Update();
        }
        
    }
    virtual T getState(){
        return currstate;
    }
};

/* -------------------------------------------------------------------------- */
/*                              Concrete Subject                              */
/* -------------------------------------------------------------------------- */
template <class T>
class BingoCaller:public Subject<T>{
private:
public:
    BingoCaller(){

    }
    ~BingoCaller(){}
    void ChooseNewWord(T inword){
        std::cout<<"I am the caller and i just got the word "<<inword<<std::endl;
        this->currstate=inword;
        this->Notify();//Call all observers
    }
};



/* -------------------------------------------------------------------------- */
/*                             Concreate Observers                            */
/* -------------------------------------------------------------------------- */
template <class T>
class BingoPlayer:public Observer<T>{
private:
    T currentword;
    BingoCaller<T>& state;
    std::string name;
public:
    BingoPlayer(BingoCaller<T>& instate,std::string inname):state(instate){
        name=inname;
    }
    ~BingoPlayer(){

    }
    void Update(){
        currentword=state.getState();
        std::cout<<"I am a bingo player ("<<name<<") and got a new word "<<currentword<<std::endl;
    }
};

template <class T>
class OldBingoPlayer:public Observer<T>{
private:
    T currentword;
    BingoCaller<T>& state;
    std::string name;
public:
    OldBingoPlayer(BingoCaller<T>& instate,std::string inname):state(instate){
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


template <class T>
void callObserver(T arr[]){
/* ---------------------------- Make the objects ---------------------------- */
    std::unique_ptr<BingoCaller<T>> caller=std::make_unique<BingoCaller<T>>();
    std::unique_ptr<BingoPlayer<T>> bob=std::make_unique<BingoPlayer<T>>(*caller.get(),"Bob");
    std::unique_ptr<BingoPlayer<T>> jack=std::make_unique<BingoPlayer<T>>(*caller.get(),"Jack");
    std::unique_ptr<OldBingoPlayer<T>> steve=std::make_unique<OldBingoPlayer<T>>(*caller.get(),"steve");
    std::unique_ptr<OldBingoPlayer<T>> tim=std::make_unique<OldBingoPlayer<T>>(*caller.get(),"Tim");

    /* -------------------------- Attach the observers -------------------------- */
    caller->Attach(bob.get());
    caller->Attach(jack.get());
    caller->Attach(steve.get());
    caller->Attach(tim.get());

    /* ------------------------------ Do some calls ----------------------------- */
    
    std::cout<<"--------------------------------------------"<<std::endl;
    std::cout<<"Choosing new"<<std::endl;
    caller->ChooseNewWord(arr[0]);
    std::cout<<"Word chosen"<<std::endl;
    std::cout<<"--------------------------------------------"<<std::endl;


    std::cout<<"--------------------------------------------"<<std::endl;
    std::cout<<"Choosing new"<<std::endl;
    caller->ChooseNewWord(arr[1]);
    std::cout<<"Word chosen"<<std::endl;
    std::cout<<"--------------------------------------------"<<std::endl;

    std::cout<<"Detaching bob, lol bye bob"<<std::endl;
    caller->Detach(bob.get());

    std::cout<<"--------------------------------------------"<<std::endl;
    std::cout<<"Choosing new"<<std::endl;
    caller->ChooseNewWord(arr[2]);
    std::cout<<"Word chosen"<<std::endl;
    std::cout<<"--------------------------------------------"<<std::endl;
 
    std::cout<<"--------------------------------------------"<<std::endl;
    std::cout<<"Choosing new"<<std::endl;
    caller->ChooseNewWord(arr[3]);
    std::cout<<"Word chosen"<<std::endl;
    std::cout<<"--------------------------------------------"<<std::endl;

}

void docExample(){
    /* ------------------------------ With strings ------------------------------ */
    std::unique_ptr<BingoCaller<std::string>> caller=std::make_unique<BingoCaller<std::string>>();
    std::unique_ptr<BingoPlayer<std::string>> bob=std::make_unique<BingoPlayer<std::string>>(*caller.get(),"Bob");
    caller->Attach(bob.get());
    caller->ChooseNewWord("Shelf");

    /* ------------------------------- With ints -------------------------------- */
    std::unique_ptr<BingoCaller<int>> caller2=std::make_unique<BingoCaller<int>>();
    std::unique_ptr<BingoPlayer<int>> jack=std::make_unique<BingoPlayer<int>>(*caller2.get(),"Jack");
    caller2->Attach(jack.get());
    caller2->ChooseNewWord(1);
}


int main()
{
    /* ---------------------------- Code from report ---------------------------- */
    docExample();
    /* -------------------------- More complex examples ------------------------- */
    // std::cout<<"Calling with strings"<<std::endl;
    // std::cout<<"--------------------------------------------"<<std::endl;
    // std::string arr[]={"Shelf","Drawer","Chair","Desk"};
    // callObserver<std::string>(arr);

    // std::cout<<"Calling with ints"<<std::endl;
    // std::cout<<"--------------------------------------------"<<std::endl;
    // int intarr[]={1,4,2,3};
    // callObserver<int>(intarr);

    return 0;
}
