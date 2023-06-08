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
    virtual void Update(T) = 0;
    ~Observer() {}
};

/* -------------------------------------------------------------------------- */
/*                                   Subject                                  */
/* -------------------------------------------------------------------------- */
template <class T>
class Subject
{
private:
    std::list<Observer<T> *> _observers;

protected:
public:
    ~Subject() {}
    virtual void Attach(Observer<T> *o)
    {
        _observers.push_back(o);
    }
    virtual void Detach(Observer<T> *o)
    {
        _observers.remove(o);
    }
    virtual void Notify(T newstate)
    {
        typename std::list<Observer<T> *>::iterator i;
        for (i = _observers.begin(); i != _observers.end(); ++i)
        {
            (*i)->Update(newstate);
        }
    }
};

/* -------------------------------------------------------------------------- */
/*                              Concrete Subject                              */
/* -------------------------------------------------------------------------- */
template <class T>
class BingoCaller : public Subject<T>
{
private:
public:
    BingoCaller()
    {
    }
    ~BingoCaller() {}
    void ChooseNewWord(T inword)
    {
        std::cout << "I am the caller and i just got the word " << inword << std::endl;
        this->Notify(inword); // Call all observers
    }
};

/* -------------------------------------------------------------------------- */
/*                             Concreate Observers                            */
/* -------------------------------------------------------------------------- */
template <class T>
class BingoPlayer : public Observer<T>
{
private:
    T currentword;
    std::string name;

public:
    BingoPlayer(std::string inname)
    {
        name = inname;
    }
    ~BingoPlayer()
    {
    }
    void Update(T newstate)
    {
        currentword = newstate;
        std::cout << "I am a bingo player (" << name << ") and got a new word " << currentword << std::endl;
    }
};

template <class T>
class OldBingoPlayer : public Observer<T>
{
private:
    T currentword;
    std::string name;

public:
    OldBingoPlayer(std::string inname)
    {
        name = inname;
    }
    ~OldBingoPlayer() {}
    void Update(T newstate)
    {
        currentword = newstate;
        std::cout << "I am an old bingo player (" << name << ") and got a new word " << currentword << std::endl;
    }
};

/* -------------------------------------------------------------------------- */
/*                                   Client                                   */
/* -------------------------------------------------------------------------- */

template <class T>
void callObserver(T arr[])
{
    /* --------- Removed some from the previous version for readability --------- */

    /* ---------------------------- Make the objects ---------------------------- */
    std::unique_ptr<BingoCaller<T>> caller = std::make_unique<BingoCaller<T>>();
    std::unique_ptr<BingoCaller<T>> caller2 = std::make_unique<BingoCaller<T>>();
    std::unique_ptr<BingoPlayer<T>> bob = std::make_unique<BingoPlayer<T>>("Bob");
    std::unique_ptr<BingoPlayer<T>> jack = std::make_unique<BingoPlayer<T>>("Jack");
    std::unique_ptr<OldBingoPlayer<T>> steve = std::make_unique<OldBingoPlayer<T>>("steve");

    /* -------------------------- Attach the observers -------------------------- */
    caller->Attach(bob.get());
    caller->Attach(jack.get());
    caller->Attach(steve.get());
    caller2->Attach(bob.get());

    /* ------------------------------ Do some calls ----------------------------- */

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Caller Choosing new" << std::endl;
    caller->ChooseNewWord(arr[0]);
    std::cout << "Word chosen" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Caller2 Choosing new" << std::endl;
    caller2->ChooseNewWord(arr[1]);
    std::cout << "Word chosen" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;


    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Caller Choosing new" << std::endl;
    caller->ChooseNewWord(arr[2]);
    std::cout << "Word chosen" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;

    std::cout << "Detaching bob from caller 1" << std::endl;
    caller->Detach(bob.get());

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Caller Choosing new" << std::endl;
    caller->ChooseNewWord(arr[3]);
    std::cout << "Word chosen" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
}

void docExample(){
    std::unique_ptr<BingoCaller<std::string>> caller = std::make_unique<BingoCaller<std::string>>();
    std::unique_ptr<BingoCaller<std::string>> caller2 = std::make_unique<BingoCaller<std::string>>();
    std::unique_ptr<BingoPlayer<std::string>> jack = std::make_unique<BingoPlayer<std::string>>("Jack");
    std::unique_ptr<BingoPlayer<std::string>> bob = std::make_unique<BingoPlayer<std::string>>("Bob");
    caller->Attach(bob.get());
    caller->Attach(jack.get());
    caller2->Attach(bob.get());

    caller->ChooseNewWord("Shelf");
    caller2->ChooseNewWord("Drawer");
    
}

int main()
{
    /* ----------------------------- Report Example ----------------------------- */
    docExample();

    /* ----------------------------- Complex Example ---------------------------- */

    // std::cout << "Calling with strings" << std::endl;
    // std::cout << "--------------------------------------------" << std::endl;
    // std::string arr[] = {"Shelf", "Drawer","Cupboard","Fridge"};
    // callObserver<std::string>(arr);

    // This still works but makes it alot less readable
    // std::cout<<"Calling with ints"<<std::endl;
    // std::cout<<"--------------------------------------------"<<std::endl;
    // int intarr[]={1,4,2,3};
    // callObserver<int>(intarr);

    return 0;
}
