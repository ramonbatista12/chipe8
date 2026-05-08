#pragma once
#include <cstdint>
#include <random>
#include <chrono>
using byte = uint8_t;

class Chipe8{
	typedef void (Chipe8::*funcao)();
public :
	long long int interacao = 1;
	byte regidores[16]{};
	byte memoria[4096]{};//
	uint16_t  stack[16]{};
	uint16_t pc{};
	byte sp{};
	uint16_t indice{};
	byte deleayDeTempo{};
	byte delayDeSom{};
	byte keypad[16]{};
	uint32_t display[64 * 32]{};
	uint16_t opcod;
	std::default_random_engine gerador;
	std::uniform_int_distribution<int> distribuicao{ 0, 255 };
	funcao tabela[16];
	funcao tabela0[16];
	funcao tabela8[16];
	funcao tabelaE[16];
	funcao tabelaF[0x65 + 1];
	Chipe8();
	~Chipe8();
	void run();
	void looadRon(char const* caminho);
	void up_code_00E0();
	void up_code_00EE();
	void up_code_1nnn();
	void up_code_2nnn();
	void up_code_3xkk();
	void up_cod_4xkk();
	void up_cod_5xy0();
	void up_cod_6xkk();
	void up_cod_7xkk();
	void up_cod_8xy0();
	void up_cod_8xy1();
	void up_cod_8xy2();
	void up_cod_8xy3();
	void up_cod_8xy4();
	void up_cod_8xy5();
	void up_cod_8xy6();
	void up_cod_8xy7();
	void up_cod_8xyE();
	void up_cod_9xy0();
	void up_cod_annn();
	void up_cod_bnnn();
	void up_cod_cxkk();
	void up_cod_dxyn();
	void up_cod_ex9e();
	void up_cod_exa1();
	void up_cod_fx07();
	void up_cod_fx0a();
	void up_cod_fx15();
	void up_cod_fx18();
	void up_cod_fx1e();
	void up_cod_fx29();
	void up_cod_fx33();
	void up_cod_fx55();
	void up_cod_fx65();
private:
	
	void Tabela0();
	void Tabela8();
	void TabelaE();
	void TabelaF();
	void up_cod_nulo();
};
