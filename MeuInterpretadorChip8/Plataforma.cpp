#pragma once
#include "SDL3/SDL.h"
#include "Plataforma.h"
#include <iostream>


Plataforma::Plataforma(const char* titulo, int largura, int autura, int larguraDaTestura, int auturaDaTestura) {
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "SDL init erro: " << SDL_GetError() << "\n";
	};
	janelaSdl = SDL_CreateWindow(titulo,  largura,autura, SDL_WINDOW_OPENGL);
	renderizador = SDL_CreateRenderer(janelaSdl,nullptr); //SDL_CreateRenderer(janelaSdl,nullptr);
	testura = SDL_CreateTexture(renderizador,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,larguraDaTestura,auturaDaTestura);
	
	SDL_Log("teste");
	SDL_Log("erro: %s", SDL_GetError());
};

Plataforma::~Plataforma() {
	SDL_DestroyTexture(testura);
	SDL_DestroyRenderer(renderizador);
	SDL_DestroyWindow(janelaSdl);
	SDL_Quit();

};

void Plataforma::update(void const* bufer, int pitch) {
	SDL_UpdateTexture(testura, nullptr, bufer, pitch);
	SDL_RenderClear(renderizador);
	SDL_RenderTexture(renderizador, testura, nullptr, nullptr);
	SDL_RenderPresent(renderizador);
};

bool Plataforma::procesamentoDeImput(uint8_t* teclas) {
	bool sair = false;
	SDL_Event eventoSdl;
	
	while (SDL_PollEvent(&eventoSdl)) {
	  
		switch (eventoSdl.type){
		case SDL_EVENT_QUIT: {
			sair = true;
			break;
		}


		case SDL_EVENT_KEY_DOWN: {
			switch (eventoSdl.key.key)
			{
			case SDLK_ESCAPE: { sair = true; break; }
			case SDLK_X: { teclas[0]=1; break; }
			case SDLK_1: { teclas[1] = 1; break; }
			case SDLK_2: { teclas[2] = 1; break; }
			case SDLK_3: { teclas[3] = 1; break; }
			case SDLK_Q: { teclas[4] = 1; break; }
			case SDLK_W: { teclas[5] = 1; break; }
			case SDLK_E: { teclas[6] = 1; break; }
			case SDLK_A: { teclas[7] = 1; break; }
			case SDLK_S: { teclas[8] = 1; break; }
			case SDLK_D: { teclas[9] = 1; break; }
			case SDLK_Z: { teclas[10] = 1; break; }
			case SDLK_C: { teclas[11] = 1; break; }
			case SDLK_4: { teclas[12] = 1; break; } 
			case SDLK_R: { teclas[13] = 1; break; }
			case SDLK_F: { teclas[14] = 1; break; }
			case SDLK_V: { teclas[15] = 1; break; }
			default:
				break;
			}


			break;

		}
		case SDL_EVENT_KEY_UP:{
			switch (eventoSdl.key.key)
			{
			
			case SDLK_X: { teclas[0] = 0; break; }
			case SDLK_1: { teclas[1] = 0; break; }
			case SDLK_2: { teclas[2] = 0; break; }
			case SDLK_3: { teclas[3] = 0; break; }
			case SDLK_Q: { teclas[4] = 0; break; }
			case SDLK_W: { teclas[5] = 0; break; }
			case SDLK_E: { teclas[6] = 0; break; }
			case SDLK_A: { teclas[7] = 0; break; }
			case SDLK_S: { teclas[8] = 0; break; }
			case SDLK_D: { teclas[9] = 0; break; }
			case SDLK_Z: { teclas[10] = 0; break; }
			case SDLK_C: { teclas[11] = 0; break; }
			case SDLK_4: { teclas[12] = 0; break; }
			case SDLK_R: { teclas[13] = 0; break; }
			case SDLK_F: { teclas[14] = 0; break; }
			case SDLK_V: { teclas[15] = 0; break; }
			default:
				break;
			}
			break;
		}

		
		}
		
	
	}
	return sair;
};