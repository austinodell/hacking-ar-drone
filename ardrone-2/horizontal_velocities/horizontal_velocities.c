#include "../video/video.h"
#include "../video/blocksum.h"
#include "../util/util.h"
#include "horizontal_velocities.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct vid_struct vid;

struct img_struct* img_old;
struct img_struct* img_new;

/** these are protected by mutex */

unsigned long seqNum;
double xv, yv, dt;

/** width of a pixel in meters at 1 m height */
#define CAM_HEIGHT_SCALE_FACTOR 0.005

pthread_t horizontal_velocities_thread;
pthread_mutex_t velocity_access_mutex = PTHREAD_MUTEX_INITIALIZER;

unsigned char writeImagesToDisk=1;

void *horizontal_velocities_thread_main(void *data) {
	double prevTime = 0.0;

	video_GrabImageGrey(&vid, img_old);
	for (;;) {
		video_GrabImageGrey(&vid, img_new);
//        double start=util_timestamp();

		int dxi;
		int dyi;
		video_blocksum(img_old, img_new, &dyi, &dxi);

		if (dxi != 0 || dyi != 0) {
			//swap buffers
			struct img_struct* tmp = img_new;
			img_new = img_old;
			img_old = tmp;
		}

		double currentTime = util_timestamp();
		pthread_mutex_lock(&velocity_access_mutex);

		dt = currentTime - prevTime;
		xv = dxi / dt;
		yv = dyi / dt;

		prevTime = currentTime;

		seqNum++;

		pthread_mutex_unlock(&velocity_access_mutex);

		if(writeImagesToDisk) {
			char filename[50];
			sprintf (filename,"images/img_%05ld.pgm",seqNum);
			write_pgm(img_new, filename);
		}

//	double endTime=util_timestamp();
//	printf("   Loop took %f ms\n", (endTime-start)*1000);
	}

	video_Close(&vid);

	return 0;
}

int horizontal_velocities_init(struct horizontal_velocities_struct *hv) {
	vid.device = (char*) "/dev/video2";

	printf("Device is %s\n", vid.device);
	vid.w = 320;
	vid.h = 240;
	vid.n_buffers = 1;
	if (video_Init(&vid) != 0)
		exit(-1);

	img_old = video_CreateImage(&vid, 1);
	img_new = video_CreateImage(&vid, 1);

	seqNum = 0;

	xv = 0;
	yv = 0;
	dt = 0;

	int rc = pthread_create(&horizontal_velocities_thread, NULL,
			horizontal_velocities_thread_main, NULL);
	if (rc) {
		printf(
				"ctl_Init: Return code from pthread_create(hor_vel_thread) is %d\n",
				rc);
		return 202;
	}
	return 0;
}

void horizontal_velocities_getSample(struct horizontal_velocities_struct *hv,
		struct att_struct *att) {
	pthread_mutex_lock(&velocity_access_mutex);

	/**     @todo kalman or luenberger for filtering */
	if (dt > 0) {
		hv->xv = xv * att->h * CAM_HEIGHT_SCALE_FACTOR;
		hv->yv = yv * att->h * CAM_HEIGHT_SCALE_FACTOR;
		hv->dt = dt;
	}
	hv->seqNum = seqNum;
	pthread_mutex_unlock(&velocity_access_mutex);
}

void horizontal_velocities_print(struct horizontal_velocities_struct *hv,
		double xpos, double ypos, double h) {
	printf(
			"seq=%ld   xv=%5.1f,yv=%5.1f, dt=%4.1f xpos=%4.1f ypos=%4.1f h=%4.1f\n",
			hv->seqNum, hv->xv, hv->yv, hv->dt * 1000, xpos, ypos, h);
}

