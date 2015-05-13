/* Copyright 2015 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * Queue policies.
 */
#ifndef INCLUDE_QUEUE_POLICIES_H
#define INCLUDE_QUEUE_POLICIES_H

#include "queue.h"
#include "consumer.h"
#include "producer.h"

/*
 * The direct notification policy manages a 1-to-1 producer consumer model.
 * When new units are added to the queue the consumer is notified directly, in
 * whatever context (interrupt, deferred, task...) that the queue addition
 * happened.  Similarly, queue removals directly notify the producer.
 */
struct queue_policy_direct {
	struct queue_policy policy;

	struct producer const *producer;
	struct consumer const *consumer;
};

void queue_add_direct(struct queue_policy const *policy, size_t count);
void queue_remove_direct(struct queue_policy const *policy, size_t count);

#define QUEUE_POLICY_DIRECT(PRODUCER, CONSUMER)			\
	((struct queue_policy_direct const) {			\
		.policy = {					\
			.add    = queue_add_direct,		\
			.remove = queue_remove_direct,		\
		},						\
		.producer = &PRODUCER,				\
		.consumer = &CONSUMER,				\
	})

#define QUEUE_DIRECT(SIZE, TYPE, PRODUCER, CONSUMER)			\
	QUEUE(SIZE, TYPE, QUEUE_POLICY_DIRECT(PRODUCER, CONSUMER).policy)

#endif /* INCLUDE_QUEUE_POLICIES_H */
