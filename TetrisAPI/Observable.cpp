#include "Observable.h"
using namespace TetrisAPI;

void Observable::Register(const std::weak_ptr<IObserver>& observer)
{
    m_observers.emplace_back(observer);
}

template <typename T, typename U>
bool equals(const std::weak_ptr<T>& t, const std::weak_ptr<U>& u)
{
    return !t.owner_before(u) && !u.owner_before(t);
}

void Observable::Remove(const std::weak_ptr<IObserver>& observer)
{
    m_observers.erase(
        std::remove_if(
            m_observers.begin(),
            m_observers.end(),
            [&](const std::weak_ptr<IObserver>& registeredObserver) {
                return equals(observer, registeredObserver);
            }),
        m_observers.end());
}

void Observable::NotifyAll(uint16_t numLines)
{
    for (auto it = m_observers.begin(); it != m_observers.end();)
    {
        if (auto sp = it->lock())
        {
            sp->OnLinesCleared(numLines);
            ++it;
        }
        else
        {
            it = m_observers.erase(it);
        }
    }
}
