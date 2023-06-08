#include <iostream>
#include <list>
#include <memory>
#include <type_traits>
#include <functional>

/* -------------------------------------------------------------------------- */
/*                         Some of the failed attempts                        */
/* -------------------------------------------------------------------------- */




/* -------------------------------------------------------------------------- */
/*                                   Subject                                  */
/* -------------------------------------------------------------------------- */
template <class T>
class Subject
{
private:
    typedef std::function<void(T)> func;
    std::list<func> _observers;

protected:
public:
    Subject(){}
    ~Subject() {}
    virtual void Attach(typename void (*)(std::string) o)
    {
        _observers.push_back(o);
    }
    virtual void Detach(typename void (*)(std::string) o)
    {
        _observers.remove(o);
    }
    virtual void Notify(std::string t)
    {
        // typename std::list<func>::iterator i;
        // for (i = _observers.begin(); i != _observers.end(); ++i)
        // {
        //     (*i)(t);
        // }
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
        // std::cout << "I am the caller and i just got the word " << inword << std::endl;
        this->Notify(inword); // Call all observers
    }
};

/* -------------------------------------------------------------------------- */
/*                             Concreate Observers                            */
/* -------------------------------------------------------------------------- */
template <class T>
class BingoPlayer
{
private:
    std::string name;
    T state;
public:
    BingoPlayer(std::string inname)
    {
        name = inname;
    }
    ~BingoPlayer()
    {
    }
    void Update(T curr)
    {
        std::cout << "I am a bingo player (" << name << ") and got a new word " << curr<< std::endl;
    }
};

template <class T>
class OldBingoPlayer
{
private:
    std::string name;
    T state;
public:
    OldBingoPlayer(std::string inname)
    {
        name = inname;
    }
    ~OldBingoPlayer() {}
    void Update(T curr)
    {
        std::cout << "I am a bingo player (" << name << ") and got a new word " << curr<< std::endl;
    }
};

/* -------------------------------------------------------------------------- */
/*                                   Client                                   */
/* -------------------------------------------------------------------------- */

int main()
{
    /* ---------------- Decreased amount of code for readability ---------------- */
    
    std::unique_ptr<BingoCaller<std::string>> caller= std::make_unique<BingoCaller<std::string>>();

    // std::unique_ptr<BingoCaller<std::string,double>> caller2= std::make_unique<BingoCaller<std::string,double>>();
    // std::unique_ptr<BingoPlayer<std::string,int>> bob = std::make_unique<BingoPlayer<std::string,int>>("Bob");
    // std::unique_ptr<BingoPlayer<std::string,int>> steve = std::make_unique<BingoPlayer<std::string,int>>("Steve");

    // caller->Attach(bob.get());
    // //caller2->Attach(bob.get()); <-- this would cause a compile error as types do not match

    // caller->ChooseNewWord("Table",1);
    // caller->ChooseNewWord("Chair",2);
    // caller->ChooseNewWord("Chair",2,3); <-- this would cause a compile error as types do not match

    // std::list<std::function<void(int, int)>> funclist;
    // funclist.push_back(testfunc);
    // typename std::list<std::function<void(int, int)>>::iterator i;
    // for (i = funclist.begin(); i != funclist.end(); ++i)
    // {
    //     (*i)(1, 2);
    // }

    return 0;
}
