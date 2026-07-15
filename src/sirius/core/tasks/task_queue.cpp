/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "task_queue.h"

#include <utility>

namespace sirius::core::tasks
{

	CTaskQueue::~CTaskQueue() noexcept = default;

	bool CTaskQueue::Dispatch(FTask Task)
	{
		if(!Task)
		{
			return false;
		}

		m_Tasks.push_back(std::move(Task));
		return true;
	}

	std::size_t CTaskQueue::ExecutePending(std::size_t MaximumTasks)
	{
		std::size_t ExecutedTasks = 0;

		while(ExecutedTasks < MaximumTasks && !m_Tasks.empty())
		{
			FTask Task = std::move(m_Tasks.front());
			m_Tasks.pop_front();

			Task();
			++ExecutedTasks;
		}

		return ExecutedTasks;
	}

	std::size_t CTaskQueue::PendingCount() const noexcept
	{
		return m_Tasks.size();
	}

	void CTaskQueue::Clear() noexcept
	{
		m_Tasks.clear();
	}

} // namespace sirius::core::tasks
