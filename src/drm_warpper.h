#include <xf86drm.h>
#include <xf86drmMode.h>
#include <stdint.h>

#pragma once


#define DRM_FORMAT_MOD_VENDOR_ALLWINNER 0x09
#define DRM_FORMAT_MOD_ALLWINNER_TILED fourcc_mod_code(ALLWINNER, 1)

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint32_t handle;
    uint32_t size;
    uint8_t *vaddr;
    uint32_t fb_id;
} buffer_object_t;


typedef struct {
  int fd;
  drmModeConnector *conn;
  drmModeRes *res;
  drmModePlaneRes *plane_res;
  uint32_t crtc_id;
  uint32_t conn_id;
  buffer_object_t plane_buf[4];
} drm_warpper_t;

typedef enum {
    DRM_WARPPER_LAYER_MODE_RGB565,
    DRM_WARPPER_LAYER_MODE_ARGB8888,
    DRM_WARPPER_LAYER_MODE_MB32_NV12, //allwinner specific format
} drm_warpper_layer_mode_t;

int drm_warpper_init(drm_warpper_t *drm_warpper);
int drm_warpper_destroy(drm_warpper_t *drm_warpper);
int drm_warpper_init_layer(drm_warpper_t *drm_warpper,int layer_id,int width,int height,drm_warpper_layer_mode_t mode);
int drm_warpper_destroy_layer(drm_warpper_t *drm_warpper,int layer_id);
int drm_warpper_get_layer_buffer(drm_warpper_t *drm_warpper,int layer_id,uint8_t **vaddr);
int drm_warpper_set_layer_position(drm_warpper_t *drm_warpper,int layer_id,int x,int y);

