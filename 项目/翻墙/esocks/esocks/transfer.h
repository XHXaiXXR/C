/*
 * transfer.h
 *
 *  Created on: Aug 21, 2016
 *      Author: huoyin
 */

#ifndef TRANSFER_H_
#define TRANSFER_H_

struct TParam {
	int in;
	int out;
	pthread_t bro;
};

void *transfer(void *p);

#endif /* TRANSFER_H_ */

