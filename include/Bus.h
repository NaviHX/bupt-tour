#ifndef __BUS_H__
#define __BUS_H__

#include <vector>
#include <string>

class Bus
{
private:
    int from;
    int to;
    std::string name;

public:
    Bus(int f, int t, const std::string &n) : from(f), to(t), name(n) {}

    virtual int getNearestTime() = 0;
    int getFrom() const { return from; }
    int getTo() const { return to; }
    const std::string &getName() const { return name; }
    bool check(int f,int t);
};

class FixedBus : public Bus
{
private:
    std::vector<int> time;

public:
    FixedBus(int f, int t, const std::string &n, std::vector<int> &v);
    virtual int getNearestTime() override;
};

class RepeatBus : public Bus
{
private:
    int interval;

public:
    RepeatBus(int f, int t, const std::string &n, int interv);
    virtual int getNearestTime() override;
};

#endif
