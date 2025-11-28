#pragma once

#include "cdx_config.h"
#include "CdxParser.h"
#include "vdecoder.h"
#include "memoryAdapter.h"
#include <stdint.h>
#include <pthread.h>

/* fixed output frame size */
#define MEDIAPLAYER_FRAME_WIDTH   352
#define MEDIAPLAYER_FRAME_HEIGHT  640

/* internal state flags */
#define MEDIAPLAYER_PARSER_ERROR   (1 << 0)
#define MEDIAPLAYER_DECODER_ERROR  (1 << 1)
#define MEDIAPLAYER_DECODE_FINISH  (1 << 2)
#define MEDIAPLAYER_PARSER_EXIT    (1 << 3)
#define MEDIAPLAYER_DECODER_EXIT   (1 << 4)

typedef struct MultiThreadCtx {
    pthread_rwlock_t rwlock;
    int end_of_stream;
    int state;
    int requested_stop;
} MultiThreadCtx;

typedef struct {
    VideoDecoder        *decoder;
    CdxParserT          *parser;
    CdxDataSourceT       source;
    CdxMediaInfoT        media_info;
    struct ScMemOpsS    *memops;

    pthread_t            parser_thread;
    pthread_t            decoder_thread;
    pthread_mutex_t      parser_mutex;
    MultiThreadCtx       thread;

    char                 input_uri[256];
    uint8_t             *output_buf;
    int                  running;
    int                  framerate;
} mediaplayer_t;

/* initialize mediaplayer context */
int mediaplayer_init(mediaplayer_t *mediaplayer);

/* destroy mediaplayer context and release all resources */
int mediaplayer_destroy(mediaplayer_t *mediaplayer);

/* decode one frame from file into buf (YUV MB32 420, fixed size) */
int mediaplayer_play_video(mediaplayer_t *mediaplayer, const char *file, uint8_t *buf);

/* stop current decoding if running */
int mediaplayer_stop(mediaplayer_t *mediaplayer);