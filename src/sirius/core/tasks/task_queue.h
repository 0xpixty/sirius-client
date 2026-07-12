/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_TASKS_TASK_QUEUE_H
#define SIRIUS_CORE_TASKS_TASK_QUEUE_H

#include "task.h"

#include <cstddef>
#include <deque>

namespace sirius::core::tasks
{

	class CTaskQueue final
	{
	public:
		CTaskQueue() = default;
		~CTaskQueue() noexcept;

		CTaskQueue(const CTaskQueue &Other) = delete;
		CTaskQueue &operator=(const CTaskQueue &Other) = delete;
		CTaskQueue(CTaskQueue &&Other) = delete;
		CTaskQueue &operator=(CTaskQueue &&Other) = delete;

		bool Dispatch(FTask Task);
		std::size_t ExecutePending(std::size_t MaximumTasks);
		std::size_t PendingCount() const noexcept;
		void Clear() noexcept;

	private:
		std::deque<FTask> m_Tasks;
	};

} // namespace sirius::core::tasks

#endif
