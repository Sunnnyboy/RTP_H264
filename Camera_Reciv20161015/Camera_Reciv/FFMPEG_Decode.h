#pragma once
#include<iostream>
#include"include/opencv/cv.h"

#include"include/jrtplib/rtpsession.h"
#include"include/jrtplib/rtperrors.h"
#include"include/jrtplib/rtpudpv4transmitter.h"
#include"include/jrtplib/rtpsessionparams.h"
#include"include/jrtplib/rtpsourcedata.h"
#include"include/jrtplib/rtppacket.h"

using namespace std;
using namespace jrtplib;
extern "C"
{
#include "include/libavcodec/avcodec.h"
#include "include/libswscale/swscale.h"
#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_main.h"
//#include "include/libavutil/frame.h"
};

#define IN_BUFSIZE 4096
#define SDL_MAIN_HANDLED

class FFMPEG_Decode 
{
public:
	/*FFMPEG ����*/
	AVCodec								*pCodec;
	AVCodecContext				*pCodecCtx;
	AVFrame							*pFrame;
	AVFrame							*pFrameRGB;
	AVFrame							*pFrameYUV;
	AVPacket							*packet;
	AVCodecID							codec_id;
	struct SwsContext			*img_convert_ctx;
	IplImage								*pCVFrame;
	uint8_t								*out_buffer;
	uint32_t								frame_count;
	int										got_picture;

	/*SDL����*/
	SDL_Window						*screen;			  //һ�����ڣ�������ʾYUV
	SDL_Renderer					*sdlRender;     //��Ⱦ��
	SDL_Texture						*sdlTexture;     //YUV�����������Ϊһ��ͼƬ������ͬ��ͼƬ
	SDL_Rect							sdlRect;

	unsigned char in_buffer[IN_BUFSIZE + FF_INPUT_BUFFER_PADDING_SIZE];
public:
	FFMPEG_Decode();
	~FFMPEG_Decode();
	void DecodeInit();
	void DecodeFrame(uint8_t*frame, uint32_t frame_len);
	void GetOpencvFrame();
	void GetSDLFrame();
	void SDL_INIT();
};

