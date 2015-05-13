/* Copyright 2015 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * Consumer interface
 *
 * The consumer abstraction allows for code that wants to be able to read from
 * a queue, and be notified of new additions to the queue, or of requests to
 * flush (empty) the queue.
 */
#ifndef INCLUDE_CONSUMER_H
#define INCLUDE_CONSUMER_H

#include "queue.h"

#include <stddef.h>
#include <stdint.h>

struct consumer;
struct producer;

struct consumer_ops {
	/*
	 * Inform the consumer that count units were written to the queue.
	 * This gives it the oportunity to read additional units from the queue
	 * or to wake up a task or interrupt to do the same.  If a consumer has
	 * no need for this information it can set this to NULL.
	 */
	void (*written)(struct consumer const *consumer, size_t count);

	/*
	 * Flush (read) everything from the associated queue.  This call blocks
	 * until the consumer has flushed the queue.
	 */
	void (*flush)(struct consumer const *consumer);
};

struct consumer {
	/*
	 * A consumer references the queue that it is reading from.
	 */
	struct queue const *queue;

	struct consumer_ops const *ops;
};

#endif /* INCLUDE_CONSUMER_H */
