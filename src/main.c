#include "drm_warpper.h"
#include "mediaplayer.h"
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(){
    drm_warpper_t drm_warpper;
    drm_warpper_init(&drm_warpper);

    int img_width, img_height, img_channels;
    uint8_t *img_data;
    // uint8_t *img_data = stbi_load("testimg.png", &img_width, &img_height, &img_channels, 4);
    // printf("img_width %d,img_height %d\n",img_width,img_height);


    // drm_warpper_init_layer(&drm_warpper, 0, img_width, img_height, DRM_WARPPER_LAYER_MODE_RGB565);
    // uint8_t *vaddr;
    // drm_warpper_get_layer_buffer(&drm_warpper, 0, &vaddr);
    // for (int i = 0; i < img_width*img_height; i++) {
    //     int b = img_data[i*4+2];
    //     int g = img_data[i*4+1];
    //     int r = img_data[i*4+0];
    //     ((uint16_t *)vaddr)[i] = (r>>3)<<11 | (g>>2)<<5 | (b>>3);
    // }
    // free(img_data);
    // drm_warpper_set_layer_position(&drm_warpper, 0, 0, 0);

    drm_warpper_init_layer(&drm_warpper, 0, 352, 640, DRM_WARPPER_LAYER_MODE_MB32_NV12);
    uint8_t *vaddr;
    drm_warpper_get_layer_buffer(&drm_warpper, 0, &vaddr);
    drm_warpper_set_layer_position(&drm_warpper, 0, 0, 0);

    mediaplayer_t mediaplayer;
    mediaplayer_init(&mediaplayer);
    mediaplayer_play_video(&mediaplayer, "./test.mp4", vaddr);
    mediaplayer_stop(&mediaplayer);
    mediaplayer_destroy(&mediaplayer);

    img_data = stbi_load("infotest.png", &img_width, &img_height, &img_channels, 4);
    printf("img_width %d,img_height %d\n",img_width,img_height);
    drm_warpper_init_layer(&drm_warpper, 1, img_width, img_height, DRM_WARPPER_LAYER_MODE_ARGB8888);
    drm_warpper_get_layer_buffer(&drm_warpper, 1, &vaddr);
    for (int i = 0; i < img_width*img_height; i++) {
        int a = img_data[i*4+3];
        int r = img_data[i*4+2];
        int g = img_data[i*4+1];
        int b = img_data[i*4+0];
        ((uint32_t *)vaddr)[i] = (a<<24) | (r<<16) | (g<<8) | b;
    }
    free(img_data);
    drm_warpper_set_layer_position(&drm_warpper, 1, 0, 0);

    getchar();    

    drm_warpper_destroy(&drm_warpper);
    return 0;

}