#include "Chipe8.h"
#include <fstream>
#include <iostream>
#include <bitset>
const uint16_t enderecodecaregamentoDaroon = 0x200;
const uint16_t enderecoDecaregamentoDosCaracteres = 0x50;
const uint8_t larguradatela = 64;
const uint8_t auturaDatela = 32;

const uint8_t caracteres[80]={
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chipe8::Chipe8() {
	pc = enderecodecaregamentoDaroon;
	for (unsigned int i = 0; i < 80; i++)
	{
		memoria[enderecoDecaregamentoDosCaracteres + i] = caracteres[i];
	}	
	auto tempodoSystema = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	gerador=std::default_random_engine(tempodoSystema);
	pc = enderecodecaregamentoDaroon;
	
	tabela[0] = &Chipe8::Tabela0;
	tabela[1] = &Chipe8::up_code_1nnn;
	tabela[2] = &Chipe8::up_code_2nnn;
	tabela[3] = &Chipe8::up_code_3xkk;
	tabela[4] = &Chipe8::up_cod_4xkk;
	tabela[5] = &Chipe8::up_cod_5xy0;
	tabela[6] = &Chipe8::up_cod_6xkk;
	tabela[7] = &Chipe8::up_cod_7xkk;
	tabela[8] = &Chipe8::Tabela8;
	tabela[9] = &Chipe8::up_cod_9xy0;
	tabela[10] = &Chipe8::up_cod_annn;
	tabela[11] = &Chipe8::up_cod_bnnn;
	tabela[12] = &Chipe8::up_cod_cxkk;
	tabela[13] = &Chipe8::up_cod_dxyn;
	tabela[14] = &Chipe8::TabelaE;
	tabela[15] = &Chipe8::TabelaF;

	for (int i = 0; i < 16; i++) {
	tabela8[i]= &Chipe8::up_cod_nulo;
	tabela0[i] = &Chipe8::up_cod_nulo;
	tabelaE[i] = &Chipe8::up_cod_nulo;
	}
	tabela0[0] = &Chipe8::up_code_00E0;
	tabela0[15] = &Chipe8::up_code_00EE;

	tabela8[0] = &Chipe8::up_cod_8xy0;
	tabela8[1] = &Chipe8::up_cod_8xy1;
	tabela8[2] = &Chipe8::up_cod_8xy2;
	tabela8[3] = &Chipe8::up_cod_8xy3;
	tabela8[4] = &Chipe8::up_cod_8xy4;
	tabela8[5] = &Chipe8::up_cod_8xy5;
	tabela8[6] = &Chipe8::up_cod_8xy6;
	tabela8[7] = &Chipe8::up_cod_8xy7;
	tabela8[14] = &Chipe8::up_cod_8xyE;

	tabelaE[1] = &Chipe8::up_cod_exa1;
	tabelaE[14] = &Chipe8::up_cod_ex9e;

	for (int i = 0; i < 64; i++) {
		tabelaF[i] = &Chipe8::up_cod_nulo;
	}
	tabelaF[0x07] = &Chipe8::up_cod_fx07;
	tabelaF[0x0A] = &Chipe8::up_cod_fx0a;
	tabelaF[0x15] = &Chipe8::up_cod_fx15;
	tabelaF[0x18] = &Chipe8::up_cod_fx18;
	tabelaF[0x1E] = &Chipe8::up_cod_fx1e;
	tabelaF[0x29] = &Chipe8::up_cod_fx29;
	tabelaF[0x33] = &Chipe8::up_cod_fx33;
	tabelaF[0x55] = &Chipe8::up_cod_fx55;
	tabelaF[0x65] = &Chipe8::up_cod_fx65;

};

void Chipe8::Tabela0() {
	((*this).*(tabela0[opcod & 0b0000'0000'0000'1111]))();
};
void Chipe8::Tabela8() { ((*this).*(tabela8[opcod & 0b0000'0000'0000'1111]))(); };
void Chipe8::TabelaE() { ((*this).*(tabelaE[opcod & 0b0000'0000'0000'1111]))(); };
void Chipe8::TabelaF() { ((*this).*(tabelaF[opcod & 0b0000'0000'0000'1111]))(); };
void Chipe8::up_cod_nulo(){};

Chipe8::~Chipe8() {};
void Chipe8::run() {
	
	auto grupo = memoria[pc] << 8;
	auto grupo2 = memoria[pc + 1];
	//std::cout << "valor do grupo " << grupo << " valor do grupo 2 " << grupo2<<" valor de pc "<<pc<<" intercao do chipe "<<interacao << "\n";
	pc += 2;
    opcod = grupo | grupo2;
	std::cout << "opcod" << std::bitset<8>(opcod) << "\n";
	uint8_t valorchamado = opcod >> 12u;
	std::cout << "valor chamdo " << valorchamado << "\n";
	if (valorchamado == 13u) { std::cout << "valor chamdo e 13 e algo vai ser desenhado" << std::bitset<8>(valorchamado) << "\n"; }
	((*this).*(tabela[valorchamado]))();
	if (delayDeSom > 0) --delayDeSom;
	if (deleayDeTempo > 0)--deleayDeTempo;
	interacao++;
};

void Chipe8::looadRon(char const* caminho) {
	std::ifstream file(caminho, std::ios::binary | std::ios::ate);
	if (file.is_open()) {
		std::streampos tamanho = file.tellg();
		char* buffer = new char[tamanho];
		file.seekg(0, std::ios::beg);
		file.read(buffer, tamanho);
		file.close();
		for (unsigned int i = 0; i < tamanho; i++)
		{
			memoria[enderecodecaregamentoDaroon + i] = buffer[i];

		}

		
		delete[] buffer;
	}

	

};
// 00E0 - CLS: Limpa a tela de video.
void Chipe8::up_code_00E0() {
  
	memset(display, 0, sizeof(display));

};

//retorne 
void Chipe8::up_code_00EE() {
	--sp;
	pc = stack[sp];

};


//va para o endereco nnn
void Chipe8::up_code_1nnn() {
	uint16_t endereco = opcod & 0b0000'1111'1111'1111;
	pc = endereco;

};

// chame a instrucao pc nova e coloque a intrucao de retorno  nna stack
void Chipe8::up_code_2nnn() {
	uint16_t endereco = opcod & 0b0000'1111'1111'1111;
	stack[sp] = pc;
	++sp;
	pc = endereco;
};

//ignore a prosima intrucao  se o registrador x==kk
void Chipe8::up_code_3xkk() {
	uint16_t registrador = (this->opcod & 0b0000'1111'1111'1111) >> 8u;
	uint16_t valor_comparcao = (opcod & 0b0000'0000'1111'1111);
	if (regidores[registrador] == valor_comparcao) {
		pc += 2;
	}
};
//ignore a prosima instrucao se o registrador x != kk
void Chipe8::up_cod_4xkk() {
	uint16_t registrador = (opcod & 0b0000'1111'1111'1111) >> 8u;
	uint16_t valor_comparcao = (opcod & 0b0000'0000'1111'1111);
	if (this->regidores[registrador] != valor_comparcao)pc += 2;
};
//ignore a prosima intrucao se o registrador a == registrador b
void Chipe8::up_cod_5xy0() {
	uint16_t registradora = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t registradorb = (this->opcod & 0b0000'0000'1111'0000) >> 4u;
	if (this->regidores[registradora] == this->regidores[registradorb])pc += 2;

};
// careque o registrador x com o valor kk
void Chipe8::up_cod_6xkk() {
	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t valor = opcod & 0b0000'0000'1111'1111;
	regidores[registrador] = valor;

};
//some o valor ao registrador
void Chipe8::up_cod_7xkk() {
 uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
 uint16_t valor = opcod & 0b0000'0000'1111'1111;
 regidores[registrador] += valor;
};

//peque o valor no registrador b e o coloque em a
void Chipe8::up_cod_8xy0() {
	uint16_t registradora = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t registradorb = (this->opcod & 0b0000'0000'1111'0000) >> 4u;
	regidores[registradora] = regidores[registradorb];
};
//coloque no registrador a  omresultado de  a | b
void Chipe8::up_cod_8xy1() {
	uint16_t registradora = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t registradorb = (this->opcod & 0b0000'0000'1111'0000) >> 4u;
	regidores[registradora] = regidores[registradora] | regidores[registradorb];
};
//coloque no registrador a  omresultado de  a & b
void Chipe8::up_cod_8xy2() {
	uint16_t registradora = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t registradorb = (this->opcod & 0b0000'0000'1111'0000) >> 4u;
	regidores[registradora] = regidores[registradora] & regidores[registradorb];
};
//coloque no registrador a  omresultado de  a ^ b
void Chipe8::up_cod_8xy3() {
	uint16_t registradora = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t registradorb = (this->opcod & 0b0000'0000'1111'0000) >> 4u;
	regidores[registradora] = regidores[registradora] ^ regidores[registradorb];
};
//coloque no registrador a  omresultado de  a + b e se ouve o vai 1 asenda a flaque
void Chipe8::up_cod_8xy4() {
	uint16_t registradora = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t registradorb = (this->opcod & 0b0000'0000'1111'0000) >> 4u;
	uint16_t soma = regidores[registradora] + regidores[registradorb];
	if (soma > 255u)regidores[0xf] = 1;
	else regidores[0xf] = 0;
	regidores[registradora] = soma & 0xFFu;
};
//coloque no registrador a  omresultado de  a - b e se o reseultado for negativo 1 asenda a flaque
void Chipe8::up_cod_8xy5() {
	uint16_t registradora = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t registradorb = (this->opcod & 0b0000'0000'1111'0000) >> 4u;
	
	if (regidores[registradora] > regidores[registradorb])regidores[0xf] = 1;
	else regidores[0xf] = 0;
	regidores[registradora] = regidores[registradora] - regidores[registradorb];
};
//descloca 0 valor do registrador a >>1 e salva o bite menos sginificativo anterior
void Chipe8::up_cod_8xy6() {
	uint16_t registradora = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	
	regidores[0xf] = (regidores[registradora] & 0b0000'0001);
	regidores[registradora] = regidores[registradora] >> 1;
};
//subitria o registrador a do regitrador b seouve emprestimo sinaliza com 0
void Chipe8::up_cod_8xy7() {
	uint16_t registradora = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t registradorb = (this->opcod & 0b0000'0000'1111'0000) >> 4u;
	
	if (regidores[registradorb] > regidores[registradora])regidores[0xf] = 1;
	else regidores[0xf] = 0;
	regidores[registradora] = regidores[registradorb] - regidores[registradora];
};
//checa o bit mais significativo se for um ele salva em vf e depois multiplica por 2
void Chipe8::up_cod_8xyE() {
	uint16_t registradora = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	regidores[0xf] = (regidores[registradora]& 0b1000'0000) >> 7u;
	regidores[registradora] = regidores[registradora]<<1;
}; 
//ignora a prosima intrucao se registrador a !- do registrador b
void Chipe8::up_cod_9xy0() {
	uint16_t registradora = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t registradorb = (this->opcod & 0b0000'0000'1111'0000) >> 4u;

	if (regidores[registradora] != regidores[registradorb])pc += 2;
};
//caregque o indice como endereco 
void Chipe8::up_cod_annn() {
	uint16_t endereco= (this->opcod & 0b0000'1111'1111'1111) ;
	indice = endereco;

	
};
//ir pr alocalizacao registrador 0 +nnn
void Chipe8::up_cod_bnnn() {
	uint16_t endereco = opcod & 0b0000'1111'1111'1111;
	pc = regidores[0] + endereco;

};
//coloque no registrador  (byte aleatorio & valor)
void Chipe8::up_cod_cxkk() {
	uint16_t registrador = (this->opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t valor = (this->opcod & 0b0000'0000'1111'1111);
	regidores[registrador] = static_cast<uint8_t>(this->distribuicao(this->gerador)) & valor;
};
// desenha 
void Chipe8::up_cod_dxyn() {
	std::cout << "chamndo metodo de desenho dos sprites "<<"\n";
	uint16_t  registradora = (opcod & 0b0000'1111'0000'0000) >> 8u;
	uint16_t  registradorb = (opcod & 0b0000'0000'1111'0000) >> 4u;
	uint16_t  alturaDoSprite = (opcod & 0b0000'0000'0000'1111);

	uint8_t posicaox = regidores[registradora] % larguradatela;
	uint8_t posicaoy = regidores[registradorb] % auturaDatela;
	 
	regidores[0xf] = 0;
	for (uint8_t linha = 0; linha < alturaDoSprite; linha++) {
	     
		uint8_t linhaDosprite = memoria[indice + linha];
		
		for (uint8_t shiftichecagem = 0; shiftichecagem < 8; shiftichecagem++) {
		
			uint8_t bitechecado = (linhaDosprite) & (0x80u>> shiftichecagem);
			uint32_t achandoAposicaoDalinha = (posicaoy+linha)*larguradatela;
			uint32_t achandoAposicaoDaColuna = (posicaox + shiftichecagem);
			uint32_t* ponteiroparaByteAserdesenhado = &display[achandoAposicaoDalinha+achandoAposicaoDaColuna];
			if (bitechecado) {
				if (*ponteiroparaByteAserdesenhado == 0xFFFFFFFF) {
					regidores[0xf] = 1;
				}
				*ponteiroparaByteAserdesenhado ^= 0xFFFFFFFF;

					
			
			}
		
		}
	
	
	}
 
};
//ignorre a prosima intrucao se a tecal referenciadao pelo registrador estiver presionada
void Chipe8::up_cod_ex9e() {
	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	uint8_t teclapresionada = regidores[registrador];
	if (keypad[teclapresionada]) {
		pc += 2;

	}

};
//ignorre a prosima intrucao se a tecal referenciadao pelo registrador estiver solta
void Chipe8::up_cod_exa1() {
	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	uint8_t teclapresionada = regidores[registrador];
	if (keypad[teclapresionada]) {
		pc += 2;

	}

};
// defina o registrador com o valor do registrador de atrazo
void Chipe8::up_cod_fx07() {
	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	regidores[registrador]=deleayDeTempo;
};

//espere ate que uma tecla seja presionada e guardde o valor no registrados
void Chipe8::up_cod_fx0a() {

	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	

	if (keypad[0]) {
		regidores[registrador] = 0;
	}
	else if (keypad[1]) {
		regidores[registrador] = 1;
	}
	else if (keypad[2]) {
		regidores[registrador] = 2;
	}
	else if (keypad[3]) {
		regidores[registrador] = 3;
	}
	else if (keypad[4]) {
		regidores[registrador] = 4;
	}
	else if (keypad[5]) {
		regidores[registrador] = 5;
	}
	else if (keypad[6]) {
		regidores[registrador] = 6;
	}
	else if (keypad[7]) {
		regidores[registrador] = 7;
	}
	else if (keypad[8]) {
		regidores[registrador] = 8;
	}
	else if (keypad[9]) {
		regidores[registrador] = 9;
	}
	else if (keypad[10]) {
		regidores[registrador] = 10;
	}
	else if (keypad[11]) {
		regidores[registrador] = 11;

	}
	else if (keypad[12]) {
		regidores[registrador] = 12;
	}
	else if (keypad[13]) {
		regidores[registrador] = 13;
	}
	else if (keypad[14]) {
		regidores[registrador] = 14;
	}
	else if (keypad[15]) { regidores[registrador] = 15; }
	else pc -= 2;

};

//defina o temporizador de atrazo com o valor do registrador
void Chipe8::up_cod_fx15() {
	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	deleayDeTempo=regidores[registrador] ;

};
//defina o temporizador de som com o valor do registrador
void Chipe8::up_cod_fx18() {
	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	delayDeSom = regidores[registrador];

};
//defina o temporizador de som com o valor do registrador
void Chipe8::up_cod_fx1e() {
	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	indice+= regidores[registrador];

};

void Chipe8::up_cod_fx29() {
	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	uint8_t digito = regidores[registrador];
	indice = enderecoDecaregamentoDosCaracteres + (5 * digito);

};

void Chipe8::up_cod_fx33() {
	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	uint8_t valor = regidores[registrador];
	memoria[indice + 2] = valor % 10;
	valor /= 10;
	memoria[indice + 1] = valor % 10;
	valor /= 10;
	memoria[indice ] = valor % 10;
	valor /= 10;

};
//armazene os regsotradores ate registrador na memoria
void Chipe8::up_cod_fx55() {
	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	for (unsigned int x = 0; x < registrador; x++) {
		memoria[indice + x] = regidores[x];
	}
};

//leis os regsotradores ate registrador da memoria
void Chipe8::up_cod_fx65() {
	uint16_t registrador = (opcod & 0b0000'1111'0000'0000) >> 8u;
	for (unsigned int x = 0; x < registrador; x++) {
		regidores[x]= memoria[indice + x] ;
	}
};