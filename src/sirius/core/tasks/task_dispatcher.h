/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_TASKS_TASK_DISPATCHER_H
#define SIRIUS_CORE_TASKS_TASK_DISPATCHER_H

#include "task.h"
#include "task_queue.h"

#include <cstddef>

namespace sirius::core::tasks
{

	class CTaskDispatcher final
	{
	public:
		CTaskDispatcher() = default;
		~CTaskDispatcher() noexcept;

		CTaskDispatcher(const CTaskDispatcher &Other) = delete;
		CTaskDispatcher &operator=(const CTaskDispatcher &Other) = delete;
		CTaskDispatcher(CTaskDispatcher &&Other) = delete;
		CTaskDispatcher &operator=(CTaskDispatcher &&Other) = delete;

		bool Dispatch(ETaskQueue Queue, FTask Task);
		std::size_t ExecutePending(ETaskQueue Queue, std::size_t MaximumTasks);
		std::size_t PendingCount(ETaskQueue Queue) const noexcept;
		void Clear(ETaskQueue Queue) noexcept;

	private:
		CTaskQueue &Queue(ETaskQueue Queue) noexcept;
		const CTaskQueue &Queue(ETaskQueue Queue) const noexcept;

		CTaskQueue m_MainQueue;
		CTaskQueue m_BackgroundQueue;
	};

} // namespace sirius::core::tasks

#endif
