/* (c) Sirius Client contributors. See licence.txt in the root of the distribution for more information. */
#ifndef SIRIUS_CORE_TASKS_TASK_H
#define SIRIUS_CORE_TASKS_TASK_H

#include <functional>

namespace sirius::core::tasks
{

	using FTask = std::function<void()>;

	enum class ETaskQueue
	{
		Main,
		Background,
	};

} // namespace sirius::core::tasks

#endif
