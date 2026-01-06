#include "engine/trainer.h"

void trainer_init(struct trainer_t *trainer)
{
	if (trainer == NULL) {
		PRINT_ERROR("trainer cannot be NULL");
	}

	trainer->advance = &trainer_advance;

	trainer->load     = &trainer_load;
	trainer->unload   = &trainer_unload;
	trainer->activate = &trainer_activate;
}

void trainer_advance(struct trainer_t *trainer, struct rng_t *rng)
{
	if (trainer->type == TRAINER_TYPE_STATIC || trainer->status != TRAINER_STATUS_ACTIVE) {
		return;
	}

	if (trainer->timer > 0) {
		trainer->timer--;
	}

	if (trainer->timer == 0) {

		if (trainer->type == TRAINER_TYPE_SPINNER) {
			trainer_new_timer(trainer, rng);
			trainer_new_dir(trainer, rng);
		} else if (trainer->delay == TRAINER_TYPE_SPINNER_DEAF) {
			trainer_new_dir(trainer, rng);
			trainer->delay--;
		} else {
			if (trainer->delay == 0) {
				trainer_new_timer(trainer, rng);
				trainer->timer--;
				trainer->delay = trainer->type;
			} else {
				trainer->delay--;
			}
		}
	}
}

void trainer_load(struct trainer_t *trainer, struct rng_t *rng)
{
	if (trainer->status != TRAINER_STATUS_LOADED) {
		return;
	}

	trainer->status = TRAINER_STATUS_LOADED;
	trainer_new_timer(trainer, rng);
}

void trainer_activate(struct trainer_t *trainer)
{

	// Only activate trainers that are already loaded
	if (trainer->status != TRAINER_STATUS_LOADED) {
		return;
	}

	trainer->delay = trainer->type;

	trainer->status = TRAINER_STATUS_ACTIVE;

	trainer->timer += trainer->extra_adv;
}

void trainer_unload(struct trainer_t *trainer)
{
	trainer->status = TRAINER_STATUS_UNLOADED;
}

void trainer_new_timer(struct trainer_t *trainer, struct rng_t *rng)
{
	trainer->timer = TRAINER_TIMERS[rng->next_rand(rng, 4)];
}

void trainer_new_dir(struct trainer_t *trainer, struct rng_t *rng)
{
	trainer->dir = trainer->dirs[rng->next_rand(rng, trainer->dirs_amt)];
}
