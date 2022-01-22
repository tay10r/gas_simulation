#pragma once

#include <memory>
#include <vector>

template<typename Item>
class History final
{
public:
  History(Item* item = new Item()) { m_snapshots.emplace_back(item); }

  void undo()
  {
    if (m_current > 0)
      m_current--;
  }

  void redo()
  {
    if ((m_current + 1) < m_snapshots.size())
      m_current++;
  }

  void snapshot()
  {
    m_current++;

    m_snapshots.erase(std::next(m_snapshots.begin(), m_current), m_snapshots.end());

    m_snapshots.emplace_back(new Item(*m_snapshots.back()));
  }

  Item& getCurrent() { return *m_snapshots[m_current].get(); }

  const Item& getCurrent() const { return *m_snapshots[m_current].get(); }

private:
  std::vector<std::shared_ptr<Item>> m_snapshots;

  size_t m_current = 0;
};
