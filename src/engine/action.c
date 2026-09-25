#include "engine/action.h"

// ptr?
action_t *aq_pop(action_queue_t *queue)
{
	if (queue->index <= 0) {
		return nullptr;
	}

	return &queue->queue[queue->index--];
}

void aq_push(action_queue_t *action, action_t action)
{

}


void process_action(action_queue_t *queue)
{
}
