#pragma once
#include "SDL3/SDL.h"


class Plataforma {
public:
	Plataforma(const char* titulo,int largura,int autura,int larguraDaTestura,int auturaDaTestura);
	~Plataforma();
	SDL_Renderer * renderizador ;
	SDL_Window * janelaSdl ;
	SDL_Texture * testura ;
	
	void update(void const* bufer,int pitch);
	bool procesamentoDeImput(uint8_t * teclas);
};