/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#include "task_dispatcher.h"

#include <utility>

namespace sirius::core::tasks
{

	CTaskDispatcher::~CTaskDispatcher() noexcept = default;

	bool CTaskDispatcher::Dispatch(ETaskQueue QueueId, FTask Task)
	{
		return Queue(QueueId).Dispatch(std::move(Task));
	}

	std::size_t CTaskDispatcher::ExecutePending(ETaskQueue QueueId, std::size_t MaximumTasks)
	{
		return Queue(QueueId).ExecutePending(MaximumTasks);
	}

	std::size_t CTaskDispatcher::PendingCount(ETaskQueue QueueId) const noexcept
	{
		return Queue(QueueId).PendingCount();
	}

	void CTaskDispatcher::Clear(ETaskQueue QueueId) noexcept
	{
		Queue(QueueId).Clear();
	}

	CTaskQueue &CTaskDispatcher::Queue(ETaskQueue QueueId) noexcept
	{
		switch(QueueId)
		{
		case ETaskQueue::Main:
			return m_MainQueue;
		case ETaskQueue::Background:
			return m_BackgroundQueue;
		}

		return m_MainQueue;
	}

	const CTaskQueue &CTaskDispatcher::Queue(ETaskQueue QueueId) const noexcept
	{
		switch(QueueId)
		{
		case ETaskQueue::Main:
			return m_MainQueue;
		case ETaskQueue::Background:
			return m_BackgroundQueue;
		}

		return m_MainQueue;
	}

} // namespace sirius::core::tasks

