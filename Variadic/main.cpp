#include <iostream>
#include <list>
#include <memory>
#include <type_traits>
#include <cassert>
/* -------------------------------------------------------------------------- */
/*                                  Observer                                  */
/* -------------------------------------------------------------------------- */
template <class... args>
class Observer
{
private:
public:
    virtual void Update(args...) = 0;
    ~Observer() {}
};

/* -------------------------------------------------------------------------- */
/*                                   Subject                                  */
/* -------------------------------------------------------------------------- */
template <class... args>
class Subject
{
private:
    std::list<Observer<args...> *> _observers;

protected:
public:
    Subject() {}
    ~Subject() {}
    virtual void Attach(Observer<args...> *o)
    {
        _observers.push_back(o);
    }
    virtual void Detach(Observer<args...> *o)
    {
        _observers.remove(o);
    }
    virtual void Notify(args... t)
    {
        typename std::list<Observer<args...> *>::iterator i;
        for (i = _observers.begin(); i != _observers.end(); ++i)
        {
            (*i)->Update(t...);
        }
    }
};

/* -------------------------------------------------------------------------- */
/*                              Concrete Subject                              */
/* -------------------------------------------------------------------------- */
template <class... args>
class BingoCaller : public Subject<args...>
{
private:
public:
    BingoCaller()
    {
    }
    ~BingoCaller() {}
    void ChooseNewWord(args... inword)
    {
        // std::cout << "I am the caller and i just got the word " << inword << std::endl;
        this->Notify(inword...); // Call all observers
    }
};

/* -------------------------------------------------------------------------- */
/*                             Concreate Observers                            */
/* -------------------------------------------------------------------------- */
template <class... args>
class BingoPlayer : public Observer<args...>
{
private:
    std::string name;

public:
    BingoPlayer(std::string inname)
    {
        name = inname;
    }
    ~BingoPlayer()
    {
    }
    void Update(std::string curr, int currint)
    {
        std::cout << "I am a bingo player (" << name << ") and got a new word " << curr << " with the point multiplier of " << currint << std::endl;
    }
};

template <class... args>
class OldBingoPlayer : public Observer<args...>
{
private:
    std::string name;

public:
    OldBingoPlayer(std::string inname)
    {
        name = inname;
    }
    ~OldBingoPlayer() {}
    void Update(std::string curr, int currint)
    {
        std::cout << "I am a bingo player (" << name << ") and got a new word " << curr << " with the point multiplier of " << currint << std::endl;
    }
};

/* -------------------------------------------------------------------------- */
/*                                   Client                                   */
/* -------------------------------------------------------------------------- */

int main()
{
    /* ---------------- Decreased amount of code for readability ---------------- */

    std::unique_ptr<BingoCaller<std::string, int>> caller = std::make_unique<BingoCaller<std::string, int>>();
    std::unique_ptr<BingoCaller<std::string, int>> caller2 = std::make_unique<BingoCaller<std::string, int>>();
    std::unique_ptr<BingoPlayer<std::string, int>> bob = std::make_unique<BingoPlayer<std::string, int>>("Bob");
    std::unique_ptr<OldBingoPlayer<std::string, int>> steve = std::make_unique<OldBingoPlayer<std::string, int>>("Steve");

    caller->Attach(bob.get());
    caller2->Attach(bob.get());
    caller->Attach(steve.get());
    // caller2->Attach(bob.get()); <-- this would cause a compile error as types do not match

    caller->ChooseNewWord("Table", 1);
    std::cout<<"-----------"<<std::endl;
    caller2->ChooseNewWord("Chair", 2);
    // caller->ChooseNewWord("Chair",2,3); <-- this would cause a compile error as types do not match

    return 0;
}
